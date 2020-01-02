#include <iostream>

#include "Functions.hpp"

using namespace std;

int main() {
    /* collapse */
    cout << "Testing collapse" << endl;

    Stack<int> s1;
    s1.push(7);
    s1.push(2);
    s1.push(8);
    s1.push(9);
    s1.push(4);
    s1.push(11);
    s1.push(7);
    s1.push(1);
    s1.push(42);

    collapse(s1);

    cout << "Stack s1:" << endl;
    while (!s1.isEmpty()) {
        cout << s1.pop() << endl;
    }

    /* equals */
    cout << "Testing equals" << endl;

    Stack<int> s2;
    s2.push(7);
    s2.push(2);
    s2.push(8);

    Stack<int> s3;
    s3.push(7);
    s3.push(2);
    s3.push(8);

    Stack<int> s4;
    s4.push(7);
    s4.push(2);

    bool equalsS2S3 = equals(s2, s3);
    bool equalsS2S4 = equals(s2, s4);

    cout << "equals s2 and s3 : " << (equalsS2S3 ? "true" : "false") << endl;
    cout << "equals s2 and s4 : " << (equalsS2S4 ? "true" : "false") << endl;

    cout << "Stack s2:" << endl;
    while (!s2.isEmpty()) {
        cout << s2.pop() << endl;
    }
    cout << "Stack s3:" << endl;
    while (!s3.isEmpty()) {
        cout << s3.pop() << endl;
    }
    cout << "Stack s4:" << endl;
    while (!s4.isEmpty()) {
        cout << s4.pop() << endl;
    }

    /* reorder */
    cout << "Testing reorder" << endl;

    Queue<int> q1;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(-2);
    q1.enqueue(4);
    q1.enqueue(-5);
    q1.enqueue(8);
    q1.enqueue(-8);
    q1.enqueue(12);
    q1.enqueue(-15);

    reorder(q1);

    cout<< "Queue q1:" << endl;
    while(!q1.isEmpty())
        cout << q1.dequeue() << " ";
    cout << endl;

    return 0;
}