#ifndef __SPLITMIX32_H__
#define __SPLITMIX32_H__

typedef long int uint32_t;

uint32_t splitmix32_x;

void splitmix32_seed(uint32_t seed) {
    splitmix32_x = seed;
}

uint32_t splitmix32() {
	uint32_t s = splitmix32_x += 2654435769;
	
    s ^= s >> 16;
	s *= 0x85ebca6b;
	s ^= s >> 13;
	s *= 0xc2b2ae35;
	s ^= s >> 16;

	return s;
}

#endif