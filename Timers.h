#include "WProgram.h"

#ifndef timers_h
#define timers_h

#define STATIC_SIZE 8


typedef void (*timerFunc)(void);


void NOP(void);


class TimerPool
{
	private:
		timerFunc *funcs;
		unsigned long *intervals;
		unsigned long *begin_times;
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
		timerFunc funcs[STATIC_SIZE];
		unsigned long intervals[STATIC_SIZE];
		unsigned long begin_times[STATIC_SIZE];
		
	public:
		LimitedTimerPool(void);
		void connect(byte slot, unsigned long interval, timerFunc func);
		void setInterval(byte slot, unsigned long interval);
		void update(void);
};

#endif
