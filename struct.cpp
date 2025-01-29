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
