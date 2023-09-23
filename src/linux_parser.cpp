 #include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>


#include "linux_parser.h"
#include "format.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;



// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}



// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}




// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}




// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 

 float Mem_total = 0.0 , Mem_free = 0.0;
 std::string line ;
 std::string title ;

 std::ifstream getdata (kProcDirectory + kMeminfoFilename);
 if(getdata.is_open()){
  while (getline(getdata , line)){
    std::istringstream data (line);
    data >> title ;

    if(title == "MemTotal:") {
      data >> Mem_total;
    }

    else if(title == "MemAvailable:") {
      data >> Mem_free ;
      break;
    }
    }
  getdata.close();
 }
   return (Mem_total - Mem_free)/Mem_total;
   }



// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
std::string line;
 std::string sys_uptime;
long uptime;
  std::ifstream getdata (kProcDirectory + kUptimeFilename);
  if(getdata.is_open()) {
    std::getline(getdata , line );
      std::istringstream data(line);
      data >> sys_uptime ;
    }
    uptime = std::stol(sys_uptime);
  return uptime;
 }



// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {  
  std::vector<string> Jiff = LinuxParser::CpuUtilization();
  long total_sys_jiffies;
    for(size_t i=1; i<Jiff.size(); i++)
    {
      
        total_sys_jiffies += std::stol(Jiff[i]);
    }
    return total_sys_jiffies;
 }



// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 

  long Pid_jiffies;
  std::vector<string> jiffies;
  std::string line , jif;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if(stream.is_open()) 
  {
    std::getline(stream , line);
    std::istringstream data (line);
    while (data >> jif)
    {
      jiffies.emplace_back(jif);
    }
  }
    
    
  Pid_jiffies = std::stol(jiffies[Process_States::kUtime]) +
                std::stol(jiffies[Process_States::kStime]) +
                std::stol(jiffies[Process_States::kCutime]) +
                std::stol(jiffies[Process_States::kCstime]) ;
  
  return Pid_jiffies/sysconf(_SC_CLK_TCK);
}




// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  std::vector<string> Jiff = LinuxParser::CpuUtilization();
  long Active_Jiffies;
  for(size_t i = 0; i < Jiff.size(); i++){
    if(i != CPUStates::kIdle_ && i != CPUStates::kIOwait_) {
        Active_Jiffies += std::stol(Jiff[i]);
  
  }} 
  return Active_Jiffies;
 }



//Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  std::vector<string> Jiff = LinuxParser::CpuUtilization();
  long idle_Jiffies;
  idle_Jiffies = std::stol(Jiff[CPUStates::kIdle_]) +std::stol(Jiff[CPUStates::kIOwait_]);
  return idle_Jiffies;
  }




//Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {   
  std::string line;
  std::vector<string> cpu_stats;
  std::string CPU , jif;
  std::ifstream getdata(kProcDirectory + kStatFilename);
  if(getdata.is_open()) {
    std::getline(getdata , line);
    std::istringstream data (line);
    data >> CPU;
      while (data >> jif){
        cpu_stats.emplace_back(jif);
      }
    }
      getdata.close();
    return cpu_stats;
}



//Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  std::string line , title , value;
  int T_process, cont;

  
  std::ifstream getdata (kProcDirectory + kStatFilename);
  if(getdata.is_open()) {
    while(getline(getdata , line)){
      std::istringstream data (line);
      data >> title >> value;
      if(title == "processes"){
        T_process =std::stoi(value);
        ++cont;
      }
      if(cont == 1)
      break;
    }
    return T_process;
  }
  getdata.close();
  return 0;
}


// Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  std::string line , title , value;
  int R_process;
  std::ifstream getdata (kProcDirectory + kStatFilename);
  if(getdata.is_open()) {
    while(getline(getdata , line)){
      std::istringstream data (line);
      data >> title;
      if(title == "procs_running"){
        data >> value;
        R_process =std::stoi(value);
        break;
      }
    }
    }
  
  return R_process;
} 

// TODO: Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
std::string Command;
    std::ifstream stream (kProcDirectory + to_string(pid) + kCmdlineFilename);
  if(stream.is_open()){
    std::getline(stream , Command);
   
  }
  stream.close();
  return Command;
 }



//Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  
  std::string getdata , Ram , size;
  long mem, Vmrss , Vmswap;
  std::ifstream stream (LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kStatusFilename);
  if(stream.is_open()) {
   while( std::getline(stream , getdata)) {
    std::istringstream line (getdata);
    line >> Ram ; 
     
      if(Ram == "VmRSS:") {
        line >> Vmrss; 
      }
      else if(Ram == "VmSwap:") 
      {
        line >> Vmswap;
        break;
      }
   }
  }
  mem = Vmrss + Vmswap;
  mem /= 1024;
  size = std::to_string(mem);
    return size; 
  }



//Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
  
  std::string getdata;
  std::string uid , key;
  std::ifstream stream (LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kStatusFilename);
  if(stream.is_open()) {
    while(std::getline(stream , getdata)) {
    std::istringstream line (getdata);
    line >> key ;
      if(key == "Uid:"){
        line >> uid;
       break;
      }
    }
  }
  return uid;
}


//Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  
  std::string getdata ;
  std::string user , id , x;
  std::string name = "DF";
  std::ifstream stream(kPasswordPath);
  std::string uid = LinuxParser::Uid(pid);
  if(stream.is_open()) {
     while(std::getline(stream , getdata)) {
      
        std::replace(getdata.begin() , getdata.end() , ':' , ' ');
        std::istringstream line(getdata);
        line >> user >> x >>id;
          if(id == uid) {
            name = user;
            break;
        }
      }
  }
 
  return name;
   }




// Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
  long time {0};
  std::vector<string> stats;
  std::string line , jif;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if(stream.is_open()) 
  {
    std::getline(stream , line);
    std::istringstream data (line);
    while (data >> jif)
    {
      stats.emplace_back(jif);
    }
  }
    time = (std::stol(stats[Process_States::kStarttime]))/sysconf(_SC_CLK_TCK);

  
   return time;
}
