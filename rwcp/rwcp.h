#include "stdint.h"


#ifdef RWCP_DEBUG
#include "stdio.h"
#define RWCP_LOG(...)   printf(...)
#else
#define RWCP_LOG(...)
#endif

#define SEND_RETRY_TIMES 3
#define SEND_INTERVAL 30    //ms


#define SLIDE_WINDOW_SIZE   10 //unit packages to send one time
#define SLIDE_SEND_TIMEOUT  2000//unit ms
#define SLIDE_SEND_RETRY    3//unit times
#define SLIDE_SEND_INTERVAL    3//unit times

#define SEND_MTU    20


typedef enum {
    ERR_NONE,
    ERR_SERVER_RST,
    ERR_SERVER_NO_REPLY
}error_t;

int rwcp_send(uint8_t *pbuf,uint32_t length);
int rwcp_client_reset(void);
int rwcp_sever_reset(void);
int rwcp_client_on_receive(uint8_t *pbuf,uint32_t length);
int rwcp_server_on_receive(uint8_t *pbuf,uint32_t length);
