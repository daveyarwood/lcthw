echo
echo "Running unit tests:"
echo

testfile=tests/ex29_tests

# $1: expected output
# $2: actual output
function assert_equal {
  if echo "$2" | grep -Fx "$(echo $1)" 2>> tests/tests.log; then
    echo $testfile PASS
  else
    echo $testfile "FAIL: expected $1, got $2"
  fi
}

# testing failing test
assert_equal \
  "helloo world" \
  "$(./$testfile build/libex29.so lowercase 12 "HELLO WORLD" 2>> tests/tests.log)"

assert_equal \
  "hello world" \
  "$(./$testfile build/libex29.so lowercase 12 \"HELLO WORLD\" 2>> tests/tests.log)"
