#include <reg52.h>
#include "scheduler.h"

#define TIMER_2_OVERFLOW_INTERRUPT 5
#define NULL ((void*)0)
	
s_Task arr_tasks[MAX_TASKS];
// used to know number of tasks added to arr_task to stop adding after reaching the maximum
static unsigned char task_index = 0 ;

void sch_init(void)
{
	unsigned char index;
	
	// initialize aaray of tasks
	
	
	for(index=0;index < MAX_TASKS ; index++)
	{
		arr_tasks[index].pf = NULL;
		arr_tasks[index].delay = 0;
		arr_tasks[index].period=0;
		arr_tasks[index].Run_Me=0;
	
	}
  
			T2CON = 0x04; // load Timer 2 control 
			//T2MOD = 0x00; // load Timer 2 mode 
			TH2 = 0xEE; // load timer 2 high byte
			RCAP2H =0xEE; // load timer 2 reload capture reg, high byte
			TL2 = 0x00; // load timer 2 low byte
			RCAP2L = 0x00; // load timer 2 reload capture reg, low byte
			ET2 = 1; // Timer 2  is enabled
			TR2 = 1; // Start Timer 2
	
}

void sch_delete_task(unsigned char task_id)
{
	
	arr_tasks[task_id].pf = NULL;
	arr_tasks[task_id].delay = 0;
	arr_tasks[task_id].period=0;
	arr_tasks[task_id].Run_Me=0;
}


void sch_dispatcher(void)
{

	// run the task that Run_Me = 1
	unsigned char index;
	
				for(index=0;index < MAX_TASKS ; index++)
				{
								if(arr_tasks[index].pf != NULL)
								{
										
											if(arr_tasks[index].Run_Me == 1)
											{
												
														// run specefic task that is ready to run
														(*arr_tasks[index].pf)();
														
														// return it back to waiting state
														arr_tasks[index].Run_Me = 0; 
												
														// if it on shoot (period = 0) -> delete it
														if( arr_tasks[index].period == 0)
															{
																
																sch_delete_task(index);

															}

											
											}

								}
				
				}


}

unsigned char sch_add_task(void(*pf)(void),unsigned int delay ,unsigned int period)
{
	
	
			if ( task_index < MAX_TASKS)
			{
				arr_tasks[task_index].pf = pf;
				arr_tasks[task_index].delay =delay;
				arr_tasks[task_index].period=period;	
				task_index++;
				
				
			}else
			{
			
			}

  return task_index;

}



void sch_update() interrupt TIMER_2_OVERFLOW_INTERRUPT
{
	
	unsigned char index;
	// Have to manually clear this.
	TF2 = 0; 

	// update array of tasks

	for(index=0;index < MAX_TASKS ; index++)
	{
		if(arr_tasks[index].pf != NULL)
		{
			
					if(arr_tasks[index].delay == 0)
					{
						arr_tasks[index].Run_Me = 1 ;
						
						if( arr_tasks[index].period != 0 )
						{
									// Schedule periodic tasks to run again
								arr_tasks[index].delay = arr_tasks[index].period;
						}
					}
					else
					{
					  arr_tasks[index].delay--;
					}
		
		
		}
		
	
	}

}




void sch_start(void)
{

   // enable all interrupts
	EA = 1 ;


}
