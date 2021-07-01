//
// Created by yeefongwu on 3/22/21.
//

#include "blackout.h"
#include <vector>
#include <string>

//increase will let the Puzzle increase by one point, if its cross y2+=1, if its down x2+=1
void Puzzle::increase() {
    if(cross()){y2+=1;}
    else{x2+=1;}
}

//word length calculate the length of word, if its cross y2-y1, if its down x2-x1
int Puzzle::word_length() const {
    if(cross()){return y2-y1;}
    else{return x2-x1;}
}

//word function will print out the string of word by searching their location from the grid
std::string Puzzle::word(const std::vector<std::vector<char> > &grid) const {
    char word[this->word_length()];
    if(cross_){
        int length = grid[0].size() - y1;
        //min is used because sometimes increase function will be out of bound without it
        // ex:in the recursive findWord() function, there is no min, it will go out of bound
        for(int i=0;i<std::min(this->word_length(), length);i++){word[i]=grid[x1][y1+i];}
    }
    else{
        int length = grid.size() - x1;
        for(int i=0;i<std::min(this->word_length(), length);i++){word[i]=grid[x1+i][y1];}
    }
    word[word_length()]='\0';
    return std::string(word);
}

