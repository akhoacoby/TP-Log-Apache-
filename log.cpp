#include "log.h"

Log::Log():IP(""), User_Logname(""), Auth_User(""), Date_time({1, Month::JAN, 0, 0, 0, 0, {1, 0, 0}}), Request({Action_type::GET, "", "", ""}),
          status(0), size(0), referer(""), id_client("")
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
  string datePart, timePart;
  getline(dateStream, datePart, ' '); // Get the date in format DD/MON/YYYY
  getline(dateStream, timePart, ' '); // Get the time in format :HH:MM:SS
  timePart.erase(0,1); // Change time format to HH:MM:SS

  // DATE //
  istringstream datePartStream(datePart);
  string dayStr, monthStr, yearStr;
  getline(datePartStream, dayStr, '/');
  getline(datePartStream, monthStr, '/');
  getline(datePartStream, yearStr,':');
  Date_time.day = stoi(dayStr);
  if (monthStr == "Jan") Date_time.month = Month::JAN;
  else if (monthStr == "Feb") Date_time.month = Month::FEB;
  else if (monthStr == "Mar") Date_time.month = Month::MAR;
  else if (monthStr == "Apr") Date_time.month = Month::APR;
  else if (monthStr == "May") Date_time.month = Month::MAY;
  else if (monthStr == "Jun") Date_time.month = Month::JUN;
  else if (monthStr == "Jul") Date_time.month = Month::JUL;
  else if (monthStr == "Aug") Date_time.month = Month::AUG;
  else if (monthStr == "Sep") Date_time.month = Month::SEP;
  else if (monthStr == "Oct") Date_time.month = Month::OCT;
  else if (monthStr == "Nov") Date_time.month = Month::NOV;
  else if (monthStr == "Dec") Date_time.month = Month::DEC;
  else {
      throw invalid_argument("Invalid Month string: " + monthStr);
    }
  Date_time.year = stoi(yearStr);

  // TIME
  istringstream timePartStream(timePart);
  string hourStr, minuteStr, secondStr, timeZone;
  getline(timePartStream, hourStr, ':');
  getline(timePartStream, minuteStr, ':');
  getline(timePartStream, secondStr, ':');
  getline(dateStream, timeZone, ' ');
  Date_time.hour = stoi(hourStr);
  Date_time.minute = stoi(minuteStr);
  Date_time.second = stoi(secondStr);

  //TIMEZONE
  if (timeZone[0] == '+') {
      Date_time.zone.signe = 1;
  } else if (timeZone[0] == '-') {
      Date_time.zone.signe = -1;
  } else {
      throw invalid_argument("Invalid time zone format: " + timeZone);
  }
  Date_time.zone.hour = stoi(timeZone.substr(1, 2));
  Date_time.zone.minute = stoi(timeZone.substr(3, 2));

  //REQUEST
  string actionStr, urlStr, protocolStr;
  stream >> actionStr;
  actionStr.erase(0,1);
  stream >> urlStr;
  getline(stream, protocolStr, '"');
  protocolStr.erase(0,1);

  Request.url = urlStr;

  int dot = 0;
  for (long unsigned int i=0; i<urlStr.length(); i++){
      if (urlStr[i] == '.'){
        dot = i;
      }
  }

  Request.protocol = protocolStr;
  Request.extension = urlStr.erase(0,dot + 1);
  if (actionStr == "GET") {
    Request.action = Action_type::GET;
  }
  else if (actionStr == "POST") {
    Request.action = Action_type::POST;
  }
  else if (actionStr == "OPTIONS") {
    Request.action = Action_type::OPTIONS;
  }
  else if (actionStr == "HEAD") {
    Request.action = Action_type::HEAD;
  }
  else if (actionStr == "PROPFIND") {
    Request.action = Action_type::PROPFIND;
  } else {
    throw invalid_argument("Invalid Action string: " + actionStr);
}

  string statusStr, sizeStr;
  stream >> statusStr;
  stream >> sizeStr;
  status = stoi(statusStr);
  size = stoi(sizeStr);

  getline(stream, temp, '"');
  getline(stream, referer, '"');

  getline(stream, temp, '"');
  getline(stream, id_client, '"');
}

Log::~Log() {}

ostream& operator<<(ostream& os, const Log l) {
    os << "IP: " << l.IP << endl
       << "User Logname: " << l.User_Logname << endl
       << "Auth User: " << l.Auth_User << endl
       << "Date: " << l.Date_time.day << "/"
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
       << "Status: " << l.status << endl
       << "Size: " << l.size << endl
       << "Referer: " << l.referer << endl
       << "ID Client: " << l.id_client << endl;

    return os;
}
