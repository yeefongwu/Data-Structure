//
// Created by yeefongwu on 3/22/21.
//

#ifndef HW6_BLACKOUT_H
#define HW6_BLACKOUT_H

#include <vector>
#include <string>

class Puzzle{
public:
    //default constructor
    Puzzle(int x1_,int y1_,int x2_,int y2_,bool cross1): x1(x1_),y1(y1_),x2(x2_),y2(y2_),cross_(cross1){}

    //accessor
    int get_x1() const {return x1;}
    int get_x2() const {return x2;}
    int get_y1() const {return y1;}
    int get_y2() const {return y2;}
    bool cross() const {return cross_;}

    //helper
    std::string word(const std::vector<std::vector<char> >&grid) const;
    int word_length() const;
    void increase();
    bool overlap(const Puzzle& p) const;


private:

    //member variable x1,y1 stand for the point where the word start
    //x2,y2 stand for the point where the word end, cross is true if its cross, false if its down
    int x1;
    int y1;
    int x2;
    int y2;
    bool cross_;
};

#endif //HW6_BLACKOUT_H
