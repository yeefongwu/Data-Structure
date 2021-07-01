//
// Created by yeefongwu on 2/22/21.
//

#ifndef HW3_JAGGED_ARRAY_H
#define HW3_JAGGED_ARRAY_H

using namespace std;
template <class T>  class JaggedArray{
public:
    //typedef
    typedef unsigned int size_type;
    //constructor
    JaggedArray(){this->create();}
    JaggedArray(size_type b){this->create(b);}
    JaggedArray(const JaggedArray& ja){this->copy(ja);}
    //operator
    JaggedArray& operator=(const JaggedArray& ja);

    //destructor
    ~JaggedArray(){this->empty();};
    void empty();
    //accessors
    bool isPacked() const {return m_pack_data!=NULL;}
    size_type numElements() const {return element;}
    size_type numBins() const {return bin;}
    size_type numElementsInBin(const int& b) const;
    const T getElement(const size_type& b, const size_type& el) const;
    //modifier
    void addElement(const size_type& b, const T& e);
    void removeElement(const size_type& b, const size_type& el);
    void print();
    void unpack();
    void pack();
    void clear();
private:
    //private member function
    void create();
    void create(size_type b);
    void copy(const JaggedArray<T>& ja);
    //representation
    size_type element;//total element
    size_type bin;//number of bins
    size_type k;//the number of elements in the largest bin
    size_type* offsets;
    size_type* counts;
    T* m_pack_data;
    T** m_unpack_data;

};

//empty create all data as NULL
template<class T> void JaggedArray<T>::create(){
    m_pack_data=NULL;
    m_unpack_data=NULL;
    offsets=NULL;
    counts=NULL;
    element = bin = 0;
}

//create with bin number and other as 0 or null to make sure initialized
template<class T> void JaggedArray<T>::create(size_type b){
    element=k=0;
    bin=b;
    m_unpack_data=new T*[b];
    for(int i=0;i<b;i++){
        m_unpack_data[i]=NULL;
    }
    m_pack_data=NULL;
    offsets= NULL;
    counts = new size_type[b];
    for(int i=0;i<b;i++){
        counts[i]=0;
    }
}

//for copy constructor and operator=     give value for all data
template<class T> void JaggedArray<T>::copy(const JaggedArray<T>& ja){
    create();//make sure initialize, set all data as NULL
    this->element=ja.element;
    this->bin=ja.bin;
    if(ja.isPacked()){//if its packed, copy offset and m_pack_data to this
        this->offsets = new size_type [this->bin];
        for(int i=0;i<bin;i++){
            this->offsets[i]=ja.offsets[i];
        }
        this->m_pack_data = new T[this->element];
        for(int i=0;i<this->element;i++){
            this->m_pack_data[i]=ja.m_pack_data[i];
        }
    }

    else{//if its not packed, copy counts and m_unpack_data
        this->counts = new size_type [this->bin];
        for(int i=0;i<this->bin;i++){
            this->counts[i]=ja.counts[i];
        }
        this->m_unpack_data=new T*[this->bin];
        for(int i=0;i<this->bin;i++){
            this->m_unpack_data[i]=new T[counts[i]];
            for(int j=0;j<this->counts[i];j++){
                this->m_unpack_data[i][j]=ja.m_unpack_data[i][j];
            }
        }

    }
}



//operator= using copy and empty
template<class T> JaggedArray<T>& JaggedArray<T>::operator=(const JaggedArray<T> &ja) {
    if (this != &ja) {//in case they are same cause alias
        this->empty();//delete the original data and set them as NULL
        this->bin=this->element=0;//turn bin and element into 0 as well
        this->copy(ja);//copy them
    }
    return *this;
}


//make delete every data and set them as NULL to prevent memory leak and uninitialized for destructor
template<class T> void JaggedArray<T>::empty() {
    if(counts!=NULL){delete [] counts; counts=NULL;}
    if(offsets!=NULL){delete [] offsets; offsets=NULL;}
    if(m_pack_data!=NULL){delete [] m_pack_data; m_pack_data=NULL;}
    if(m_unpack_data!=NULL){
        for(int i=0;i<bin;i++){
            if(m_unpack_data[i]!=NULL){delete [] m_unpack_data[i];m_unpack_data[i]=NULL;}
        }
        delete [] m_unpack_data;
        m_unpack_data=NULL;
    }
}


//clear will delete counts and unpack_data because its only work under unpack mode so no need to change offset and pack_Data. ALso turn element into 0 but do not set bin into 0
template<class T> void JaggedArray<T>::clear() {
    delete []counts;
    for(int i=0;i<bin;i++){
        delete []m_unpack_data[i];
    }
    delete [] m_unpack_data;
    element=0;
    counts=new size_type[bin];
    for(int i=0;i<bin;i++){
        counts[i]=0;
    }
    m_unpack_data=new T*[bin];
    for(int i=0;i<bin;i++){
        m_unpack_data[i]=NULL;
    }
}


