//
// Created by yeefongwu on 3/7/21.
//

#ifndef HW5_UNROLLED_H
#define HW5_UNROLLED_H

#include <iostream>
#include <cassert>
const int NUM_ELEMENTS_PER_NODE=6;

template<class T>
class Node{
public:
    //constructor
    Node(): num_element(0), next_(NULL), prev_(NULL){}
    Node(const T& v):num_element(0),next_(NULL),prev_(NULL){
        num_element+=1;
        element[0]=v;
    }
    Node(const Node<T>& v):num_element(v.num_element),next_(NULL),prev_(NULL){
        for(int i=0;i<num_element;i++){element[i]=v.element[i];}
    }
    //helper
    bool full(){return num_element==NUM_ELEMENTS_PER_NODE;}
    //member variable
    T element[NUM_ELEMENTS_PER_NODE];
    int num_element;
    Node<T>* next_;
    Node<T>* prev_;
};


template<class T> class UnrolledLL;

template<class T>
class list_iterator{
public:
    //constructor and friend class
    friend class UnrolledLL<T>;
    list_iterator(): ptr_(NULL),offset(0),url(NULL){}
    list_iterator(Node<T>* p,UnrolledLL<T>* u): ptr_(p),offset(0),url(u){}
    list_iterator(Node<T>* p, int i,UnrolledLL<T>* u): ptr_(p),offset(i),url(u){}
    list_iterator(list_iterator<T> const& old):ptr_(old.ptr_),offset(old.offset),url(old.url){}
    //operator
    T& operator*(){return ptr_->element[offset];}

    //pre-increment ++itr
    list_iterator<T>& operator++(){
        if(offset==(ptr_->num_element)-1){
            ptr_=ptr_->next_;
            offset=0;
        }
        else{offset+=1;}
        return *this;
    }
    //post-increment itr++
    list_iterator<T> operator++(int){
        list_iterator<T> temp(*this);
        ++(*this);
        return temp;
    }
    //pre-decrement --itr
    list_iterator<T>& operator--(){
        if(ptr_==NULL){ptr_=url->tail_;offset=url->tail_->num_element-1;}
        else if(offset==0){
            ptr_=ptr_->prev_;
            offset=(ptr_->num_element)-1;
        }
        else{offset-=1;}
        return *this;
    }
    //post-decrement itr--
    list_iterator<T> operator--(int){
        list_iterator<T> temp(*this);
        --(*this);
        return temp;
    }

    // Comparions operators are straightforward
    bool operator==(const list_iterator<T>& r) const {
        return ptr_ == r.ptr_; }
    bool operator!=(const list_iterator<T>& r) const {
        return ptr_ != r.ptr_; }

private:
    Node<T>* ptr_;
    int offset;
    UnrolledLL<T>* url;//for the use of decrement, when heading tail
};



template<class T>
class UnrolledLL{
public:
    //default constructor, copy constructor, assignment operator
    UnrolledLL(): head_(NULL),tail_(NULL),size_(0){}
    UnrolledLL(const UnrolledLL<T>& old){copy_list(old);}
    UnrolledLL& operator= (const UnrolledLL<T>& old);
    ~UnrolledLL(){destroy_list();}

    typedef list_iterator<T> iterator;
    friend list_iterator<T>;

    //simple accessor and modifiers
    unsigned int size() const {return size_;}
    void clear(){
        if(size_==0){std::cout<<"LIST IS ALREADY EMPTY"<<std::endl;}
        destroy_list();
    }

    //read/write access to contents
    const T& front() const {return head_->element[0];}
    T& front() {return head_->element[0];}
    const T& back() const {return tail_->element[tail_->num_element-1];}
    T& back() {return tail_->element[tail_->num_element-1];}

    //modify the linked list structure
    void push_front(const T& v);
    void pop_front();
    void push_back(const T& v);
    void pop_back();
    void print(std::ostream& ostr);

    iterator erase(iterator itr);
    iterator insert(iterator itr, const T& v);
    iterator begin() {return iterator(head_,this);}
    iterator end() {return iterator(NULL,this);}



private:
    //private helper function
    void copy_list(const UnrolledLL<T>& old);
    void destroy_list();

    //representation
    Node<T>* head_;
    Node<T>* tail_;
    unsigned int size_;//total number of element


};

