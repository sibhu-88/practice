#include<iostream>
using namespace std;

namespace A
{
    int x=10;
} // namespace A

namespace B
{
    int x=30;
} // namespace B

int main(){
    using namespace A;
    cout<<x<<endl;
    cout<<B::x<<endl;
}