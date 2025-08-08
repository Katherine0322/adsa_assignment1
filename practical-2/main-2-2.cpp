#include <iostream>
using namespace std;
extern int binary_to_int(int binary_digits[], int);
int main(){
    int array[]={1,1,0,1,0};
    int n=5;
    cout<<binary_to_int(array,n)<<endl;
    return 0;
}