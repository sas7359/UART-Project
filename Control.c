
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "Control.h"
#include "Commands.h"
#include <string.h>
#include <stdio.h>

volatile static uint8_t count_down_flag;

void SysTick_Init() {
	SysTick->LOAD = 80000; // Set reset value
	SysTick->CTRL |= (1<<2); // Set to processor clock
	SysTick->CTRL |= 1; // Enable
	SysTick->CTRL |= (1<<1); // Enable interupts
}

void SysTick_Handler(void) {
	if (count_down_flag > 0) {
		count_down_flag--;
	}
}

void Delay(uint32_t nTime) {
	count_down_flag = nTime;      
	while(count_down_flag != 0);
}


void controlLoop(void) {
	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	UART2_Init();
	SysTick_Init();
	
	int loopCounter = 0;
	char inputBuffer[20];
	int i = 0;
	
	while (1) {
		char curByte = USART_Read(USART2);
		if (curByte != '\0') {
			if (curByte == '\r') {
				inputBuffer[i] = '\0';
				handleInput(inputBuffer);
				i = 0;
				memset(inputBuffer, 0, sizeof inputBuffer);
			}
			else if (curByte == 0x08 || curByte == 0x7F) {
				inputBuffer[--i] = '\0';
				USART_Write(USART2, (uint8_t *) "\r", 1);
				USART_Write(USART2, (uint8_t *) &inputBuffer, strlen(inputBuffer));
				USART_Write(USART2, (uint8_t *) " ", 1);
				USART_Write(USART2, (uint8_t *) "\r", 1);
				USART_Write(USART2, (uint8_t *) &inputBuffer, strlen(inputBuffer));
			}
			else {
				inputBuffer[i++] = curByte;
				USART_Write(USART2, (uint8_t *) &curByte, 1);
			}
		}
		Delay(1);		
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

