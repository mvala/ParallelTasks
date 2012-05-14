//
// Class AliParallelTaskManager
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ALIPARALLELTASKMANAGER_H
#define ALIPARALLELTASKMANAGER_H

#include <TTask.h>
#include <Rtypes.h>
#include <TCondition.h>

class TCondition;
class AliParallelTaskManager : public TTask {
public:
   AliParallelTaskManager(const char *name = "ManagerTask", const char *title = "Manager Task",Bool_t isParallel=kTRUE);
   AliParallelTaskManager(const AliParallelTaskManager &obj);
   AliParallelTaskManager &operator=(const AliParallelTaskManager &obj);
   virtual ~AliParallelTaskManager();

   virtual void Exec(Option_t *option);

   void ExecuteParallel(Option_t *option="");

   void SetMaxThreads(Int_t max) { fMaxThreads = max; }

   void SetRunningParallel(Bool_t isParallel=kTRUE) { fIsRunningParallel = isParallel;}
private:

   Int_t     fMaxThreads;
   Bool_t    fIsRunningParallel;

   ClassDef(AliParallelTaskManager, 1)

};

#endif
