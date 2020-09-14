#include "stdio.h"
#include "scheduler.h"

uint32_t my_task_fun1(uint32_t evt,void *p_context)
{
    log_info("task 1 excuting");

//    if(evt & 0x0001)
//    {
//
//    }

    return 0;
}


uint32_t my_task_fun2(uint32_t evt,void *p_context)
{
    log_info("task 2 excuting");
    return 0;
}


uint32_t my_task_fun3(uint32_t evt,void *p_context)
{
    log_info("task 3 excuting");
    return 0;
}

task_t task_table[] =
{
    {my_task_fun1,0,NULL},
    {my_task_fun2,0,NULL},
    {my_task_fun3,0,NULL},
};

int main(void)
{
    uint32_t time = 10;

    scheduler_init(task_table,sizeof(task_table));

    while(time--)
    {
        scheduler_run();
    }

    return 0;
}





// void timer_create(void);
// void timer_start(void);
// void timer_stop(void);
// void timer_scheduler(void);

// void log_init(void);
// void log_error(char *, ...);
// void log_info(char *, ...);
// void log_debug(char *, ...);
// void log_module(u_int32_t module_id,u_int8_t enable);

