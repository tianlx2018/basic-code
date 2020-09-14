#include <stdio.h>
#include <stdlib.h>

//#define pr_debug(fmt,arg...) \
//printf(fmt, ##arg)

#define pr_debug(fmt,...) \
printf(fmt,__VA_ARGS__)
int main()
{

    pr_debug("Hello world! %d %d\n",1,2);

    return 0;
}
