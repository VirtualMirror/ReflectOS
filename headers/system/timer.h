#pragma once


#ifndef __SYSTEM__TIMER__
#define __SYSTEM__TIMER__


void timer_init();
void timer_load(long);
void timer_IRQ_clear();
unsigned long get_timer_value();


#endif