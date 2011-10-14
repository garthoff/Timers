#include "Timers.h"

void NOP(void)
{
	return;
}


TimerPool::TimerPool(byte size)
{
	_size = size;
	funcs = (timerFunc *) malloc(sizeof(timerFunc)*size);
	intervals = (unsigned long *) malloc(sizeof(unsigned long)*size);
	next_times = (unsigned long *) malloc(sizeof(unsigned long)*size);
	for (int i=0; i<_size; i++)
	{
		funcs[i] = NOP;
		intervals[i] = 0;
		next_times[i] = 0;
	}
}

TimerPool::~TimerPool()
{
	free(funcs);
	free(intervals);
	free(next_times);
}

void TimerPool::connect(byte slot, unsigned long interval, timerFunc func)
{
	funcs[slot] = func;
	intervals[slot] = interval;
	next_times[slot] = millis() + interval;
}

void TimerPool::setInterval(byte slot, unsigned long interval)
{
	intervals[slot] = interval;
	next_times[slot] = millis() + interval;
}

void TimerPool::update(void)
{
	unsigned long actual_time = millis();
	
	for (int i=0; i<_size; i++)
	{
		if (intervals[i] > 0 && actual_time > next_times[i])
		{
			funcs[i]();
			next_times[i] = actual_time + intervals[i];
		}
	}
}


LimitedTimerPool::LimitedTimerPool(void)
{
	for (int i=0; i<STATIC_SIZE; i++)
	{
		funcs[i] = NOP;
		intervals[i] = 0;
		next_times[i] = 0;
	}
}

void LimitedTimerPool::connect(byte slot, unsigned long interval, timerFunc func)
{
	funcs[slot] = func;
	intervals[slot] = interval;
	next_times[slot] = millis() + interval;
}

void LimitedTimerPool::setInterval(byte slot, unsigned long interval)
{
	intervals[slot] = interval;
	next_times[slot] = millis() + interval;
}

void LimitedTimerPool::update(void)
{
	unsigned long actual_time = millis();
	
	for (int i=0; i<STATIC_SIZE; i++)
	{
		if (intervals[i] > 0 && actual_time > next_times[i])
		{
			funcs[i]();
			next_times[i] = actual_time + intervals[i];
		}
	}
}
