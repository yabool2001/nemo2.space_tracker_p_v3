/*
 * my_astronode.h
 *
 *  Created on: Oct 23, 2023
 *      Author: mzeml
 */

#ifndef ASTROCAST_INC_MY_ASTRONODE_H_
#define ASTROCAST_INC_MY_ASTRONODE_H_

#include "my_global.h"
#include "astronode_application.h"
#include "astronode_definitions.h"
#include "astronode_transport.h"

extern char my_astro_rcv_cmd[40] ;
extern bool	my_astro_rcv_cmd_flag ;

typedef struct
{
	uint8_t		code ;
	uint32_t	value ;
	bool		is_executed ;
} my_astro_cmd ;


extern void		send_debug_logs ( const char* ) ;
extern void		send_astronode_request ( uint8_t* , uint32_t ) ;
extern uint32_t	get_systick ( void ) ;
extern bool		is_systick_timeout_over ( uint32_t , uint16_t ) ;
extern bool		is_astronode_character_received ( uint8_t* ) ;
extern void		astro_reset ( void ) ;

bool my_astro_init ( void ) ;
void my_astro_write_coordinates ( int32_t , int32_t ) ;
bool my_astro_add_payload_2_queue ( uint16_t , const char* ) ;
bool my_astro_handle_evt ( void ) ;
bool my_astro_log ( void ) ;

#endif /* ASTROCAST_INC_MY_ASTRONODE_H_ */
