#include "Arduino.h"

#ifndef timers_h
#define timers_h

#ifndef TIMER_ITEMS
#define TIMER_ITEMS 8
#endif

typedef void (*timerFunc)(void);


void NOP(void);


struct TimerElement
{
	timerFunc func;
	unsigned long interval;
	unsigned long begin_time;
};


class Timers
{
	private:
		struct TimerElement _elements[TIMER_ITEMS];
		
	public:
		Timers(void);
		void attach(byte slot, unsigned long interval, timerFunc func);
		void setInterval(byte slot, unsigned long interval);
		void process(void);
};

#endif
