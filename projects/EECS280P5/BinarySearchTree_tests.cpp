// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

TEST(empty_impl_test) {
    // 0 elements
    BinarySearchTree<int> tree1;
    assert(tree1.empty());
    
    // 1 element
    BinarySearchTree<int> tree2;
    tree2.insert(307);
    assert(!tree2.empty());
    
    // > 1 elements
    BinarySearchTree<int> tree3;
    tree3.insert(307);
    tree3.insert(208);
    tree3.insert(102);
    tree3.insert(390);
    assert(!tree3.empty());
}

TEST(size_impl_test) {
    // 0 elements
    BinarySearchTree<int> tree1;
    ASSERT_EQUAL(tree1.size(), 0);
    
    // 1 element
    BinarySearchTree<int> tree2;
    tree2.insert(90);
    ASSERT_EQUAL(tree2.size(), 1);
    
    // > 1 elements
    BinarySearchTree<int> tree3;
    tree3.insert(743);
    tree3.insert(584);
    tree3.insert(692);
    tree3.insert(430);
    ASSERT_EQUAL(tree3.size(), 4);
}

TEST(height_impl_test) {
    // 0 elements
    BinarySearchTree<int> tree1;
    ASSERT_EQUAL(tree1.height(), 0);
    
    // 1 element
    BinarySearchTree<int> tree2;
    tree2.insert(90);
    ASSERT_EQUAL(tree2.height(), 1);
    
    // > 1 elements
    BinarySearchTree<int> tree3;
    tree3.insert(700);
    tree3.insert(800);
    tree3.insert(600);
    tree3.insert(500);
    tree3.insert(400);
    ASSERT_EQUAL(tree3.height(), 4);
}

TEST(copy_nodes_impl_test) {
    // 0 elements
    BinarySearchTree<int> tree1;
    BinarySearchTree<int> tree1Copy(tree1);
    assert(tree1Copy.empty());
    
    // 1 element
    BinarySearchTree<int> tree2;
    tree2.insert(90);
    std::ostringstream tree2Stream;
    tree2.traverse_inorder(tree2Stream);
    BinarySearchTree<int> tree2Copy(tree2);
    std::ostringstream tree2CopyStream;
    tree2Copy.traverse_inorder(tree2CopyStream);
    ASSERT_EQUAL(tree2Stream.str(), tree2CopyStream.str());
    
    // > 1 elements
    BinarySearchTree<int> tree3;
    tree3.insert(700);
    tree3.insert(800);
    tree3.insert(600);
    tree3.insert(500);
    tree3.insert(400);
    std::ostringstream tree3Stream;
    tree3.traverse_inorder(tree3Stream);
    BinarySearchTree<int> tree3Copy(tree3);
    std::ostringstream tree3CopyStream;
    tree3Copy.traverse_inorder(tree3CopyStream);
    ASSERT_EQUAL(tree3Stream.str(), tree3CopyStream.str());
}

TEST(destroy_nodes_impl_test) {
    // 0 elements
    BinarySearchTree<int> tree1;
    tree1 = BinarySearchTree<int>();
    assert(tree1.empty());
    
    // 1 element
    BinarySearchTree<int> tree2;
    tree2.insert(90);
    tree2 = BinarySearchTree<int>();
    assert(tree2.empty());
    
    // > 1 elements
    BinarySearchTree<int> tree3;
    tree3.insert(700);
    tree3.insert(800);
    tree3.insert(600);
    tree3.insert(500);
    tree3.insert(400);
    tree3 = BinarySearchTree<int>();
    assert(tree3.empty());
}

TEST(find_impl_test) {
    // 0 elements
    BinarySearchTree<int> tree1;
    ASSERT_EQUAL(tree1.find(10), tree1.end());
    
    // 1 element
    BinarySearchTree<int> tree2;
    tree2.insert(90);
    ASSERT_EQUAL(*(tree2.find(90)), 90);
    ASSERT_EQUAL(tree2.find(50), tree2.end());
    
    // > 1 elements
    BinarySearchTree<int> tree3;
    tree3.insert(700);
    tree3.insert(800);
    tree3.insert(600);
    tree3.insert(500);
    tree3.insert(400);
    ASSERT_EQUAL(*(tree3.find(800)), 800);
    ASSERT_EQUAL(*(tree3.find(600)), 600);
    ASSERT_EQUAL(tree3.find(100), tree3.end());
}

