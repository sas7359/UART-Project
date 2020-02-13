#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"

#include <string.h>
#include <stdio.h>

char RxComByte = 0;
uint8_t buffer[BufferSize];
char str[] = "Give Red LED control input ('on' = On, 'off' = off):\r\n";

int main(void){
	char  rxByte;
	int		a;
	int		n;
	int		i;
	float b;
	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	UART2_Init();
		
	while (1){
		n = sprintf((char *)buffer, "a = %d\t", a);
		n += sprintf((char *)buffer + n, "b = %f\r\n", b);
		USART_Write(USART2, buffer, n);		
		a = a + 1;
		b = (float)a/100;
		// now spin for a while to slow it down
		for (i = 0; i < 4000000; i++)
			;

// Commented out LED code for reference.
// Change this code to only accept "on" or "off" followed by
// the carriage return. Ignore what was typed until you see a
// carriage return (Enter key). Print an error if you see
// something other than "on" or "off" (without the quote marks of course).

		char byteBuffer[10];
		
		//USART_Write(USART2, (uint8_t *)str, strlen(str));	
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
}

