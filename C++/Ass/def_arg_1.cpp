//1. Create a function to calculate the area of a rectangle. The function should take the length and width as arguments, with default values of 1.0 for both.

#include<iostream>
using namespace std;

double calculate(double length=1.0, double width=1.0){
    return length*width;
}

int main(){
    int length=41.1, width=9.5;
    cout<<"area of rectangle = "<<calculate()<<endl;
    cout<<"area of rectangle = "<<calculate(length)<<endl;
    cout<<"area of rectangle = "<<calculate(length,width)<<endl;
}