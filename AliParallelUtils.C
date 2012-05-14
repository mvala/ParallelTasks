void AliParallelUtils() {

}

AliParallelTask *AddParallelTask(AliParallelTaskManager *mgr,const char *name,const char *title,Long64_t masxum=1,Bool_t isActive=kTRUE) {
   if (!mgr) {
      Printf("Task %s was NOT added. mgr is null !!!",name);
      return 0;
   }
   AliParallelTask *t= new AliParallelTask(name,title);
   t->SetMaxNum(masxum);
   mgr->Add(t);
   return t;
}
