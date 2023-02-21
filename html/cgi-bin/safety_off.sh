#!/bin/sh

filename="/dev/ttyACM"*
echo 'q' | tee $filename
