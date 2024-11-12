
// Project Identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043
// Binary Priority Queue header for Project 2b (Priority Queues).
// Defines a Binary Heap-based priority queue with the standard push, pop, and top functions.
// The implementation uses the comparison functor for custom priority management.

// Project identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043

#ifndef BINARYPQ_H
#define BINARYPQ_H


#include <algorithm>
#include "Eecs281PQ.h"
#include <vector>
#include <iterator>
#include <iostream>


// A specialized version of the priority queue ADT implemented as a binary
// heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;
    
public:
    // Description: Construct an empty PQ with an optional comparison functor.
    // Runtime: O(1)
    explicit BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
    BaseClass{ comp } {
        // TODO: Implement this function, or verify that it is already done
        data.push_back(TYPE());
        this->compare = comp;
    } // BinaryPQ
    
    
    // Description: Construct a PQ out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    BinaryPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
    BaseClass{ comp } {
        // TODO: Implement this function
        data.push_back(TYPE());
        this->compare = comp;
        
        while (start != end){
            data.push_back(*start);
            start++;
        }

       //data.insert(data.end(), start, end);
        
        updatePriorities();
        
    } // BinaryPQ
    
    
    // Description: Destructor doesn't need any code, the data vector will
    //              be destroyed automatically.
    virtual ~BinaryPQ() {
    } // ~BinaryPQ()
    
    
    // Description: Assumes that all elements inside the heap are out of
    //              order and 'rebuilds' the heap by fixing the heap
    //              invariant.
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
        size_t dataSize = size()/2;
        while (dataSize > 0){
            fix_down(dataSize);
            dataSize--;
        }
    } // updatePriorities()
    
    
    // Description: Add a new element to the PQ.
    // Runtime: O(log(n))
    virtual void push(const TYPE &val) {
        // TODO: Implement this function.
        data.push_back(val);
        fix_up(data.size() - 1);
    } // push()
    
    
    // Description: Remove the most extreme (defined by 'compare') element
    //              from the PQ.
    // Note: We will not run tests on your code that would require it to pop
    //       an element when the PQ is empty. Though you are welcome to if
    //       you are familiar with them, you do not need to use exceptions in
    //       this project.
    // Runtime: O(log(n))
    virtual void pop() {
        // TODO: Implement this function.
        data[1] = data.back();
        data.pop_back();
        fix_down(1);
    } // pop()
    
    
    // Description: Return the most extreme (defined by 'compare') element of
    //              the PQ. This should be a reference for speed. It MUST
    //              be const because we cannot allow it to be modified, as
    //              that might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function.
        return data[1];
        
    } // top()
    
    
    // Description: Get the number of elements in the PQ.
    // Runtime: O(1)
    virtual std::size_t size() const {
        // TODO: Implement this function. Might be very simple,
        return data.size() - 1;
    } // size()
    
    
    // Description: Return true if the PQ is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        // TODO: Implement this function. Might be very simple,
        return (size() == 0);
    } // empty()
    
    
private:
    // Note: This vector *must* be used for your PQ implementation.
    std::vector<TYPE> data;
    // NOTE: You are not allowed to add any member variables. You don't need
    //       a "heapSize", since you can call your own size() member
    //       function, or check data.size().
    
    // TODO: Add any additional member functions you require here. For
    //       instance, you might add fixUp() and fixDown().
    
    //    T& get_element(size_t idx) {
    //        return data[idx - 1];
    //    } // get_element()
    //
    //    const T& get_element(size_t idx) const {
    //        return data[idx - 1]; // BinaryPQ
    //    }
    
    void fix_up(size_t index) {
        // swap modified element with parent until root is reached or a parent
        // with a greater than or equal priority is found
        while (index > 1 && this->compare(data[index / 2], data[index])) {
            std::swap(data[index], data[index / 2]);
            index /= 2;
        } // while
    } // fix_up()
    
    
    void fix_down(size_t index) {
        size_t heap_size = size();
        while (2 * index <= heap_size) {
            // initialize highest priority child to left child
            size_t larger_child = 2 * index;
            // if right child has higher priority, set larger child to right child
            if (larger_child < heap_size && this->compare(data[larger_child], data[larger_child + 1])) {
                ++larger_child;
            } // if
            // if children all have lower priority, the heap is restored so break out of the loop
            if (this->compare(data[larger_child], data[index])) {
                break;
            } // if
            // otherwise, swap the modified element with the largest child
            std::swap(data[index], data[larger_child]);
            // set new index value for next iteration of loop
            index = larger_child;
        } // while
    } // fix_down()
};

#endif // BINARYPQ_H
