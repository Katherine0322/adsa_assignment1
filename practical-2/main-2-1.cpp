#include <iostream>
using namespace std;
extern void print_binary_str(string);
int main(){
    string number;
    cin>>number;
    print_binary_str(number);
    return 0;
}