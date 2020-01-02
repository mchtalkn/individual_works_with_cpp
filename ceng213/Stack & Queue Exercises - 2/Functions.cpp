#include <iostream>

#include "Functions.hpp"

using namespace std;

/******************************************************************************************************
 * Each of the following 3 problems indicates what kind of structure to use as auxiliary storage.     *
 * You should not use any other auxiliary data structure to solve the problems,                       *
 * although you can create as many simple variables as you would like.                                *
 ******************************************************************************************************/

/******************************************************************************************************
 * Write a method called "collapse" that accepts a stack of integers as a parameter and that          *
 * collapses it by replacing each successive pair of integers with the sum of the pair.               *
 * For example if the stack stores [7, 2, 8, 9, 4, 11, 7, 1, 42] such that 42 is at top and           *
 * 7 is at bottom, the first pair should be collapsed into 9 (7+2) , the second pair                  *
 * should be collapsed into 17 (8+9) and so on. If the stack stores and odd number of elements        *
 * the final element is not collapsed (such as the 42 in our example). So for this stack              *
 * your method would yield [9, 17, 15, 8, 42], where 9 is at bottom and 42 is at top.                 *
 * You can only use one queue as auxiliary storage.                                                   *
 * You are not allowed to use any other auxiliary data structures.                                    *
 ******************************************************************************************************/
void collapse(Stack<int>& s) {

    Queue<int> q;
    while(!s.isEmpty()){
      q.enqueue(s.pop());
    }
    while(!q.isEmpty()){
      s.push(q.dequeue());
    }
    while(!s.isEmpty()){
      q.enqueue(s.pop()+(s.isEmpty()?0:s.pop()));
    }
    while(!q.isEmpty()){
      s.push(q.dequeue());
    }

}

/******************************************************************************************************
 * Write a method called equals that accepts two stacks of integers as parameters and                 *
 * returns true if the two stacks are exactly the same sequence of integer values in the same order.  *
 * Your method must restore the two stacks to their original state before returning.                  *
 * Use one stack as auxiliary storage.                                                                *
 ******************************************************************************************************/
bool equals(Stack<int>& s1, Stack<int>& s2) {

    Stack<int> s3;

    while(!s1.isEmpty()&&!s2.isEmpty()){

      if(s1.peek()==s2.peek()){
        s3.push(s2.pop());
        s1.pop();
      }else{
        while(!s3.isEmpty()){
          s1.push(s3.peek());
          s2.push(s3.pop());
        }
        return false;
      }
    }
    while(!s3.isEmpty()){
      s1.push(s3.peek());
      s2.push(s3.pop());
    }
    return true;
}

/******************************************************************************************************
 * Write a method called reorder that accepts a queue of integers as a parameter and that             *
 * puts the integers into sorted (nondecreasing) order, assuming that the queue is already sorted     *
 * by absolute value. For example if the queue stores [1, 2, -2, 4, -5, 8, -8, 12, -15],              *
 * notice that the values appear in sorted order if you ignore the sign of the numbers.               *
 * Your method should reorder the values so that the queue stores [-15, -8, -5, -2, 1, 2, 4, 8, 12].  *
 * Use one stack as auxiliary storage.                                                                *
 ******************************************************************************************************/
void reorder(Queue<int>& q) {
    Stack<int> s;

    while(!q.isEmpty()){
      if(q.peek()>0){
        s.push(q.dequeue());
      }else {
        if(!s.isEmpty()&&(s.peek()*(-1)<q.peek())){
          break;
        }else{
          q.enqueue(q.dequeue());
        }
      }
    }
    while(!q.isEmpty()){
      s.push(q.dequeue());
    }
    while(!s.isEmpty()){
      q.enqueue(s.pop());
    }
    while(q.peek()<0){
      s.push(q.dequeue());
    }
    while(!s.isEmpty()){
      q.enqueue(s.pop());
    }
    while(!q.isEmpty()){
      s.push(q.dequeue());
    }
    while(!s.isEmpty()){
      q.enqueue(s.pop());
    }
}
