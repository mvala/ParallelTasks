#!/bin/bash

MY_DIR="$(dirname $(dirname $(readlink -m $0)))"
cd $MY_DIR/ParalleTasks
make
cd $MY_DIR
root Test.C
