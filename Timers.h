#ifndef timers_h
#define timers_h

#include "Arduino.h"
#include <inttypes.h>

typedef void (*timersFunc)(void);

struct TimersElement
{
  timersFunc func;
  uint32_t interval;
  uint32_t last_time;
  bool once;
  uint8_t id;
};

class CTimers
{
private:
  struct TimersElement *_elements;
  uint8_t _length;

  bool _anyId(uint8_t id);
  uint8_t _getFreeId();
  uint8_t _getIndex(uint8_t id);
  uint8_t _attach(timersFunc func, uint32_t interval, bool once=false);

public:
  CTimers();
  ~CTimers();
  uint8_t every(uint32_t interval, timersFunc func);
  uint8_t after(uint32_t interval, timersFunc func);
  bool clear(uint8_t id);
  bool reset(uint8_t id, uint32_t interval);
  bool update(uint8_t id, uint32_t interval);
  uint8_t length();
  void process();
};

extern CTimers Timers;

#endif