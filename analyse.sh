#!/bin/bash

# Number of times to run the program
N=$1
POP=$2
GEN=$3
MUT=$4
# Output file
OUTPUT_FILE=$5

# Clear the output file
> $OUTPUT_FILE

# Run the program N times
for ((i=1; i<=N; i++))
do
    # Execute the program and capture the output
    ./main $POP $GEN $MUT >> $OUTPUT_FILE 
done

echo "Completed $N runs. Results written to $OUTPUT_FILE."

./average $OUTPUT_FILE