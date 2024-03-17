/*
 * my_conversions.h
 *
 *  Created on: Oct 7, 2023
 *      Author: mzeml
 */

#ifndef MY_CONVERSIONS_H_
#define MY_CONVERSIONS_H_

#include "my_global.h"


double		my_string2double_conv ( const char* ) ;
float		my_string2float_conv ( const char* ) ;
uint8_t		my_find_char_position ( const char* , const char , uint8_t ) ;
uint32_t	my_conv_rtc2timestamp ( RTC_DateTypeDef* , RTC_TimeTypeDef* ) ;
void		my_conv_timestamp2rtc ( uint32_t , RTC_DateTypeDef* , RTC_TimeTypeDef* ) ;
int			my_conv_is_leap_year ( int ) ;
void		my_conv_dt_2_dts ( RTC_DateTypeDef* d , RTC_TimeTypeDef* t , char* dt_s ) ;
uint32_t	my_conv_string_2_uint32_t ( const char* c ) ;
#endif /* MY_CONVERSIONS_H_ */
