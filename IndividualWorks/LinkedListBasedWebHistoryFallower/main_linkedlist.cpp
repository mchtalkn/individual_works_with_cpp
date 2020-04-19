#include <iostream>

#include "LinkedList.hpp"

int main() {
    LinkedList<int> llist;
    llist.printAllNodes();


    llist.insertAtTheEnd(1);
    llist.insertAtTheEnd(7);
    llist.insertAtTheEnd(4);

    llist.printAllNodes();


    llist.removeNode(llist.findNode(8));
    llist.printAllNodes();
    llist.removeAllNodes();
    llist.removeAllNodes();
    llist.insertAtTheEnd(1);
    llist.insertAtTheEnd(7);
    llist.printAllNodes();
    LinkedList<int> listcpy(llist);
    listcpy.printAllNodes();
    return 0;
}
