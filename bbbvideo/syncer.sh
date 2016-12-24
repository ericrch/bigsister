#!/bin/bash
/usr/bin/rsync -av  -e "ssh -l erich" --remove-source-files  bbbout/  erich@192.168.1.5:~/Desktop/beehive
