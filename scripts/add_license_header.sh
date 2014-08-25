#!/bin/bash  
for f in $(find ../ -name '*.cpp' -or -name '*.h' -or -name '*.m' -or -name '*.mm')
do
  echo "Processing $f" 
  if ! grep -q Copyright $f
  then
    cat copyright.txt $f >$f.new && mv $f.new $f
  fi
done