

#include "uart.h"
#include "pc_link.h"
#include <reg52.h>




/***********************************************************
         
				  global variable decleration and defentions

*************************************************************/

unsigned char In_waiting_index_G = 0;       // index to data in recieve buffer that not read yet

unsigned char In_read_index_G = 0;         // index to data that have been read

unsigned char Out_waiting_index_G = 0;    // index to data in recieve buffer that not written yet

unsigned char Out_send_index_G = 0;      // index to data that have been sends


static char Tran_buffer[SIZE_OF_TRANSMITE_BUFFER];    // buffer used to store chars to send


static char recieve_buffer[SIZE_OF_RECIEVE_BUFFER];   // buffer used to store chars that have been recieved



/**********************************************************

             functions implementation

*****************************************************/



void pc_link_write_char_to_buffer(const char CHARACHTER)
{

	
	 /*******************************************************************
	 *
	 * check if the Out_waiting_index_G less than  SIZE_OF_TRANSMITE_BUFFER /
	 * in the buffer if it is true put CHARACHTER in the buffer else raise error
	 *
	 ********************************************************************/
	 if( Out_waiting_index_G < SIZE_OF_TRANSMITE_BUFFER )
	 {
			  // store CHARACHTER in the transmite buffer
			 Tran_buffer[Out_waiting_index_G] = CHARACHTER;
			 // make it point to next place in the buffer that we will put on it hte next character comes.
			 Out_waiting_index_G++;
				 
	 
	 }
	 else
	  {
		  
		}
	 

}






void pc_link_write_string_to_buffer(const char * const string , unsigned int SIZE)
{
	
	
			unsigned int index =0;
			
			for(;index < SIZE ; index++)
			{
					pc_link_write_char_to_buffer(string[index]);
					
			
			}

	

}




char pc_link_get_char_from_buffer(void)
{
	
	 char return_character = 127;
	
	/*******************************************************************
	 *
	 * check if the In_read_index_G less than SIZE_OF_RECIEVE_BUFFER /
	 * in the buffer if it is true get the character in the index of  In_read_index_G in the buffer else raise error
	 *
	 ********************************************************************/
					if (In_read_index_G < In_waiting_index_G)
					{
						return_character = recieve_buffer[In_read_index_G] ;
									
									if( In_read_index_G < SIZE_OF_RECIEVE_BUFFER )
								 {
												// get the character in the index of  In_read_index_G in the buffer
											 
											 // make it point to next place in the buffer that we will read from it in the next time.
											 In_read_index_G ++;

								 }
								 
					}

     
		return return_character;


}



/*
char pc_link_get_the_next_char_in_transmite_buffer(void)
{
	
	 char return_char = Tran_buffer[Out_send_index_G]; 
	
	 Out_send_index_G++;
	 
	 return return_char;


}





void pc_link_put_character_at_next_position_in_recieve_buffer(void)
{
			recieve_buffer[In_waiting_index_G] = SBUF;
				if (In_waiting_index_G < SIZE_OF_RECIEVE_BUFFER)
				{
						// Increment without overflowing buffer
						In_waiting_index_G++;
				}
				RI = 0; // Clear RT flag

}



*/


void pc_link_update(void)
{
	
	    

	
			/*******************************************************************
			 *
			 * check if the Out_send_index_G exceed the waiting character /
			 * in the buffer if it is true reset both to the begin of the buffer
			 *
			 ********************************************************************/
			
	      if (Out_send_index_G < Out_waiting_index_G)
					{
					uart_send_char(Tran_buffer[Out_send_index_G]);
					Out_send_index_G++;
					}
					else
					{
					// No data to send – just reset the buffer index
					Out_waiting_index_G = 0;
					Out_send_index_G = 0;
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
					
					
					recieve_buffer[In_waiting_index_G] = SBUF;
				if (In_waiting_index_G < SIZE_OF_RECIEVE_BUFFER)
				{
						// Increment without overflowing buffer
						In_waiting_index_G++;
				}
				RI = 0; // Clear RT flag

			 
			 }
			 


}