#!/bin/bash
/bin/echo ADAFRUIT-SPI0>/sys/devices/bone_capemgr.9/slots
/sbin/insmod /lib/modules/3.8.13-bone79/v4l2loopback.ko
/usr/bin/v4l2-ctl --set-fmt-video-out=width=80,height=60,pixelformat=1
/usr/bin/v4l2-ctl --set-parm=8
#/usr/bin/touch /home/debian/ERCH
/usr/bin/vncserver :1 -geometry 1280x720 -depth 24

