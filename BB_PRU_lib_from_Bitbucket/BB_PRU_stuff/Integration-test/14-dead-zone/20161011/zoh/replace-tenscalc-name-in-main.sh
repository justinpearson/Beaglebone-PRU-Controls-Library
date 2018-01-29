#!/bin/bash

# tmpC_TS_20161011_091554_094025_classname

# Get the name of the new tenscalc from the .c file in the pwd, eg, 
# tmpC_TS_20161011_091554_094025_classname
tenscalc=$(ls -1 -t tmpC_TS_*.c | head -n 1)
new="${tenscalc%.*}"  # remove file extension

# Get the nanme of the old tenscalc from main.c
# eg  tmpC_TS_20161011_091554_094025_classname
oldtens=$(egrep 'tmpC_TS_[[:digit:]]{8}_[[:digit:]]{6}_[[:digit:]]{6}_classname_set_x0' main.c | head -n 1 | xargs) # trailing xargs to remove whitespace on either end
old=${oldtens:0:40}


echo "Replacing old tenscalc function prefix ($old) with new function name ($new)..."

echo "Oldtens: \"$oldtens\", Old: \"$old\""
echo "tenscalc: \"$tenscalc\", New: \"$new\""


sed --in-place=".sedbak" --expression="s/$old/$new/g" main.c