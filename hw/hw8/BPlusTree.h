/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <list>
#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE
///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree;

template <class T>
class BPlusTreeNode{
public:
    BPlusTreeNode() : parent(NULL) {};
    bool is_leaf();
    bool contains(const T& key);

    //For grading only. This is bad practice to have, because
    //it exposes a private member variable.
    BPlusTreeNode* get_parent() { return parent; }

    //We need this to let BPlusTree access private members
    friend class BPlusTree<T>;
private:
    bool contains(const T& key,std::size_t low,std::size_t high);
    std::vector<T> keys;
    std::vector<BPlusTreeNode*> children;
    BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
    for(unsigned int i=0; i<children.size(); i++){
        if(children[i]){
            return false;
        }
    }
    return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
    return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
    if(low>high){
        return false;
    }
    if(low==high){
        return key == keys[low];
    }
    std::size_t mid = (low+high)/2;
    if(key<=keys[mid]){
        return contains(key,0,mid);
    }
    else{
        return contains(key,mid+1,high);
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

template<class T>
class BPlusTree{
public:
    // default constructor and copy constructor and destructor
    BPlusTree(int n) {size_=n;root_=NULL;}
    BPlusTree(const BPlusTree<T>& old) {
        this->size_=old.size_;
        this->root_ = this->copy_tree(old.root_);
    }
    ~BPlusTree() {this->destroy_tree(root_);root_=NULL;}

    //helpger function
    BPlusTreeNode<T>* find(const T& value);
    void insert(const T& value);
    void print_sideways(std::ostream& ostr){print_sideways_help(ostr, root_, 0);}
    void print_BFS(std::ostream& ostr);

private:
    //private member
    int size_;
    BPlusTreeNode<T>* root_;
    //private member function
    BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* old_root);
    void destroy_tree(BPlusTreeNode<T>* BPTN);
    void insert_help(const T& value,BPlusTreeNode<T>*& temp);
    void split(const T& value,BPlusTreeNode<T>*& temp);
    void print_sideways_help(std::ostream& ostr,BPlusTreeNode<T>* BPTN,const int i);

};

//copy tree used for copy constructor recursively call until all part are copied
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::copy_tree(BPlusTreeNode<T>* old) {
    BPlusTreeNode<T>* temp = new BPlusTreeNode<T>;
    temp->keys = old->keys;
    temp->parent = old->parent;
    for (int i = 0; i < old->children.size(); ++i)
        temp->children.push_back(copy_tree(old->children[i]));
    return temp;
}

//destroy tree is for destructor it will  recursively call until all part are deleted
template <class T>
void BPlusTree<T>::destroy_tree(BPlusTreeNode<T>* BPTN) {
    if(BPTN){
        for (int i = 0; i < BPTN->children.size(); ++i)
            destroy_tree(BPTN->children[i]);

        delete BPTN;
    }
}

//find function is using while loop to keep going down if the temp is not a leaf node
//return a leaf node either exist value or have value that supposed to be insert at
template<class T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T &value) {
    if(root_==NULL){return NULL;}
    BPlusTreeNode<T>* temp=root_;
    while(!temp->is_leaf()){
        bool flag=true;
        for(int i=0;i<temp->keys.size();i++){
            if(value<temp->keys[i]){temp=temp->children[i];flag=false;break;}
        }
        if(flag){temp=temp->children[temp->children.size()-1];}
    }
    return temp;
}


//insert function will create a new root if tree is empty
//otherwise it will call the helper function insert help

template<class T>
void BPlusTree<T>::insert(const T &value) {
    if(root_==NULL){
        root_=new BPlusTreeNode<T>;
        root_->keys.push_back(value);
        return;
    }
    BPlusTreeNode<T>* temp=root_;
    insert_help(value,temp);

}

//insert help is a recursive function that keep calling until it reach the leaf nod
//after each insert help it will go through a split function that check overflow and fix that
template<class T>
void BPlusTree<T>::insert_help(const T &value, BPlusTreeNode<T>*& temp) {
    if(temp==find(value)){//when it hit the leaf node
        bool flag=true;
        for(typename std::vector<T>::iterator itr=temp->keys.begin();itr!=temp->keys.end();itr++){
            if(value<*itr){flag=false;temp->keys.insert(itr,value);break;}
        }
        if(flag){temp->keys.push_back(value);}
        split(value,temp);
        return;
    }
    //normal case when its not leaf node
    for(int i=0;i<temp->keys.size();i++){
        if(value<temp->keys[i]){
            insert_help(value,temp->children[i]);
            split(value,temp);
            return;
        }
    }
    insert_help(value,temp->children[temp->keys.size()]);
    split(value,temp);
}