//assignment operation, destroy the old one copy the new one if its not the same
template<class T>
UnrolledLL<T> & UnrolledLL<T>::operator=(const UnrolledLL<T> & old){
    if(&old!=this){
        destroy_list();
        copy_list(old);
    }
    return *this;
}

//add an element to the front
template<class T>
void UnrolledLL<T>::push_front(const T &v) {
    if(head_==NULL){//in case its an empty list
        head_= tail_=new Node<T>(v);
    }
    else{
        if(head_->full()){//if the node is full create a new node and make it head
            Node<T>* newp = new Node<T>(v);
            newp->next_=head_;
            head_->prev_=newp;
            head_=newp;
        }
        else{//normal case
            for(int i=head_->num_element-1;i>=0;i--){head_->element[i+1]=head_->element[i];}
            head_->num_element+=1;
            head_->element[0]=v;
        }
    }
    ++size_;
}

//remove the first element
template<class T>
void UnrolledLL<T>::pop_front() {
    if(head_==NULL){//in case list is empty
        std::cout<<"WARNING NO NODE EXIST"<<std::endl;
        return;
    }
    if(size_==1 && head_->num_element==1){//in case only one node and one element in that node, that way empty the list
        head_=NULL;
        tail_=NULL;
    }
    else{//when there is more than one node
        if(head_->num_element==1){//when head node has one element, pop it, change the head to the next node
            Node<T>* temp;
            temp=head_->next_;
            delete head_;
            head_=temp;
            head_->prev_=NULL;
        }
        else{//normal case
            for(int i=0;i<head_->num_element-1;i++){head_->element[i]=head_->element[i+1];}
            head_->num_element-=1;
        }
    }
    --size_;
}

//add an element to the last
template<class T>
void UnrolledLL<T>::push_back(const T &v) {
    if(tail_==NULL){//in case list is empty
        head_=new Node<T>(v);
        tail_=head_;
    }
    else{
        if(tail_->full()){//in case tail is full, create a new node and make it tail
            Node<T>* newp = new Node<T>(v);
            newp->prev_=tail_;
            tail_->next_=newp;
            tail_=newp;
        }
        else{//normal case
            tail_->element[tail_->num_element]=v;
            tail_->num_element+=1;
        }
    }
    ++size_;
}

//pop out element at last
template<class T>
void UnrolledLL<T>::pop_back() {
    if(tail_==NULL){//in case empty list
        std::cout<<"WARNING NO NODES EXIST."<<std::endl;
        return;
    }
    if(size_==1 && tail_->num_element==1){//if there is only one node with one element, make it empty
        head_=NULL;
        tail_=NULL;
    }
    else{
        if(tail_->num_element==1){//if tail has one element, make the previous one tail
            Node<T>* temp;
            temp=tail_->prev_;
            delete tail_;
            tail_=temp;
            temp->next_=NULL;
        }
        else{//normal case
            tail_->num_element-=1;
        }
    }
    --size_;
}

//erase an element from a give iterator
template<class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
    if(size_==0){//in case empty list
        std::cout<<"WARNING NO NODES EXIST."<<std::endl;
        exit(1);
    }
    size_--;
    if(itr.ptr_->num_element==1){
        if(size_==0) {//in case only one node and one element, emtpy the list
            delete head_;
            head_=tail_=NULL;
            return iterator(NULL,this);}
        else if(itr.ptr_==head_){//if head has one element, change head
            itr.ptr_->next_->prev_=NULL;
            delete head_;
            head_=itr.ptr_->next_;
            delete itr.ptr_;
            return iterator(head_,this);

        }
        else if(itr.ptr_==tail_){//if tail has one element, change tail
            itr.ptr_->prev_->next_=NULL;
            delete tail_;
            tail_=itr.ptr_->prev_;
            delete itr.ptr_;
            return iterator(NULL,this);
        }
        else{//other change prev and next
            Node<T>* temp = itr.ptr_->next_;
            itr.ptr_->next_->prev_ = itr.ptr_->prev_;
            itr.ptr_->prev_->next_ = itr.ptr_->next_;
            delete itr.ptr_;
            return iterator(temp,this);
        }
    }
    else{//normal case
        for(int i=itr.offset;i<itr.ptr_->num_element-1;i++){itr.ptr_->element[i]=itr.ptr_->element[i+1];}
        itr.ptr_->num_element-=1;
        if (itr.offset == itr.ptr_->num_element){
            return iterator(itr.ptr_->next_,this);}
        else{
            return itr;}
    }
}


