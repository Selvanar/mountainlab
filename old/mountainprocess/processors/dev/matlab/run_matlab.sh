#!/bin/bash

script_dir=$1

#command -v matlab
#if [ $? -eq 0 ]
#then
#  echo "Using matlab."
#  cmd="matlab -nosplash -nojvm -r"
#  $cmd "try, addpath('$script_dir'); $2; exit(0);, catch err, disp(getReport(err,'extended')); exit(-1);, end;"
#else
#  echo "Matlab is not installed. Checking for Octave"
  command -v octave
  if [ $? -eq 0 ]
  then
    echo "Using octave."
    cmd="octave --no-gui --eval"
    $cmd "try, addpath('$script_dir'); $2; exit(0);, catch err, exit(-1);, end;"
  else
  	echo "You must either install matlab or octave."
    echo "You must install octave"
  	exit -1
  fi
#fi


#cmd="octave --no-gui --eval"




