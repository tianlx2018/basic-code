#ifndef _LOG_H
#define _LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

#define LOG_DEFAULT_LEVEL_ALL   4


#define LOG_MODULE_ID_APP       0
#define LOG_MODULE_ID_IO          1
#define LOG_MODULE_ID_MAX      31

//ALL <DEBUG<INFO<WARN<ERROR<FATAL<OFF¡£
typedef enum{
    LOG_OFF,//level 0,turn off all logs
    LOG_FATAL,//level 1
    LOG_ERROR,//level 2
    LOG_WARN,//level 3
    LOG_INFOR,//level 4
    LOG_TRACE//level 5
}log_level_t;



void log_init(uint32_t module_id,   uint32_t enable_mask );
void log_infor(uint32_t module_id,  const char *p_str, ...);
//void log_fatal(uint32_t module_id,  char *, ...);
//void log_error(uint32_t module_id,  char *, ...);
//void log_warn(uint32_t module_id,   char *, ...);
//void log_trace(uint32_t module_id,  char *, ...);
//void log_module_level_set(uint32_t module_id,   uint8_t level);
//void log_module_enable(uint32_t module_id,  uint8_t enable);
#ifdef __cplusplus
}
#endif
#endif/*_LOG_H*/
