#ifndef __player_h_
#define __player_h_

#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <iomanip>
#include<algorithm>
#include <cstdlib>
using namespace std;

class Player{
public:
    //accessor
    const string& first() const {return _first;}
    const string& last() const {return _last;}
    const vector<vector<int> > getRound() const {return round;}
    const vector<int> getFrame() const {return frame;}
    const vector<int> getScore_in_one() const {return score_in_one;}
    vector<int> getFrame_in_round();
    const int getFinal_score() const {return frame_in_round[frame_in_round.size()-1];}
    //modifier
    bool read(istream& ins);
    void print_form(int w,ostream& ous);
    int getPlain_score() const;
private:
    string _first;
    string _last;
    vector<vector<int> >round;
    vector<int> frame;
    vector<int> score_in_one;
    vector<int> frame_in_round;
};

bool name_alphabet(const Player& p1, const Player& p2);
bool score_sort(const Player& p1, const Player& p2);
bool plain_sort(const Player& p1, const Player& p2);
#endif