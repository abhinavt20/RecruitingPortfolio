#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL
#include <sstream>
#include <string>
#include <utility>


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  List();

  //adding in the big three
  //1. Copy constructor
  List(const List &other);

  // 2. Assignment operator
  List &operator=(const List &rhs){
    if (this == &rhs) {
      return *this;
    }
    
    clear();
    copy_all(rhs);
    return *this;
  }

  //3. Destructor
  ~List();


  //EFFECTS:  returns true if the list is empty
  bool empty() const;

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front();

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back();

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum);

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum);

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front();

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back();

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear();

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int nodeCounter; // keeps track of the size of the list of nodes

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other);

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List
    friend class List;

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    Iterator(Node *p) : node_ptr(p) {}
    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    Iterator() : node_ptr(nullptr) {}

    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator & operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    T & operator* () const{
      assert(node_ptr != nullptr);
      return node_ptr->datum;
    }

    Iterator & operator++ () {
      assert(node_ptr != nullptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    bool operator!= (Iterator rhs) const {
      return node_ptr != rhs.node_ptr;
    }

    bool operator== (Iterator rhs) const {
      return node_ptr == rhs.node_ptr;
    }


  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here

    // construct an Iterator at a specific position
   // Iterator(Node *p);

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const{
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i);

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum);

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

//List ctor implementation
template <typename T>
List<T>::List() : first(nullptr), last(nullptr), nodeCounter(0) {}

//List ctor copy implementation
template <typename T>
List<T>::List(const List &other) : first(nullptr), last(nullptr), nodeCounter(0) {
    copy_all(other);
}

//List dtor implementation
template <typename T>
List<T>::~List() {
    clear();
}

// List member function implementations
template <typename T>
bool List<T>::empty() const {
    if (nodeCounter == 0) {
        return true;
    }
    return false;
}

template <typename T>
int List<T>::size() const {
    return nodeCounter;
}

template <typename T>
T& List<T>::front() {
    assert(nodeCounter > 0);
    return first->datum;
}

template <typename T>
T& List<T>::back() {
    assert(nodeCounter > 0);
    return last->datum;
}

template <typename T>
void List<T>::push_front(const T &datum) {
    Node *newNode = new Node{first, nullptr, datum};
    //if empty
    if (empty()) {
        first = newNode;
        last = newNode;
    }
    //if not empty
    else {
        first->prev = newNode;
        first = newNode;
    }
    nodeCounter++;
}

template <typename T>
void List<T>::push_back(const T &datum) {
    Node *newNode = new Node{nullptr, last, datum};
    
    // if not empty 
    if (nodeCounter > 0) {
      last->next = newNode;
      newNode->prev = last;
      last = newNode;
    }
     //if empty
    else  {
      first = newNode;
      last = newNode;
      //push_front(datum);
    }

    nodeCounter++;
}

template <typename T>
void List<T>::pop_front() {
    assert(nodeCounter > 0);
    if (nodeCounter == 1) {
        last = nullptr;
        first = nullptr;
        delete first;
        nodeCounter--;
    }
    else {
        Node *newNode = first->next;
        delete first;
        first = newNode;
        first->prev = nullptr;
        nodeCounter--;
    }
}

template <typename T>
void List<T>::pop_back() {
    assert(!empty());
    //if only 1 element
    if (nodeCounter == 1) {
        first = nullptr;
        last = nullptr;
        delete last;
        nodeCounter--;
    }
    //if multiple elements
    else {
        Node *toMakeLast = last->prev;
        delete last;
        last = toMakeLast;
        last->next = nullptr;
        nodeCounter--;
    }
}


template <typename T>
void List<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template <typename T>
void List<T>::insert(Iterator i, const T &datum) {
    if (i == begin()) {
      push_front(datum);
    }
    else if (empty() || i == end()) {
      push_back(datum);
    }
    else {
      Node *node = new Node{i.node_ptr, i.node_ptr->prev, datum};
    
      node->next->prev = node;
      node->prev->next = node;
    
      nodeCounter++;
    }
}

template <typename T>
void List<T>::erase(Iterator i) {
    if (empty()) {
      return;
    }
    else if (i.node_ptr == first) {
      pop_front();
    }
    else if (i.node_ptr == last) {
      pop_back();
    }
    else {
      (i.node_ptr->prev)->next = i.node_ptr->next;
      (i.node_ptr->next)->prev = i.node_ptr->prev;
      delete i.node_ptr;
      nodeCounter--;
    }
}

template <typename T>
void List<T>::copy_all(const List<T> &other) {
    assert(empty());

  for (Node *node_ptr = other.first; node_ptr; node_ptr = node_ptr->next) {
    push_back(node_ptr->datum);
  }
  
    // for (List<T>::Iterator it = other.begin(); it != other.end(); ++it) {
    //     push_back(*it);
    // }

}


#endif // Do not remove this. Write all your code above this line.



