/* Binary tree Node */

template <typedef T>
class BNode {
public:
    BNode(const T& t, BNode *left = 0, BNode *right = 0): t(t), left(left), right(right) {}

private:
    T t;
    BNode *left, *right;
};
