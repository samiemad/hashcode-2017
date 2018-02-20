#!/bin/bash

echo "Compiling..."
g++ score.cpp --std=c++14 -O3 -o score || exit -1
g++ sol-naive.cpp --std=c++14 -O3 -o vid || exit -1

if [[ -z $1 ]]; then
	files="example";
else
	files="me_at_the_zoo videos_worth_spreading trending_today";
#	files="me_at_the_zoo videos_worth_spreading trending_today kittens";
fi

#for f in input/*.in; do
#	name=${f#*/}
#	name=${name%.*}
for name in $files; do
	printf "Running for file $name...";
	time ./vid < "input/${name}.in" > "output/${name}.out" ;
	score=`./score "output/$name.out" < "input/$name.in"` || exit -1
	echo "Your score for $name is: $score"
	total=$(python -c "print $total+$score")
#	echo "file $name processing done";
done

echo "Total score: $total"
