//Returning a Reference from a Function
#include<iostream>
using namespace std;

int &findmax(int &a,int &b){
    return (a>b)?a:b;
}

int main(){
    int a=3468,b=864;
    cout<<"max = "<<findmax(a,b)<<endl;
}