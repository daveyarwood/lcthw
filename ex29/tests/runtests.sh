echo
echo "Running unit tests:"
echo

testfile=tests/ex29_tests

# $1: expected output
# $2: actual output
function assert_equal {
  if echo "$2" | grep -Fx "$1" >/dev/null; then
    echo $testfile PASS
  else
    echo $testfile "FAIL: expected $1, got $2"
  fi
}

function assert_failure {
  if ! [ "$1" ]; then
    echo $testfile PASS
  else
    echo $testfile "FAIL: expected failure, got $1"
  fi
}

assert_equal \
  "HELLO THERE" \
  "$(./$testfile build/libex29.so uppercase 12 "hello there" 2>> tests/test.log)"

assert_equal \
  "hello there" \
  "$(./$testfile build/libex29.so lowercase 12 "HELLO tHeRe" 2>> tests/test.log)"

assert_failure \
  "$(./$testfile build/libex29.so fail_on_purpose 42 "i fail" 2>> tests/test.log)"

assert_failure \
  "$(./$testfile build/libex29.so fail_on_purpose 2>> tests/test.log)"

assert_failure \
  "$(./$testfile build/libex29.so nonexistent_function 666 "lol" 2>> tests/test.log)"

assert_failure \
  "$(./$testfile build/libex666nonexistentlol.so lowercase 12 "HELLO tHeRe" 2>> tests/test.log)"


