

#include "scheduler.h"

static task_t *p_task_array = NULL;
static uint32_t task_number = 0;

u_int32_t scheduler_init(task_t *p_task,uint32_t task_number)
{
    p_task_array = p_task;
    task_number = task_number;

    return 
}

u_int32_t scheduler_run(void)
{
    uint32_t task_index = 0;

    while (task_index++ < task_number)
    {
        p_task_t p_task = p_task_array[task_index].p_fun;
        uint32_t event = p_task_array[task_index].event;
        void * p_context = p_task_array[task_index].p_context;

        if(p_task != NULL && event != 0)
            p_task(event,p_context);
    }

    return ERR_SCHD_NONE;
}

scheduler_error_t scheduler_event_emit(uint32_t task_handler,uint32_t evt,void *p_context);


void timer_create(void)
{

}
void timer_start(void)
{
    
}
void timer_stop(void)
{
    
}
void timer_scheduler(void)
{
    
}