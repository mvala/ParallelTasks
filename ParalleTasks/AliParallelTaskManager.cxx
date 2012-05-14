//
// Class AliParallelTaskManager
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//
#include <TThread.h>
#include <TStopwatch.h>

#include "AliParallelTaskManager.h"
#include "AliParallelTask.h"

ClassImp(AliParallelTaskManager)

//_________________________________________________________________________________________________
AliParallelTaskManager::AliParallelTaskManager(const char *name, const char *title,Bool_t isParallel) :
   TTask(name, title),
   fMaxThreads(-1),
   fIsRunningParallel(isParallel)
{
   //
   // Std constructor
   //
}

//_________________________________________________________________________________________________
AliParallelTaskManager::~AliParallelTaskManager()
{
   //
   // Destructor
   //
}

//_________________________________________________________________________________________________
AliParallelTaskManager::AliParallelTaskManager(const AliParallelTaskManager &obj) :
   TTask(obj),
   fMaxThreads(obj.fMaxThreads),
   fIsRunningParallel(obj.fIsRunningParallel)
{
   //
   // Copy constructor
   //
}

//_________________________________________________________________________________________________
AliParallelTaskManager &AliParallelTaskManager::operator=(const AliParallelTaskManager &obj )
{
   //
   // Assigned operator
   //
   if (&obj != this) {
      TTask::operator=(obj);
      fMaxThreads = obj.fMaxThreads;
      fIsRunningParallel = obj.fIsRunningParallel;
   }
   return *this;
}

//_________________________________________________________________________________________________
void AliParallelTaskManager::Exec(Option_t *option)
{
   //
   // Exec of manager task
   //

   TTask::Exec(option);

   if (fIsRunningParallel) {
      if (fMaxThreads<=0) {
         SysInfo_t s;
         if (!gSystem->GetSysInfo(&s)) fMaxThreads = s.fCpus;
         else fMaxThreads = 1;
      }
   } else {
      fMaxThreads = 1;
   }

   // let finish last thread from prefious group
   while (TThread::Exists()>0) {
      gSystem->Sleep(100);
   }

   Int_t numThreads = TThread::Exists();
   Printf("Running Manager %s::Exec(\"%s\") [START] %d/%d",GetName(),option,numThreads,fMaxThreads);
   TIter next(GetListOfTasks());
   TObject *o;
   AliParallelTask *task;
   AliParallelTaskManager *taskMgr;
   while ((o = (TObject *)next())) {

      // check if max thread was reached
      while (TThread::Exists()>=fMaxThreads) {
         gSystem->Sleep(100);
      }

      if (o->InheritsFrom(AliParallelTask::Class())) {
         task = (AliParallelTask *) o;
         if (task->IsActive()) {
            if (fIsRunningParallel) task->ThreadStart();
            else task->Exec(option);
         }
      } else if (o->InheritsFrom(AliParallelTaskManager::Class())) {
         taskMgr = (AliParallelTaskManager *)o;
         if (taskMgr->IsActive()) {
            taskMgr->SetRunningParallel(fIsRunningParallel);
            taskMgr->Exec(option);
         }
      }
   }

   // let finish last thread
   while (TThread::Exists()>0) {
      gSystem->Sleep(100);
   }

   numThreads = TThread::Exists();
   Printf("Running Manager %s::Exec(\"%s\")  [DONE] %d/%d",GetName(),option,numThreads,fMaxThreads);

}

//_________________________________________________________________________________________________
void AliParallelTaskManager::ExecuteParallel(Option_t *option)
{
   if (fIsRunningParallel) {
      Exec(option);
   } else {
      ExecuteTasks(option);
   }
}