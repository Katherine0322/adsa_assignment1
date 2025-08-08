#include <iostream>
using namespace std;
void print_binary_str(std::string decimal_number){
    unsigned long long n=stoull(decimal_number);
    string bin;
    if(n==0){
        bin="0";
    }
    else{
        while(n>0){
            bin=char('0'+(n%2))+bin;
            n/=2;
        }
    }
    cout<<bin<<'\n';
}