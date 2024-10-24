// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>


using namespace std;

// Add your test cases here


TEST(test_empty) {
    // make empty List, "empty()" should return true
    List<int> emptyList;
    assert(emptyList.empty());
    
    // make non-empty List, "empty()" should return false
    List<int> nonEmptyList;
    nonEmptyList.push_front(10);
    assert(nonEmptyList.empty() == false);
}

TEST(test_size) {
    // make empty List, "size()" should return 0
    List<int> emptyList;
    assert(emptyList.size() == 0);
    
    // make List with 3 ints, "size()" should return 3
    List<int> nonEmptyList;
    nonEmptyList.push_back(4);
    nonEmptyList.push_back(7);
    nonEmptyList.push_back(1);
    assert(nonEmptyList.size() == 3);
}

TEST(test_size1) {
    List<int> list1;
    list1.push_back(29);
    list1.push_back(78);
    list1.push_back(39);
    list1.push_back(58);
    assert(list1.size() == 4);
    List<int> list2;
    list2 = list1;
    assert(list2.size() == 4);
    assert(list2.front() == 29);
    assert(list2.back() == 58);
}

TEST(test_push_front) {
    List<int> list1;
    list1.push_front(12);
    ASSERT_EQUAL(list1.front(), 12);
    list1.push_front(10);
    ASSERT_EQUAL(list1.front(), 10);
    ASSERT_EQUAL(list1.back(), 12);
}

TEST(test_push_back) {
    List<int> list1;
    list1.push_back(20);
    ASSERT_EQUAL(list1.front(), 20);
    ASSERT_EQUAL(list1.back(), 20);
    list1.push_back(30);
    ASSERT_EQUAL(list1.front(), 20);
    ASSERT_EQUAL(list1.back(), 30);
}

TEST(test_pop_front) {
    List<int> list1;
    list1.push_front(12);
    ASSERT_EQUAL(list1.front(), 12);
    list1.pop_front();
    assert(list1.empty());
    list1.push_front(34);
    list1.push_front(35);
    list1.pop_front();
    ASSERT_EQUAL(list1.size(), 1);
    ASSERT_EQUAL(list1.back(), 34);
}

TEST(test_pop_back) {
    List<int> list1;
    list1.push_back(100);
    list1.push_back(200);
    list1.pop_back();
    ASSERT_EQUAL(list1.size(), 1);
    ASSERT_EQUAL(list1.front(), 100);
    list1.push_front(34);
    list1.push_back(35);
    list1.pop_back();
    ASSERT_EQUAL(list1.size(), 2);
    ASSERT_EQUAL(list1.back(), 100);
    list1.pop_back();
    list1.pop_back();
    assert(list1.empty());
}

TEST(test_front1) {
    List<int> list1;
    list1.push_back(87);
    assert(list1.front() == 87);
}

TEST(test_front2) {
    List<int> list1;
    list1.push_back(87);
    list1.push_front(78);
    assert(list1.front() == 78);
}

TEST(test_back1) {
    List<int> list1;
    list1.push_front(101);
    assert(list1.back() == 101);
    list1.push_front(100);
    assert(list1.back() == 101);
    assert(list1.front() == 100);
}

TEST(test_back2) {
    List<int> list1;
    list1.push_back(87);
    list1.push_back(78);
    assert(list1.back() == 78);
}

TEST(test_clear) {
    List<int> list1;
    list1.clear();
    assert(list1.empty());
}

TEST(test_clear2){
    List<int> list2;
    list2.push_back(11);
    list2.push_back(12);
    list2.push_back(13);
    list2.push_back(14);
    list2.push_back(15);
    list2.clear();
    assert(list2.empty());
}

TEST(test_clear3){
    List<int> list3;
    list3.push_back(2000);
    list3.clear();
    assert(list3.empty());
}


// TEST(test_copy_all) {
//     List<int> otherList1;
//     otherList1.push_back(201);
//     otherList1.push_back(202);
//     otherList1.push_front(107);
//     otherList1.push_front(108);
    
//     List<int> list1;
//     list1 = otherList1;
//     ASSERT_EQUAL(list1.front(), 108);
//     ASSERT_EQUAL(list1.back(), 202);
//     ASSERT_EQUAL(list1.size(), 4);
// }

// TEST(test_copy_all2) {
//     List<int> otherList2;
//     List<int> list2;
//     list2 = otherList2;
//     ASSERT_EQUAL(list2.size(), 0);

// }

// TEST(test_copy_all3) {
    
//     List<int> otherList3;
//     otherList3.push_back(1000);
//     List<int> list3;
//     list3 = otherList3 ;
//     ASSERT_EQUAL(list3.front(), 1000);
//     ASSERT_EQUAL(list3.back(), 1000);
//     ASSERT_EQUAL(list3.size(), 1);
// }

TEST(test_insert) {
    //empty list, insert 1 int
    List<int> list1;
    List<int>::Iterator it1 = list1.begin();
    list1.insert(it1, 110);
    ASSERT_EQUAL(list1.front(), 110);
}


