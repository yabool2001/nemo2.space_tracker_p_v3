/*
 * my_nmea.h
 *
 *  Created on: Oct 2, 2023
 *      Author: mzeml
 */

#ifndef MY_NMEA_H_
#define MY_NMEA_H_

#include "my_global.h"
#include "my_conversions.h"

#define MY_NMEA_MESSAGE_MAX_SIZE 250

#define NMEA_DELIMETER			','
#define RMC_DATE_POSITION		9 // Liczona ilość znaków a nie delimeter
#define RMC_DATE_YY_OFFSET		4
#define RMC_DATE_MM_OFFSET		2
#define RMC_DATE_DD_OFFSET		0
#define RMC_DATE_PART_LENGTH	2
#define RMC_UTC_POSITION		1
#define RMC_UTC_HH_OFFSET		0
#define RMC_UTC_MM_OFFSET		2
#define RMC_UTC_SS_OFFSET		4
#define RMC_UTC_SSS_OFFSET		7
#define RMC_UTC_PART_LENGTH		2
#define RMC_UTC_SSS_LENGTH		3
#define GSA_PDOP_POSITION		15
#define GLL_LATITUDE_POSITION	1
#define GSV_TNS_POSITION		3
#define GSV_TNS_LENGTH			2


int 		my_nmea_message ( uint8_t* , uint8_t* , uint8_t* ) ;
bool 		is_my_nmea_checksum_ok ( const char* ) ;
uint8_t* 	nmea_format ( uint8_t* ) ;
//uint8_t 	get_my_nmea_gngsa_fixed_mode_d ( uint8_t* ) ;
const char	get_my_nmea_gngsa_fixed_mode_s ( const char* ) ;
//const char	get_my_nmea_gngsa_pdop_s ( const char* ) ;
double		get_my_nmea_gngsa_pdop_d ( const char* ) ;
double 		nmea2decimal ( const char* , char ) ;
void		my_nmea_get_gngll_coordinates ( const char* , my_gnss_fix* ) ;
void		get_my_nmea_gngll_coordinates ( const char* , char* , char* , int32_t* , int32_t* ) ;
uint16_t	my_nmea_get_gsv_tns ( const char* ) ;
void		my_nmea_get_rmc_date_yy	( const char* , uint8_t* ) ;
void		my_nmea_get_rmc_date_mm	( const char* , uint8_t* ) ;
void		my_nmea_get_rmc_date_dd	( const char* , uint8_t* ) ;
void		my_nmea_get_rmc_utc_hh	( const char* , uint8_t* ) ;
void		my_nmea_get_rmc_utc_mm	( const char* , uint8_t* ) ;
void		my_nmea_get_rmc_utc_ss	( const char* , uint8_t* ) ;
void		my_nmea_get_rmc_utc_sss	( const char* , uint32_t* ) ;

#endif /* MY_NMEA_H_ */
