#include "struct.h"

ostream& operator<<(ostream& os, const Month month) {
  switch (month) {
    case Month::JAN:
      os << "January";
      break;
    case Month::FEB:
      os << "February";
      break;
    case Month::MAR:
      os << "March";
      break;
    case Month::APR:
      os << "April";
      break;
    case Month::MAY:
      os << "May";
      break;
    case Month::JUN:
      os << "June";
      break;
    case Month::JUL:
      os << "July";
      break;
    case Month::AUG:
      os << "August";
      break;
    case Month::SEP:
      os << "September";
      break;
    case Month::OCT:
      os << "October";
      break;
    case Month::NOV:
      os << "November";
      break;
    case Month::DEC:
     os << "December";
     break;
   }
   return os;
};

ostream& operator<<(ostream& os, const Action_type action) {
  switch (action) {
    case Action_type::GET:
      os << "GET";
      break;
    case Action_type::POST:
      os << "POST";
      break;
    case Action_type::OPTIONS:
      os << "OPTIONS";
      break;
    case Action_type::HEAD:
      os << "HEAD";
      break;
    case Action_type::PROPFIND:
      os << "PROPFIND";
      break;
   }
   return os;
};

bool Date::isLeapYear(int y){
  if (y % 400 == 0){
    return true;
  }
  else if (y % 4 == 0 && y % 100 != 0){
    return true;
  }
  else{
    return false;
  }
};

int Date::daysInMonth(Month m, int y) {
    switch (m) {
        case Month::JAN: case Month::MAR: case Month::MAY: case Month::JUL:
        case Month::AUG: case Month::OCT: case Month::DEC:
            return 31;
        case Month::APR: case Month::JUN: case Month::SEP: case Month::NOV:
            return 30;
        case Month::FEB:
          if (isLeapYear(y)){
            return 29;
          }
          else{
            return 28;
          }
        default:
          return 31;
    }
};

string Date::to_string(){
  int time = hour * 3600 + minute * 60 + second;
  int temp_day = day;
  Month temp_month = month;
  int temp_year = year;
  int jet_lag = zone.signe * (zone.hour * 3600 + zone.minute * 60);
  int absolute_time = time + jet_lag;

  if (absolute_time >= 24 * 3600) {
    absolute_time -= 24 * 3600;
    temp_day++;


    if (temp_day > daysInMonth(temp_month, temp_year)) {
      temp_day = 1;
      temp_month = static_cast<Month>(static_cast<int>(temp_month) + 1);

      if (temp_month > Month::DEC) {
          temp_month = Month::JAN;
          temp_year++;
      }
    }
  }
  else if (absolute_time < 0) {
    absolute_time += 24 * 3600;
    temp_day--;


    if (temp_day == 0) {
      temp_month = static_cast<Month>(static_cast<int>(temp_month) - 1);

      if (temp_month < Month::JAN) {
          temp_month = Month::DEC;
          temp_year--;
      }
      temp_day = daysInMonth(temp_month, temp_year);
    }
  }


int new_hour = absolute_time / 3600;
int new_minute = (absolute_time % 3600) / 60;
int new_second = absolute_time % 60;


return (std::to_string(temp_day) + "/" + std::to_string(static_cast<int>(temp_month)) + "/" +
            std::to_string(temp_year) + " " + std::to_string(new_hour) + ":" +
            std::to_string(new_minute) + ":" + std::to_string(new_second));
};
