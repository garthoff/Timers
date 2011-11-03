#include "Arduino.h"

#ifndef timers_h
#define timers_h

#define STATIC_SIZE 8


typedef void (*timerFunc)(void);


void NOP(void);


struct TimerElement
{
	timerFunc func;
	unsigned long interval;
	unsigned long begin_time;
};


class TimerPool
{
	private:
		struct TimerElement *_elements;
		byte _size;
		
	public:
		TimerPool(byte size);
		void connect(byte slot, unsigned long interval, timerFunc func);
		void setInterval(byte slot, unsigned long interval);
		void update(void);
		~TimerPool();
};


class LimitedTimerPool
{
	private:
		struct TimerElement _elements[STATIC_SIZE];
		
	public:
		LimitedTimerPool(void);
		void connect(byte slot, unsigned long interval, timerFunc func);
		void setInterval(byte slot, unsigned long interval);
		void update(void);
};

#endif
