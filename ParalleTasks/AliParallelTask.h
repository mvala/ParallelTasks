//
// Class AliParallelTask
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ALIPARALLELTASK_H
#define ALIPARALLELTASK_H

#include <TTask.h>
#include <Rtypes.h>
#include <TCondition.h>

class TThread;

// static void* AliParallelTask::Thread0(void *arg);

class AliParallelTask : public TTask {
public:
   AliParallelTask(const char *name = "Task", const char *title = "Task");
   AliParallelTask(const AliParallelTask &obj);
   AliParallelTask &operator=(const AliParallelTask &obj);
   virtual ~AliParallelTask();

   virtual void Exec(Option_t *option);

   void SetMaxNum(Long64_t num) { fMaxNum = num;}
   Long64_t GetMaxNum() { return fMaxNum; }

   Int_t ThreadStart();
   Int_t ThreadStop();

   TThread *GetThread() { return fThread; }
   TCondition *GetCondition() { return &fCondition; }
   static void *Thread0(void *arg);

private:
   TThread *fThread;
   TCondition fCondition;

   Long64_t fMaxNum; // max num to sum


   ClassDef(AliParallelTask, 1)

};

#endif
