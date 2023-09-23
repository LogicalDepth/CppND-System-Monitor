#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // See src/processor.cpp
  
  long CurrentActive();
  long CurrentIdle();
  long CurrentTotal();

  long PrevIdle();
  long PrevTotal();

  void Update (long m_active , long m_idle , long m_total);

  //Declare any necessary private members
 private:
 long M_Total {0} , M_Idle {0} , M_Active {0};
};

#endif