#include "processor.h"
#include "linux_parser.h"

/*  -------------------------------------------Logic Implemented------------------------------------------------

PrevIdle = previdle + previowait
Idle = idle + iowait

PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
NonIdle = user + nice + system + irq + softirq + steal

PrevTotal = PrevIdle + PrevNonIdle
Total = Idle + NonIdle

# differentiate: actual value minus the previous one
totald = Total - PrevTotal
idled = Idle - PrevIdle 

CPU_Percentage = (totald - idled)/totald */

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
     long C_Active , C_Idle , C_Total , P_Total , P_Idle;

     C_Active = CurrentActive();
     C_Idle = CurrentIdle();
     C_Total = CurrentTotal();

     P_Idle = PrevIdle();
     P_Total = PrevTotal();

     Update(C_Active , C_Idle , C_Total);

     float TotalD = (float)C_Total - (float)P_Total;
     float IdleD = (float)C_Idle - (float)P_Idle;

     float Percentage = (TotalD - IdleD)/TotalD;
     return Percentage; 
}
 
 long Processor::CurrentActive () {return LinuxParser::ActiveJiffies();}
 long Processor::CurrentIdle() {return LinuxParser::IdleJiffies();}
 long Processor::CurrentTotal() {return LinuxParser::Jiffies();}

 long Processor::PrevIdle() {return M_Idle;}
 long Processor::PrevTotal() {return M_Total;}
   
void Processor::Update(long C_Active , long C_Idle , long C_Total) {
     M_Active = C_Active;
     M_Idle = C_Idle;
     M_Total = C_Total;
}

























