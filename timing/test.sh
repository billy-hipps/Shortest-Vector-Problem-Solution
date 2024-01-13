#!/bin/bash
make
test_cases=(
    
)
for test_case in "${test_cases[@]}"; do
    ./runme $test_case > output.txt
    diff output.txt expected_output.txt

    if [ $? -eq 0 ]; then
        echo "Test passed for arguments: $test_case"
    else
        echo "Test failed for arguments: $test_case"
    fi
done
make clean
