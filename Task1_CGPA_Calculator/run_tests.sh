#!/bin/bash

# Test runner for CGPA Calculator
# Compares only the last line (CGPA value)
# Author: Gabriel Olaru


g++ cgpa.cpp -o cgpa
if [ $? -ne 0 ]; then
  echo "Compilation failed."
  exit 1
fi

echo "Compilation successful."
echo "-----------------------------"

passed=0
total=0

for infile in test*_*.in; do
  ((total++))
  base=${infile%.in}
  outfile="$base.ref"

  cp "$infile" cgpa.in
  ./cgpa > /dev/null 2>&1

  expected_last=$(tail -n 1 "$outfile")
  got_last=$(tail -n 1 cgpa.out)

  if [[ "$expected_last" == "$got_last" ]]; then
    echo "${base}: PASS"
    ((passed++))
  else
    echo "${base}: FAIL"
    echo "Expected: $expected_last"
    echo "Got:      $got_last"
    echo "-----------------------------"
  fi
done

echo "-----------------------------"
echo "Tests passed: $passed / $total"

rm -f cgpa.in cgpa.out cgpa
