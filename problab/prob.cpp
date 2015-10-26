#include <iostream>

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

// expected number of calls: 1/(2p(1-p))
bool good_flip() {
	bool a, b;
	do {
		a = bad_flip();
		b = bad_flip();
	} while (a == b);
	return a;
}

int main() {}