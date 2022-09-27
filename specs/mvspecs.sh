#!/bin/bash
# move BASEk.yaml --> BASE(k+i).yaml for k=FIRST to LAST and i=INCR
# e.g., PROG lab 8 23 -1
#
PROG=`basename $0`
USAGE="Usage:   $PROG [-t] <base> <first> <last>
Example: $PROG lab 9 20 -1
    moves lab9.yaml-->lab8.yaml, ... lab20.yaml-->lab19.yaml
-t flag prints moves without making them.  BEWARE OF OVERWRITES"
    
TEST=false
case "$1" in
    -t) TEST=true; shift;;
    *) ;;
esac

case $# in 
     4) ;;
     *) echo "$USAGE" ; exit 1;;
esac

BASE=$1   FIRST=$2   LAST=$3   INCR=`echo $4 | sed s/^-/_/`

CMD="mv"
$TEST && { CMD="echo $CMD" ; echo Planned actions: ; }
for k in `seq $FIRST $LAST`
do  DEST=`echo $k $INCR+p | dc`
    $CMD $BASE$k.yaml $BASE$DEST.yaml
done
