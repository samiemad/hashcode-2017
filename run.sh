#!/bin/bash

echo "Compiling..."
mkdir -p bin output
g++ score.cpp --std=c++14 -O3 -o bin/score || exit -1
g++ sol-naive.cpp --std=c++14 -O3 -o bin/vid || exit -1

if [[ $1 == "all" ]]; then
	files="me_at_the_zoo videos_worth_spreading trending_today kittens";
elif [[ $1 == "fast" ]]; then
	files="me_at_the_zoo videos_worth_spreading trending_today";
else
	files="example";
fi

for name in $files; do
	printf "Running for file $name...";
	time ./bin/vid < "input/${name}.in" > "output/${name}.out" ;
	score=`./bin/score "output/$name.out" < "input/$name.in"` || exit -1
	echo "Your score for $name is: $score"
	total=$(python -c "print $total+$score")
done

echo "Total score: $total"
