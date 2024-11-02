//2. Write a function to print a formatted message. The function should take a message and a formatting character as arguments. The default formatting character should be '*'.
#include<iostream>
using namespace std;

void print(string message,char format='*'){
    cout<<format<<message<<format<<endl;
}

int main(){
    string message = " Hello siva ";
    print(message);
}