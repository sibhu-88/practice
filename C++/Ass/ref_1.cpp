//Pass-by-Reference for Modifying Variables

#include<iostream>
using namespace std;

void increment(int &i){
    i+=10;
}

int main(){
    int x=14;
    cout<<"before value change = "<<x<<endl;
    increment(x);
    cout<<"after value change = "<<x<<endl;
}