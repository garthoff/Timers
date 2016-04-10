#include "Timers.h"


void Timer::restart()
{
  _lastTime = millis();
}

void Timer::begin(const uint32_t interval)
{
  time(interval);
  restart();
}

bool Timer::available()
{
  if (_time == 0)
  {
    return false;
  }

  uint32_t actualTime = millis();
  uint32_t deltaTime = actualTime - _lastTime;
  if (deltaTime >= _time)
  {
    return true;
  }

  return false;
}

uint32_t Timer::time()
{
  if (_time == 0)
  {
    return 0;
  }

  uint32_t actualTime = millis();
  uint32_t deltaTime = actualTime - _lastTime;

  return _time - deltaTime;
}

void Timer::time(const uint32_t interval)
{
  _time = interval;
}
