#include "./switch.h"





// initialize the global status variable 

unsigned char sw_status_G ;

 // it is variable used to block the switch_update from update switch status for specific time
 
static unsigned char sw_blocked_G ;

// it variable use to cancle switch bouncing

static unsigned char sw_press_duration;




void switch_init()
{
	
	#if (FAMILY == 51 )
	  
	 // to make it as input pin
	
	   switch_pin = 1;
	 
	#endif
	
	
	// initialize the global variables 
	
	sw_status_G = SWITCH_OFF;
	
	
	sw_blocked_G = 0 ;
	
	
	sw_press_duration = 0; 



}





void switch_manage()
{
	
		if(sw_blocked_G > 0 )
			{
				
				
				 
			 sw_blocked_G--;
			
			
			
			}
		else
			{ 
				
				 
				
								 if (switch_pin == SWITCH_PRESSED)
									 {
										 
													 sw_press_duration++;
												 
													 /*if it still pressed for long time bigger 
														than bouncing time so it is realy pressed */
													 if( sw_press_duration > SWITCH_THRESHOLD )
														{ 
																	// so if it still pressed over the threshold it will not affect the status
																	sw_press_duration = SWITCH_THRESHOLD;
															
																	// change the status of the switch depending of the previos value 
																	if ( sw_status_G == SWITCH_ON)
																	 {
																		   sw_status_G = SWITCH_OFF;
																	 }
																	 else
																		 {  
																			 
																			 sw_status_G = SWITCH_ON;

																		 }
																		
																	// near one second blocking for any changes in status of switch_pin	 
																	sw_blocked_G = 5;
																		 
																		 
														
														}
														else
															{
																// still not enough pressing 
																 
															}
						
									 }
									 
									 else
									 {
										 
										 
										 // reset the variable to its initial value
									 
										 sw_press_duration = 0;
										 
										 
									 
									 }
							
							
							
			
			
			
			
			
			
			}









}
