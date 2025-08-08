#include <iostream>
using namespace std;
extern void print_scaled(int array[3][3],int);
int main(){
    int array[3][3]={
        {2,2,2},
        {3,3,3},
        {4,4,4}
    };
    int scale=3;
    print_scaled(array,scale);
    return 0;
}