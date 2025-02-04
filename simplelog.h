#ifndef SIMPLE_LOG_H
#define SIMPLE_LOG_H

#include "log.h"

class SimpleLog {
  friend class Stats;
  friend class Lecture;
  friend class Log;
  friend ostream& operator<<(ostream& os, const SimpleLog l);
public:
    SimpleLog();
    SimpleLog(const Log& log);
    ~SimpleLog();
protected:
    Date Date_time;
    Request_info Request;
    string referer;
};
#endif
