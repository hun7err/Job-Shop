#!/bin/bash

#for i in `seq 1 $1`
#do
	for j in `seq 1 $1`
	do
		#echo "jobCount: $j"
		BIN="`pwd`/job-shop"
        	OUT=`$BIN 1 "instances/taillard/$2.txt" $j`
		echo $OUT
	done
#done
