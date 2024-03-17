/*
 * my_astronode.c
 *
 *  Created on: Oct 23, 2023
 *      Author: mzeml
 */
#include "my_astronode.h"

char 		my_astro_rcv_cmd[40] = {0} ;
bool		astro_rcv_cmd_flag = false ;


bool my_astro_init ()
{
	bool cfg_wr = false ;

	while ( !cfg_wr )
	{
		astro_reset () ;
		// Satellite Acknowledgement (true): Asset informed of ACK to satellite (default)
		// Add Geolocation (true)
		// Enable_ephemeris (true)
		// Deep Sleep Mode (false) NOT used
		// Satellite Ack Event Pin Mask (true): EVT pin shows EVT register Payload Ack bit state
		// Reset Notification Event Pin Mask (true):  EVT pin shows EVT register Reset Event Notification bit state
		// Command Available Event Pin Mask (true): EVT pin shows EVT register Command Available bit state
		// Message Transmission (Tx) Pending Event Pin Mask (false):  EVT pin does not show EVT register Msg Tx Pending bit state
		cfg_wr = astronode_send_cfg_wr ( true , true , true , false , true , true , true , false  ) ;
	}

	if ( cfg_wr )
	{
		astronode_send_rtc_rr () ;
		astronode_send_cfg_sr () ;
		astronode_send_mpn_rr () ;
		astronode_send_msn_rr () ;
		astronode_send_mgi_rr () ;
		astronode_send_pld_fr () ;
		return true ;
	}
	else
		return false ;
}

bool my_astro_add_payload_2_queue ( uint16_t id , const char* payload )
{
	size_t l = strlen ( payload ) ;
	if ( l <= ASTRONODE_APP_PAYLOAD_MAX_LEN_BYTES )
	{
		if ( astronode_send_pld_er ( id , payload , l ) )
		{
			return true ;
		}
	}
	else
	{
		send_debug_logs ( "my_astronode.c,my_astro_add_payload_2_queue,Payload exceeded ASTRONODE_APP_PAYLOAD_MAX_LEN_BYTES value." ) ;
	}
	return false ;
}
bool my_astro_handle_evt ( void )
{
	send_debug_logs ( "my_astronode.c,my_astro_handle_evt,evt pin is high." ) ;
	astronode_send_evt_rr () ;
	if (is_sak_available () )
	{
	  astronode_send_sak_rr () ;
	  astronode_send_sak_cr () ;
	  send_debug_logs ( "my_astronode.c,my_astro_handle_evt,message has been acknowledged." ) ;
	  //astronode_send_per_rr () ;
	}
	if ( is_astronode_reset () )
	{
	  send_debug_logs ( "my_astronode.c,my_astro_handle_evt,terminal has been reset." ) ;
	  astronode_send_res_cr () ;
	}
	if ( is_command_available () )
	{
	  send_debug_logs ( "my_astronode.c,my_astro_handle_evt,unicast command is available" ) ;
	  if ( astronode_send_cmd_rr ( my_astro_rcv_cmd ) )
	  {
		  astro_rcv_cmd_flag = true ;
	  }
	  astronode_send_cmd_cr () ;
	}
	return true ;
}
bool my_astro_log ( void )
{
	astronode_send_rtc_rr ();
	astronode_send_nco_rr () ;
	//astronode_send_lcd_rr () ;
	//astronode_send_end_rr () ;
	//astronode_send_per_rr () ;
	return true ;
}

void my_astro_write_coordinates ( int32_t astro_geo_wr_latitude , int32_t astro_geo_wr_longitude )
{
	astronode_send_geo_wr ( astro_geo_wr_latitude , astro_geo_wr_longitude ) ;
}


