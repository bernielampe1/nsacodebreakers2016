#!/bin/bash

i=1472947200 # sep 4 00:00:00 GMT
while true
do
    if [[ $i -ge 1475193600 ]]
    then
        echo "FAILED!!!!"
        exit 1
    fi

    LD_PRELOAD=./mysrand.so SEED="$i" ./keygen -g -k 767936614 -o t

    diff key.decoded.txt 767936614.key > /dev/null

    if [[ $? -eq 0 ]]
    then
        echo "FOUND IT SEED = $i!"
        exit 0
    fi

    i=$((i+1))
done

