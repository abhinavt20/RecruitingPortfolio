
// Project Identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043
// Pairing Heap Priority Queue header for Project 2b.
// Implements a priority queue using the Pairing Heap data structure, supporting dynamic priority adjustments.

// Project identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include "Eecs281PQ.h"
#include <deque>
#include <utility>

// A specialized version of the priority queue ADT implemented as a pairing
// heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Each node within the pairing heap
    class Node {
        public:
            // TODO: After you add add one extra pointer (see below), be sure
            //       to initialize it here.
            explicit Node(const TYPE &val)
        : elt{ val }, child{ nullptr }, sibling{ nullptr }, previous{nullptr}
            {}

            // Description: Allows access to the element at that Node's
            //              position. There are two versions, getElt() and a
            //              dereference operator, use whichever one seems
            //              more natural to you.
            // Runtime: O(1) - this has been provided for you.
            const TYPE &getElt() const { return elt; }
            const TYPE &operator*() const { return elt; }

            // The following line allows you to access any private data
            // members of this Node class from within the PairingPQ class.
            // (ie: myNode.elt is a legal statement in PairingPQ's add_node()
            // function).
            friend PairingPQ;

        private:
            TYPE elt;
            Node *child;
            Node *sibling;
            Node *previous;
            // TODO: Add one extra pointer (parent or previous) as desired.
    }; // Node


    // Description: Construct an empty pairing heap with an optional
    //              comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
    BaseClass{ comp }, root{nullptr}, numNodes{0} {
        this->compare = comp;

    } // PairingPQ()


    // Description: Construct a pairing heap out of an iterator range with an
    //              optional comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
    BaseClass{ comp }, root{nullptr}, numNodes{0} {
        // TODO: Implement this function.
            this->compare = comp;

            while (start != end){
                push(*start);
                start++;
            }
            
            updatePriorities();
       
    } // PairingPQ()


    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ &other) :
    BaseClass{ other.compare }, root{nullptr}, numNodes{0} {
        // TODO: Implement this function.
        // NOTE: The structure does not have to be identical to the original,
        //       but it must still be a valid pairing heap.
        this->compare = other.compare;
        
        std::deque<Node*> nodeDeque;
        Node * currNode = other.root;
        nodeDeque.push_back(currNode);
        
        while(!nodeDeque.empty()){
            currNode = nodeDeque.front();
            if(currNode->sibling){
                nodeDeque.push_back(currNode->sibling);
            }
            if(currNode->child){
                nodeDeque.push_back(currNode->child);
            }
            
            push(currNode->elt);
            nodeDeque.pop_front();
        }

    } // PairingPQ()


    // Description: Copy assignment operator.
    // Runtime: O(n)
    PairingPQ &operator=(const PairingPQ &rhs) {
        // TODO: Implement this function.
        // HINT: Use the copy-swap method from the "Arrays and Containers"
        //       lecture.
        PairingPQ temp(rhs);

//        std::swap(root, temp.root);
//        std::swap(numNodes, temp.numNodes);
        
        std::swap(this->root, temp.root);
        std::swap(this->numNodes, temp.numNodes);
   
        return *this;
    } // operator=()


    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
        // TODO: Implement this function.
        std::deque<Node*> deleteNodes;
        Node * firstNode;

        if (root != nullptr){
            deleteNodes.push_back(root);
            root = nullptr;
            
            while(!deleteNodes.empty()){
                firstNode = deleteNodes.front();
                if(firstNode->sibling){
                    deleteNodes.push_back(firstNode->sibling);
                }
                if(firstNode->child){
                    deleteNodes.push_back(firstNode->child);
                }
                
                firstNode->sibling = nullptr;
                firstNode->child = nullptr;
                firstNode->previous = nullptr;

                delete firstNode;
                firstNode = nullptr;
                deleteNodes.pop_front();
            }
            
//            TODO: DO I NEED TO UPDATE numNodes and delete root?
        
        }
    } // ~PairingPQ()


    // Description: Assumes that all elements inside the pairing heap are out
    //              of order and 'rebuilds' the pairing heap by fixing the
    //              pairing heap invariant. You CANNOT delete 'old' nodes
    //              and create new ones!
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
        
        std::deque<Node*> nodeUP;
        nodeUP.push_back(root);
        root = nullptr;
        
