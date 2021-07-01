#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>         // to access the STL vector class
#include <cmath>          // to use standard math library and sqrt
using namespace std;

vector<string> longword(string word,int length)//to seperate the long word
{
  vector <string> x;
  while(word.size()>length)
  {
    string y=word.substr(0,length-1) + "-";//take out the length of width   and -1 for hyphen
    x.push_back(y);//add it into vector y
    word.erase(0,length-1);//erase the part have been added
  }
  x.push_back(word);//the last part
  return x;
}


vector<vector<string> >whole_text(ifstream& inf,int twidth)//return a 2-d vector
{
  string temp;
  vector<vector<string> >text;//set up a 2-d vector to store each line vector
  vector<string>line;//set up a vector to store one line
  int space=twidth;
  while(inf>>temp)
  {
    bool flag=true;//make it true every loop, flag to take place of the elif in python
    space=space-temp.size();
    if(space>0 && flag==true)//when there is space
    {
      line.push_back(temp);//put word in line
      space-=1;//minus the space after word
      flag=false;//change the flag to avoid the following if statement ,go to next loop directly
    }
    if(space==0 && flag==true)//when there is just fit in
    {
      line.push_back(temp);//add it into the line
      text.push_back(line);//line is full so add the line into the text
      line.clear();//clear the line
      space=twidth;//restore the value of space as its an empty new line
      flag=false;
    }
    if(space<0 && flag==true)//when word doesnt fit int
    {
      if(temp.size()>twidth)//in case for super big word
      {
        vector<string>x=longword(temp,twidth);//seperate the long word into a vector
        if(!line.empty())//if it's not in the first word of the line, start a new line
        {
          text.push_back(line);
          line.clear();
        }
        for(int i=0;i<x.size()-1;i++)// -1 because the last part will be with other words if possible
        {
          line.push_back(x[i]);
          text.push_back(line);
          line.clear();
        }
        temp=x[x.size()-1];
        line.push_back(temp);
        space=twidth-temp.size()-1;
        flag=false;
      }
      else
      {
        text.push_back(line);//change to a new line
        line.clear();
        line.push_back(temp);
        space=twidth-temp.size()-1;
        flag=false;
      }
    }
  }
  text.push_back(line);//this is for the last line which is not include in loop
  return text;
}

/*
int main(int argc,char**argv)
{
  ifstream i(argv[1]);
  ofstream o(argv[2]);
  int width=atoi(argv[3]);
  vector<vector<string> >x=whole_text(i,width);
  for(int i=0;i<x.size();i++)
  {
    for(int j=0;j<x[i].size();j++)
    {
      cout<<x[i][j]<<" ";
    }
    cout<<endl;
  }
}

*/
int space_determined(int width,vector<string> & a)//to determine how many space between word for full justify
{
  int total_char=0;
  int space_need=0;
  for(int i=0;i<a.size();i++)
  {
    total_char=a[i].size()+total_char;
  }
  int num_space = width - total_char;
  space_need=num_space/(a.size()-1);//calculate the space need
  return space_need;
}

int number_space(int width,vector<string> & a)//to determine the number of space as one function cant return two value
{
  int total_char=0;
  for(int i=0;i<a.size();i++)
  {
    total_char=a[i].size()+total_char;
  }
  int num_space = width - total_char;
  return num_space;
}

int main(int argc, char** argv)
{
  ifstream inf(argv[1]);
  if(!inf.good())
  {
    cout<<"Can't open "<<argv[1]<<" to read.";
    exit(1);
  }
  ofstream ouf(argv[2]);
  if(!ouf.good())
  {
    cout<<"Can't open "<<argv[2]<<" to write.";
    exit(1);
  }
  int twidth=atoi(argv[3]);//text width
  if(twidth<0)
  {
    cout<<"Width enter is not an integer.";
    exit(1);
  }
  string mode=argv[4];
  if (!(mode=="flush_left" || mode=="flush_right" || mode=="full_justify"))
  {
    cout<<"Wrong mode.";
    exit(1);
  }

  vector<vector<string> >a=whole_text(inf,twidth);
  string first_line(twidth+4,'-');
  ouf<<first_line<<endl;
  for(int i=0;i<a.size();i++)//build a nested for loop to write the file. this one is for locating the line vector
  {
    ouf<<"| ";
    if(mode=="flush_left")
    {
      string output_line;
      for(int j=0;j<a[i].size()-1;j++)//this one is to locate the word inside the line vector
      {
        output_line+=a[i][j];
        output_line+=" ";//combine these word into a string with space except the last one without the space
      }
      output_line+=a[i][a[i].size()-1];
      int extra_space=number_space(twidth,a[i])-(a[i].size()-1);
      string space_need(extra_space,' ');
      output_line+=space_need;
      ouf<<output_line;
      ouf<<" |"<<endl;//change the line when one line vector end
    }
    if(mode=="flush_right")
    {
      string output_line;
      int extra_space=number_space(twidth,a[i])-(a[i].size()-1);
      string space_need(extra_space,' ');
      output_line+=space_need;
      for(int j=0;j<a[i].size()-1;j++)//this one is to locate the word inside the line vector
      {
        output_line+=a[i][j];
        output_line+=" ";//combine these word into a string with space except the last one without the space
      }
      output_line+=a[i][a[i].size()-1];
      ouf<<output_line;
      ouf<<" |"<<endl;//change the line when one line vector end
    }
    if(mode=="full_justify")
    {
      string output_line;
      if(i==a.size()-1)
      {
        for(int j=0;j<a[i].size()-1;j++)
        {
          output_line+=a[i][j];
          output_line+=" ";
        }
        output_line+=a[i][a[i].size()-1];
        ouf.width(twidth);//define the width of ouf
        ouf<<left<<output_line;//if its the last line make it left justify
      }
      else
      {
        if(a[i].size()==1)
        {
          output_line=a[i][0];
          ouf.width(twidth);
          ouf<<left<<output_line;//if there is only one word in line make it left justify
        }
        else
        {
          int num_space_need=space_determined(twidth,a[i]);//numer of space needed
          int extra_space=number_space(twidth,a[i])%(a[i].size()-1);//how many left hand side words will have extra space
          string needed_space(num_space_need,' ');//turn space into string
          for(int j=0;j<a[i].size()-1;j++)//this one is to locate the word inside the line vector
          {
            if(j<extra_space)//if space are distribute uneven give it to the left hand side first
            {
              output_line+=a[i][j];
              output_line+=needed_space;//combine these word into a string with space except the last one without the space
              output_line+=" ";
            }
            else
            {
              output_line+=a[i][j];
              output_line+=needed_space;//combine these word into a string with space except the last one without the space
            }
          }
          output_line+=a[i][a[i].size()-1];
          ouf<<output_line;
        }
      }
      ouf<<" |"<<endl;
    }
  }
  ouf<<first_line<<endl;
}
