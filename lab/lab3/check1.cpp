#include <iostream>
using namespace std;


void compute_squars(unsigned int n,unsigned int a[], unsigned int b[]){
    unsigned int* pa,*pb;
    pb=b;
    for(pa=a;pa<n+a;++pa){
        *pb=*pa * *pa;
        //cout<<*pa<<" "<<*pb<<endl;
        pb++;
    }
}

int main() {
    unsigned int b[3] ={65535,1,2};
    unsigned int c[3];
    compute_squars(3,b,c);
    for(int i=0;i<3;i++){
        cout<<c[i]<<endl;
    }

}