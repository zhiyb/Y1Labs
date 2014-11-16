/* This is the C code for host program,
 * to control the boost converter.
 * Wrote by Yubo Zhi (yz39g13@soton.ac.uk)
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "rs232.h"
#include "comm.h"

#ifdef __linux__
#include <unistd.h>
#else
#include <windows.h>
#define usleep(s)	Sleep(s / 1000);
#endif

#define BAUDRATE	9600
#define UARTDELAY	50000		// us
#define PWMMAX		1024
#define ADCMAX		1024

#define VIN	1.5
#define VREF	3.3
#define VMAX	15.0
#define R1	22
#define R2	4.7
#define R3	0.22

struct {
	int portnum, opened;
} com = {
	.portnum = 0,
	.opened = 0,
};
float set = 12.0;

void COM_open(char *name)
{
	int i;
	if (com.opened) {
		RS232_CloseComport(com.portnum);
		com.opened = 0;
	}
	for (i = 0; i < COMPORTS; i++)
		if (strcmp(name, comports[i]) == 0)
			break;
	if (i == COMPORTS || RS232_OpenComport(i, BAUDRATE) != 0) {
		fputs("Cannot open serial port!\n", stderr);
		return;
	}
	com.portnum = i;
	com.opened = 1;
}

int COM_isOpened(void)
{
	if (!com.opened)
		fputs("Serial port not opened!\n", stderr);
	return com.opened;
}

char *readline(void)
{
	char c;
	char *str = (char *)malloc(sizeof(char));
	*str = '\0';
	while ((c = getchar()) != '\n')
	{
		str = realloc(str, strlen(str) + 2);
		*(str + strlen(str) + 1) = '\0';
		*(str + strlen(str)) = c;
	}
	return str;
}

float conv2Volt(int adc)
{
	return ((float)adc / ADCMAX * VREF) / R2 * (R1 + R2);
}

int conv2ADC(float v)
{
	return (int)(v / (R1 + R2) * (R2) * ADCMAX / VREF);
}

void help(void)
{
	puts("Boost Controller Host\n" \
			"\n" \
			"Available commands:\n" \
			"quit / exit	Exit this program\n" \
			"help		Show this help context\n" \
			"connect		Open serial port\n" \
			"disconnect	Close serial port\n" \
			"report		MCU report readings\n" \
			"set		Set output voltage");
}

int main(void)
{
	char *str;
	puts("Boost Controller Host");
	puts("`help' for help, `connect' to connect to serial port.\n");
start:
	printf("> ");
	fflush(stdout);
	str = readline();
	if (strcasecmp(str, "quit") == 0 || strcasecmp(str, "exit") == 0) {
		free(str);
		return 0;
	} else if (strcasecmp(str, "help") == 0)
		help();
	else if (strcasecmp(str, "connect") == 0) {
#ifdef __linux__
		printf("Port name? [/dev/ttyUSB0] ");
#else
		printf("Port name? [COM2] ");
#endif
		free(str);
		str = readline();
		if (strcmp(str, "") == 0) {
#ifdef __linux__
			str = realloc(str, 13);
			strcpy(str, "/dev/ttyUSB0");
#else
			str = realloc(str, 5);
			strcpy(str, "COM2");
#endif
		}
#ifndef __linux__
		str = realloc(str, strlen(str) + 5);
		*(str + 4 + strlen(str)) = '\0';
		strncpy(str + 4, str, strlen(str));
		strncpy(str, "\\\\.\\", 4);
#endif
		COM_open(str);
	} else if (strcasecmp(str, "disconnect") == 0) {
		RS232_CloseComport(com.portnum);
		com.opened = 0;
	} else if (strcasecmp(str, "report") == 0) {
		int value[4], num;
		char buff[255];
		if (!COM_isOpened())
			goto ret;
		RS232_SendByte(com.portnum, COMM_GET);
		usleep(UARTDELAY);
		num = RS232_PollComport(com.portnum, \
				(unsigned char *)buff, 255);
		buff[num] = '\0';
		if (num == 0) {
			fputs("Not connected!\n", stderr);
			goto ret;
		}
		value[0] = atoi(strtok(buff, " "));
		value[1] = atoi(strtok(NULL, " "));
		value[2] = atoi(strtok(NULL, " "));
		value[3] = atoi(strtok(NULL, " "));
		printf("Set: %fV\n", conv2Volt(value[1]));
		printf("ADC: %fV\n", conv2Volt(value[0]));
		printf("PWM: %f%% (%d/%d)\n", \
				(float)(value[2] + 1) / PWMMAX * 100, \
				value[2], PWMMAX);
		printf("Current: %fA\n", \
				(float)value[3] / ADCMAX * VREF / R3);
	} else if (strcasecmp(str, "set") == 0) {
		int num;
		char buff[255];
		float vout = set;
		if (!COM_isOpened())
			goto ret;
		printf("Output voltage? [%.1f] ", set);
		free(str);
		str = readline();
		if (strcmp(str, "") != 0) {
			vout = atof(str);
			if (vout < VIN || vout > VMAX) {
				fputs("Invalid input!\n", stderr);
				goto ret;
			}
			set = vout;
		}
		str = realloc(str, sizeof(char) * 5);
		sprintf(str, "%d\n", conv2ADC(vout));
		RS232_SendByte(com.portnum, COMM_SET);
		RS232_cputs(com.portnum, str);
		usleep(UARTDELAY);
		num = RS232_PollComport(com.portnum, \
				(unsigned char *)buff, 255);
		buff[num] = '\0';
		if (num == 0) {
			fputs("Response not received!\n", stderr);
			goto ret;
		}
		printf("Output voltage set to: %fV\n", \
				conv2Volt(atoi(buff)));
	} else if (strcasecmp(str, "time") == 0)
#ifdef __linux__
		system("date '+%Y:%m:%d %H:%M:%S'");
#else
		system("echo %date% %time%");
#endif
	else
		fprintf(stderr, "Unrecognised command!\n");
ret:
	free(str);
	goto start;
	return 0;
}