//        Node * currNode;
        while (!nodeUP.empty()){
            Node * currNode = nodeUP.front();
            nodeUP.pop_front();
            
            if(currNode->child != nullptr){
                nodeUP.push_back(currNode->child);
            }
            if(currNode->sibling != nullptr){
                nodeUP.push_back(currNode->sibling);
            }
            
            currNode->child = nullptr;
            currNode->sibling = nullptr;
            currNode->previous = nullptr;
            
            if (root == nullptr){
                root = currNode;
            }
            else{
                root = meld(root, currNode);
            }
        }
        

        
    } // updatePriorities()


    // Description: Add a new element to the pairing heap. This is already
    //              done. You should implement push functionality entirely in
    //              the addNode() function, and this function calls
    //              addNode().
    // Runtime: O(1)
    virtual void push(const TYPE &val) {
        addNode(val);
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the pairing heap.
    // Note: We will not run tests on your code that would require it to pop
    //       an element when the pairing heap is empty. Though you are
    //       welcome to if you are familiar with them, you do not need to use
    //       exceptions in this project.
    // Runtime: Amortized O(log(n))
    virtual void pop() {
        // TODO: Implement this function.
//        Node * rootPtr = root;

        if (numNodes == 1){
            delete root;
            root = nullptr;
            numNodes--;
            return;
        }
        else{
            std::deque<Node*> popDeque;
            Node * p = root->child;

            while(p != nullptr){
                popDeque.push_back(p);
                p = p->sibling;
            }
            
            delete root;
            popDeque[0]->sibling = nullptr;
            popDeque[0]->previous = nullptr;

            while (popDeque.size() > 1) {
//                Node * front = popDeque.front();
                popDeque[0]->sibling = nullptr;
                popDeque[0]->previous = nullptr;
//                popDeque.pop_front();
                
                
//                Node * front2 = popDeque.front();
                popDeque[1]->sibling = nullptr;
                popDeque[1]->previous = nullptr;
//                popDeque.pop_front();
                
//                Node * meldBack = meld(front, front2);
                popDeque.push_back(meld(popDeque[0], popDeque[1]));
                popDeque.pop_front();
                popDeque.pop_front();
            }
            
            root = popDeque.front();
            numNodes--;
        }
    
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the pairing heap. This should be a reference for speed.
    //              It MUST be const because we cannot allow it to be
    //              modified, as that might make it no longer be the most
    //              extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        return root->elt;
    } // top()


    // Description: Get the number of elements in the pairing heap.
    // Runtime: O(1)
    virtual std::size_t size() const {
        return numNodes;
    } // size()

    // Description: Return true if the pairing heap is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        if (numNodes == 0){
            return true;
        }
        return false;
    } // empty()


    // Description: Updates the priority of an element already in the pairing
    //              heap by replacing the element refered to by the Node with
    //              new_value. Must maintain pairing heap invariants.
    //
    // PRECONDITION: The new priority, given by 'new_value' must be more
    //               extreme (as defined by comp) than the old priority.
    //
    // Runtime: As discussed in reading material.
    void updateElt(Node* node, const TYPE &new_value) {
        
        if (node == root){
            return;
        }
        
        if(this->compare(node->elt, new_value)){
            
            node->elt = new_value;
            
            //if left most
            if (node->previous->child == node){
                //has siblings
                if (node->sibling != nullptr){
                    node->sibling->previous = node->previous;
                    node->previous->child = node->sibling;
                }
                else{
                    node->previous->child = nullptr;
                }
            }
            
            //if not left most
            else{
                //has siblings
                if (node->sibling != nullptr){
                    node->sibling->previous = node->previous;
                    node->previous->sibling = node->sibling;
                }
                //no siblings
                else{
                    node->previous->sibling = nullptr;
                }
            }
            
            node->previous = nullptr;
            node->sibling = nullptr;
            
            root = meld(root, node);
        }
        
    } // updateElt()


    // Description: Add a new element to the pairing heap. Returns a Node*
    //              corresponding to the newly added element.
    // NOTE: Whenever you create a node, and thus return a Node *, you must
    //       be sure to never move or copy/delete that node in the future,
    //       until it is eliminated by the user calling pop(). Remember this
    //       when you implement updateElt() and updatePriorities().
    // Runtime: O(1)
    Node* addNode(const TYPE &val) {
        // TODO: Implement this function
        Node * newNode = new Node(val);
    
        if(root == nullptr){
            root = newNode;
        }
        
        else{
            root = meld(root, newNode);
        }
        
        numNodes++;
        return newNode;
    } // addNode()


private:
    // TODO: Add any additional member variables or member functions you
    //       require here.
        Node * root;
        size_t numNodes;
    // TODO: We recommend creating a 'meld' function (see the Pairing Heap
    //       papers).
    
    Node * meld(Node * pA, Node * pB){
        // if pB has higher priority then pA
        if (this->compare(pA->elt, pB->elt)) {
            if (pB->child){
                pA->sibling = pB->child;
                pB->child->previous = pA;
            }
            pB->child = pA;
            pA->previous = pB;
            return pB;
            }
        
        else {
            if (pA->child){
                pB->sibling = pA->child;
                pA->child->previous = pB;
            }
            pA->child = pB;
            pB->previous = pA;
            return pA;
            }
            
        }

    // NOTE: For member variables, you are only allowed to add a "root
    //       pointer" and a "count" of the number of nodes. Anything else
    //       (such as a deque) should be declared inside of member functions
    //       as needed.
};


#endif // PAIRINGPQ_H
