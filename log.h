#IF ! DEFINED (LOG_H)
#DEFINE LOG_H

#include <iostream>
#include <string>
#include "struct.h"
using namespace :stl

class Log: {
friend class Stats;
friend class Lecture;
public:
  ostream& operator<<(ostream& os, const Log& l)
  {
      os << ;
      return os;
  };
  Log ():
 IP(""), User_Logname(""), Auth_User(""), status(0), size(0), referer(""), id_client("")
    {
      TimeZone init_time_zone;
      Request_info init_request;
      init_time_zone.signe = 1;
      init_time_zone.hour = 0;
      init_time_zone.minute = 0;
      init_request.action = GET;
      init_request.url = "";
      init_request.protocol = "";
      init_request.extension = "";
      Date_time.day = 1;
      Date_time.month = JAN;
      Date_time.year = 0;
      Date_time.hour = 0;
      Date_time.minute = 0;
      Date_time.second = 0;
      Date_time.zone = init_time_zone;
    };
  virtual ~Log ();
  Log(const str log):{
    
  }
  
protected:
  str IP;
  str User_Logname;
  str Auth_User;
  Date Date_time;
  Request_info Request;
  int status;
  unsigned int size;
  str referer;
  str id_client;
};
#endif
