#!/bin/sh

filename="/dev/ttyACM"*
echo 'e' | tee $filename
