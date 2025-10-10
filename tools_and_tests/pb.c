#include <stdint.h>
#include <stdio.h>

#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0')

void    pb(uint8_t byte)
{
    printf("%c%c%c%c%c%c%c%c ", BYTE_TO_BINARY(byte));
}

void    print_singular_bit(uint32_t bit)
{
    pb((uint8_t)(bit>>24) & 0xFF);
    pb((uint8_t)(bit>>16) & 0xFF);
    pb((uint8_t)(bit>>8) & 0xFF);
    pb((uint8_t)bit & 0xFF);
}

int main(int argc, char const *argv[])
{
	uint32_t val = 0b10101010101010100101010101010101;
	print_singular_bit(val);
	return 0;
}
