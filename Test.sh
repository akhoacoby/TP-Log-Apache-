#!/bin/bash

# Set the base directory containing the tests
TEST_DIR="./Tests"

# Check if the test directory exists
if [ ! -d "$TEST_DIR" ]; then
    echo "Error: Test directory '$TEST_DIR' not found!"
    exit 1
fi

# Function to compare files
compare_files() {
    local expected="$1"
    local actual="$2"
    local label="$3"

    if [ -f "$expected" ]; then
        if diff -q "$expected" "$actual" > /dev/null; then
            echo "✅ $label matches expected output."
        else
            echo "❌ $label does not match expected output!"
            diff "$expected" "$actual" | head -n 20 # Show first 20 differences
        fi
    else
        echo "⚠️  No reference file for $label, skipping comparison."
    fi
}

# Loop through each test directory
for test_case in "$TEST_DIR"/*/; do
    echo "--------------------------------------"
    echo "Running test: $(basename "$test_case")"

    # Read the command to run
    if [ ! -f "$test_case/run" ]; then
        echo "⚠️  No 'run' file found, skipping test."
        continue
    fi

    COMMAND=$(cat "$test_case/run")
    echo "Executing: $COMMAND"

    # Run the command and capture outputs
    STDOUT_FILE="$test_case/std.out.actual"
    STDERR_FILE="$test_case/stderr.out.actual"
    RETURN_CODE_FILE="$test_case/returncode.actual"

    eval "$COMMAND" > "$STDOUT_FILE" 2> "$STDERR_FILE"
    echo $? > "$RETURN_CODE_FILE"

    # Compare outputs
    compare_files "$test_case/std.out" "$STDOUT_FILE" "Standard Output"
    compare_files "$test_case/stderr.out" "$STDERR_FILE" "Standard Error"
    
    # Compare return code
    if [ -f "$test_case/Returncode" ]; then
        EXPECTED_RETURN_CODE=$(cat "$test_case/Returncode")
        ACTUAL_RETURN_CODE=$(cat "$RETURN_CODE_FILE")
        if [ "$EXPECTED_RETURN_CODE" -eq "$ACTUAL_RETURN_CODE" ]; then
            echo "✅ Return code matches expected ($EXPECTED_RETURN_CODE)."
        else
            echo "❌ Return code mismatch! Expected: $EXPECTED_RETURN_CODE, Got: $ACTUAL_RETURN_CODE"
        fi
    else
        echo "⚠️  No reference return code, skipping comparison."
    fi

    # Compare expected output files (e.g., x.dot -> x.dot.outfile)
    for ref_file in "$test_case"/*.outfile; do
        if [ -f "$ref_file" ]; then
            actual_file="${ref_file%.outfile}"  # Remove .outfile extension
            compare_files "$ref_file" "$actual_file" "Output File $(basename "$ref_file")"
        fi
    done

    echo "--------------------------------------"
done
