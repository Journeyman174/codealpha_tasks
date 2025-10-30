#!/bin/bash


# Sudoku output checker – compares program outputs with reference files
# Olaru Gabriel

EXEC=./sudoku
TOTAL=6
PASS=0
FAIL=0

echo "============================"
echo "     Sudoku Checker "
echo "============================"

for i in $(seq 1 $TOTAL); do
  IN="sudoku${i}.in"
  REF="sudoku${i}.ref"
  OUT="sudoku.out"

  echo -e "\nRunning test #$i ($IN)..."

  if [ ! -f "$IN" ]; then
    echo "Missing input file: $IN"
    ((FAIL++))
    continue
  fi

  if [ ! -f "$REF" ]; then
    echo "Missing reference file: $REF"
    ((FAIL++))
    continue
  fi

  # Run Sudoku solver
  $EXEC "$IN" > /dev/null 2>&1

  # Compare generated output with reference
  if diff -q "$OUT" "$REF" > /dev/null; then
    echo "Test $i PASSED"
    ((PASS++))
  else
    echo "Test $i FAILED"
    echo "   Differences:"
    diff --color=always -y "$OUT" "$REF" | head -n 10
    ((FAIL++))
  fi
done

echo -e "\n============================"
echo "Tests passed: $PASS / $TOTAL"
echo "Tests failed: $FAIL / $TOTAL"
echo "============================"
