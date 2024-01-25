#include "dn-interface.h"

/* Convert to BCD */
byte to_bcd(byte b) {

	byte x = 0;
	byte res = 0;

	while (b > 0)
	{
		res |= (b % 10) << (x++ << 2);
		b /= 10;
	}

	return res;
}