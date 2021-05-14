#ifndef SCHEDULER_H
#define SCHEDULER_H


#include "./scheduler_configuration.h"
#include "./task.h"


void sch_init(void);

void sch_dispatcher(void);

unsigned char sch_add_task(void(*pf)(void),unsigned int delay ,unsigned int period);

void sch_delete_task(unsigned char task_id);

void sch_start(void);








#endif