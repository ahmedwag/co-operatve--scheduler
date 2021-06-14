
#ifndef PC_LINK_H
#define PC_LINK_H


/***********************************************************
         
				  global variable decleration 

*************************************************************/


extern unsigned char In_waiting_index_G ;       // index to data in recieve buffer that not read yet

extern unsigned char In_read_index_G ;         // index to data that have been read

extern unsigned char Out_waiting_index_G ;    // index to data in recieve buffer that not written yet

extern unsigned char Out_send_index_G ;      // index to data that have been sends




/**********************************************************

             important defentions 

*****************************************************/

#define SIZE_OF_TRANSMITE_BUFFER 100


#define SIZE_OF_RECIEVE_BUFFER   8




/**********************************************************

             functions proto-types

*****************************************************/



void pc_link_write_char_to_buffer(const char CHARACTER);




void pc_link_write_string_to_buffer(const char * const string , unsigned int SIZE);




char pc_link_get_char_from_buffer(void);

/*

char pc_link_get_the_next_char_in_transmite_buffer(void);



void pc_link_put_character_at_next_position_in_recieve_buffer();

*/

void pc_link_update(void);




#endif