#!/bin/sh

$PWD/unittest/build/bin/unittest

echo 'Gcov process started...'
mkdir gcov-coverage
cd gcov-coverage

for x in $PWD/../unittest/build/CMakeFiles/unittest.dir/*.cpp.o; do
  echo "x: $x"
  gcov "$x"
done


#Create HTML files of the coverage data:
lcov --directory . --capture --output-file app.info

genhtml app.info