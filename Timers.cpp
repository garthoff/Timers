#include "Timers.h"

void NOP(void)
{
	return;
}


TimerPool::TimerPool(byte size)
{
	_size = size;
	_elements = (TimerElement *) malloc(sizeof(TimerElement)*size);

	for (int i=0; i<_size; i++)
	{
		_elements[i].func = NOP;
		_elements[i].interval = 0;
		_elements[i].begin_time = 0;
	}
}

TimerPool::~TimerPool()
{
	free(_elements);
}

void TimerPool::connect(byte slot, unsigned long interval, timerFunc func)
{
	_elements[slot].func = func;
	_elements[slot].interval = interval;
	_elements[slot].begin_time = millis();
}

void TimerPool::setInterval(byte slot, unsigned long interval)
{
	_elements[slot].interval = interval;
	_elements[slot].begin_time = millis();
}

void TimerPool::update(void)
{
	unsigned long actual_time = millis();
	
	for (int i=0; i<_size; i++)
	{
		long long delta_time = actual_time - _elements[i].begin_time;

		if (delta_time < 0)
		{
			delta_time += 0xffffffff;
			delta_time += 1;
		}
		if (_elements[i].interval > 0 && delta_time >= _elements[i].interval)
		{
			_elements[i].func();
			_elements[i].begin_time = actual_time;
		}
	}
}


LimitedTimerPool::LimitedTimerPool(void)
{
	for (int i=0; i<STATIC_SIZE; i++)
	{
		_elements[i].func = NOP;
		_elements[i].interval = 0;
		_elements[i].begin_time = 0;
	}
}

void LimitedTimerPool::connect(byte slot, unsigned long interval, timerFunc func)
{
	_elements[slot].func = func;
	_elements[slot].interval = interval;
	_elements[slot].begin_time = millis();
}

void LimitedTimerPool::setInterval(byte slot, unsigned long interval)
{
	_elements[slot].interval = interval;
	_elements[slot].begin_time = millis();
}

void LimitedTimerPool::update(void)
{
	unsigned long actual_time = millis();
	
	for (int i=0; i<STATIC_SIZE; i++)
	{
	  long long delta_time = actual_time - _elements[i].begin_time;
	  
	  if (delta_time < 0)
	  {
	    delta_time += 0xffffffff;
	    delta_time += 1;
	  }
		if (_elements[i].interval > 0 && delta_time >= _elements[i].interval)
		{
			_elements[i].func();
			_elements[i].begin_time = actual_time;
		}
	}
}

