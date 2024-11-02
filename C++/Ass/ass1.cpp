#include <iostream>
using namespace std;

class employee{
    int age;
    int yos;//year of Service
    int salary;
    public:
    int calculation(int salary){
        int salarythousend = salary/1000;
        int total = (salarythousend + 40) / 80 * 80;
        return total;
    }
};

int main(){
    employee emp1,emp2,emp3,emp4,emp5;

    cout<<"employee1 = "<< emp1.calculation(150000)<<endl;
    cout<<"employee2 = "<< emp2.calculation(117000)<<endl;
    cout<<"employee3 = "<< emp3.calculation(1354000)<<endl;
    cout<<"employee4 = "<< emp4.calculation(146000)<<endl;
    cout<<"employee5 = "<< emp5.calculation(19313000)<<endl;
}