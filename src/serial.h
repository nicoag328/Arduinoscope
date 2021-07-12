#include <libserialport.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "serial.c"

int serial_init (char **argv);
u_int16_t* serial_read ();
int serial_free();

