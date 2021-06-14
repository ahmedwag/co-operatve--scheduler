

#include "uart.h"

#include <reg52.h>

#include "./scheduler_configuration.h"



/**********************************************************

             functions implementation

*****************************************************/



/*******************************************
*
* uart_init()
* it will initialize the nedded registers for turn on uart 
***->  input : baudrate -> it determine the baudrate that the uart will operate on it
***->  return : void
*
***********************************************/


void uart_init(unsigned int baudrate)
{
	
	   const  unsigned int baud = baudrate;
     /* unsigned long temp = 0 ,temp2 = 0 ;
	    unsigned char temp3 = 0 ;*/
			PCON &= 0x7F; // Set SMOD bit to 0 (don’t double baud rates)
	
			// Receiver enabled.
			// 8-bit data, 1 start bit, 1 stop bit,
			// Variable baud rate (asynchronous)
			// Receive flag will only be set if a valid stop bit is received
			// Set TI (transmit buffer is empty)
	
			SCON = 0x72;
			TMOD |= 0x20; // T1 in mode 2, 8-bit auto reload
	   /*  temp = baud * INS_PER_CYCLE * 1000;
	     temp2 = ((unsigned long)(OSC_FREQ / 100))*3125 ;
       temp3 = 	(unsigned char)(temp2	/ temp);*/
			TH1 = -3; // use 9600 baudrate
			TL1 = TH1;
			TR1 = 1; // Run the timer
			TI = 1; // Send first character (dummy)

}




void uart_send_char(const char CHARACTER)
{
								 
										 unsigned long Timeout1 = 0;
								unsigned long Timeout2 = 0;
								if (CHARACTER == '\n')
								{
												if (RI)
												{
															if (SBUF == XOFF)
															{
																		Timeout2 = 0;
																		
																		
																		do {
																					RI = 0;
																					// Wait for uart (with simple timeout)
																					Timeout1 = 0;
																			
																					while ((++Timeout1) && (RI == 0));
																			
																					if (Timeout1 == 0)
																					{
																					    return;
																					}
																		} while ((++Timeout2) && (SBUF != XON));
																		if (Timeout2 == 0)
																		{
																		    return;
																		}
																		RI = 0;
															}
												}
												Timeout1 = 0;
												while ((++Timeout1) && (TI == 0));
												if (Timeout1 == 0)
												{
												
												return;
												}
												TI = 0;
												SBUF = 0x0d; // output CR
								}
								if (RI)
								{
											if (SBUF == XOFF)
											{
														Timeout2 = 0;
														do {
																		RI = 0;
																		
																		// Wait for USART (with simple timeout)
																		Timeout1 = 0;
															
																		while ((++Timeout1) && (RI == 0));
															
																		if (Timeout1 == 0)
																		{
																		     return;
																		}
														} while ((++Timeout2) && (SBUF != XON));
														
														RI = 0;
								     }

								}
								
								
						Timeout1 = 0;
						while ((++Timeout1) && (TI == 0));
								
						if (Timeout1 == 0)
						{
								// USART did not respond – error
								return;
						}
						TI = 0;
						SBUF = CHARACTER;
}




void uart_send_string(const char * const string)
{
	
	 unsigned int index =0;
	
	while(string[index] != '\0')
	{
			uart_send_char(string[index]);
			index++;
	
	}

}
