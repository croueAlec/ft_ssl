import sys

def print_in_blocks_of_eight(input_string):
    substrings = input_string.split()
    full_rows = 0
    row_number = 1

    for i in range(0, len(substrings), 8):
        block = substrings[i:i+8]
        print(f"" + ' '.join(block))
        row_number += 1

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python script.py \"your input string here\"")
    else:
        input_string = ' '.join(sys.argv[1:])
        print_in_blocks_of_eight(input_string)