TEST(test_insert1) {
    // list with 3 elements, inserts before last element,
    // deletes last element, asserts inserted element is in back position
    List<int> list2;
    list2.push_back(121);
    list2.push_back(111);
    list2.push_back(101);
    List<int>::Iterator it2 = list2.end();
    list2.insert(it2, 91);
    list2.pop_back();
    assert(list2.front() == 121);
    assert(list2.back() == 101);
    assert(list2.size() == 3);
}

TEST(test_insert2) {
    // list with 5 elements, inserts before first element,
    // increments iterator 4 times to and then checks that
    // it is at the last element
    List<int> list2;
    list2.push_back(223);
    list2.push_back(245);
    list2.push_back(267);
    list2.push_back(229);
    list2.push_back(290);
    List<int>::Iterator it2 = list2.begin();
    list2.insert(it2, 91);
    ++it2;
    ++it2;
    ++it2;
    ++it2;
    assert(list2.front() == 91);
    assert(*it2 == 290);
}

TEST(test_insert3) {
    List<int> list3;
    list3.push_back(304);
    list3.push_back(305);
    list3.push_back(306);
    list3.push_back(307);
    List<int>::Iterator it3 = list3.begin();
    ++++it3;
    list3.insert(it3, 13);
    List<int>::Iterator it13 = list3.begin();
    ++++it13;
    assert(*it13 == 13);
}

TEST(test_erase) {
    List<int> list1;
    list1.push_back(3);
    list1.push_back(4);
    List<int>::Iterator it1 = list1.begin();
    list1.erase(it1);
    ASSERT_EQUAL(list1.front(), 4);
    ASSERT_EQUAL(list1.back(), 4);
    ASSERT_EQUAL(list1.size(), 1);
}

TEST(test_erase0) {
    List<int> list0;
    list0.push_front(300);
    list0.push_front(301);
    list0.push_front(302);
    List<int>::Iterator it0(++++list0.begin());
    list0.erase(it0);
    assert(list0.back() == 301);
}

TEST(test_erase1) {
    List<int> list1;
    list1.push_back(12);
    list1.push_back(13);
    list1.erase(++list1.begin());
    assert(list1.back() == 12);
}

TEST(test_erase2) {
    List<int> list2;
    list2.push_back(3);
    list2.push_back(4);
    list2.push_front(10);
    List<int>::Iterator it2 = list2.begin();
    list2.erase(it2);
    ASSERT_EQUAL(list2.front(), 3);
    ASSERT_EQUAL(list2.back(), 4);
    ASSERT_EQUAL(list2.size(), 2);
}

TEST(test_erase3) {
    List<int> list2;
    list2.push_back(3);
    list2.push_back(4);
    list2.push_front(10);
    list2.push_front(12);
    List<int>::Iterator it2 = list2.begin();
    ++it2;
    ++it2;
    ++it2;
    list2.erase(it2);
    ASSERT_EQUAL(list2.front(), 12);
    ASSERT_EQUAL(list2.back(), 3);
    ASSERT_EQUAL(list2.size(), 3);
}

TEST(test_erase4) {
    List<int> list4;
    list4.push_back(7);
    list4.erase(list4.begin());
    ASSERT_TRUE(list4.empty());
}

TEST(test_erase5) {
    List<int> list5;
    list5.push_back(7);
    list5.push_back(8);
    list5.push_back(9);
    list5.push_back(10);
    list5.erase(list5.begin());
    assert(list5.front() == 8);
}
/*
TEST(test_erase6) {
    List<int> list6;
    list6.push_back(78);
    list6.push_back(77);
    list6.push_back(76);
    List<int>::Iterator it6(++list6.begin());
    list6.erase(it6);
    ASSERT_EQUAL(*(++it6), 76)
}
 */

TEST(test_iterator_operators) {
    // "==" and "!="
    List<int> list1;
    list1.push_front(71);
    list1.push_front(62);
    List<int>::Iterator it1 = list1.begin();
    List<int>::Iterator it11 = list1.begin();
    List<int>::Iterator it12 = list1.end();
    assert(it1 == it11);
    assert(it1 != it12);
}

TEST(test_iterator_operators2) {
    
    // "++" and "--"
    List<int> list2;
    list2.push_back(100);
    list2.push_back(102);
    List<int>::Iterator it2 = list2.begin();
    ++it2;
    ++it2;
    ASSERT_EQUAL(it2, list2.end());
   
    List<int>::Iterator it22 = list2.begin();
    ++it22;
    --it22;
    ASSERT_EQUAL(it22, list2.begin());

}
    
TEST(test_iterator_operators3) {
    // "*"
    List<int> list3;
    list3.push_back(201);
    list3.push_back(203);
    List<int>::Iterator it3 = list3.begin();
    //List<int>::Iterator it33 = list3.end();
    assert(*it3 == 201);
    //assert(*it33 == 203);
    
}


TEST_MAIN()

