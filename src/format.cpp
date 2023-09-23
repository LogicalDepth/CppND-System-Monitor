#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    
    int sec , min , hrs;
    sec = seconds % 60;
    min = (seconds / 60) % 60;
    hrs = seconds / (60*60);
    
   string hh , mm , ss;

   hh =   (hrs < 10) ? "0" + std::to_string(hrs) +":" : std::to_string(hrs) + ":" ;
   mm =   (min < 10) ? "0" + std::to_string(min) +":" : std::to_string(min) + ":"  ;
   ss =   (sec < 10) ? "0" + std::to_string(sec) : std::to_string(sec)  ;
   string hms = hh+mm+ss;
    return hms;
     }