//split function used to check overflow and if it does split node and change parent and children relatively
template<class T>
void BPlusTree<T>::split(const T &value, BPlusTreeNode<T>*& temp){
    //if it's key size is not full, -1 because when size is 3 only 2 keys are allowed in one node
    if(temp->keys.size()<=size_-1){return;}
    //when the node is a leaf node
    if(temp->is_leaf()){
        //first half of the node is the origin one, second half is the new one
        //in case of odd number of key origin one will have one less key than new one
        int first=temp->keys.size()/2;
        int second=temp->keys.size()-first;
        BPlusTreeNode<T>* new_child=new BPlusTreeNode<T>;
        //when the second one reach the number of keys stop, each time take one from the origin node
        // and add to front of new node and then pop that one out
        while(new_child->keys.size()!=second){
            new_child->keys.insert(new_child->keys.begin(),temp->keys.back());
            temp->keys.pop_back();
        }
        //in case its a leaf and a root which makes the new parent the new root
        if(root_==temp){
            BPlusTreeNode<T>* new_parent=new BPlusTreeNode<T>;
            temp->parent=new_parent;
            new_child->parent=new_parent;
            new_parent->children.push_back(temp);
            new_parent->children.push_back(new_child);
            new_parent->keys.push_back(new_child->keys.front());
            root_=new_parent;
        }
        //when the leaf node has parent
        else{
            bool flag=true;
            new_child->parent=temp->parent;
            //find out where the new child will be insert in it's parent key and children
            for(int j=0;j<temp->parent->keys.size();j++){
                if(new_child->keys.back()<temp->parent->keys[j]){
                    temp->parent->keys.insert(temp->parent->keys.begin()+j,new_child->keys[0]);
                    temp->parent->children.insert(temp->parent->children.begin()+j+1,new_child);
                    flag=false;
                    break;
                }
            }
            //when it is the largest one compare to other key and children
            if(flag){
                temp->parent->keys.push_back(new_child->keys[0]);
                temp->parent->children.push_back(new_child);
            }
        }
    }
    //in case the node is not a leaf, the code is similar to the leaf node, it have to change its children node only when overflow the one that will go to parent
    //will not stay in its original node key anymore
    else{
        int first=temp->keys.size()/2;
        int second=temp->keys.size()-first;
        BPlusTreeNode<T>* new_child=new BPlusTreeNode<T>;
        //split one node into 2
        while(new_child->keys.size()!=second){
            new_child->keys.insert(new_child->keys.begin(),temp->keys.back());
            temp->keys.pop_back();
        }
        //split their children into 2
        while(new_child->children.size()!=new_child->keys.size()){
            new_child->children.insert(new_child->children.begin(),temp->children.back());
            new_child->children[0]->parent=new_child;
            temp->children.pop_back();
        }
        //in case the node's is the root
        if(temp->parent==NULL){
            BPlusTreeNode<T>* new_parent=new BPlusTreeNode<T>;
            temp->parent=new_parent;
            new_child->parent=new_parent;
            new_parent->children.push_back(temp);
            new_parent->children.push_back(new_child);
            new_parent->keys.push_back(new_child->keys.front());
            new_child->keys.erase(new_child->keys.begin());
            root_=new_parent;
        }
        //normal case when node has parent, the while loop wil first insert new child into the parent keys and children
        //then it will erase the first key of the children
        else{
            bool flag=true;
            new_child->parent=temp->parent;
            for(int j=0;j<temp->parent->keys.size();j++){
                if(new_child->keys.back()<temp->parent->keys[j]){
                    temp->parent->keys.insert(temp->parent->keys.begin()+j,new_child->keys[0]);
                    temp->parent->children.insert(temp->parent->children.begin()+j,new_child);
                    new_child->keys.erase(new_child->keys.begin());
                    flag=false;
                    break;
                }
            }
            //in case it's the biggest compare to parents other children
            if(flag){
                temp->parent->keys.push_back(new_child->keys[0]);
                temp->parent->children.push_back(new_child);
                new_child->keys.erase(new_child->keys.begin());
            }
        }
    }
}


//print side way help is recursively call until the BPTN is NULL which is leaf node
template <class T>
void BPlusTree<T>::print_sideways_help(std::ostream &ostr, BPlusTreeNode<T>*BPTN, const int i){
    if(root_==NULL){ostr<<"Tree is empty."<<std::endl;return;}
    if(BPTN==NULL){return;}
    int left = BPTN->children.size() / 2;
    //go to the left
    for(int j=0;j<left;j++){
        print_sideways_help(ostr,BPTN->children[j],i+1);
    }
    for (int j = 0; j < i; j++){ostr << '\t';}
    ostr << BPTN->keys[0];

    for(int j=1;j<BPTN->keys.size();j++){ostr<<","<<BPTN->keys[j];}
    ostr<<std::endl;
    //go to the right
    for(int j=left;j<BPTN->children.size();j++){
        print_sideways_help(ostr,BPTN->children[j],i+1);
    }
}

//print bfs print out tree in breath first by using while loop to add each level into the list
//and extract it and push back its children into the list keep doing it until list is empty
//using level list is easier for the switch line when level are different, using list instead of vector and map
//is because list has pop front which is the fastest.
template <class T>
void BPlusTree<T>::print_BFS(std::ostream& ostr){
    if(root_==NULL){ostr<<"Tree is empty."<<std::endl;return;}
    //list used to collect all the key, level used to collect the number of node in one level
    std::list<BPlusTreeNode<T>*> bfs_list;
    std::list<int> bfs_level;
    bfs_list.push_back(root_);
    bfs_level.push_back(0);
    //flag level is used to determine which level we are currently in
    int flag_level=0;
    while(!bfs_list.empty()){
        //release one node and add all the children into the back of the list, add number of level into the level list as well
        BPlusTreeNode<T>* current_node=bfs_list.front();
        int current_level=bfs_level.front();
        for(int i=0;i<current_node->children.size();i++){
            bfs_list.push_back(current_node->children[i]);
            bfs_level.push_back(current_level+1);
        }
        bfs_list.pop_front();
        bfs_level.pop_front();
        //if same level go with tab, if other level switch line
        if(current_level!=flag_level){ostr<<std::endl;}
        else if(current_level==flag_level && current_level>0){ostr<<'\t';}
        //print out all the keys
        for(int i=0;i<current_node->keys.size()-1;i++){
            ostr<<current_node->keys[i]<<',';
        }
        ostr<<current_node->keys.back();
        flag_level=current_level;
    }
    ostr<<std::endl;
}

#endif

