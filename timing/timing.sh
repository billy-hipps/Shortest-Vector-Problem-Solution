#!/bin/bash

# Output file for recording execution times
timing_file="timing_results.txt"

# Function to generate n n-dimensional orthogonal vectors
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

# Loop through dimensions and run the program
for dim in {2..10}; do
    # Generate n n-dimensional orthogonal vectors
    orthogonal_vectors=$(generate_orthogonal_vectors $dim)

    # Record start time
    start_time=$(date +%s.%N)

    # Run the program with the current orthogonal vectors
    ./runme $orthogonal_vectors >> "$timing_file"  # Redirect output to timing file

    # Record end time
    end_time=$(date +%s.%N)

    # Calculate and record execution time
    execution_time=$(echo "$end_time - $start_time" | bc)
    echo "Dimension $dim: $execution_time seconds" >> "$timing_file"
done
echo "Script completed."
