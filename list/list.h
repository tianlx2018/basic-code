#ifndef _LIST_H
#define _LIST_H

#include <stdint.h>

#define ERR_LIST_NONE                   0
#define ERR_LIST_PTR_NULL               0xff
#define ERR_LIST_MEM_FAILED             0xfe
#define ERR_LIST_LENGTH_ZERO            0xfc

//typedef struct  {
//    list_hdr_t *p_prev;
//    list_hdr_t *p_next;
//}list_hdr_t;





//list_hdr_t * list_init(void);
//int  list_add_to_tail(list_hdr_t *p_tail);
//int  list_add_to_head(list_hdr_t *p_head);
//int  list_destory(list_hdr_t *p_list_hdr);
#endif // _LIST_H
