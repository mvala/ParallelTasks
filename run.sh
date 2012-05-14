#!/bin/bash

MY_DIR="$(dirname $(readlink -m $0))"
cd $MY_DIR/ParallelTasks
make
cd $MY_DIR
root -b Test.C