//packed function NULL the counts and m_unpack_data after turn them into offsets and m_pack_data
template<class T> void JaggedArray<T>::pack(){
    m_pack_data=new T[element];
    offsets=new size_type[bin];
    offsets[0]=0;//first offset is 0
    for(int i=0;i<bin-1;i++){
        offsets[i+1]=counts[i]+offsets[i];
    }
    int x=0;
    for(int i=0;i<bin;i++){
        for(int j=0;j<counts[i];j++){
            m_pack_data[x]=m_unpack_data[i][j];
            x+=1;
        }
        delete [] m_unpack_data[i];
    }
    delete [] counts;
    delete [] m_unpack_data;
    counts=NULL;
    m_unpack_data=NULL;
}

//unpack function NULL the offset and m_pack_data after turn them into counts and m_unpack_data
template<class T> void JaggedArray<T>::unpack() {
    counts = new size_type [bin];
    for(int i=0;i<bin-1;i++){
        counts[i]=offsets[i+1]-offsets[i];
    }
    counts[bin-1]=element-offsets[bin-1];
    m_unpack_data=new T*[bin];
    int x=0;
    for(int i=0;i<bin;i++){
        m_unpack_data[i]=new T[counts[i]];
        for(int j=0;j<counts[i];j++){
            m_unpack_data[i][j]=m_pack_data[x];
            x+=1;
        }
    }
    delete [] m_pack_data;
    delete [] offsets;
    m_pack_data=NULL;
    offsets=NULL;
}

//add element with number of bin 'b' and the element 'e'
template<class T> void JaggedArray<T>::addElement(const size_type& b, const T& e) {
    if(b>bin || b<0){cerr<<"bin number is wrong."<<endl; exit(1);}//if out of index quit
    else{
    if(!isPacked()){//if its unpack
        counts[b]+=1;
        element+=1;
        T* temp=new T[counts[b]];
        for(int i=0;i<counts[b]-1;i++){
            temp[i]=m_unpack_data[b][i];
        }
        temp[counts[b]-1]=e;
        delete [] m_unpack_data[b];
        m_unpack_data[b]=temp;
    }
    else{//if its pack can't work
        cerr<<"Pack mode."<<endl;
        exit(1);
    }}
}

template<class T> void JaggedArray<T>::removeElement(const size_type &b, const size_type &el) {
    if(b>bin || b<0){cerr<<"bin number is wrong."<<endl;exit(1);}//if out of index quit
    else{
    if(!isPacked()){//if its unpack
        counts[b]-=1;
        element-=1;
        T* temp=new T[counts[b]];
        for(int i=0;i<el;i++){
            temp[i]=m_unpack_data[b][i];
        }
        for(int i=el;i<counts[b];i++){
            temp[i]=m_unpack_data[b][i+1];
        }
        delete [] m_unpack_data[b];
        m_unpack_data[b]=temp;
    }
    else{//if its pack cant work
        cerr<<"Pack mode."<<endl;
        exit(1);
    }}
}

//print function print out the table
template<class T> void JaggedArray<T>::print()  {
    if(!isPacked()){//in case of unpack
        k=0;//k is the number of element in largest bin   initialized it everytime, in case of add element or remove element or clear
        for(int i=0;i<bin;i++){
            if(counts[i]>k){k=counts[i];}
        }
        cout<<"unpacked JaggedArray"<<endl;
        cout<<"  num_bins: "<<bin<<endl;
        cout<<"  num_elements: "<<element<<endl;
        cout<<"  counts:  ";
        for(int i=0;i<bin;i++){
            cout<<counts[i]<<" ";
        }
        cout<<endl;
        cout<<"  values:  ";
        for(int i=0;i<k;i++){
            if(i!=0){cout<<"           ";}
            for(int j=0;j<bin;j++){
               if(counts[j]>i){cout<<m_unpack_data[j][i]<<" ";}
               else{cout<<"  ";}
            }
            cout<<endl;
        }
        if(k==0){cout<<endl;}//if there is no data, it has been clear
    }

    if(isPacked()){//in case of pack
        cout<<"packed JaggedArray"<<endl;
        cout<<"  num_bins: "<<bin<<endl;
        cout<<"  num_elements: "<<element<<endl;
        cout<<"  offsets:  ";
        for(int i=0;i<bin;i++){
            cout<<offsets[i]<<" ";
        }
        cout<<endl;
        cout<<"  values:   ";
        for(int i=0;i<element;i++){
            cout<<m_pack_data[i]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}


//using number of bin 'b' and the location in that bin 'el' to get the element in that location
template<class T> const T JaggedArray<T>::getElement(const size_type &b, const size_type &el) const {
    if(b>=bin || b<0){cerr<<"Bin number is wrong."<<endl;exit(1);}//in case out of index
    //else if(el<0 || el>counts[b]){cerr<<"Element location is wrong."<<endl;exit(1);}
    else{
    if(!isPacked()){//unpack mode
        return m_unpack_data[b][el];
    }
    else{//pack mode
        return m_pack_data[offsets[b]+el];
    }}
}


//using number of bin 'b' to get how many element in that bin
template<class T> unsigned int JaggedArray<T>::numElementsInBin(const int &b) const {
    if(b>bin || b<0){cerr<<"Bin number is wrong."<<endl;exit(1);}//in case out of index
    else{
    if(!isPacked()){//unpack mode
        return counts[b];
    }
    else{//pack mode
        if(b==bin-1){//except the last one
            return element-offsets[b];
        }
        else{//last one is different
            return offsets[b+1]-offsets[b];
        }
    }}
}





#endif //HW3_JAGGED_ARRAY_H

