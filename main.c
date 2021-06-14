
#include <reg52.h>
#include "scheduler.h"
#include "pc_menu.h"
#include "uart.h"
#include "pc_link.h"
#define LED_ON 1
#define LED_OFF 0

sbit led_bit = P1^0;


void led_update(void)
{
	
	if(led_bit == LED_ON )
	{
	  led_bit = LED_OFF;
		pc_link_write_string_to_buffer("led is off \n",sizeof("led is off \n"));
		
	}else{
	     
	     led_bit =LED_ON;
		pc_link_write_string_to_buffer("led is oNN \n",sizeof("led is oNN \n"));
	}
  
}










int main (void)
{
	
	
	sch_init();
	uart_init(9600);
	sch_add_task(led_update,0,200);
	sch_add_task(MENU_Command_Processor,3,20);
	
	
	sch_start();
	
	
	
	while(1)
	{
	
	  sch_dispatcher();
	
	}
	


}





