#!/bin/bash
MY_PARALLEL=1
if [ -n "$1" ];then
  MY_PARALLEL=$1
fi
MY_DIR="$(dirname $(readlink -m $0))"
cd $MY_DIR/ParallelTasks
make
cd $MY_DIR
root -b Test.C\($MY_PARALLEL\)