//insert an element in given iterator
template<class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T &v) {
    ++size_;
    if(itr.ptr_==NULL){return iterator(NULL,this);}
    if(itr.ptr_->full()){//in case node is full create two new node pointer and split the itr.ptr->element into these two.  n1 is before n2
        Node<T>* n1= new Node<T>;
        Node<T>* n2=new Node<T>;
        if(itr.offset!=NUM_ELEMENTS_PER_NODE-1) {
            n1->num_element=itr.offset+1;
            n2->num_element=NUM_ELEMENTS_PER_NODE-itr.offset;
            for (int i = 0; i < itr.offset; i++) {
                n1->element[i] = itr.ptr_->element[i];
            }
            n1->element[itr.offset] = v;
            for (int i = 0; i < n2->num_element; i++) {
                n2->element[i] = itr.ptr_->element[i + itr.offset];
            }
        }
        else{
            n1->num_element=itr.ptr_->num_element;
            n2->num_element=1;
            for(int i=0;i<NUM_ELEMENTS_PER_NODE;i++){
                n1->element[i]=itr.ptr_->element[i];
            }
            n2->element[0]=v;
        }
        n1->next_=n2;
        n2->prev_=n1;
        if(head_==tail_){//in case only one node, split then into two
            head_=n1;
            tail_=n2;
        }
        else if(itr.ptr_==head_){//in case node is head change n1 to head
            itr.ptr_->next_->prev_=n2;
            n2->next_=itr.ptr_->next_;
            n1->prev_=NULL;
            head_=n1;
        }
        else if(itr.ptr_==tail_){//in case node is tail change n2 to tail
            itr.ptr_->prev_->next_=n1;
            n1->prev_=itr.ptr_->prev_;
            n2->next_=NULL;
            tail_=n2;
        }
        else {//normal case
            itr.ptr_->prev_->next_ = n1;
            itr.ptr_->next_->prev_ = n2;
            n2->next_ = itr.ptr_->next_;
            n1->prev_ = itr.ptr_->prev_;
        }
        delete itr.ptr_;
        return iterator(n1,n1->num_element-1,this);
    }
    else{//not full
        for(int i=itr.ptr_->num_element;i>itr.offset;i--){itr.ptr_->element[i]=itr.ptr_->element[i-1];}
        itr.ptr_->element[itr.offset]=v;
        itr.ptr_->num_element+=1;
        return itr;
    }
}

//copy the list
template<class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T> &old) {
    size_=old.size_;
    if(size_==0){//copy an empty list
        head_=tail_=0;
        std::cout<<" COPY EMPTY LIST"<<std::endl;
        return;
    }
    // Create a new head node.
    head_ = new Node<T>(*old.head_);
    // tail_ will point to the last node created and therefore will move
    // down the new list as it is built
    tail_ = head_;
    // old_p will point to the next node to be copied in the old list
    Node<T>* old_p = old.head_ -> next_;
    // copy the remainder of the old list, one node at a time
    while (old_p) {
        tail_ -> next_ = new Node<T>(*old_p);
        tail_ -> next_ -> prev_ = tail_;
        tail_ = tail_ -> next_;
        old_p = old_p -> next_;
    }
}

//destroy the list use for clear and destructor
template<class T>
void UnrolledLL<T>::destroy_list() {
    if(size_==0){return;}
    Node<T>* temp=head_;
    while(temp!=tail_){
        head_=head_->next_;
        delete temp;
        temp=head_;
    }
    delete temp;
    head_=NULL;
    tail_=NULL;
    size_=0;
}

//print function
template<class T>
void UnrolledLL<T>::print(std::ostream& ostr){
    if(size_==0){//in case no node
        std::cout<<"WARNING NO NODE EXIST."<<std::endl;
        return;
    }
    list_iterator<T> itr;
    ostr<<"UnrolledLL, size: "<<size_<<std::endl;
    for(itr=begin();itr!=end();itr.ptr_=itr.ptr_->next_){
        ostr<<" node:["<<itr.ptr_->num_element<<"] ";
        for(int i=0;i<itr.ptr_->num_element;i++){
            ostr<<itr.ptr_->element[i]<<" ";
        }
        ostr<<std::endl;
    }
}
#endif //HW5_UNROLLED_H
