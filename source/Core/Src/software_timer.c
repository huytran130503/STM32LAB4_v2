/*
 * software_timer.c
 *
 *  Created on: Nov 13, 2023
 *      Author: DELL
 */


#include "software_timer.h"

int timer_counter[5] = {0};
int timer_flag[5] = {0};

void setTimer(int dur, int num){
	timer_counter[num] = dur;
	timer_flag[num] = 0;
}
void timerRun(int num){
	if(timer_counter[num] > 0){
		timer_counter[num]--;
		if(timer_counter[num] <= 0){
			timer_flag[num] = 1;
		}
	}
}
