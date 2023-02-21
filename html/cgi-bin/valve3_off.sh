#!/bin/sh

filename="/dev/ttyACM"*
echo 'l' | tee $filename
