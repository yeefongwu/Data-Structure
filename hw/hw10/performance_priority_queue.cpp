#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

// defined in performance.cpp
void usage();

//priority queue always pop out the smallest one if using greater, so in a way already sorted
template<class T>
void pq_sort(priority_queue<T,vector<T>,greater<T> >& pq,ostream& ostr, int& output_count){
    while(!pq.empty()){
        ostr<<pq.top()<<endl;
        pq.pop();
        output_count++;
    }
}

//pq cant remove duplicate
template<class T>
void pq_remove_duplicates(priority_queue<T,vector<T>,greater<T> >& pq,ostream& ostr, int& output_count){
    output_count=0;
    ostr<<"X"<<endl;

}

//pq mode is similar to a sorted list
template<class T>
void pq_mode(priority_queue<T,vector<T>,greater<T> >& pq,ostream& ostr, int& output_count){
    output_count=1;
    int mode_number=1;
    int current_number=0;
    T mode=pq.top();
    pq.pop();
    T current;
    //loop until empty
    while(!pq.empty()){
        T temp=pq.top();
        //if same
        if(temp==mode){mode_number+=1;}
        else{
            //if not the mode but same as previous one
            if(temp==current){
                current_number+=1;
                //in case mode change
                if(current_number>mode_number){
                    mode=temp;
                    mode_number=current_number;
                    current_number=0;
                }
            }
            else{
                // different
                current=temp;
                current_number=1;
            }
        }
        pq.pop();
    }
    ostr<<mode<<endl;
}

//because it's in a way sorted so like list closest pair
void pq_closest_pair(priority_queue<int,vector<int>,greater<int> >& pq,ostream& ostr, int& output_count){
    int best;
    bool flag=true;
    output_count=2;
    int first = pq.top();
    int second;
    int prev=first;
    pq.pop();
    while(!pq.empty()){
        int temp=pq.top();
        if(temp!=prev){
            int diff = temp - prev;
            if(flag || diff<best){
                flag= false;
                best=diff;
                second=temp;
                first=prev;
            }
            prev=temp;
        }
        pq.pop();
    }
    ostr<<first<<endl;
    ostr<<second<<endl;
}

//in a way sorted so just print out as required
template<class T>
void pq_first_sorted(priority_queue<T,vector<T>,greater<T> >& pq,ostream& ostr, int& output_count,int optional_arg){
    int i=0;
    while(i!=optional_arg){
        ostr<<pq.top()<<endl;
        pq.pop();
        i++;
    }
}

//it cant find longest substring because cant compare two string
void pq_longest_substring(priority_queue<string,vector<string>,greater<string> >& pq,ostream& ostr, int& output_count){
    output_count=0;
    ostr<<"X"<<endl;
}

void priority_queue_test(const std::string &operation, const std::string &type,
                         std::istream &istr, std::ostream &ostr,
                         int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your priority_queue like this:

  // std::priority_queue<std::string,std::vector<std::string> > pq;
  // (this will make a "max" priority queue, with big values at the top)

  // OR
  
  // std::priority_queue<std::string,std::vector<std::string>, std::greater<std::string> > pq;
  // (this will make a "min" priority queue, with big values at the bottom)

  if(type=="string"){
      priority_queue<string, vector<string>, greater<string> > pq;
      string mstring;
      input_count=0;
      while(istr>>mstring){
          pq.push(mstring);
          input_count++;
      }
      if      (operation == "sort")              { pq_sort                (pq,ostr,output_count); }
      else if (operation == "remove_duplicates") { pq_remove_duplicates   (pq,ostr,output_count); }
      else if (operation == "mode")              { pq_mode                (pq,ostr,output_count); }
          // "closest_pair" not available for strings
      else if (operation == "first_sorted")      { pq_first_sorted        (pq,ostr,output_count,optional_arg); }
      else if (operation == "longest_substring") { pq_longest_substring   (pq,ostr,output_count); }
      else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }

  }
  else if(type=="integer"){
      priority_queue<int, vector<int>, greater<int> > pq;
      int v;
      input_count=0;
      while(istr>>v){
          pq.push(v);
          input_count++;
      }
      if      (operation == "sort")              { pq_sort                (pq,ostr,output_count); }
      else if (operation == "remove_duplicates") { pq_remove_duplicates   (pq,ostr,output_count); }
      else if (operation == "mode")              { pq_mode                (pq,ostr,output_count); }
      else if (operation == "closest_pair")      { pq_closest_pair        (pq,ostr,output_count); }
      else if (operation == "first_sorted")      { pq_first_sorted        (pq,ostr,output_count,optional_arg); }
          // "longest_substring" not available for integers
      else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }

  }
  else{
      std::cerr << "Error: DATA STRUCTURE NOT IMPLEMENTED" << std::endl;
      exit(0);
  }
}
