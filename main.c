#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "Control.h"

#include <string.h>
#include <stdio.h>

int main(void){
	/*
	char  rxByte;
	int		a;
	int		n;
	int		i;
	float b;
	*/
		
	controlLoop();
	
	/*
	while (1){
		n = sprintf((char *)buffer, "a = %d\t", a);
		n += sprintf((char *)buffer + n, "b = %f\r\n", b);
		USART_Write(USART2, buffer, n);		
		a = a + 1;
		b = (float)a/100;
		// now spin for a while to slow it down
		for (i = 0; i < 4000000; i++)
			;
		
		char byteBuffer[10];

		int idx = 0;
		while ((rxByte = USART_Read(USART2)) != '\r') {
			byteBuffer[idx] = rxByte;
			USART_Write(USART2, (uint8_t *) &rxByte, 1);
			idx++;
		}
		USART_Write(USART2, (uint8_t *)"\r\n", 2);
		
		byteBuffer[idx] = '\0';
		
		if (strcmp(byteBuffer, "off") == 0){
			Red_LED_Off();
			USART_Write(USART2, (uint8_t *)"LED is Off\r\n\r\n", 16);
		}
		else if (strcmp(byteBuffer, "on") == 0){
			Red_LED_On();
			USART_Write(USART2, (uint8_t *)"LED is on\r\n\r\n", 15);
		}
		else {
			USART_Write(USART2, (uint8_t *)"Error: invalid command\r\n\r\n", 26);
		}
		
		memset(byteBuffer, 0, sizeof byteBuffer);
		
	}
	*/
}

