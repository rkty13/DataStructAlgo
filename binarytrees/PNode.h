/* Binary tree Node with pointer to parent */

template <typedef T>
class PNode {
public:
    PNode(const T& t, PNode *left = 0, PNode *parent = 0, Node *right = 0): t(t), left(left), parent(parent), right(right) {}

private:
    T t;
    PNode *left, *parent, *right;
};
