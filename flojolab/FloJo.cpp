#include <iostream>
#include <cassert>

#include "FloJo.h"

/*
 * Robert Kim
 * September 28th, 2015
 * FloJo Lab
 */

vector<int> loopTail(Link<int> *head) {
    vector<int> a(2, 0);
    if (head == 0) return a;
    Link<int> *slow = head, *fast = head;
    
    int length = 1;
    do {
        for (int i = 0; i < 2; i++) {
            fast = fast->next;
            if (fast == 0) {
                a[1] = length;
                return a;
            }
            ++length;
        }
        slow = slow->next;
    } while (slow != fast);
    a[1] = 0;
    
    int loopLength = 0;
    do {
        slow = slow->next;
        ++loopLength;
    } while (slow != fast);
    a[0] = loopLength;

    int tailLength = 0;
    slow = fast = head;
    for (int i = 0; i < loopLength; ++i) 
        fast = fast->next;

    while(slow != fast) {
        slow = slow->next;
        fast = fast->next;
        ++tailLength;
    }
    a[1] = tailLength;
    return a;
}

vector<int> josephus(int n, int k) {
    assert(k > 0);
    Link<int> *head = new Link<int>(1);
    Link<int> *ohead = head;
    for (int i = 2; i <= n; ++i) {
        Link<int> *tmp = new Link<int>(i);
        head->next = tmp;
        head = tmp;
    }
    head->next = ohead;
    vector<int> a;

    while (head) {
        if (head->next == head) {
            a.push_back(head->info);
            break;
        }
        for (int j = 0; j < k - 1; ++j) {
            head = head->next;
        }
        a.push_back(head->next->info);
        head->next = head->next->next;
    }

    return a;
}

int main() {}