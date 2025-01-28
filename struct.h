#ifndef STRUCT_H
#define STRUCT_H

#include <string>
using namespace std;

typedef struct time_zone {
    int signe;   // +1 ou -1 
    unsigned int hour; // déclage en valeur absolue
    unsigned int minute;  
} TimeZone;

enum class Month {
    JAN = 1,    
    FEB = 2,   
    MAR = 3,  
    APR = 4,    
    MAY = 5,    
    JUN = 6,    
    JUL = 7,   
    AUG = 8,    
    SEP = 9,    
    OCT = 10,   
    NOV = 11,  
    DEC = 12  
}; 

typedef struct Date {
    unsigned int day;  
    Month month;       
    int year;           
    unsigned int hour;  
    unsigned int minute; 
    unsigned int second; 
    TimeZone zone;      
} Date;

enum class Action_type {
    GET = 1,
    POST = 2,
    OPTIONS = 3,
    HEAD = 4,
    PROPFIND = 5,
};

typedef struct Request_info {
    Action_type action;
    string url;
    string protocol;
    string extension;
} Request_info;

#endif
