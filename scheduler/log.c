#include "stdint.h"
#include "log.h"
#include "stdio.h"

#ifdef USE_VENDOR_IO
#define LOG(STR,VAR)    //add vendor io function here
#else
#define LOG(...) printf(__VA_ARGS__)
#endif // USE_VENDOR_IO

#define LOG_MODULE_MASK(n)           (uint32_t)(1<<n)

uint32_t module_enable = 0xffffffff;//all module enable
uint8_t level[LOG_MODULE_ID_MAX] = {0};


void log_init(uint32_t module_id,   uint32_t enable_mask )
{

}
void log_infor(uint32_t module_id,  const char *p_str,...)
{
    if(module_id > LOG_MODULE_ID_MAX)
        return;

    if((LOG_MODULE_MASK(module_id) & module_enable) && (level[module_id] <= LOG_INFOR))
    {
        LOG(p_str,__VA_ARGS__);
    }
}
void log_fatal(uint32_t module_id,  char *p_str, ...)
{
}
void log_error(uint32_t module_id,  char *p_str, ...)
{

}
void log_warn(uint32_t module_id,   char *p_str, ...)
{

}
void log_trace(uint32_t module_id,  char *p_str, ...)
{
}
void log_module_level_set(uint32_t module_id,   uint8_t level)
{

}
void log_module_enable(uint32_t module_id,  uint8_t enable)
{

}
