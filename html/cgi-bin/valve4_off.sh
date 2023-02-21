#!/bin/sh

filename="/dev/ttyACM"*
echo 'o' | tee $filename
