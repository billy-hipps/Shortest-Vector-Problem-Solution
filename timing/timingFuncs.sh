#!/bin/bash

# Function to generate orthogonal vectors
generate_orthogonal_vectors() {
    dim=$1
    vectors=()

    for ((i=1; i<=dim; i++)); do
        vector="["
        for ((j=1; j<=dim; j++)); do
            if [ $j -eq $i ]; then
                vector+="1"
            else
                vector+="0"
            fi

            if [ $j -lt $dim ]; then
                vector+=" "
            fi
        done
        vector+="]"
        vectors+=("$vector")
    done

    echo "${vectors[@]}"
}

program="./runme"

# Loop to run program with dimensions from 2 to 9 inclusive
for ((dim=2; dim<=9; dim++)); do
    # Generate orthogonal vectors
    input_args=$(generate_orthogonal_vectors $dim)

    # Run program
    $program $input_args

    # Print a message indicating the current run
    echo "Run completed with dimension $dim"
done

echo "Script completed."
