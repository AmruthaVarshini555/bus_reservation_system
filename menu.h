#include<iostream>
#include<string>
#include"logger.h"
using namespace std;

class Menu
{
    public:
        Menu(){
            LOG_INFO("\nDefault constructor of mainmenu invoked");
        }
        void welcomeScreen();
        void mainMenu();
        void adminLogin();
        void adminMenu();
        void userLogin();
        void valid(string);
        void userMenu();
        void viewBookingsMenu();
        ~Menu(){
            LOG_INFO("\nDestructor invoked");
        }
};
