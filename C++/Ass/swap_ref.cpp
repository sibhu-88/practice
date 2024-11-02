//Swapping Values Using References

#include<iostream>
using namespace std;

void swap(int &x,int &y){
    int temp =x;
    x=y;
    y=temp;
}

int main(){
    int a=20,b=40;
    cout<<"before swap a= "<<a<<" b= "<<b<<endl;
    swap(a,b);
    cout<<"after swap a= "<<a<<" b= "<<b<<endl;
}