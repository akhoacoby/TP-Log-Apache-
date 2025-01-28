#include "log.h"

Log::Log():IP(""), User_Logname(""), Auth_User(""), status(0), size(0), referer(""), id_client(""),
          Date_time({1, month::JAN, 0, 0, 0, 0, {1, 0, 0}}), Request({GET, "", "", ""})
          {};

Log::Log(const string log){
  istringstream stream(log);
  string temp;

  getline(stream, IP, ' ');
  getline(stream, User_Logname, ' ');
  getline(stream, Auth_User, ' ');

  getline(stream, temp, '[');
  getline(stream, temp, ']');
  istringstream dateStream(temp);
  char delimiter;
  dateStream >> Date_time.day >> delimiter;
  string monthStr;
  dateStream >> monthStr >> delimiter;      // Sep/
  if (monthStr == "Jan") {
    Date_time.month = month::JAN;
  }
  else if (monthStr == "Feb") {
    Date_time.month = month::FEB;
  }
  else if (monthStr == "Mar") {
    Date_time.month = month::MAR;
  }
  else if (monthStr == "Apr") {
    Date_time.month = month::APR;
  }
  else if (monthStr == "May") {
    Date_time.month = month::MAY;
  }
  else if (monthStr == "Jun") {
    Date_time.month = month::JUN;
  }
  else if (monthStr == "Jul") {
    Date_time.month = month::JUL;
  }
  else if (monthStr == "Aug") {
    Date_time.month = month::AUG;
  }
  else if (monthStr == "Sep") {
    Date_time.month = month::SEP;
  }
  else if (monthStr == "Oct") {
    Date_time.month = month::OCT;
  }
  else if (monthStr == "Nov") {
    Date_time.month = month::NOV;
  }
  else if (monthStr == "Dec") {
    Date_time.month = month::DEC;
  }
  else {
    throw invalid_argument("Invalid month string: " + monthStr);
}
  dateStream >> Date_time.year >> delimiter;
  dateStream >> Date_time.hour >> delimiter;
  dateStream >> Date_time.minute >> delimiter;
  dateStream >> Date_time.second;
  dateStream >> timeZone;
  if (timeZone[0] == '+') {
    Date_time.zone.signe = 1;
  }
  else if (timeZone[0] == '-') {
      Date_time.zone.signe = -1;
  }
  else {
      throw invalid_argument("Invalid time zone format: " + timeZone);
  }

Date_time.zone.hour = stoi(timeZone.substr(1, 2));
Date_time.zone.minute = stoi(timeZone.substr(3, 2));

stream >> status;
stream >> size;

getline(stream, temp, '"');
getline(stream, referer, '"');

getline(stream, temp, '"');
getline(stream, id_client, '"');
}

ostream& operator<<(ostream& os, const Log& l) {
    os << "IP: " << l.IP << endl
       << "User Logname: " << l.User_Logname << endl
       << "Auth User: " << l.Auth_User << endl
       << "Date: " << l.Date_time.day << "/"
       << l.Date_time.month << "/"
       << l.Date_time.year << " "
       << l.Date_time.hour << ":"
       << l.Date_time.minute << ":"
       << l.Date_time.second << endl
       << "Time zone: " << l.Date_time.zone.signe << " "
       << l.Date_time.zone.hour << ":"
       << l.Date_time.zone.minute << endl
       << "Request: " << l.Request.action << " "
       << l.Request.url << " "
       << l.Request.protocol << endl
       << "Status: " << l.status << endl
       << "Size: " << l.size << endl
       << "Referer: " << l.referer << endl
       << "ID Client: " << l.id_client;

    return os;
}
