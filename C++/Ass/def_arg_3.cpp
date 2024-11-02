//3. Create a function to calculate the factorial of a number. The function should take the number as an argument, with a default value of 0.

#include<iostream>
using namespace std;

int factorial(int n=0){
    if ((n==0)||(n==1))
    return 1;
    else
    return n*factorial(n-1);    
}

int main(){
    int x;
    cin>>x;
    cout<<factorial(x)<<endl;
}