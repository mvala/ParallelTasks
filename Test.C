#ifndef __CINT__
#include <TString.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TStopwatch.h>
#include <TThread.h>
#endif

void Test(Bool_t runParallel = kTRUE,Long64_t base=1e8) {

   gSystem->SetDynamicPath(Form("%s/ParallelTasks/:%s", gSystem->pwd(),gSystem->GetDynamicPath()));

   gSystem->Load("libThread.so");
   gSystem->Load("libHist.so");
   gSystem->Load("libParallelTasks.so");
   
   gROOT->LoadMacro("AliParallelUtils.C");

   AliParallelTaskManager *mgrMain = new AliParallelTaskManager("Main","Main Manager",runParallel);
//    mgr->SetMaxThreads(2);
   AliParallelTaskManager *mgrSel = new AliParallelTaskManager("MrgSelection","Selection Manager",runParallel);
//    mgrSel->SetActive(kFALSE);

   AddParallelTask(mgrMain,"Task_1","Task 1",2.0*base);
   AddParallelTask(mgrMain,"Task_2","Task 2",1.0*base);
   AddParallelTask(mgrMain,"Task_3","Task 3",1.0*base);
   AddParallelTask(mgrMain,"Task_4","Task 4",1.5*base);
   
   mgrMain->Add(mgrSel);
   if (mgrSel->IsActive()) {
      AddParallelTask(mgrSel,"Task_5_1","Task 5 1",2.0*base);
      AddParallelTask(mgrSel,"Task_5_2","Task 5 2",1.0*base);
      AddParallelTask(mgrSel,"Task_5_3","Task 5 3",1.5*base);
      AddParallelTask(mgrSel,"Task_5_4","Task 5 4",1.0*base);
      AddParallelTask(mgrSel,"Task_5_5","Task 5 5",2.0*base);
      AddParallelTask(mgrSel,"Task_5_6","Task 5 6",1.0*base);
   }
   
   AddParallelTask(mgrMain,"Task_6","Task 6",2.0*base);
   AddParallelTask(mgrMain,"Task_7","Task 7",2.5*base);
   AddParallelTask(mgrMain,"Task_8","Task 8",2.5*base);


   TStopwatch timer;
   timer.Start();

   mgrMain->ExecuteParallel("");

   timer.Stop();
   timer.Print();
}
