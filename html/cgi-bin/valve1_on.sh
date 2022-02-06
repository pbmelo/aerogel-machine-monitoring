#!/bin/sh

filename="/dev/ttyACM"*
echo 's' | tee $filename
