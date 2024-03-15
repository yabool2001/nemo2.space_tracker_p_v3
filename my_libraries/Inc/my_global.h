/*
 * my_global.h
 *
 *  Created on: Jan 7, 2024
 *      Author: mzeml
 */

#ifndef MY_GLOBAL_H_
#define MY_GLOBAL_H_

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stm32g0xx_hal.h"

#define TIME_THS_15_SEC				15
#define TIME_THS_30_SEC				30
#define TIME_THS_45_SEC				45
#define TIME_THS_1_MIN				60
#define TIME_THS_2_MIN				120
#define TIME_THS_5_MIN				300
#define TIME_THS_10_MIN				600
#define TIME_THS_15_MIN				900 // Nic nie powinno tego przekraczać, bo to jest okres watchdog
#define TIME_THS_1_H				3600
#define TIME_THS_100_D				8640000

#define UART_TX_MAX_BUFF_SIZE		250


// SYS
extern char		dbg_payload[UART_TX_MAX_BUFF_SIZE] ;

void			send_debug_logs ( const char* ) ;
void			my_astronode_reset ( void ) ;
void			send_astronode_request ( uint8_t* , uint32_t ) ;
uint32_t		get_systick ( void ) ;
bool			is_systick_timeout_over ( uint32_t , uint16_t ) ;
bool			is_astronode_character_received ( uint8_t* ) ;


#endif /* MY_GLOBAL_H_ */