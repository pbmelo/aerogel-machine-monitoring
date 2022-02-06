#!/bin/sh

filename="/dev/ttyACM"*
echo 'w' | tee $filename
