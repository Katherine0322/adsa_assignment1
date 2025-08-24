#include<iostream>
#include<string>
#include<algorithm> //use, reverse, sort, etc.
#include<vector>

using namespace std;

string stripZeros(string s){
    int i=0;
    while (i<(int)s.length()-1&&s[i]=='0'){
        i++;
    }
    return s.substr(i);
}
//Pad zeros on the left to reach the desired length 
string add_zero(string s, int n){
    int diff=n-(int)s.length();
    if (diff>0){
        return string(diff, '0')+s;
    }
    return s;
}
//compare two large integer strings
//return: -1(a<b), 0(a==b), 1(a>b)

int compare(string a, string b){
    a=stripZeros(a);
    b=stripZeros(b);
    if (a.length()<b.length())return -1;
    if (a.length()>b.length())return 1;
    if (a.length()!=b.length()){
        return(a.length()<b.length())?-1:1;
    }
    if (a==b)return 0;
    return (a<b)?-1:1;
}

//add 0 in the end
string end_zeros(string s, int k){
    string t = stripZeros(s);
    if (t =="0")return "0";
    return t+string(k,'0');
}

string add_method_school(string a, string b, int base){
    int n=max(a.length(), b.length());
    a=add_zero(a,n);
    b=add_zero(b,n);


    int carry=0;
    string res="";
    res.reserve(n+1); //reserve space for the result

    for (int i=n-1;i>=0;i--){
        int d1=a[i]-'0';
        int d2=b[i]-'0';
        int sum=d1+d2+carry;

        res.push_back(char('0'+(sum%base))); //current digit
        carry=sum/base; //carry
    }
    if(carry)res.push_back(char('0'+carry)); //if there is a carry, add it to the result
    //reverse the result to get the correct order
    reverse(res.begin(), res.end());
    return stripZeros(res);
}

string sub_method_school(string a, string b, int base){
    if (compare(a,b)<0){
        cout<<"Error: a<b in sub_method_school"<<endl;
        return "0"; //error case, should handle properly
    }
    int n=max((int)a.length(),(int)b.length());
    a=add_zero(a,n);
    b=add_zero(b,n);

    int borrow=0;
    string res="";
    res.reserve(n);//reserve space for the result

    for (int i=n-1;i>=0;i--){
        int d1=a[i]-'0'-borrow;
        int d2=b[i]-'0';

        if (d1<d2){
            d1=d1+base;
            borrow=1;
        }
        else{
            borrow=0;
        }
        res.push_back(char('0'+(d1-d2))); //current digit
    }
    reverse(res.begin(), res.end());
    return stripZeros(res);
}

string multiply_school(string a, string b, int base){
    a=stripZeros(a);
    b=stripZeros(b);

    if (a=="0"||b=="0"){
        return "0";
    }

    int n=(int)a.length();
    int m=(int)b.length();

    vector<int>acc(n+m, 0); //the maximum length of result

    for (int i=n-1;i>=0;i--){
        for (int j=m-1;j>=0;j--){
            acc[i+j+1]=acc[i+j+1]+(a[i]-'0')*(b[j]-'0');
        }
    }

    //process the carry
    for (int k=n+m-1;k>0;k--){
        acc[k-1]=acc[k-1]+acc[k]/base;
        acc[k]=acc[k]%base;
    }
    //convert the result to a string
    string res;
    res.reserve(n+m); //reserve space for the result
    for (int x:acc)res.push_back(char('0'+x));

    return stripZeros(res);
}

string karatsuba(string a, string b, int base){
    a=stripZeros(a);
    b=stripZeros(b);
    if (a=="0"||b=="0"){
        return "0";
    }
    //apply the schoolbook algorithm for small multiplications (<=32 bits)
    int n=max((int)a.length(), (int)b.length());
    if (n<=32){
        return multiply_school(a,b,base);
    }
    //if the lengths are not equal, add 0
    a=add_zero(a,n);
    b=add_zero(b,n);

    //Split x=a|b, y=c|d
    int m=n/2; //length of the right part
    int high=n-m; //length of the left part
    string q=a.substr(0,high); //left part of a
    string r=a.substr(high); //right part of a
    string s=b.substr(0,high); //left part of b
    string t=b.substr(high); //right part of b

    //three multiplications
    string a1=karatsuba(q,s,base); //a*c
    string a2=karatsuba(r,t,base); //b*d
    string a3=karatsuba(add_method_school(q,r,base), add_method_school(s,t,base),base);
    //(a+b)*(c+d)-a1-a2
    string mid=sub_method_school(a3,add_method_school(a1,a2,base),base);

    //combine: a1*base^(2*m) +mid*base^m +a2
    string part1=end_zeros(a1,2*m); //a1*base^(2*m)
    string part2=end_zeros(mid,m); //mid*base^m
    string result=add_method_school(add_method_school(part1,part2,base),a2,base);

    return stripZeros(result);

    //remove leading zeros
    return stripZeros(result);
}

bool vaildDigit(char ch, int base){
    if (ch>='0'&&ch<='9'){
        return(ch-'0')<base;
    }
    return false;
}

int main(){
    //1.read two large integers(string type)and the base(int type, between 2-10)
    string I1;
    string I2;
    int B;

    //exit immediately if the input format is invalid
    if (!(cin>>I1>>I2>>B))return 0;

    //check whether the base is between 2 and 10
    if (B<2||B>10){
        cout<<"Invalid base"<<endl;
        return 0;
    }

    //check whether the numbers are negative
    if (I1[0]=='-'||I2[0]=='-'){
        cout<<"Negative numbers are not supported"<<endl;
        return 0;
    }

    //check whether each cheracter is a valid digit in the given base
    if (!vaildDigit(I1[0],B)||!vaildDigit(I2[0],B)){
        cout<<"Invalid input"<<endl;
        return 0;
    }

    //remove leading zeros from both numbers
    I1=stripZeros(I1);
    I2=stripZeros(I2);

    //Debug: print the sanitized input
    //cout<<"Input numbers:"<<I1<<" "<<I2<<"Base: "<<B<<endl;

    //2.for now, do not perform full computation; just use placeholder results:
    string sum_res=add_method_school(I1,I2,B);
    //string sub_method_school_res=sub_method_school(I1,I2,B);
    //cout<<"Subtraction result: "<<sub_method_school_res<<endl;
    //string mul_school_res=multiply_school(I1,I2,B);
    //cout<<"Multiplication result: "<<mul_school_res<<endl;
    string mul_res=karatsuba(I1,I2,B);
    string div_res="0";

    //3. Output the results, separated by spaces
    cout<<sum_res<<" "<<mul_res<<" "<<div_res<<endl;
    return 0;
}