//
//  tree.h
//  
//
//  Binary Tree Programming Assignment
//  Due: November 17, 2015 at 4:10 PM
//

/*
    Implement the data types specified below. You may #include a modified tree.h, but it must be a superset of this specfication.
 
    Notice the structure of the Tree class: it contains two private structs, Entry, and Node, and a public subclass, It which serves as the iterator for traversing the tree. Remember that the data field n in a Node is necessary to implement a random-access iterator, i.e., an iterator that can jump any specified number of positions. The implementation should accomplish this in O(h) time, where h is the height of the tree.
 
    The purpose of kill(Node *p) is to avoid stack overflow when deleting every node in a tree even if the tree is very deep.
 
    The iterator class It should allow the following for traversing the tree:
 
    Tree::It it = tree.lo();
    while (it != tree.none())
        cout << *it++ << '\n';
    
    it = tree.none();
    while (--it != tree.none())
        cout << *it;
 
    it = tree.none();
    while (++it != tree.none())
        cout << *it;
 
    if (it + 1000000 == tree.none())
        cerr << "iterator is out of range\n";
 
    etc.
 
    Note that Tree is declared a friend of It so that it may access the private constructor It(Node*, const stack<Node*>&).
 
    Note also (this is a hint, that you don't have to follow) that I implemented the Tree member function del() with a private member function del() of It. It could be convenient to have a public del() in the It class, but the problem I found, was that if the root of the tree was deleted (which should be permissible), there was no way to re-assign the root data field from within the It class. Having del (in It) private, allowed it to be called only under circumstances where the caller took the responsibility to re-attach root to the new root of the tree.
*/
#ifndef _tree_h
#define _tree_h

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using std::string;
using std::vector;
using std::stack;
using std::cin;
using std::cout;
using std::cerr;

class Tree {
    
    struct Entry {
        Entry(const string& key = "", double val = 0.0);
        Entry(const Entry& e);
        
        string key;
        double val;
    };
    
    struct Node {
        explicit Node(const Entry& e = Entry(), Node *l = 0, Node *r = 0, size_t n = 1);
        ~Node();
        
        // For debugging only
        bool check_sizes() const;
        
        Entry e;    // Application-specific information
        Node *l;    // Left subtree
        Node *r;    // Right subtree
        size_t n;   // # of nodes in this subtree
        
        static void kill(Node *p);  // De-allocate this subtree
    };
    
public:
    
    // The class for users to move around within the tree
    class It {
        friend class Tree;
    public:
        It(const It& i);
        ~It();
        
        double& operator*() const;
        It operator++(int);     // Post-increment
        It& operator++();       // Pre-increment
        It operator--(int);     // Post-decremenmt
        It& operator--();       // Pre-decrement
        It operator+(long j) const; // Get iterator to new location
        bool operator!=(const It& it) const;
        bool operator==(const It& it) const;
        
    private:
        Node *p;                // Iterator refers to this location in tree
        stack<Node*> s;         // Need a stack because NO PARENT POINTERS
        
        It(Node *p, const stack<Node*>& s);
        void del(bool erase = true);   // Delete the node referred to by *this
    };
    
    Tree();
    ~Tree();
    
    size_t size() const;                        // # of nodes in tree
    bool empty() const;                         // Is the tree empty?
    It get(const string& key) const;            // return iterator to key or none()
    bool set(const string& key, double val);    // Set val, possibly adding node
    bool del(const string& key);                // Remove the node having this key
    It lo() const;                              // Iterator to smallest node
    It hi() const;                              // Iterator to largest node
    It none() const;                            // Sentry iterator (for loops)
    
    // For debugging only
    bool check_sizes() const;
    
private:
    Node *root;
};

#endif
