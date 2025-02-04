#include "simplelog.h"

SimpleLog::SimpleLog():Date_time({1, Month::JAN, 0, 0, 0, 0, {1, 0, 0}}), Request({Action_type::GET, "-", "-", "-"}),
          referer("-"){
}

SimpleLog::SimpleLog(const Log & log) {
    this->Date_time = log.Date_time;
    this->Request = log.Request;
    string row_referer = log.referer;
    int dot = 0;
    for (long unsigned int i = row_referer.length() - 1; i >= 0; i--){
        if (row_referer[i] == '.'){
          if (dot == 0){
            dot = i;
          }
          else{
            dot = i;
            break;
          }
        }
    }
    this->referer = row_referer.erase(0,dot + 3);
}

SimpleLog::~SimpleLog() {
}

ostream& operator<<(ostream& os, const SimpleLog l) {
    os << "Date: " << l.Date_time.day << "/"
       << l.Date_time.month << "/"
       << l.Date_time.year << " "
       << l.Date_time.hour << ":"
       << l.Date_time.minute << ":"
       << l.Date_time.second << endl;
    if (l.Date_time.zone.signe >= 0){
      os << "Time zone: " << "+" << " ";
    }
    else{
      os << "Time zone: " << "-" << " ";
    }
    os << l.Date_time.zone.hour << ":"
       << l.Date_time.zone.minute << endl
       << "Request: " << l.Request.action << " "
       << l.Request.url << " "
       << l.Request.protocol << endl
       << "Page extension: " << l.Request.extension << endl
       << "Referer: " << l.referer << "\n" << endl;
    return os;
}
