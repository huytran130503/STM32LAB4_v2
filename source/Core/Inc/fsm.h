/*
 * fsm.h
 *
 *  Created on: Nov 13, 2023
 *      Author: DELL
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "stdint.h"
#include "stdio.h"
#include <string.h>
#include "software_timer.h"
#include "main.h"

#define PARSER_IDLE 1
#define PARSER_REC 2

#define UART_IDLE 3
#define UART_LOAD 4
#define UART_SEND 5
#define UART_WAIT 6
#define MAX_BUFFER_SIZE 30

extern int parser_state;
extern int uart_state;
extern uint8_t temp;
extern uint8_t index_buffer;
extern uint8_t buffer_flag;
extern uint8_t previous;
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;
extern uint32_t ADC_value;
extern uint32_t ADC_temp;

uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t command_data[MAX_BUFFER_SIZE];


char str[1000];

void uart_fsm();
void command_parser_fsm();
void clear();

#endif /* INC_FSM_H_ */
