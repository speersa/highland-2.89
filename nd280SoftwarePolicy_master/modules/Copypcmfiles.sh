#!/bin/sh
cd $1
destination=$2
if test -n "$(find . -maxdepth 1 -name "*.pcm" -print -quit)"
then
    cp *.pcm $2
fi
