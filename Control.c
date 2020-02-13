
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "Commands.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

void controlLoop(void) {
	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	UART2_Init();
	
	int loopCounter = 0;
	char inputBuffer[20];
	int i = 0;
	
	while (1) {
		char curByte = USART_Read(USART2);
		if (isalpha(curByte)) {
			if (curByte == '\r') {
				// Run commands
				i = 0;
				memset(inputBuffer, 0, sizeof inputBuffer);
			}
			else if (curByte == '\b') {
				inputBuffer[--i] = 0x00;
				USART_Write(USART2, (uint8_t *) "\r", 1);
				USART_Write(USART2, (uint8_t *) &inputBuffer, strlen(inputBuffer));
			}
			else {
				inputBuffer[i++] = curByte;
				USART_Write(USART2, (uint8_t *) "\r", 1);
				USART_Write(USART2, (uint8_t *) &inputBuffer, strlen(inputBuffer));
			}
		}
		USART_Delay(1000);
		if (isRedFlashing() || isGreenFlashing()) {
			loopCounter = loopCounter + 10;
			if (loopCounter >= 1000) {
				if (isRedFlashing()) {
					Red_LED_Toggle();
				}
				if (isGreenFlashing()) {
					Green_LED_Toggle();
				}
				loopCounter = 0;
			}
		}
	}
	
}

