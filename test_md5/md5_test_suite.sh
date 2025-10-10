#!/bin/bash

FAIL=0;

compare() {
	diff <(echo "$1") <(echo "$3") >/dev/null
	DIFF_STATUS=$?

	if [ "$DIFF_STATUS" -eq 1 ]; then
		echo "$2 and $4 are different ========================= WARNING =="
		echo ">> $1 $3"
		FAIL=1;
	elif [ "$DIFF_STATUS" -eq 2 ]; then
		echo "Error in diff command!"
	elif [ "$DIFF_STATUS" -eq 0 ]; then
		echo "$2 and $4 are identical"
	fi
}

test() {
	echo "Testing '$1'"
	echo ""
	OWN="$(./a.out "$1")"
	OPENSSL="$(echo -n "$1" | openssl md5 | awk '{print $2}')"

	compare "$OWN" "own" "$OPENSSL" "true"

	echo "Test over"
	echo ""
}

test ""
test "salut"
test "echo"
test "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv"
test "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv"
test "abcdefghijklmnopqrstuvwxyz"
test "abcdefghijklmnopqrstuvwxyzABCDE"
test "abcdefghijklmnopqrstuvwxyzABCDEF"
test "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ012"
test "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123"


echo "MD5 test suite:"
test ""
test "a"
test "abc"
test "message digest"
test "abcdefghijklmnopqrstuvwxyz"
test "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
test "12345678901234567890123456789012345678901234567890123456789012345678901234567890"

if [ "$FAIL" -eq 1 ]; then
	echo "Testing failed"
	exit 1;
elif [ "$FAIL" -eq 0 ]; then
	echo "Testing A-OK"
	exit 0;
fi

exit 0;
