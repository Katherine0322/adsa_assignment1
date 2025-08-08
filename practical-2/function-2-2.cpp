#include <iostream>
using namespace std;
int binary_to_int(int binary_digits[], int number_of_digits){
    if(number_of_digits<=0||number_of_digits>30){
        return -1;
    }
    int value=0;
    for(int i=0;i<number_of_digits;i++){
        value=value*2+binary_digits[i];
    }
    return value;
}