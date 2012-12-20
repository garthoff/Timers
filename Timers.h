#include "Arduino.h"

#ifndef timers_h
#define timers_h

typedef void (*timerFunc)(void);
typedef void (*timerEventFunc)(byte);

void NOP(void)
{
  return;
}

void NOP2(byte slot)
{
  return;
}

struct TimerElement
{
  timerFunc func;
  unsigned long interval;
  unsigned long begin_time;
};


template<byte TIMER_ITEMS>
class Timers
{
  private:
    struct TimerElement _elements[TIMER_ITEMS];
    
  public:
    timerEventFunc onTime;

    Timers(void)
    {
      for (int i=0; i<TIMER_ITEMS; i++)
      {
        _elements[i].func = NOP;
        _elements[i].interval = 0;
        _elements[i].begin_time = 0;
      }

      onTime = NOP2;
    }

    void attach(byte slot, unsigned long interval, timerFunc func)
    {
      _elements[slot].func = func;
      _elements[slot].interval = interval;
      _elements[slot].begin_time = millis();
    }

    void setInterval(byte slot, unsigned long interval)
    {
      _elements[slot].interval = interval;
      _elements[slot].begin_time = millis();
    }

    void process(void)
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
          onTime(i);
          _elements[i].func();
          _elements[i].begin_time = actual_time;
        }
      }
    }
};

#endif
