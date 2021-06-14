
#include "pc_link.h"
#include "pc_commond.h"
#include "uart.h"
#include <reg52.h>



/**********************************************************

             functions implementation

*****************************************************/



void pc_link_update(void)
{
	
	    char temp_char;

	
			/*******************************************************************
			 *
			 * check if the Out_send_index_G exceed the waiting character /
			 * in the buffer if it is true reset both to the begin of the buffer
			 *
			 ********************************************************************/
			
			 if( Out_send_index_G > Out_waiting_index_G )
			 {
				 Out_waiting_index_G = 0;
				 Out_send_index_G = 0;
			 
			 }
			 else
			 {
				 temp_char = pc_link_get_the_next_char_in_transmite_buffer();
				 
				 uart_send_char( temp_char);

			 }
			 
			 
			 /*******************************************************************
			 *
			 * check if the if we recive any new thing in reciever of uart/
			 *
			 ********************************************************************/
			 
			 if( RI == 1 )
			 {
			 
			    if(In_waiting_index_G == In_read_index_G)
					{
					   In_waiting_index_G = 0;
						 In_read_index_G = 0 ;
					
					}
					
					pc_link_put_character_at_next_position_in_recieve_buffer();

			 
			 }
			 


}