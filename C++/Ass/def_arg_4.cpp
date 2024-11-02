//4. Write a function to convert a temperature from Celsius to Fahrenheit. The function should take the temperature in Celsius as an argument, with a default value of 0.

#include<iostream>
using namespace std;

double celsiusToFahrenheit(double celsius=0){
    return (celsius * 9 / 5) + 32;
}

int main(){
    cout<<celsiusToFahrenheit()<<endl;
    cout<<celsiusToFahrenheit(45)<<endl;
}