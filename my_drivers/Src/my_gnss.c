/*
 * my_lx6_gnss.c
 *
 *  Created on: Oct 27, 2023
 *      Author: mzeml
 */

#include "my_gnss.h"

bool my_gnss_acq_coordinates ( fix_astro* fix3d )
{
	bool		r = false ;
	bool		is_utc_saved = false ;
	uint8_t		rx_byte = 0 ;
	uint8_t		i_nmea = 0 ;
	uint8_t		gsv_tns = 0 ;
	uint8_t		nmea_message[UART_TX_MAX_BUFF_SIZE] = {0} ;
	uint8_t		gngll_message[UART_TX_MAX_BUFF_SIZE] = {0} ;
	char* 		nmea_gsv_label = "GPGSV" ;
	char* 		nmea_rmc_label = "GNRMC" ;
	char* 		nmea_gngsa_label = "GNGSA" ;
	char* 		nmea_gngll_label = "GNGLL" ;

	fix3d->fix_mode = '0' ;
	fix3d->pdop = 1000 ;
	my_tim_start () ;
	while ( tim_seconds < fix_acq_ths )
	// Pierwsze
	{
		my_gnss_receive_byte ( &rx_byte, true ) ;
		if ( rx_byte )
		{
			if ( my_nmea_message ( &rx_byte , nmea_message , &i_nmea ) == 2 )
			{
				if ( is_my_nmea_checksum_ok ( (char*) nmea_message ) )
				{
					if ( !is_utc_saved )
					{
						if ( fix3d->fix_mode == NMEA_3D_FIX )
						{
							if ( strstr ( (char*) nmea_message , nmea_rmc_label ) )
							{
								my_rtc_set_dt_from_nmea_rmc ( (char*) nmea_message ) ; // Jeśli masz fix to na pewno czas jest dobry
								is_utc_saved = true ;
							}
						}
					}
					if ( strstr ( (char*) nmea_message , nmea_gsv_label ) && gsv_tns < MIN_TNS ) // Nie ma co tego później monitorować, bo jest cała kaskada wiadomości
					{
						if ( tim_seconds > min_tns_time_ths )
						{
							break ;
						}
						gsv_tns = my_nmea_get_gsv_tns ( (char*) nmea_message ) ;
					}
					if ( strstr ( (char*) nmea_message , nmea_gngsa_label ) ) // Koniecznie monitorować cały czas
					{
						fix3d->fix_mode = get_my_nmea_gngsa_fixed_mode_s ( (char*) nmea_message ) ;
						fix3d->pdop = get_my_nmea_gngsa_pdop_d ( (char*) nmea_message ) ;
					}
					if ( strstr ( (char*) nmea_message , nmea_gngll_label ) && is_utc_saved )
					{
						if ( fix3d->fix_mode != NMEA_3D_FIX ) // Solution for Issue #3 Handle a lost of fix during acquisition.
						{
							break ;
						}
						memcpy ( gngll_message , nmea_message , UART_TX_MAX_BUFF_SIZE ) ;
						if ( fix3d->pdop <= pdop_ths )
						{
							break ;
						}
					}
				}
			}
		}
	}
	my_tim_stop () ;
	// WYŁĄCZYĆ I ZASAVEOWAĆ BRAK GLONASS BO OSTATNIO NIE ZROBIŁEM SAVE TO NVRAM

	if ( gngll_message[0] )
	{
		my_nmea_get_gngll_coordinates ( (char*) gngll_message , fix3d ) ;
		r = true ;
	}
	fix3d->acq_time = tim_seconds ;
	fix3d->acq_total_time += tim_seconds ; // UWAGA: Tutaj nie mogę zaokrąglać, bo będę tracił za każdym razem resztę co się uzbiera w duży błąd
	return r ;
}


bool my_gnss_get_pair ( char pair_response[2][250] )
{
	char* 		nmea_pair_label = "$PAIR" ;
	uint8_t		i = 0 ;
	uint8_t		rx_byte = 0 ;
	uint8_t		i_nmea = 0 ;
	uint8_t		nmea_message[UART_TX_MAX_BUFF_SIZE] = {0} ;

	my_tim_start () ;
	while ( tim_seconds < 10 )
	{
		my_gnss_receive_byte ( &rx_byte, false ) ;
		if ( rx_byte )
		{
			if ( my_nmea_message ( &rx_byte , nmea_message , &i_nmea ) == 2 )
			{
				if ( is_my_nmea_checksum_ok ( (char*) nmea_message ) )
				{
					if ( strstr ( (char*) nmea_message , nmea_pair_label ) )
					{
						memcpy ( pair_response[i++] , nmea_message , UART_TX_MAX_BUFF_SIZE ) ;
						if (i == 2 )
						{
							break ;
						}
					}
				}
			}
		}
	}
	my_tim_stop () ;
	return i > 0 ? true : false ;
}
