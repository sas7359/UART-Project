#include "LED.h"
#include "Commands.h"
#include "UART.h"
#include <string.h>
#include <stdio.h>

/*
* Command functionality
* Author: Spencer Stissi
*/

// Variables
int redFlashing = 0;
int greenFlashing = 0;

// Functions
void handleInput(char* input) {
		if (strcmp(input, "RON") == 0) {
			Red_LED_On();
			if (redFlashing == 1) {
				redFlashing = 0;
			}
			USART_Write(USART2, (uint8_t *) "\n\rTurning red led on.\n\r", 23);
		}
		else if (strcmp(input, "ROFF") == 0) {
			Red_LED_Off();
			if (redFlashing == 1) {
				redFlashing = 0;
			}
			USART_Write(USART2, (uint8_t *) "\n\rTurning red led off.\n\r", 24);
		}
		else if (strcmp(input, "GON") == 0) {
			Green_LED_On();
			if (greenFlashing == 1) {
				greenFlashing = 0;
			}
			USART_Write(USART2, (uint8_t *) "\n\rTurning green led on.\n\r", 25);
		}
		else if (strcmp(input, "GOFF") == 0) {
			Green_LED_Off();
			if (greenFlashing == 1) {
				greenFlashing = 0;
			}
			USART_Write(USART2, (uint8_t *) "\n\rTurning green led off.\n\r", 26);
		}
		else if (strcmp(input, "RFLASH") == 0) {
			redFlashing = 1;
			USART_Write(USART2, (uint8_t *) "\n\rTurning red flash on.\n\r", 25);
		}
		else if (strcmp(input, "GFLASH") == 0) {
			greenFlashing = 1;
			USART_Write(USART2, (uint8_t *) "\n\rTurning green flash on.\n\r", 27);
		}
		else if (strcmp(input, "FLASHOFF") == 0) {
			redFlashing = 0;
			greenFlashing = 0;
			// Clean up incase either LED stays on
			Red_LED_Off();
			Green_LED_Off();
			USART_Write(USART2, (uint8_t *) "\n\rTurning all flashing off.\n\r", 29);
		}
		else {
			USART_Write(USART2, (uint8_t *) "\n\rError: invalid command!\n\r", 27);
		}
}

void setRedFlash(int value) {
	redFlashing = value;
}

void setGreenFlash(int value) {
	greenFlashing = value;
}

int isRedFlashing() {
	return redFlashing;
}

int isGreenFlashing() {
	return greenFlashing;
}
