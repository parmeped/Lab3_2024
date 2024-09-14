#ifndef _ICOMMON_H
#define _ICOMMON_H

#define LOG_LEVEL DEBUG

typedef enum
{
    NONE, // NONE
    DEBUG, // ALL
    WARN, // ONLY WARN AND ERR
    ERR // ONLY ERR
}LogLevel;

void printLn();
void logErr(char*);
void logInfo(char*);
void logWarn(char*);

#endif