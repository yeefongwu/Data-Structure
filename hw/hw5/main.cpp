//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD ONLY CONTAIN
//       CHANGES TO MoreTests()
//

#include <iostream>
#include <cassert>
#include <list>

#include "unrolled.h"
using namespace std;
// ===================================================================
// This function compares an unrolled linked list to an STL list.  It
// returns true iff the lists are the same size, and contain the same
// elements in the same order.
template <class T>
bool SAME(UnrolledLL<T>& a, std::list<T> &b) {
  if (a.size() != b.size()) return false;
  typename UnrolledLL<T>::iterator a_iter = a.begin();
  typename std::list<T>::iterator b_iter = b.begin();
  while (a_iter != a.end() && b_iter != b.end()) {
    if (*a_iter != *b_iter) return false;
    a_iter++;
    b_iter++;
  }
  assert (a_iter == a.end() && b_iter == b.end());
  return true;
}


// ===================================================================
void BasicTests();
void MoreTests();

int main() {
  BasicTests();
  MoreTests();
  std::cout << "Finished MoreTests()" << std::endl;
}


// ===================================================================
// NOTE: Your internal data structure may be different (& thus print
// differently), depending on how you implement your internal member
// functions.  That's ok!
void BasicTests() {

  // make two matching list of integers, one using an unrolled list,
  // one using an STL list.  They should stay the "SAME" throughout
  // these tests.
  UnrolledLL<int> a;
  std::list<int> b;
  for (int i = 10; i < 30; ++i) {
    a.push_back(i);
    b.push_back(i);
  }

  // iterate through the integers and print them out
  std::cout << "the integers from 10->29" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl << std::endl;
  assert (SAME(a,b));

  // use the output operator to print the underlying representation
  std::cout << "initial" << std::endl;
  a.print(std::cout);
  std::cout << std::endl;

  // testing some basic functions in the class
  std::cout << "some editing with pop & push" << std::endl;
  assert (a.size() == 20);
  assert (a.front() == 10);
  assert (a.back() == 29);
  a.pop_front();
  b.pop_front();
  assert (a.size() == 19);
  assert (a.front() == 11);
  a.pop_back();
  b.pop_back();
  assert (a.size() == 18);
  assert (a.back() == 28);
  a.print(std::cout);
  std::cout << std::endl;
  assert (SAME(a,b));

  // more editing
  std::cout << "more editing with pop & push" << std::endl;
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  a.print(std::cout);
  a.pop_back();
  b.pop_back();
  a.print(std::cout);
  assert (a.size() == 12);
  assert (a.front() == 16);
  assert (a.back() == 27);
  a.push_front(90);
  a.push_front(91);
  a.push_front(92);
  a.push_front(93);
  b.push_front(90);
  b.push_front(91);
  b.push_front(92);
  b.push_front(93);
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 16);
  assert (a.front() == 93);
  assert (SAME(a,b));

  // erase the multiples of 3
  std::cout <<"erase the multiples of 3" << std::endl;
  UnrolledLL<int>::iterator a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter % 3 == 0) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  std::list<int>::iterator b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter % 3 == 0) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 10);
  assert (SAME(a,b));

  // inserting elements
  std::cout << "do some inserts" << std::endl;
  // insert some stuff
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = a.insert(itr,77);
      itr++;
    }
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = b.insert(itr,77);
      itr++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 14);
  assert (SAME(a,b));
  // overflowing an insert
  std::cout << "insert that overflows the node" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 17) {
      itr = a.insert(itr,88);
      itr++;
    }
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 17) {
      itr = b.insert(itr,88);
      itr++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 15);
  assert (SAME(a,b));

  // more erasing
  std::cout << "erasing that removes a node" << std::endl;
  a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter == 77 || *a_iter == 16 || *a_iter == 88) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter == 77 || *b_iter == 16 || *b_iter == 88) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 9);
  assert (SAME(a,b));

}


// ===================================================================
void MoreTests() {

    cout<<"\nStart more test"<<endl;
    UnrolledLL<int> a;
    list<int> b;
    for(int i=0;i<6;i++){
        a.push_back(i);
        b.push_back(i);
    }
    assert(SAME(a,b));


    //testing copy and assignment operation
    UnrolledLL<int> c(a);
    UnrolledLL<int> d;
    d=a;
    cout<<"\ncopy constructor c print"<<endl;
    c.print(cout);
    cout<<"\nassignment operation d print"<<endl;
    d.print(cout);



    //testing corner case for when only one node and insert overflow
    UnrolledLL<int>::iterator itr=a.begin();
    list<int>::iterator itr1=b.begin();
    a.insert(itr,99);
    b.insert(itr1,99);
    assert(SAME(a,b));
    cout<<"\ninsert overflow with just one node"<<endl;
    a.print(cout);

    //testing corner case when its head and insert overflow
    a.pop_front();
    b.pop_front();
    assert(SAME(a,b));
    for(int i=6;i<12;i++){
        a.push_back(i);
        b.push_back(i);
    }
    itr=a.begin();
    itr1=b.begin();
    a.insert(itr,88);
    b.insert(itr1,88);
    assert(SAME(a,b));
    cout<<"\ninsert overflow when head"<<endl;
    a.print(cout);

    //overflow when tail
    itr=a.end();
    itr1=b.end();
    itr--;
    a.insert(itr,77);
    b.insert(itr1,77);
    cout<<"\ninsert overflow when tail"<<endl;
    a.print(cout);
    assert(SAME(a,b));


    //testing the clear function
    a.clear();
    b.clear();
    assert(SAME(a,b));
    cout<<"\nclear function"<<endl;
    a.print(cout);

    //testing copy an empty list
    cout<<"\ntesting copy and assign an empty list"<<endl;
    cout<<"copy i for empty list a and try to print it"<<endl;
    UnrolledLL<int> i(a);
    i.print(cout);
    cout<<"assign j for empty list a and try to print it"<<endl;
    UnrolledLL<int> j;
    j=a;
    j.print(cout);


    //testing clear an empty list
    cout<<"\ntesting empty an already emptied list"<<endl;
    a.clear();
    a.print(cout);

    //testing corner case for pop front and pop back
    cout<<"\ncorner case for pop front when list empty"<<endl;
    a.pop_front();
    cout<<"\ncorner case for pop back when list empty"<<endl;
    a.pop_back();

    //testing for erase
    cout<<"\ntesting case for erase\nbefore erase"<<endl;
    a.push_back(1);
    b.push_back(1);
    itr=a.end();
    itr1=b.end();
    a.print(cout);
    cout<<"after erase"<<endl;
    itr--;
    itr1--;
    a.erase(itr);
    b.erase(itr1);
    a.print(cout);
    assert(SAME(a,b));


    //testing for other type
    UnrolledLL<char> e;
    list<char> f;
    e.push_back('a');
    e.push_back('b');
    e.push_back('c');
    f.push_back('a');
    f.push_back('b');
    f.push_back('c');
    assert(SAME(e,f));
    cout<<"\nchar type e output"<<endl;
    e.print(cout);


    UnrolledLL<float> g;
    list<float> h;
    g.push_back(1.1);
    g.push_back(1.2);
    g.push_back(1.3);
    h.push_back(1.1);
    h.push_back(1.2);
    h.push_back(1.3);
    assert(SAME(g,h));
    cout<<"\nfloat type g output"<<endl;
    g.print(cout);

}
