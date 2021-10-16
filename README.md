# Arduinoscope

	Arduinoscope is a project to use an Arduino UNO and a PC as a digital oscilloscope.

## How it works

	It consists in two programs, one on the Arduino UNO side that samples the signal on the analog input and sends the samples through USB serial, and the other on the PC side that reads from the serial port and graphicates the signal on the screen.

## Building

	To build the Arduino program, you can use the provided `build_arduino.sh` script that requires `arduino-cli`, or open the project under `arduino_src` with the Arduino IDE.

	To build the PC program for Linux you can use the `build_linux.sh` script. It requires the following libraries to be installed on your computer:

	- gtk3
	- libserialport

	Building on other platforms may be possible but is not supported.

## Usage

	Connect the Arduino uno with a signal with a min-max voltage range of 0-5 volts on the first analog input, and the USB cable to the PC. Then run arduinoscope with the serial device name as the first argument:

`$ arduinoscope /dev/ttyXXXX` for Linux-based systems.

