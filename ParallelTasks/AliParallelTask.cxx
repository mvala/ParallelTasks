//
// Class AliParallelTask
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#include <TThread.h>
#include <TStopwatch.h>
#include <TH1.h>
#include "AliParallelTask.h"

ClassImp(AliParallelTask)

//_________________________________________________________________________________________________
AliParallelTask::AliParallelTask(const char *name, const char *title) :
   TTask(name, title),
   fThread(0),
   fCondition(0),
   fMaxNum(1)
{
   //
   // Std constructor
   //
}

//_________________________________________________________________________________________________
AliParallelTask::~AliParallelTask()
{
   //
   // Destructor
   //
   ThreadStop();
}

//_________________________________________________________________________________________________
AliParallelTask::AliParallelTask(const AliParallelTask &obj) :
   TTask(obj),
   fThread(obj.fThread),
   fCondition(),
   fMaxNum(obj.fMaxNum)

{
   //
   // Copy constructor
   //
}

//_________________________________________________________________________________________________
AliParallelTask &AliParallelTask::operator=(const AliParallelTask &obj )
{
   //
   // Assigned operator
   //

   if (&obj != this) {
      TTask::operator=(obj);
      fThread = obj.fThread;
//       fCondition = obj.fCondition;
      fMaxNum = obj.fMaxNum;

   }
   return *this;

}

//_________________________________________________________________________________________________
void AliParallelTask::Exec(Option_t *option)
{
   //
   // Exec of manager task
   //


   TTask::Exec(option);

   TStopwatch timer;
   timer.Start();

   Int_t numThreads = TThread::Exists();
   Printf("Running %s::Exec(\"%s\") fMaxNum=%lld [START] %d",GetName(),option,fMaxNum, numThreads);
   Long64_t sum = 0;
   TH1D h("h","Hist",100,-10,10);
   h.SetDirectory(0);
   h.FillRandom("gaus",fMaxNum);

   numThreads = TThread::Exists();
   if (numThreads<0) numThreads=0;
   Printf("Running %s::Exec(\"%s\") fMaxNum=%lld  [DONE] %d",GetName(),option,fMaxNum, numThreads);
   timer.Stop();
//   timer.Print();

}

Int_t AliParallelTask::ThreadStart()
{
   if (!IsActive()) return 0;

   if (!fThread) {
      fThread = new TThread(GetName(),(void( *) (void *))&Thread0,(void *)this);
//      Printf("Starting thread %s ...",GetName());
      gSystem->Sleep(10);
      fThread->Run();
      return 0;
   }
   return 1;
}

Int_t AliParallelTask::ThreadStop()
{
   if (!IsActive()) return 0;

   if (fThread) {
//      Printf("Stoping thread %s ...",GetName());
      TThread::Delete(fThread);
      gSystem->Sleep(10);
      delete fThread;
      fThread = 0;
      return 0;
   }
   return 1;
}

void *AliParallelTask::Thread0(void *arg)
{
   AliParallelTask *task = (AliParallelTask *)arg;
   if (task) {
      if (task->IsActive())  {
         task->Exec(task->GetOption());
         task->ThreadStop();
      }
   }
   return 0;
}
