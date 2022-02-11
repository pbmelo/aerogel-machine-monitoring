# aerogel-machine-monitoring

This repository is meant to be a place where I'm able to control and keep my
files for a remote monitoring system I have developed for an aerogel machine in
the lab [I currently work on](https://www.colorado.edu/soft-matter-physics/).

## Note

The files hosted here are under active development and have some minor issues.
I expect to keep updating the repository with improvements as well as a detailed
guide on how to use and reproduce it yourself.

## What is required to build a similar system

1. An Arduino or similar controller
2. As many thermocouples as wanted (0 to 5)
3. Adafruit's max31856 thermocouple current amplifier (one per thermocouple)
4. As many pressure transducers that operate in a 4..20 mA fashion as wanted
   (0 to 5)
5. As many electrically operated pneumatic valves as wanted (0-4)
6. Generic 5V relays (one per pneumatic valve)
7. A computer that will host the web interface and talk to the Arduino board (if
   a web interface is desired)

## Contents

This repository contains

1. Source code for the Arduino board to monitor temperature and pressure
   sensors, as well as control relays
2. Required files for a system on a chip (such as Raspberry Pi) or any other
   computer, such as the following:
3. A systemd service that communicates with the Arduino to read its output and
   write it to a file, to be later used by the web server
4. Source code for the web interface that controls the Arduino.  Namely, read
   the output file, display the data to the user interface, grab user commands
   from the interface and send them to the Arduino
5. Instructions on how to wire the system and set the software up

### To do

My future plans consist of

1. Improve the performance and overall user experience of the web interface
2. Write a detailed tutorial on how to set everything up
3. Make a Raspberry Pi, other arm32/64, as well as an x86_64 image with
   everything pre configured, such that the end user will just have to clone
   them to disk
4. Upload pictures of the web interface as well as printed circuit, together
   with a short usage manual (it's all very intuitive, really!)

## LICENSE

Copyright (C) 2022 pbmelo

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <https://www.gnu.org/licenses/>.
