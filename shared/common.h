#include "icommon.h"

void printSep()
{
    printLnf("---------------------------------");
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

void printLnf(char *message)
{
    printf("%s\n", message);
}

void spinner(int duration_seconds) {
    // Array of spinner characters
    const char spinner_chars[] = {'\\', '|', '/', '-'};
    const int num_chars = sizeof(spinner_chars) / sizeof(spinner_chars[0]);
    
    time_t start_time = time(NULL);
    int i = 0;

    while (1) {
        time_t current_time = time(NULL);
        if (difftime(current_time, start_time) >= duration_seconds) {
            break;
        }

        printf("\r%c", spinner_chars[i]);
        fflush(stdout);

        i = (i + 1) % num_chars;
        
        usleep(duration_seconds / 100);
    }

    printf("\r ");
    fflush(stdout);
}


void mSpinner(int duration_mseconds) {
    // Array of spinner characters
    const char spinner_chars[] = {'\\', '|', '/', '-'};
    const int num_chars = sizeof(spinner_chars) / sizeof(spinner_chars[0]);
    int loop = 0;
    int i = 0;

    while (loop < duration_mseconds) {
        loop++;
        usleep(1000);

        printf("\r%c", spinner_chars[i]);
        fflush(stdout);

        i = (i + 1) % num_chars;
    }

    printf("\r ");
    fflush(stdout);
}

void usleepMs(int ms)
{
    usleep(ms * 1000);
    return;
}
