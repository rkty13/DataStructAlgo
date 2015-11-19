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

void Tree::Node::kill(Node *p) {
    if (!p) return;
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
            if (cur != p) {
                Node *parent = toDel.top();
                if (parent->l == cur) parent->l = 0;
                if (parent->r == cur) parent->r = 0;
            }
            delete cur;
        }
    }
    p = 0;
}

Tree::It::It(const It& i) : p(i.p), s(i.s) {}

Tree::It::~It() {
    while (!s.empty()) s.pop();
}

void Tree::It::calc_sub_size(It i) {
    while (!i.s.empty()) {
        Node *parent = i.s.top(); i.s.pop();
        (parent->n)++;
    }
}

double& Tree::It::operator*() const {
    if (!p) throw std::runtime_error("Node is null.");
    return p->e.val;
}

Tree::It Tree::It::operator++(int) {
    if (!p) {
        stack<Node *> right;
        Node *noneRoot = s.top();
        while (noneRoot->r) {
            right.push(noneRoot);
            noneRoot = noneRoot->r;
        }
        p = noneRoot;
        s = right;
    } else if (p->r) {
        s.push(p);
        p = p->r;
        while (p->l) {
            s.push(p);
            p = p->l;
        }
    } else {
        if (s.empty()) {
            stack<Node *> none;
            Node *noneNode = p; // root
            none.push(noneNode);
            p = 0;
            s = none;
        } else {
            Node *parent = s.top(); s.pop();
            while (parent && parent->r == p) {
                p = parent;
                parent = s.top(); s.pop();
            }
            p = parent;
        }
    }
    return *this;
}

Tree::It& Tree::It::operator++() {
    (*this)++; return *this;
}

Tree::It Tree::It::operator--(int) {
    if (!p) {
        stack<Node *> left;
        Node *noneRoot = s.top();
        while (noneRoot->l) {
            left.push(noneRoot);
            noneRoot = noneRoot->l;
        }
        p = noneRoot;
        s = left;
    } else if (p->l) {
        s.push(p);
        p = p->l;
        while (p->r) {
            s.push(p);
            p = p->r;
        }
    } else {
        if (s.empty()) {
            stack<Node *> none;
            Node *noneNode = p; // root
            none.push(noneNode);
            p = 0;
            s = none;
        } else {
            Node *parent = s.top(); s.pop();
            while (parent && parent->l == p) {
                p = parent;
                parent = s.top(); s.pop();
            }
            p = parent;
        }
    }
    return *this;
}

Tree::It& Tree::It::operator--() {
    (*this)--; return *this;
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

Tree::It::It(Node *p, const stack<Node*>& s) : p(p), s(s) {}

void Tree::It::del(bool erase) {
    if (!p) {}
    else if (!(p->l) && !(p->r)) {
        if (!s.empty()) {
            Node *parent = s.top(); s.pop();
            if (parent->l == p) {
                parent->l = 0;
            } else if (parent->r == p) {
                parent->r = 0;
            }
            delete p;
            p = parent;
        }
    } else if ((!(p->l) && p->r) || 
                (p->l && !(p->r))) {
        if (!s.empty()) {
            Node *parent = s.top(); s.pop();
            if (parent->l == p) {
                if (p->l) {
                    parent->l = p->l;
                    p->l = 0;
                    delete p;
                } else if (p->r) {
                    parent->l = p->r;
                    p->r = 0;
                    delete p;
                }
            } else if (parent->r == p) {
                if (p->l) {
                    parent->r = p->l;
                    p->l = 0;
                    delete p;
                } else if (p->r) {
                    parent->r = p->r;
                    p->r = 0;
                    delete p;
                }
            }
        }
    } else if (p->l && p->r) {
        if (!s.empty()) {
            Node *parent = s.top(); s.pop();
            Node *y = p->l;
            Node *z = p->r;
            Node *q = z;
            while (q->l) q = q->l;
            Node *a = q->r;
            q->l = y; q->r = z;
            Node *zl = z;
            while (zl->l) if (zl->l->l) zl = zl->l;
            zl->l = a;
            if (parent->l == p) {
                parent->l = q;
            } else if (parent->r == p) {
                parent->r = q;
            }
            delete p;
        }
    }
}

Tree::Tree() {
    root = 0;
}

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
    for (; i != hi() && i.p && key.compare(i.p->e.key) > 0; ++i) {}
    if (key.compare(i.p->e.key) == 0) return i;
    else return none();
}

bool Tree::set(const string& key, double val) {
    if (!root) {
        root = new Node(Entry(key, val));
        return false;
    }
    It i = lo();
    for (; i != hi() && i.p && key.compare(i.p->e.key) > 0; ++i) {}
    if (key.compare(i.p->e.key) < 0) {
        Node *tmp = new Node(Entry(key, val));
        if (i.p->r) {
            Node *cur = i.p->r;
            while (cur->l) cur = cur->l;
            cur->l = tmp;
            Tree::It::calc_sub_size(--i);
            return false;
        }
        i.p->r = tmp;
        Tree::It::calc_sub_size(--i);
        return false;
    } else if (key.compare(i.p->e.key) > 0) {
        Node *tmp = new Node(Entry(key, val));
        if (i.p->l) {
            Node *cur = i.p->l;
            while (cur->r) cur = cur->r;
            cur->r = tmp;
            Tree::It::calc_sub_size(++i);
            return false;
        }
        i.p->r = tmp;
        Tree::It::calc_sub_size(++i);
        return false;
    }
    i.p->e.val = val;
    return true;
}

bool Tree::del(const string& key) {
    It i = this->get(key);
    bool ret = i == none();
    i.del();
    return ret;
}

Tree::It Tree::lo() const {
    stack<Node *> s;
    Node *temp = root;
    while (temp && temp->l) {
        s.push(temp);
        temp = temp->l;
    }
    return It(temp, s);
}

Tree::It Tree::hi() const {
    stack<Node *> s;
    Node *temp = root;
    while (temp && temp->r) {
        s.push(temp);
        temp = temp->r;
    }
    return It(temp, s);
}

Tree::It Tree::none() const {
    stack<Node *> s;
    s.push(root);
    return It(0, s);
}

bool Tree::check_sizes() const {
    return false;
}

int main() {}