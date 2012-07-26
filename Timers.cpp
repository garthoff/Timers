#include "Timers.h"

void NOP(void)
{
	return;
}

Timers::Timers(void)
{
	for (int i=0; i<TIMER_ITEMS; i++)
	{
		_elements[i].func = NOP;
		_elements[i].interval = 0;
		_elements[i].begin_time = 0;
	}
}

void Timers::attach(byte slot, unsigned long interval, timerFunc func)
{
	_elements[slot].func = func;
	_elements[slot].interval = interval;
	_elements[slot].begin_time = millis();
}

void Timers::setInterval(byte slot, unsigned long interval)
{
	_elements[slot].interval = interval;
	_elements[slot].begin_time = millis();
}

void Timers::process(void)
{
	unsigned long actual_time = millis();
	
	for (int i=0; i<TIMER_ITEMS; i++)
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

