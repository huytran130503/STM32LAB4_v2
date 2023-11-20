/*
 * software_timer.h
 *
 *  Created on: Nov 13, 2023
 *      Author: DELL
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer_flag[5];

void setTimer(int dur, int num);
void timerRun(int num);


#endif /* INC_SOFTWARE_TIMER_H_ */
