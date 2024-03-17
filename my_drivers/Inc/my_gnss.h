/*
 * my_lx6_gnss.h
 *
 *  Created on: Oct 27, 2023
 *      Author: mzeml
 */

#ifndef MY_GNSS_H_
#define MY_GNSS_H_

#include "my_global.h"
#include "my_nmea.h"
#include "my_rtc.h"

#define NMEA_3D_FIX						'3'
#define MY_GNSS_COORDINATE_MAX_SIZE		12 // 10 + ew. znak minus + '\0'
#define NMEA_FIX_PDOP_STRING_BUFF_SIZE	5

// GNSS
typedef struct
{
	int32_t		latitude_astro_geo_wr ;
	int32_t		longitude_astro_geo_wr ;
	double 		pdop ;
	char		fix_mode ;
	uint16_t	acq_time ;
	uint32_t	acq_total_time ;
} my_gnss_fix ;

// Local functions
bool my_gnss_acq_coordinates ( fix_astro* ) ;
bool my_gnss_get_pair ( char pair_response[2][250] ) ;

#endif /* MY_GNSS_H_ */
