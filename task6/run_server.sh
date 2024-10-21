#!/bin/bash

export SERIAL_PORT=/dev/pts/16
export LD_PRELOAD=./myptrace.so
./server --key 767936614.key.enc
#gdb ./server
#gdbserver :1234 ./server --key 767936614.key.enc
#strace -y -f ./server --key 767936614.key.enc
#ltrace -o t -C ./server --key 767936614.key.enc

