#ifndef _ICOMMON_H
#define _ICOMMON_H

#define LOG_LEVEL DEBUG

#define CLAVE_BASE      35
#define CLAVE_BASE_2    36

#define CUAL_SEMAFORO   0
#define CANT_SEMAFORO   1
#define TIEMPO_SLEEP    5

#define SALIR		    0

#define ROJO            0
#define VERDE           1

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>

typedef enum
{
    NONE, // NONE
    DEBUG, // ALL
    WARN, // ONLY WARN AND ERR
    ERR // ONLY ERR
}LogLevel;

/// @brief Prints a separation line.
void printSep();
/// @brief Prints message, then adds a line break.
/// @param message The message to print.
void printLnf(char*);
void logErr(char*);
void logInfo(char*);
void logInfof(const char *const _Format, ...);
void logWarn(char*);
/// @brief Prints a spinner on the console.
/// @param duration The amount the spinner has to display, expressed in seconds. 
void spinner(int);
/// @brief Prints a spinner on the console.
/// @param duration The amount the spinner has to display, expressed in mili seconds. 
void mSpinner(int);
/**
 * @brief Suspende la ejecución del programa durante un número específico de milisegundos.
 *
 * @param ms El número de milisegundos durante los cuales el programa debe suspenderse.
 */
void usleepMs(int);

#endif