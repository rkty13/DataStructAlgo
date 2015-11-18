#include "tree.h"

Tree::Entry::Entry(const string& key, double val) {
    this->key = key;
    this->val = val;
}

Tree::Entry::Entry(const Entry& e) {
    this->key = e.key;
    this->val = e.val;
}

Tree::Node::Node(const Entry& e, Node *l, Node *r, size_t n) {
    this->e = e;
    this->l = l;
    this->r = r;
    this->n = n;
}

Tree::Node::~Node() {
    l = 0;
    r = 0;
}

// NOT FINISHED
void Tree::Node::kill(Node *p) {
    stack<Node *> toDel;
    toDel.push(p);
    while (!toDel.empty()) {
        Node *cur = toDel.top();
        if (cur->l) {
            toDel.push(cur->l);
        } else if (cur->r) {
            toDel.push(cur->r);
        } else {
            toDel.pop();
            delete cur;
        }
    }
}

Tree::It::It(const It& i) {
    this->p = i.p;
    this->s = i.s;
}

// NOT FINISHED
Tree::It::~It() {

}

double& Tree::It::operator*() const {
    return p->e.val;
}

Tree::It Tree::It::operator++(int) {
    Node *x = this->p;
    if (x->r) {
        s.push(x);
        x = x->r;
        while (x->l) {
            s.push(x);
            x = x->l;
        }
    } else {
        Node *parent = s.top(); s.pop();
        while (parent && parent->r == x)
            x = parent;
            parent = s.top(); s.pop();
    }
    Node *parent = s.top(); s.pop();
    this->p = parent;
    return *this;
}

Tree::It& Tree::It::operator++() {
    (*this)++;
    return *this;
}

Tree::It Tree::It::operator--(int) {
    Node *x = this->p;
    if (x->l) {
        s.push(x);
        x = x->l;
        while (x->r) {
            s.push(x);
            x = x->r;
        }
    } else {
        Node *parent = s.top(); s.pop();
        while (parent && parent->l == x) {
            x = parent;
            parent = s.top(); s.pop();
        }
    }
    Node *parent = s.top(); s.pop();
    this->p = parent;
    return *this;
}

Tree::It& Tree::It::operator--() {
    (*this)--;
    return *this;
}

Tree::It Tree::It::operator+(long j) const {
    It i = *this;
    for (long x = 0; x < j; x++) i++;
    return i;
}

bool Tree::It::operator!=(const It& it) const {
    return this->p != it.p;
}

bool Tree::It::operator==(const It& it) const {
    return this->p == it.p;
}

Tree::It::It(Node *p, const stack<Node*>& s) {
    this->p = p;
    this->s = s;
}

void Tree::It::del(bool erase) {}

Tree::Tree() {}

Tree::~Tree() {
    Node::kill(root);
}

size_t Tree::size() const {
    return root->n;
}

bool Tree::empty() const {
    return !root;
}

Tree::It Tree::get(const string& key) const {
    It i = lo();
    for (; i != hi() && i.p && key.compare(i.p->e.key) < 0; ++i) {}
    if (key.compare(i.p->e.key) == 0) return i;
    else return none();
}

bool Tree::set(const string& key, double val) {
    if (!root) {
        root = new Node(Entry(key, val));
        return false;
    }

    for (It i = lo(); i != hi() && i.p && key.compare(i.p->e.key) < 0; ++it) {}
    if (key.compare(i.p->e.key) == 0) {
        i.p->e.val = val;
        return true;
    } else if (!i.p->l && key.compare(i.p->e.key) < 0) {
        Node *tmp = new Node(Entry(key, val));
        i.p->l = tmp;

        //update parent subtree shit
        return false;
    } else if (key.compare(i.p->e.key) > 0) {
        Node *tmp = new Node(Entry(key, val));
        i.p->r = tmp;

        //update parent subtree shit
        return false;
    }


}

bool Tree::del(const string& key) {}

Tree::It Tree::lo() const {
    stack<Node *> s;
    Node *temp = root;
    while (root->l) {
        s.push(temp);
        temp = root->l;
    }
    return It(temp, s);
}

Tree::It Tree::hi() const {
    stack<Node *> s;
    Node *temp = root;
    while (root->r) {
        s.push(temp);
        temp = root->r;
    }
    return It(temp, s);
}

Tree::It Tree::none() const {
    stack<Node *> s;
    s.push(root);
    return It(0, s);
}

bool Tree::check_sizes() const {

}

int main() {
    Tree::Tree tree;
    return 0;
}