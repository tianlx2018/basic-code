#include "list.h"
#include <stdio.h>
#include <stdlib.h>

uint8_t list_dynamic_add(list_node_t *p,int data_init)
{
    p =(list_node_t*) malloc(sizeof(list_node_t));

    if(p == NULL)
        return 0xfc;

    p->data = data_init;

    return 0;
}


void list_test(void)
{
    uint8_t err_code = ERR_LIST_NONE;

    list_node_t *p = NULL;

    err_code = list_dynamic_add(p,32);

    if(err_code)
        printf("list add err:%x\r\n",err_code);
    else
        printf("list data:%x\r\n",p->data);

    free(p);

    printf("End of test\r\n");
}
