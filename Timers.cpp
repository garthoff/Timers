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
	begin_times = (unsigned long *) malloc(sizeof(unsigned long)*size);
	for (int i=0; i<_size; i++)
	{
		funcs[i] = NOP;
		intervals[i] = 0;
		begin_times[i] = 0;
	}
}

TimerPool::~TimerPool()
{
	free(funcs);
	free(intervals);
	free(begin_times);
}

void TimerPool::connect(byte slot, unsigned long interval, timerFunc func)
{
	funcs[slot] = func;
	intervals[slot] = interval;
	begin_times[slot] = millis();
}

void TimerPool::setInterval(byte slot, unsigned long interval)
{
	intervals[slot] = interval;
	begin_times[slot] = millis();
}

void TimerPool::update(void)
{
	unsigned long actual_time = millis();
	
	for (int i=0; i<_size; i++)
	{
	  long long delta_time = actual_time - begin_times[i];
	  if (delta_time < 0)
	  {
	    delta_time += 0xffffffff;
	    delta_time += 1;
	  }
		if (intervals[i] > 0 && delta_time >= intervals[i])
		{
			funcs[i]();
			begin_times[i] = actual_time;
		}
	}
}


LimitedTimerPool::LimitedTimerPool(void)
{
	for (int i=0; i<STATIC_SIZE; i++)
	{
		funcs[i] = NOP;
		intervals[i] = 0;
		begin_times[i] = 0;
	}
}

void LimitedTimerPool::connect(byte slot, unsigned long interval, timerFunc func)
{
	funcs[slot] = func;
	intervals[slot] = interval;
	begin_times[slot] = millis();
}

void LimitedTimerPool::setInterval(byte slot, unsigned long interval)
{
	intervals[slot] = interval;
	begin_times[slot] = millis();
}

void LimitedTimerPool::update(void)
{
	unsigned long actual_time = millis();
	
	for (int i=0; i<STATIC_SIZE; i++)
	{
	  long long delta_time = actual_time - begin_times[i];
	  if (delta_time < 0)
	  {
	    delta_time += 0xffffffff;
	    delta_time += 1;
	  }
		if (intervals[i] > 0 && delta_time >= intervals[i])
		{
			funcs[i]();
			begin_times[i] = actual_time;
		}
	}
}

