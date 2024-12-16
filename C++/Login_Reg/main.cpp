#include <iostrem>
using namespace std;

void welcome(void);
void login(void);
void register(void);
void resetpassword(void);

int main()
{
    int op;
    while (true)
    {
        cout << "\n\t\t\t_________________________________________\n\n\n";
        cout << "\t\t\t          welcome to the Prabhu page      \n\n\n";
        cout << "\t\t\t_________        MENU        ____________\n\n\n";
        cout << "                                                 \n\n\n";
        cout << "\t|  Press 1 to LOGIN                     |" << endl;
        cout << "\t|  Press 2 to REGISTER                  |" << endl;
        cout << "\t|  Press 3 if you forgot your PASSWORD  |" << endl;
        cout << "\n\t\t\t Please enter your choice : ";
        cin >> op;
        cout << endl;
        switch (op)
        {
        case 1:
            login();
            break;
        case 1:
            register();
            break;
        case 1:
            resetpassword();
            break;
        case 1:
            exit(0);
        default:
            cout << "Invalid Option! Try again!" << endl;
            break;
        }
    }
}

void welcome(void)
{
    system("clear");
    cout << "\n\t\tWelcome to Simple Login System!\n";
}
void login(void)
{
    string userName, password;
    cout << "\n\t\tLogin page\n"
         << endl;
    cout << "\n\t\tEnter User Name : ";
    cin >> userName;
    cout << "\n\t\tEnter Password : ";
    cin >> password;
}
void register(void)
{
}
void resetpassword(void)
{
}
