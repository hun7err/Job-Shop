#!/bin/bash

for i in `seq 1 $1`
do
	#echo "$i"
	BIN="`pwd`/job-shop"
	OUT=`$BIN 1 "instances/taillard/$2.txt"`
	echo $OUT
done
