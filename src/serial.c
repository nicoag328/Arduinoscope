#include <libserialport.h>
#include <stdio.h>
#include <stdlib.h>

//Set the timeout
unsigned int timeout = 1000;

//Return placeholder
int result;

//Port struct 
struct sp_port *port;

//Allocate a buffer
u_int8_t *buf;


int check(enum sp_return result);

int serial_init (char **argv) {

		//Port name from CLI arguments
		char *port_name = argv[1];

		//Look for specified port
		printf("Looking for port %s.\n", port_name);
		check(sp_get_port_by_name(port_name, &port));

		//Open specified port
		printf("Opening port.\n");
		check(sp_open(port, SP_MODE_READ_WRITE));

		//Configure specified port
		printf("Setting port to 460800 8N1, no flow control.\n");
		check(sp_set_baudrate(port, 460800));
		check(sp_set_bits(port, 8));
		check(sp_set_parity(port, SP_PARITY_NONE));
		check(sp_set_stopbits(port, 1));
		check(sp_set_flowcontrol(port, SP_FLOWCONTROL_NONE));
		

		buf = malloc(5);

		return 0;
}

u_int16_t* serial_read() {

		static u_int16_t number[2];

		//Try to receive data from specified port (blocking)
		result = check(sp_blocking_read(port, buf, 4, timeout));

		/* Check whether we received the number of bytes we wanted. */
		if (result == 4) {
				number[0] = (buf[0]<<8) + buf[1];
				number[1] = (buf[2]<<8) + buf[3];
		}
		else {
				printf("Serial timed out, %d/%d bytes received.\n", result, 2);
		}

		return number;
}

int serial_free() 
{

		check(sp_close(port));
		sp_free_port(port);
		free(buf);
}

// Helper function for error handling.
int check(enum sp_return result)
{
		/* For this example we'll just exit on any error by calling abort(). */
		char *error_message;

		switch (result) {
				case SP_ERR_ARG:
						printf("Serial Error: Invalid argument.\n");
						abort();
				case SP_ERR_FAIL:
						error_message = sp_last_error_message();
						printf("Serial Error: Failed: %s\n", error_message);
						sp_free_error_message(error_message);
						abort();
				case SP_ERR_SUPP:
						printf("Serial Error: Not supported.\n");
						abort();
				case SP_ERR_MEM:
						printf("Serial Error: Couldn't allocate memory.\n");
						abort();
				case SP_OK:
				default:
						return result;
		}
}
