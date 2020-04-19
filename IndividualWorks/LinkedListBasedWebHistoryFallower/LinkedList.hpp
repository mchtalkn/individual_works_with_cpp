#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>

#include "Node.hpp"
using namespace std;
template <class T>
class LinkedList
{
    public: // DO NOT CHANGE THIS PART.
        LinkedList();
        LinkedList(const LinkedList &obj);

        ~LinkedList();

        Node<T> *getFirstNode() const; //
        Node<T> *getHead() const;
        Node<T> *getTail() const;
        int getNumberOfNodes();
        bool isEmpty(); //

        void insertAtTheFront(const T &data); //
        void insertAtTheEnd(const T &data); //
        void insertAfterGivenNode(const T &data, Node<T> *prev); //

        void removeNode(Node<T> *node);
        void removeAllNodes();

        Node<T> *findNode(const T &data); //

        void printAllNodes();
        void printReversed();

        LinkedList &operator=(const LinkedList &rhs);

    private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    private: // DO NOT CHANGE THIS PART.
        Node<T> *head;
        Node<T> *tail;
};

template<class T>
LinkedList<T>::LinkedList()
{
    head =new Node<T>;
    tail =new Node<T>;
    head->next=tail;
    tail->prev=head;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList &obj)
{
  Node<T>*tmp=obj.head->next;
  Node<T>*end=obj.tail;
  Node<T>*element;
  T data;
  head =new Node<T>;
  tail =new Node<T>;
  head->next=tail;
  tail->prev=head;
  Node<T>*tmpBase=head;
  while(tmp!=end){
    data=tmp->element;
    element=new Node<T>(data,tmpBase,tail);
    tmpBase->next=element;
    tmpBase=tmpBase->next;
    tmp=tmp->next;
  }
}

template<class T>
LinkedList<T>::~LinkedList()
{
    Node<T> *tmp=head;
    while(head){
      tmp=head;
      head=head->next;
      delete tmp;
    }
}

template<class T>
Node<T> * LinkedList<T>::getFirstNode() const
{
    if(head->next!=tail){
      return head->next;
    }else{
      return NULL;
    }
}

template<class T>
Node<T> * LinkedList<T>::getHead() const
{
    return head;
}

template<class T>
Node<T> * LinkedList<T>::getTail() const
{
    return tail;
}

template<class T>
int LinkedList<T>::getNumberOfNodes()
{
    Node<T>*iterator=head;
    int count=-2;
    while(iterator){
      iterator=iterator->next;
      count++;
    }
    return count;
}

template<class T>
bool LinkedList<T>::isEmpty()
{
    return !(head && (head->next!=tail));

}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data)
{
    Node<T> *element=new Node<T>(data,head,head->next);
    head->next=element;
    element->next->prev=element;
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data)
{
    Node<T>*element=new Node<T>(data,tail->prev,tail);
    tail->prev=element;
    element->prev->next=element;
}

template<class T>
void LinkedList<T>::insertAfterGivenNode(const T &data, Node<T> *prev)
{
    Node<T>*element=new Node<T>(data,prev,prev->next);
    element->prev->next=element;
    element->next->prev=element;
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
  Node<T> *tmp=head;
  while(tmp){
    if(tmp==node) break;
    else tmp=tmp->next;
  }
  if(tmp){
    node->prev->next=node->next;
    node->next->prev=node->prev;
    delete node;
  }
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
    Node<T> *tmpScout=head->next;
    while(tmpScout!=tail){
      tmpScout=tmpScout->next;
      delete tmpScout->prev;
    }
    head->next=tail;
    tail->prev=head;
}

template<class T>
Node<T> * LinkedList<T>::findNode(const T &data)
{
  Node<T> *tmp=head->next;
    while(tmp!=tail){
      if(tmp->element==data) return tmp;
      tmp=tmp->next;
    }
    return NULL;
}

template<class T>
void LinkedList<T>::printAllNodes()
{
    Node<T>* tmp=head;
    while (tmp->next!=tail) {
      cout<<*(tmp->next)<<endl;
      tmp=tmp->next;
    }
}

template<class T>
void LinkedList<T>::printReversed()
{
    Node<T>* tmp=tail;
    while(tmp->prev!=head){
      cout<<*(tmp->prev)<<endl;
      tmp=tmp->prev;
    }
}

template<class T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList &rhs)
{
      Node<T> *tmp=(rhs.head)->next;
      removeAllNodes();
      while(tmp!=rhs.tail){
        insertAtTheEnd(tmp->element);
        tmp=tmp->next;
      }
}

#endif //LINKED_LIST_HPP
