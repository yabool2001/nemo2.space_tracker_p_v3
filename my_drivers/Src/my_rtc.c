/*
 * my_rtc.c
 *
 *  Created on: Oct 27, 2023
 *      Author: mzeml
 */
#include "my_rtc.h"

/*
** RMC: Recommended Minimum Specific GNSS Data. Time, date, position, course, and speed data provided by a GNSS receiver.
** Synopsis: $<TalkerID>RMC,<UTC>,<Status>,<Lat>,<N/S>,<Lon>,<E/W>,<SOG>,<COG>,<Date>,<MagVar>,<MagVarDir>,<ModeInd>,<NavStatus>*<Checksum><CR><LF>
** m message example from Quectel L86: "$GPRMC,085151.187,V,,,,,0.00,0.00,291023,,,N,V*3A". \r\n have been wiped out.
*/

void my_rtc_get_dt ( RTC_DateTypeDef* d , RTC_TimeTypeDef* t )
{
	HAL_RTC_GetDate ( &hrtc , d , RTC_FORMAT_BIN ) ;
	HAL_RTC_GetTime ( &hrtc , t , RTC_FORMAT_BIN ) ;
}
uint16_t my_rtc_get_dt_s ( char* dt_s )
{
	RTC_DateTypeDef gDate;
	RTC_TimeTypeDef gTime;

	//char cdt[20];

	HAL_RTC_GetTime ( &hrtc , &gTime , RTC_FORMAT_BIN ) ;
	HAL_RTC_GetDate ( &hrtc , &gDate , RTC_FORMAT_BIN ) ;

	sprintf ( dt_s , "%4d.%02d.%02d %02d:%02d:%02d" , 2000 + gDate.Year , gDate.Month , gDate.Date , gTime.Hours , gTime.Minutes , gTime.Seconds ) ;

	return (uint16_t) ( 2000 + gDate.Year ) ;
}
uint32_t my_rtc_get_ts ( void )
{
	RTC_DateTypeDef d ;
	RTC_TimeTypeDef t ;

	my_rtc_get_dt ( &d , &t ) ;
	return my_conv_rtc2timestamp ( &d , &t ) ;
}
bool my_rtc_set_alarm ( uint32_t s )
{
	char  rtc_dt_s[20] ;
	char  m[52] ;

	RTC_DateTypeDef 	d ;
	RTC_TimeTypeDef 	t ;
	RTC_AlarmTypeDef	a ;

	my_rtc_get_dt ( &d , &t ) ;
	my_rtc_get_dt_s ( rtc_dt_s ) ; // Bez tej linii będzie błąd funkcji, która zacznie ustawiać alarm na wartość poprzedniego alarmu i wszystko się zawiesi
	sprintf ( m , "%s,%d,%s" , __FILE__ , __LINE__ , rtc_dt_s ) ;
	send_debug_logs ( m ) ;
	uint32_t alarm_ts = my_conv_rtc2timestamp ( &d , &t ) + s ;
	my_conv_timestamp2rtc ( alarm_ts , &d , &t ) ;

	/** Enable the Alarm A		  */
	a.AlarmTime.Hours = t.Hours ;
	a.AlarmTime.Minutes = t.Minutes ;
	a.AlarmTime.Seconds = t.Seconds ;
	a.AlarmTime.SubSeconds = 0;
	a.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE ;
	a.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET ;
	a.AlarmMask = RTC_ALARMMASK_NONE ;
	a.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL ;
	a.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE ;
	a.AlarmDateWeekDay = d.Date ;
	a.Alarm = RTC_ALARM_A ;
	if ( HAL_RTC_SetAlarm_IT ( &hrtc , &a , RTC_FORMAT_BIN ) == HAL_OK )
	{
		my_conv_dt_2_dts ( &d , &t , rtc_dt_s ) ;
		sprintf ( m , "%s,%d,%s" , __FILE__ , __LINE__ , rtc_dt_s ) ;
		send_debug_logs ( m ) ;
		return true ;
	}
	return false ;
}

void my_rtc_set_dt_from_nmea_rmc ( const char* m )
{
	  RTC_TimeTypeDef sTime ;
	  RTC_DateTypeDef sDate ;

	  my_nmea_get_rmc_date_yy ( m , &sDate.Year ) ;
	  my_nmea_get_rmc_date_mm ( m , &sDate.Month ) ;
	  my_nmea_get_rmc_date_dd ( m , &sDate.Date ) ;
	  my_nmea_get_rmc_utc_hh ( m , &sTime.Hours ) ;
	  my_nmea_get_rmc_utc_mm ( m , &sTime.Minutes ) ;
	  my_nmea_get_rmc_utc_ss ( m , &sTime.Seconds ) ;
	  my_nmea_get_rmc_utc_sss ( m , &sTime.SubSeconds ) ;
	  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	  sTime.StoreOperation = RTC_STOREOPERATION_RESET;

	  HAL_RTCEx_EnableBypassShadow ( &hrtc ) ;
	  HAL_RTC_SetTime ( &hrtc , &sTime , RTC_FORMAT_BIN ) ;
	  HAL_RTC_SetDate ( &hrtc , &sDate , RTC_FORMAT_BIN ) ;
	  HAL_RTCEx_DisableBypassShadow ( &hrtc ) ;
}
