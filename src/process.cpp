#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

 //Constructor for Process Class
 Process::Process(int pid) {
   PID = pid;
   cmdline = LinuxParser::Command(pid);
   username = LinuxParser::User(pid);
   std::string Ram = LinuxParser::Ram(pid);
   ram = std::stoi(Ram);
   uptime = LinuxParser::UpTime(pid);

   
   long total_time = LinuxParser::ActiveJiffies(pid);
   long seconds = LinuxParser::UpTime() - uptime;
   cpu_usage = ((float)total_time/(float)seconds);

 }


//Returns the PID
int Process::Pid() const{ return PID; }


//Return this process's CPU utilization
float Process::CpuUtilization() const { 
  return cpu_usage;
 }


//Return the command that generated this process
string Process::Command() { 
  return cmdline;
}

//Return this process's memory utilization
string Process::Ram() { 
  
   return to_string(ram);

    }

//Return the user (name) that generated this process
string Process::User() { 
   return username;
}


// Return the age of this process (in seconds)
long int Process::UpTime() { return uptime;}


//Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { return this->CpuUtilization() < a.CpuUtilization(); }

bool Process::operator>(Process const& a) const { return this->CpuUtilization() > a.CpuUtilization(); }



