#!/bin/bash
set -e  # Exit on error

EXECUTABLE="./ItemTracker"
INPUT_FILE="test_input.txt"
OUTPUT_FILE="test_output.txt"

echo "Creating test input file..."
echo -e "apple\nbanana\napple\norange\nbanana\napple" > "$INPUT_FILE"

echo "Running ItemTracker with test input..."
$EXECUTABLE -i "$INPUT_FILE" -o "$OUTPUT_FILE" --width 100 > e2e_output.log

echo "Checking output file..."
if ! grep -q "apple 3" "$OUTPUT_FILE"; then
    echo "❌ ERROR: Expected 'apple 3' in output file."
    exit 1
fi
if ! grep -q "banana 2" "$OUTPUT_FILE"; then
    echo "❌ ERROR: Expected 'banana 2' in output file."
    exit 1
fi
if ! grep -q "orange 1" "$OUTPUT_FILE"; then
    echo "❌ ERROR: Expected 'orange 1' in output file."
    exit 1
fi

echo "✅ E2E Test Successfully Completed!"
