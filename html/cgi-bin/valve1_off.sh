#!/bin/sh

filename="/dev/ttyACM"*
echo 't' | tee $filename
