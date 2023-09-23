#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
/*You need to complete the mentioned TODOs in order to satisfy the rubric criteria "The student will be able to extract and display basic data about the system."

You need to properly format the uptime. Refer to the comments mentioned in format. cpp for formatting the uptime.*/

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }




// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
  processes_.clear();
  std::vector <int> ids = LinuxParser::Pids();
  for(long unsigned i = 0 ; i < ids.size(); i++) {
    if(!LinuxParser::Ram(ids[i]).empty()){
      Process PS(ids[i]);
      processes_.push_back(PS);
  }
  }
  std::sort(processes_.rbegin() , processes_.rend());
  //sort (processes_.begin() , processes_.end() , [](Process const& a , Process const& b){return a.CpuUtilization() < b.CpuUtilization();});
  return processes_;

}


// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
    std::string os , version , kernel;
    std::string line;
    std::ifstream stream (LinuxParser::kProcDirectory + LinuxParser::kVersionFilename);
    
    if(stream.is_open()){
        std::getline(stream , line);
        std::istringstream linestream(line);
        linestream >> os >> version >> kernel;
    }
    return kernel;
    }
    
    
    
    

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
return LinuxParser::MemoryUtilization();
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    string line;
    string key;
    string value;
     std::ifstream stream (LinuxParser::kOSPath);
    if(stream.is_open()){ 
      while(std::getline(stream , line)) {
        std::replace(line.begin() , line.end() , ' ','_');
        std::replace(line.begin() , line.end() , '=',' ');
        std::replace(line.begin() , line.end() , '"', ' ');
     
        std::istringstream linestream(line);
        while(linestream >> key >> value){
          if(key == "PRETTY_NAME")
          std::replace(value.begin() ,value.end() ,'_' , ' ');
          return value;
        }
      }
    }
return value; 
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }
