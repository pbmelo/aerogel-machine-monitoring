#!/bin/sh

filename="/dev/ttyACM"*
echo 'p' | tee $filename
