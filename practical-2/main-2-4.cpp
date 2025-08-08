#include <iostream>
using namespace std;
extern int sum_min_max(int integers[], int);
int main(){
    int integers[]={1,2,3,2,1};
    int length=5;
    cout<<sum_min_max(integers,length)<<endl;
    return 0;
}