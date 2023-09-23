#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
 Process(int pid);
  int Pid() const;                               // TODO: See src/process.cpp
  std::string User() ;                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization() const;                  // TODO: See src/process.cpp
  std::string Ram() ;                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  bool operator>(Process const& a) const;
  

  // TODO: Declare any necessary private members
 private:
 int PID {0};
 std::string cmdline="";
 std::string username="";
 int ram {0};
 float cpu_usage {0.0};
 long uptime {0};
 
 
};

#endif