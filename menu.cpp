#include"menu.h"
#include"bus.h"
#include"ticket.h"
#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
using namespace std;

//welcome screen function
void Menu::welcomeScreen()
{
    Menu menu;
    cout<<"\n******Welcome to bus reservation system managements project******\n";
    cout<<"\n Developed By:- Group 3\n";
    system("PAUSE");
    menu.mainMenu();
}
//main menu
void Menu:: mainMenu()
{
    int choice;
    Menu obj1;
    while(1)
    {
        system("clear");
        cout<<"\n-----------MAIN MENU------------";
        cout<<"\n1. Admin\n";
        cout<<"\n2. User\n";
        cout<<"\n3. EXIT\n";
        cout<<"\nEnter your choice";
        cin>>choice;
        switch(choice)
        {
          //main menu have 3 options user and admin exit
          case 1: obj1.adminLogin();
                  break;
          case 2: obj1.userLogin();
                  break;
          case 3: exit(0);
                  break;
          default: cout<<"Invalid choice";
                   obj1.mainMenu();
        }
    }
}

// Admin Login
void Menu:: adminLogin()
{
    Menu admin;
    string adminUsername, adminPassword;
    cout<<"\n-----------ADMIN LOGIN----------";
    //enter adminusername and password;
    cout<<"\nEnter AdminUsername:";
    cin>>adminUsername;
    cout<<"\nEnter Password";
    cin>>adminPassword;
    if(adminUsername == "reservation" && adminPassword == "Capg@123")
    {
        admin.adminMenu();
    }
    else
    {
        cout<<"\nUsername or Password is wrong...!!";
        admin.adminLogin();
    }
    
}

// admin menu functions
void Menu::adminMenu()
{
    int choice;
    Menu m;
    Bus b;
    Ticket t;
    while(1)
    {
        system("clear");
        cout<<"----------------ADMIN PORTAL-------------";
        cout<<"\n1. Add Bus\n";
        cout<<"\n2. View Bus\n";
        cout<<"\n 3. Add Ticket\n";
        cout<<"\n 4. Edit Ticket\n";
        cout<<"\n 5. Cancel Ticket\n";
        cout<<"\n 6. View Bookings\n";
        cout<<"\n 7. View Bus Details\n";
        cout<<"\n8. Edit Bus\n";
        cout<<"\n 9. Delete Bus\n";
        cout<<"\n 10. BACK\n";
        cout << "\nEnter your choice:-> ";
        cin >> choice;
        switch(choice)
        {
            case 1: b.addBus();
                    break;
            case 2: b.showAllBus() ;
                    break;
            case 3: t.bookTicket();
                    break;
            case 4: t.editTicket();
                    break;
            case 5: t.cancelTicket();
                    break;
            case 6: m.viewBookingsMenu();
                    break;
            case 7: b.viewBusDetails();
                    break;
            case 8: b.editBus();
                    break;
            case 9: b.deleteBus();
                    break;
            case 10: m.mainMenu();
                    break;
            default : cout<<"Invaild choice";
                      m.adminMenu();
        }
    }
}

//userlogin
void Menu::userLogin(){
    int ch,tm;
    string name,pswd,username;
    string usrname,password;
    ofstream fileo;
    ifstream filei;
    cout<<"\n----------USER PORTAL-----------";
    cout<<"\n 1. Register";
    cout<<"\n 2. Login";
    cout<<"\n Enter your choice: ";
    cin>>ch;
    switch(ch){
        case 1:
            cout<<"\nEnter your name: ";
            cin.ignore();
            getline(cin,name);
            cout<<"\nCreate a username: ";
            cin>>username;
            tm=0;
            valid(username);
            if(tm>=3)
            {
                continue;
            }
            cout<<"\nCreate a password: ";
            cin>>pswd;
            fileo.open("user.txt".c_str());
            fileo<<username<<","<<name<<","<<pswd<<endl;
            cout<<"\nYour are registered successfully";
            cout<<"\nPress any key to continue.."
            fileo.close();
        case 2: 
            cout<<"\nEnter your username: ";
            cin>>username;
            cout<<"\nEnter your password: ";
            cin>>pswd;
            filei.open("user.txt".c_str());
            if(!filei.is_open() && filei.fail())
            {
                cout<<"\nYou are not registered, please register before logging in..";
                filei.close();
                continue;
            }
            getline(filei,usrname);
            getline(filei,password);
            if(username==usrname && pswd==password)
            {
                cout<<"\n%s are successfully logged in :)"<<usrname;
                filei.close();
                login.userMenu();
            }
    }
    
}    

void Menu:: valid(string str)
{
    string user;
    int tm;
    ifstream file;
    file.open("user.txt".c_str());
    if(!file.is_open() && file.fail())
    {
        return;
    }
    else{
        tm++;
        if(tm==3)
        {
            cout<<"\nThis username already exists\nPlease try again";
            return;
        }
        cout<<"\nThis username already exists\n Create username: ";
        cin>>user;
        valid(user);
    }
}
    
//User Menu
void Menu::userMenu()
{
    int choice;
    Ticket t;
    Menu m;
    while(1)
    {
        system("clear");
        cout<<"\n---------USER MENU---------";
        cout<<"\n1. Book Ticket";
        cout<<"\n2. View Ticket";
        cout<<"\n3. Cancel Ticket";
        cout<<"\n4. EXIT";
        cout<<"\nEnter your choice";
        cin>>choice;
        switch(choice)
        {
            case 1: t.bookTicket();
                    break;
            case 2: t.showTicketByPNR();
                    break;
            case 3: t.cancelTicket();
                    break;
            case 4: m.mainMenu();
                    break;
            default: 
                cout<<"Invaild choice";
                system("PAUSE");     
                m.userMenu();
        }
    }
}

//view bookings menu function
void Menu::viewBookingsMenu()
{
    int choice;
    Ticket t;
    Menu m;
    while(1)
    {
        system("clear");
        cout<<"\n----------VIEW BOOKINGS-----------\n";
        cout<<"\n1. By PNR";
        cout<<"\n2. By Name";
        cout<<"\n3. By Bus";
        cout<<"\n4. By Source";
        cout<<"\n5. By Destination";
        cout<<"\n6. All Bookings";
        cout<<"\n7. EXIT";
        cout<<"\nEnter your choice\n";
        cin>>choice;
        switch(choice)
        {
            case 1: t.showTicketsByPNR();
                    break;
            case 2: t.showTicketsByName();
                    break;
            case 3: t.showTicketsByBus();
                    break;
            case 4: t.showTicketsBySource();
                    break;
            case 5: t.showTicketsByDestination();
                    break;
            case 6: t.showAllTickets();
                    break;
            case 7: m.adminMenu();
                    break;
            default: cout<<"\nInvaild choice\n";
                     m.viewBookingsMenu();
        }
    }
}
