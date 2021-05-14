
#ifndef TASK
#define TASK


typedef struct 
{
  // pointer to function of the task that will be run by dispatcher
  void (*pf)(void);
  
  // delay -> used as predelay at creation of task , and used for calculation by sch_updat()
  
  unsigned int delay ;
  
  // period used as a referance for period of task , tell when the task will run again.

  unsigned int period;
  
  // flag used to know if the task ready to run or not.

  unsigned char Run_Me ;


} s_Task;



#endif