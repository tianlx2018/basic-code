#ifndef _LIST_H
#define _LIST_H

#include <stdint.h>

#define ERR_LIST_NONE                   0
#define ERR_LIST_PTR_NULL               0xff
#define ERR_LIST_MEM_FAILED             0xfe
#define ERR_LIST_LENGTH_ZERO            0xfc

struct list_node
{
    int data;
    struct list_node *p_next;
};

typedef struct list_node list_node_t;

uint8_t list_dynamic_add(list_node_t *p,int data_init);//initialize a list with length and return the pointer p

void list_test(void);

#endif // _LIST_H
