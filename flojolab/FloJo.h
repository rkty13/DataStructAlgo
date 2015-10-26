#include <vector>

using std::vector;

template <class T>
struct Link {
	explicit Link(const T& info, Link<T> *next = 0) : info(info), next(next) {}
	~Link() {
		Link<T> *p = next;
		while (p) {
			Link<T> *q = p->next;
			p->next = 0;
			delete p;
			p = q;
		}
	}

	T info;
	Link<T> *next;
};

vector<int> loopTail(Link<int> *head);
vector<int> josephus(int n, int k);