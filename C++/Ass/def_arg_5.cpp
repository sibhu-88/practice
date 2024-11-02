//5. Create a function to generate a random number within a specified range. The function should take the minimum and maximum values as arguments, with default values of 0 and 100.

#include<iostream>
using namespace std;

int getRandomNumber(int x){
    srand(x);
    return rand();
}

int generateRandomNumber(int min = 0, int max = 100) {
    int i;
    int randomValue = getRandomNumber(i*64git);
    return min + (randomValue % (max - min + 1));
}

int main(){
    cout<<generateRandomNumber()<<endl;
}