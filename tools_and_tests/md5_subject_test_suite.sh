#!/bin/bash

make

FAIL=0;

compare() {
	diff <(echo "$1") <(echo "$3") >/dev/null
	DIFF_STATUS=$?

	if [ "$DIFF_STATUS" -eq 1 ]; then
		printf "\033[0;31m$2 and $4 are different ========================= WARNING ==\033[0m\n"
		echo ">> $1 $3"
		FAIL=1;
	elif [ "$DIFF_STATUS" -eq 2 ]; then
		echo "Error in diff command!"
	elif [ "$DIFF_STATUS" -eq 0 ]; then
		printf "\033[1;32m$2 and $4 are identical\033[0m\n"
	fi
}

test() {
	echo "'$1'"
	echo ""
	OWN=$(eval $1)
	EXPECTED_OUTPUT="$2"

	compare "$OWN" "ft_ssl" "$EXPECTED_OUTPUT" "Expected_Output"

	echo "Test over"
	echo ""
}

echo "ft_ssl md5 subject test suite"

echo "echo \"42 is nice\" | openssl md5"
echo "42 is nice" | openssl md5

echo "echo \"42 is nice\" | md5sum"
echo "42 is nice" | md5sum

test "echo \"42 is nice\" | ./ft_ssl md5" "MD5(stdin)= 35f1d6de0302e2086a4e472266efb3a9"
test "echo \"42 is nice\" | ./ft_ssl md5 -p" "MD5(\"42 is nice\")= 35f1d6de0302e2086a4e472266efb3a9"

test "echo \"Pity the living.\" | ./ft_ssl md5 -q -r" "e20c3b973f63482a778f3fd1869b7f25"

echo "And above all," > file
test "./ft_ssl md5 file" "MD5(file)= 53d53ea94217b259c11a5a2d104ec58a"
test "./ft_ssl md5 -r file" "53d53ea94217b259c11a5a2d104ec58a *file"

test "./ft_ssl md5 -s \"pity those that aren't following baerista on spotify.\"" "MD5(\"pity those that aren't following baerista on spotify.\")= a3c990a1964705d9bf0e602f44572f5f"
test "echo \"be sure to handle edge cases carefully\" | ./ft_ssl md5 -p file" "(\"be sure to handle edge cases carefully\")= 3553dc7dc5963b583c056d1b9fa3349c\nMD5(file)= 53d53ea94217b259c11a5a2d104ec58a"

test "echo \"some of this will not make sense at first\" | ./ft_ssl md5 file" "MD5(file)= 53d53ea94217b259c11a5a2d104ec58a"

test "echo \"but eventually you will understand\" | ./ft_ssl md5 -p -r file" "(\"but eventually you will understand\")= dcdd84e0f635694d2a943fa8d3905281\n53d53ea94217b259c11a5a2d104ec58a file"

test "echo \"GL HF let's go\" | ./ft_ssl md5 -p -s \"foo\" file" "(\"GL HF let's go\")= d1e3cc342b6da09480b27ec57ff243e2\nMD5 (\"foo\") = acbd18db4cc2f85cedef654fccc4a4d8\nMD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"

test "echo \"one more thing\" | ./ft_ssl md5 -r -p -s \"foo\" file -s \"bar\"" "(\"one more thing\")= a0bd1876c6f011dd50fae52827f445f5\nacbd18db4cc2f85cedef654fccc4a4d8 \"foo\"\n53d53ea94217b259c11a5a2d104ec58a file\nft_ssl: md5: -s: No such file or directory\nft_ssl: md5: bar: No such file or directory"

test "echo \"just to be extra clear\" | ./ft_ssl md5 -r -q -p -s \"foo\" file" "just to be extra clear\n3ba35f1ea0d170cb3b9a752e3360286c\nacbd18db4cc2f85cedef654fccc4a4d8\n53d53ea94217b259c11a5a2d104ec58a"

if [ "$FAIL" -eq 1 ]; then
	echo "Testing failed"
	exit 1;
elif [ "$FAIL" -eq 0 ]; then
	echo "Testing A-OK"
	exit 0;
fi

exit 0;
