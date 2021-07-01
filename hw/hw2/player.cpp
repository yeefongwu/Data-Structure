#include<iostream>
#include<vector>
#include<string>
#include<cctype>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include<algorithm>
#include "player.h"
using namespace std;

//helper to read the input file turn into a class
bool Player::read(istream& ins) {//read the input file and store all data into one_player class
    string first_name,last_name;
    if(!(ins>>first_name>>last_name)){
        return false;
    }
    _first=first_name; _last=last_name;
    int score;
    int turn=18;//exclude the last frame
    frame.clear();round.clear();score_in_one.clear();//clear it for every player
    for(int i=0; i<turn && (ins>>score) ;i++){
        score_in_one.push_back(score);
        if(score==10 && frame.size()==0){
            frame.push_back(score);
            round.push_back(frame);
            frame.clear();
            turn-=1;//if hit strike, there will be one less throw
        }
        else{
            frame.push_back(score);
        }
        if(frame.size()==2){
            round.push_back(frame);
            frame.clear();
        }
    }
    int last_frame1,last_frame2;//final frame
    ins>>last_frame1>>last_frame2;//last frame has at least two throw
    frame.push_back(last_frame1);frame.push_back(last_frame2);score_in_one.push_back(last_frame1);score_in_one.push_back(last_frame2);
    if((last_frame1+last_frame2)>=10){//in case in last frame player get either strike or spare
        int last_frame3;ins>>last_frame3;
        frame.push_back(last_frame3);score_in_one.push_back(last_frame3);}
    round.push_back(frame);
    return true;
}

//helper to get the score into one vector
vector<int> Player::getFrame_in_round(){
    int temp=0; int k=0; frame_in_round.clear();
    for(int i=0;i<round.size()-1;i++){//except the last one
        for(int j=0;j<round[i].size();j++){
            if(round[i].size()==1){//in case of strike
                temp = temp+round[i][j]+ score_in_one[k+1]+score_in_one[k+2];
            }
            else{
                if(j==1&&(score_in_one[k]+score_in_one[k-1]==10)){//in case of spare
                    temp=temp+round[i][j]+score_in_one[k+1];
                }
                else{
                    temp+=round[i][j];
                }
            }
            k+=1;
        }
        frame_in_round.push_back(temp);

    }
    for(int i=0;i<round[round.size()-1].size();i++){//for the last frame
        temp+=round[round.size()-1][i];
    }
    frame_in_round.push_back(temp);
    return frame_in_round;
}

//helper to print the form
void Player::print_form(int w,ostream& ous) {//print out the form
    vector<int> x=frame_in_round; int k=0;
    string bottom(w+66,'-'); ous<<bottom<<endl;
    string name=_first+" "+_last; int name_taken=name.size();
    string space_name(w-name_taken,' ');
    ous<<"| "<<_first<<" "<<_last<<space_name<<" | ";
    for(int i=0;i<round.size()-1;i++){
        for(int j=0;j<round[i].size();j++){
            if(round[i].size()==1){
                ous<<"  X ";
            }
            else{
                if(round[i][j]==0){
                    ous<<"- ";
                }
                else{
                    if(j==1&&(score_in_one[k]+score_in_one[k-1]==10)){
                        ous<<"/ ";
                    }
                    else{ous<<round[i][j]<<" ";}}
            }
            k+=1;
        }
        ous<<"| ";
    }
    for(int i=0;i<round[round.size()-1].size();i++){
        if(round[round.size()-1][i]==10){
            if(i==1 && round[round.size()-1][0]==0){ous<<"/ ";}
            else{ous<<"X ";}
        }
        else{
            if(round[round.size()-1][i]==0){
                ous<<"- ";
            }
            else{
                if(i==1&&round[round.size()-1].size()==3){
                    ous<<"/ ";
                }
                else{ous<<round[round.size()-1][i]<<" ";}
            }
        }
    }
    if(round[round.size()-1].size()==2){
        ous<<"  ";
    }
    ous<<"|"<<endl;
    ous<<"| ";
    string blank_space(w,' ');
    ous<<blank_space<<" | ";
    for(int i=0;i<9;i++){
        ous.width(3); ous<<right<<x[i];
        ous<<" | ";
    }
    ous.width(5);ous<<x[x.size()-1]; ous<<" |"<<endl;

}
//help to get the plain score
int Player::getPlain_score() const {
    int ps=0;
    for(int i=0;i<score_in_one.size();i++){
        ps+=score_in_one[i];
    }
    return ps;
}

bool name_alphabet(const Player& p1, const Player& p2){//naming sort
    return p1.last()<p2.last() || (p1.last()==p2.last() && p1.first() < p2.first());
}

bool score_sort(const Player& p1, const Player& p2){//score sort
    return p1.getFinal_score()>p2.getFinal_score() ||(p1.getFinal_score()==p2.getFinal_score() && name_alphabet(p1,p2));
}

bool plain_sort(const Player& p1, const Player& p2){//plain sort
    return p1.getPlain_score()>p2.getPlain_score() || (p1.getPlain_score()==p2.getPlain_score() && name_alphabet(p1,p2));
}