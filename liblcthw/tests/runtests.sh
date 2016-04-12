echo "Running unit tests:"

for testfile in tests/*_tests
do
  if test -f $testfile
  then
    if $VALGRIND ./$testfile 2>> tests/tests.log
    then
      echo $testfile PASS
    else
      echo "ERROR in test $testfile: here's tests/tests.log"
      echo "------"
      tail tests/tests.log
      exit 1
    fi
  fi
done

echo
