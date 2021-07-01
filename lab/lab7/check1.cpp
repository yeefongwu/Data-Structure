
#include <iostream>

int find_path( int x,  int y)
{
    int out = 0;

    if(x == 0 && y ==0)
    {
        return 1;
    }

    if(x >0)
    {
        out += find_path(x-1,y);
    }

    if(y > 0)
    {
        out += find_path(x,y-1);
    }


    return out;
}

int main()
{
    int i =0;
    i = find_path(0,0);

    std::cout << i << std::endl;
    return 0;
}