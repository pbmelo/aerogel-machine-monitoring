#!/bin/sh

filename="/dev/ttyACM"*
echo 'k' | tee $filename