TEST(min_element_impl_test) {
    // 0 elements
    BinarySearchTree<int> tree1;
    ASSERT_EQUAL(tree1.min_element(), tree1.end());
    
    // 1 element
    BinarySearchTree<int> tree2;
    tree2.insert(75);
    ASSERT_EQUAL(*tree2.min_element(), 75);
    
    // > 1 elements
    BinarySearchTree<int> tree3;
    tree3.insert(4);
    tree3.insert(6);
    tree3.insert(7);
    tree3.insert(2);
    ASSERT_EQUAL(*tree3.min_element(), 2);
}

TEST(max_element_impl_test) {
    // 0 elements
    BinarySearchTree<int> tree1;
    ASSERT_EQUAL(tree1.max_element(), tree1.end());
    
    // 1 element
    BinarySearchTree<int> tree2;
    tree2.insert(75);
    ASSERT_EQUAL(*tree2.max_element(), 75);
    
    // > 1 elements
    BinarySearchTree<int> tree3;
    tree3.insert(4);
    tree3.insert(6);
    tree3.insert(7);
    tree3.insert(2);
    ASSERT_EQUAL(*tree3.max_element(), 7);
}

TEST(check_sorting_invariant_test) {
    // 0 elements
    BinarySearchTree<int> tree1;
    assert(tree1.check_sorting_invariant());
    
    // 1 element
    BinarySearchTree<int> tree2;
    tree2.insert(75);
    assert(tree2.check_sorting_invariant());
    
    // > 1 elements
    BinarySearchTree<int> tree3;
    tree3.insert(10);
    tree3.insert(11);
    tree3.insert(12);
    tree3.insert(13);
    assert(tree3.check_sorting_invariant());
    BinarySearchTree<int>::Iterator desorter = tree3.find(12);
    *desorter = 5;
    assert(!tree3.check_sorting_invariant());
}

TEST(traverse_inorder_test) {
    // 0 elements
    BinarySearchTree<int> tree1;
    std::ostringstream os1;
    tree1.traverse_inorder(os1);
    ASSERT_EQUAL(os1.str(), "");
    
    // 1 element
    BinarySearchTree<int> tree2;
    tree2.insert(75);
    std::ostringstream os2;
    tree2.traverse_inorder(os2);
    ASSERT_EQUAL(os2.str(), "75 ");
    
    // > 1 elements
    BinarySearchTree<int> tree3;
    tree3.insert(74);
    tree3.insert(39);
    tree3.insert(82);
    tree3.insert(19);
    std::ostringstream os3;
    tree3.traverse_inorder(os3);
    ASSERT_EQUAL(os3.str(), "19 39 74 82 ");
}

TEST(traverse_preorder_test) {
    // 0 elements
    BinarySearchTree<int> tree1;
    std::ostringstream os1;
    tree1.traverse_preorder(os1);
    ASSERT_EQUAL(os1.str(), "");
    
    // 1 element
    BinarySearchTree<int> tree2;
    tree2.insert(75);
    std::ostringstream os2;
    tree2.traverse_preorder(os2);
    ASSERT_EQUAL(os2.str(), "75 ");
    
    // > 1 elements
    BinarySearchTree<int> tree3;
    tree3.insert(74);
    tree3.insert(82);
    tree3.insert(39);
    std::ostringstream os3;
    tree3.traverse_preorder(os3);
    ASSERT_EQUAL(os3.str(), "74 39 82 ");
}

TEST(min_greater_than_impl_test) {
    // 0 elements
    BinarySearchTree<int> tree1;
    ASSERT_EQUAL(tree1.min_greater_than(10), tree1.end());
    
    // 1 element
    BinarySearchTree<int> tree2;
    tree2.insert(75);
    ASSERT_EQUAL(tree2.min_greater_than(75), tree2.end());
    ASSERT_EQUAL(*tree2.min_greater_than(74), 75);
    
    // > 1 elements
    BinarySearchTree<int> tree3;
    tree3.insert(4);
    tree3.insert(6);
    tree3.insert(20);
    tree3.insert(5);
    ASSERT_EQUAL(tree3.min_greater_than(20), tree2.end());
    ASSERT_EQUAL(*tree3.min_greater_than(4), 5);
}















TEST_MAIN()
