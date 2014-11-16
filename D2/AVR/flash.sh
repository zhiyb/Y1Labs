#! /bin/sh

if [ "$*" = "" ]; then
	ugget Labs/D2/CPU/CPU.svf
fi
echo 'cable ft2232 vid=0x0403 pid=0x6014
detect
svf CPU.svf progress' | jtag

exit
