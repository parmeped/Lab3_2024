#include <stdio.h>
#include "icommon.h"

void printLn()
{
    printf("---------------------------------\n");
}

void logErr(char *message)
{
    if (LOG_LEVEL == NONE)
    {
        return;
    }
    printf("\033[31mError\033[0m: %s\n", message);
}

void logInfo(char *message)
{
    if (LOG_LEVEL == NONE || LOG_LEVEL == WARN || LOG_LEVEL == ERR)
    {
        return;
    }
    printf("\033[32mInfo\033[0m: %s\n", message);
}

void logWarn(char *message)
{
    if (LOG_LEVEL == NONE || LOG_LEVEL == ERR)
    {
        return;
    }
    printf("\033[33mWarn\033[0m: %s\n", message);
}
