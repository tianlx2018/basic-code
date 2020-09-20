#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
//#include "list.h"

typedef struct  {
    void *p_previous;
    void *p_next;
}list_t;

/*
call memalloc to create a list header
@param:none
@returne:list_t *p
*/

#define LIST_PTR_VALID(PTR)   (PTR == NULL)

#define LIST_DEBUG
#ifdef LIST_DEBUG
#define L_DEBUG(...) printf(__VA_ARGS__)
#else
#define L_DEBUG(...)
#endif // LIST_DEBUG

/*
@module:list
@type:export function
@brief:create a list header and initialize it
@param:none
@returne:list_t *p
@usage:
    list_t  p_list = list_new();
    if(p_list == NULL)
    {
        //create failed
    }
    else
    {
        //succeed
    }
*/
list_t *list_new(void)
{
    list_t *p_list = (list_t *)malloc(sizeof(list_t));

    if(p_list != NULL)
    {
        p_list->p_next = NULL;
        p_list->p_previous = NULL;        
    }

    return p_list;
}

list_t *list_get_next(list_t *p)
{
    //assert(LIST_PTR_VALID(p)) ;

    return (p->p_next);
}

list_t *list_get_previous(list_t *p)
{
    //assert(LIST_PTR_VALID(p)) ;

    return (p->p_previous);
}

list_t *list_get_tail(list_t *p)
{
    //assert(LIST_PTR_VALID(p)) ;

    list_t *p_list_tmp = p;

    while(p_list_tmp->p_next != NULL)
    {
        p_list_tmp = (list_t *)p_list_tmp->p_next;
    }

    return p_list_tmp;
}

list_t *list_get_header(list_t *p)
{
    //assert(LIST_PTR_VALID(p)) ;

    list_t *p_list_tmp = p;

    while(p_list_tmp->p_previous != NULL)
    {
        p_list_tmp = (list_t *)p_list_tmp->p_previous;
    }

    return p_list_tmp;
}


list_t * list_add_tail(list_t *p_list,list_t *p_node)
{
    //assert(LIST_PTR_VALID(p_list)) ;
    //assert(LIST_PTR_VALID(p_node)) ;

    list_t *p_list_tail = list_get_tail(p_list);

    if(p_list_tail != NULL)
    {
        p_list_tail->p_next = (void*)p_node;
        p_node->p_previous = p_list_tail;
    }

    return p_node;
}

list_t * list_add_head(list_t *p_list,list_t *p_node)
{
    //assert(LIST_PTR_VALID(p_list)) ;
    //assert(LIST_PTR_VALID(p_node)) ;

    list_t *p_list_header = list_get_header(p_list);

    if(p_list_header != NULL)
    {
        p_list_header->p_previous = (void*)p_node;
        p_node->p_previous = NULL;
    }

    return p_node;
}
/*
@brief release a whole chain header
@param:list_t *p_list the list header
*/
void list_free(list_t *p_list)
{
    list_t* p_list_tmp = NULL;

    do
    {
        p_list_tmp = p_list;
        p_list = p_list->p_next;          
        free(p_list_tmp);
        printf("free node:%x next node:%x\n",p_list_tmp, p_list);
    }while(p_list != NULL);
}

void list_test_print(list_t *p_list)
{
    uint8_t i = 0;
    if(p_list == NULL)
        printf("empty list ptr\n");
    else
    {
        do
        {
            printf("the %d node:%x prev: %x next:%x\n",i++, p_list,p_list->p_previous,p_list->p_next);
            p_list = (void*)(p_list->p_next);
        }while(p_list != NULL);
    }
}


int main()
{
    L_DEBUG("Hello world \n");

    list_t *p_list_header = list_new();
    printf("list_header %x\n",p_list_header);

    list_t *p_list = list_new();
    list_add_tail(p_list_header, p_list);
    printf("list_header %x\n",p_list_header);

    p_list = list_new();
    list_add_tail(p_list_header, p_list);

    p_list = list_new();
    list_add_tail(p_list_header, p_list);

    p_list = list_new();
    list_add_tail(p_list_header, p_list);

    list_test_print(p_list_header);

    list_free(p_list_header);
    p_list_header = NULL;

    return 0;
}
