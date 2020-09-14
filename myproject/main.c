#include <stdio.h>
#include <stdlib.h>
#define pr_debug(...) \
printf(__VA_ARGS__)

void log(...)
{
    pr_debug(__VA_ARGS__);
}

int main()
{
    log("Hello world! %d %d \n",1,2);
    return 0;
}
