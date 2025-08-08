#include <iostream>
using namespace std;
extern int sum_array_elements(int integers[], int);
int main(){
    int integers[]={1,2,3,2,1};
    int length=5;
    cout<<sum_array_elements(integers,length)<<endl;
    return 0;
}