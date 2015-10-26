#include <iostream>

/* Placeholder for compilation. 
 * Should return unbiased 50/50 coin flip.
 */
bool flip() {
	return false;
}

/* Returns true with probability a / b with calls only to flip() for randomness. */
bool flip(unsigned long a, unsigned long b) {
	double prob = (double) a / (double) b;
	for (int i = 0; i < sizeof(a) * 8; i++) {
		prob *= 2;
		bool tf = prob >= 1 ? true : false;
		prob -= 1;
		bool f = flip();
		if (f == tf) {
			return f;
		}
	}
	return false;
}

/* Placeholder for compilation.
 * Returns true with random probability a / b, where b > a.
 */
bool bad_flip() {
	return false;
}

/* Returns true with 50/50 probability while only calling bad_flip() for randomness.
 * Expected number of calls: 1/(2p(1-p))
 */
bool good_flip() {
	bool a, b;
	do {
		a = bad_flip();
		b = bad_flip();
	} while (a == b);
	return a;
}

int main() {}