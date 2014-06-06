#include "Timers.h"

CTimers::CTimers()
{
  _elements = NULL;
  _length = 0;
}

CTimers::~CTimers()
{
  free(_elements);
}

uint8_t CTimers::every(uint32_t interval, timersFunc func)
{
  _attach(func, interval, false);
}

uint8_t CTimers::after(uint32_t interval, timersFunc func)
{
  _attach(func, interval, true);
}

bool CTimers::clear(uint8_t id)
{
  byte index = _getIndex(id);
  if (index == 255)
    return false;

  if (index != (_length-1))
  {
    memmove(_elements+index, _elements+index+1, (_length-1-index)*sizeof(struct TimersElement));
  }

  struct TimersElement *elements;
  elements = (struct TimersElement *) realloc(_elements, (_length-1)*sizeof(struct TimersElement));
  if (elements == NULL)
    return false;

  _elements = elements;
  _length--;
  return true;
}

bool CTimers::reset(uint8_t id, uint32_t interval)
{
  uint8_t index = _getIndex(id);
  if (index == 255)
    return false;

  _elements[index].interval = interval;
  _elements[index].last_time = millis();

  return true;
}

bool CTimers::update(uint8_t id, uint32_t interval)
{
  uint8_t index = _getIndex(id);
  if (index == 255)
    return false;

  _elements[index].interval = interval;

  return true;
}

uint8_t CTimers::length()
{
  return _length;
}

void CTimers::process()
{
  unsigned long actual_time = millis();
  
  for (int i=0; i<_length; i++)
  {
    unsigned long delta_time = actual_time - _elements[i].last_time;
    
    if (_elements[i].interval > 0 && delta_time >= _elements[i].interval)
    {
      _elements[i].func();
      _elements[i].last_time = actual_time;

      if (_elements[i].once)
        clear(_elements[i].id);
    }
  }
}

uint8_t CTimers::_attach(timersFunc func, uint32_t interval, bool once)
{
  uint8_t id = _getFreeId();
  if (id == 0)
    return 0;

  struct TimersElement *elements;
  elements = (struct TimersElement *) realloc(_elements, (_length+1)*sizeof(struct TimersElement));
  if (elements == NULL)
    return 0;

  _elements = elements;
  struct TimersElement *element = &_elements[_length];
  element->func = func;
  element->interval = interval;
  element->last_time = millis();
  element->once = once;
  element->id = id;

  _length++;
  return id;
}

bool CTimers::_anyId(uint8_t id)
{
  if (_length == 0)
    return false;

  for (uint8_t i=0; i<_length; i++)
  {
    if (_elements[i].id == id)
      return true;
  }

  return false;
}

uint8_t CTimers::_getFreeId()
{
  for (uint8_t i=1; i<255; i++)
  {
    if (!_anyId(i))
      return i;
  }

  return 0;
}

uint8_t CTimers::_getIndex(uint8_t id)
{
  for (uint8_t i=0; i<_length; i++)
  {
    if (_elements[i].id == id)
      return i;
  }

  return 255;
}

CTimers Timers;