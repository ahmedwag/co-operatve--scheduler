

#include "pc_menu.h"
#include <reg52.h>
#include "pc_link.h"


void MENU_Show_Menu(void)
{
		pc_link_write_string_to_buffer("Menu:\n",sizeof("Menu:\n"));
		pc_link_write_string_to_buffer("a - AAA xxx\n",sizeof("a - AAA xxx\n"));
		pc_link_write_string_to_buffer("b - BBB xxx\n",sizeof("b - BBB xxx\n"));
		pc_link_write_string_to_buffer("c - CCC xxx\n\n",sizeof("c - CCC xxx\n\n"));
		pc_link_write_string_to_buffer("Please type a character : ",sizeof("Please type a character : "));
}

void Function_A(void)
{
		pc_link_write_string_to_buffer("\n*** Doing A ***\n\n",sizeof("\n*** Doing A ***\n\n"));
		P2 = 'A';
}
/*------------------------------------------------------------------*-
Placeholder function
-*------------------------------------------------------------------*/

void Function_B(void)
{
		pc_link_write_string_to_buffer("\n*** Doing B ***\n\n",sizeof("\n*** Doing B ***\n\n"));
		P2 = 'B';
}
/*------------------------------------------------------------------*-
Placeholder function
-*------------------------------------------------------------------*/
void Function_C(void)
{
		pc_link_write_string_to_buffer("\n*** Doing C ***\n\n",sizeof("\n*** Doing C ***\n\n"));
		P2 = 'C';
}


void MENU_Perform_Task(char c)
{
// Echo the menu option
pc_link_write_char_to_buffer(c);
pc_link_write_char_to_buffer('\n');
// Perform the task
			switch (c)
			{
							case 'a':
							case 'A':
							{
								Function_A();
								break;
							}
							case 'b':
							case 'B':
							{
									Function_B();
									break;
							}
							case 'c':
							case 'C':
							{
								 Function_C();
							}
							default : 
								break;
			}
}



void MENU_Command_Processor(void)
{
	        char Ch ;
					static bit First_time_only;
				
					if (First_time_only == 0)
					{
					First_time_only = 1;
					MENU_Show_Menu();
					}
					// Check for user inputs
					pc_link_update();
				 Ch = pc_link_get_char_from_buffer();
					if (Ch != 127)
					{
						MENU_Perform_Task(Ch);
						MENU_Show_Menu();
          }
}
