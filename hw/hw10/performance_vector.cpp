#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// defined in performance.cpp
void usage();

template <class T>
void vector_sort(std::vector<T> &vec, std::ostream &ostr, int &output_count) {
  // use the vector sort algorithm
  sort(vec.begin(),vec.end());
  output_count = vec.size();
  for (int i = 0; i < output_count; i++)
    ostr << vec[i] << "\n";
}


template <class T>
void vector_remove_duplicates(const std::vector<T> &vec, std::ostream &ostr, int &output_count) { 
  // don't reorder the elements, just do all pairwise comparisons
  output_count = 0;
  for (int i = 0; i < (int)vec.size(); i++) {
    bool dup = false;
    for (int j = 0; j < i; j++) {
      if (vec[i] == vec[j]) {
        dup = true;
        break;
      }
    }
    // if it has not already been added to the output list
    if (!dup) {
      ostr << vec[i] << "\n";
      output_count++;
    }
  }
}


template <class T>
void vector_mode(std::vector<T> &vec, std::ostream &ostr, int &output_count) {
  // use the vector sort algorithm
  sort(vec.begin(),vec.end());
  int current_count = 1;
  T mode;
  int mode_count = 0;
  // keep track of two iterators into the structure
  typename std::vector<T>::iterator current = vec.begin();
  ++current;
  typename std::vector<T>::iterator previous = vec.begin();
  for (; current != vec.end(); ++current, ++previous) {
    if (*current == *previous) {
      // if they are the same element increment the count
      current_count++;
    } else if (current_count >= mode_count) {
      // found a new mode!
      mode = *previous;
      mode_count = current_count;
      current_count = 1;
    } else {
      current_count = 1;
    }
  }
  if (current_count >= mode_count) {
    // last entry is a new mode!
    mode = *previous;
    mode_count = current_count;
  }
  // save the mode to the output vector
  output_count = 1;
  ostr << mode << "\n";
}


// note: closest_pair is only available for integer data (not string data)
void vector_closest_pair(std::vector<int> &vec, std::ostream &ostr, int &output_count) {
  assert (vec.size() >= 2);
  // use the vector sort algorithm
  sort(vec.begin(),vec.end());
  output_count = 2;
  int best;
  int best_index = -1;
  // the two elements with closest value must be next to each other in sorted order
  for (unsigned int i = 0; i < vec.size()-1; i++) {
    int diff = vec[i+1]-vec[i];
    if (best_index == -1 || diff < best) {
      best = diff;
      best_index = i;
    }
  }
  // print the two elements
  output_count = 2;
  ostr << vec[best_index] << "\n";
  ostr << vec[best_index+1] << "\n";
}


template <class T>
void vector_first_sorted(std::vector<T> &vec, std::ostream &ostr, int &output_count, int optional_arg) {
  assert (optional_arg >= 1);
  assert ((int)vec.size() >= optional_arg);
  // use the vector sort algorithm
  sort(vec.begin(),vec.end());
  output_count = optional_arg;
  for (int i = 0; i < output_count; i++) {
    ostr << vec[i] << "\n";
  }
}

//helper function, input two string and find their substring
string vector_find_substring(const string& s1, const string& s2){
    string longest="";
    //loop through each character in s1
    for(int i=0;i<s1.length();i++){
        int pos=s2.find(s1[i],0);
        //if its found, in case same letter has many locations
        while(pos!=-1){
            string temp="";
            temp+=s1[i];
            //keep looping for next word if not same break it
            for(int j=pos+1;j<s2.length();j++){
                temp+=s2[j];
                int pos2=s1.find(temp,0);
                if(pos2==-1){
                    break;
                }
                else{
                    //in case this is longer than origin one
                    if(temp.length()>longest.length()){
                        longest=temp;
                    }
                }
            }
            pos=s2.find(s1[i],pos+1);
        }
    }
    return longest;
}

// note: longest_substring is only available for string data (not integer data)
void vector_longest_substring(std::vector<std::string> &vec, std::ostream &ostr, int &output_count) {
    string length_longest="";
    for(int i=0;i<vec.size();i++){
        for(int j=i+1;j<vec.size();j++){
            string temp=vector_find_substring(vec[i],vec[j]);
            if(length_longest.length()<temp.length()){
                length_longest=temp;
            }
        }
    }
    output_count=1;
    ostr<<length_longest<<endl;
}


void vector_test(const std::string &operation, const std::string &type,
                 std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

  if (type == "string") {
    // load the data into a vector of strings
    std::vector<std::string> vec;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      vec.push_back(s);
      input_count++;
    }
    if      (operation == "sort")              { vector_sort              (vec,ostr,output_count); }
    else if (operation == "remove_duplicates") { vector_remove_duplicates (vec,ostr,output_count); }
    else if (operation == "mode")              { vector_mode              (vec,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { vector_first_sorted      (vec,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { vector_longest_substring (vec,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

  else {
    assert (type == "integer");
    // load the data into a vector of integers
    std::vector<int> vec;
    int v;
    input_count = 0;
    while (istr >> v) {
      vec.push_back(v);
      input_count++;
    }
    if      (operation == "sort")              { vector_sort              (vec,ostr,output_count); }
    else if (operation == "remove_duplicates") { vector_remove_duplicates (vec,ostr,output_count); }
    else if (operation == "mode")              { vector_mode              (vec,ostr,output_count); }
    else if (operation == "closest_pair")      { vector_closest_pair      (vec,ostr,output_count); }
    else if (operation == "first_sorted")      { vector_first_sorted      (vec,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
