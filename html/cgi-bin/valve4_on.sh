#!/bin/sh

filename="/dev/ttyACM"*
echo 'c' | tee $filename
