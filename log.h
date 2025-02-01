#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "struct.h"
using namespace std;

class Log {
  friend class Stats;
  friend class Lecture;
  friend class SimpleLog;
  friend ostream& operator<<(ostream& os, const Log l);
public:
  Log();
  Log(const string log);
  virtual ~Log ();
protected:
  string IP;
  string User_Logname;
  string Auth_User;
  Date Date_time;
  Request_info Request;
  int status;
  unsigned int size;
  string referer;
  string id_client;
};
#endif
