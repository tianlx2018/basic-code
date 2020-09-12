#ifndef _SCHDULER_H
#define _SCHDULER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "stdint.h"
// #include "platform_types.h"

#define SCHEDULER_MODE  0


typedef enum{
    ERR_SCHD_NONE,
    ERR_SCHD_INVALID_PARAM
}scheduler_error_t;

typedef u_int32_t (*p_task_t)(u_int32_t evt,void *p_context);

typedef struct 
{
    p_task_t p_fun;
    u_int32_t event;
    void * p_context;
}task_t;

scheduler_error_t scheduler_init(task_t *p_task_array,uint32_t task_number);
scheduler_error_t scheduler_run(void);
scheduler_error_t scheduler_event_emit(uint32_t task_handler,uint32_t evt,void *p_context);

void timer_create(void);
void timer_start(void);
void timer_stop(void);
void timer_scheduler(void);
#ifdef __cplusplus
}
#endif
#endif/*_SCHDULER_H*/