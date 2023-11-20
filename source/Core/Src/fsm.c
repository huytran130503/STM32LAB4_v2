/*
 * fsm.c
 *
 *  Created on: Nov 13, 2023
 *      Author: DELL
 */

#include "fsm.h"


uint32_t ADC_value = 0;
//uint32_t ADC_temp = 0;
uint8_t command_data[MAX_BUFFER_SIZE];

int uart_state = UART_IDLE;
int	parser_state = PARSER_IDLE;


void clear(){
	memset(buffer,'\0', sizeof(buffer));
	index_buffer = 0;
	temp = '\0';
}

void uart_fsm(){
	switch (uart_state) {
		case UART_IDLE:
			break;
		case UART_LOAD:
			if(memcmp(command_data,"RST#",4) == 0){
				uart_state = UART_SEND;
//				HAL_UART_Transmit(&huart2, "!ADC=", 5, 50);
				HAL_ADC_Start(&hadc1);
				ADC_value = HAL_ADC_GetValue(&hadc1);
				char* str;
				HAL_UART_Transmit(&huart2, (void*) str, sprintf(str, "%d#\n\r", ADC_value), 50);
//				HAL_ADC_Stop(&hadc1);
			}
			break;
		case UART_SEND:
			setTimer(300, 1);
			uart_state = UART_WAIT;
//			HAL_UART_Transmit(&huart2, "!ADC=", 5, 50);
			HAL_ADC_Start(&hadc1);
			ADC_value = HAL_ADC_GetValue(&hadc1);
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str , "\r\n!ADC=%d#\r", ADC_value), 1000);
			break;
		case UART_WAIT:
			if(timer_flag[1] == 1)
				uart_state = UART_SEND;
			if(memcmp(command_data,"OK#",3) == 0)
				uart_state = UART_IDLE;
			break;
		default:
			break;
	}
}

void command_parser_fsm(){
	switch (parser_state) {
		case PARSER_IDLE:
			if(temp == '!'){
				parser_state = PARSER_REC;
				clear();
			}
			clear();
			break;
		case PARSER_REC:
			if(temp == '!' )
				clear();
			if(temp == '#'){
				memcpy(command_data,buffer,sizeof(buffer));
				HAL_UART_Transmit(&huart2, "\n\r", 2, 50);
				clear();
				uart_state = UART_LOAD;
				parser_state = PARSER_IDLE;
			}
			break;
		default:
			break;
	}
}

