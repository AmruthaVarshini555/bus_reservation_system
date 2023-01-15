#include"menu.h"
#include"bus.h"
#include"ticket.h"
#include<iostream>
#include<string>
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
void Menu::userLogin(){
    Menu login;
    ifstream file;
    string name,pswd;
    int choice;
    cout<<"\n-------------USER PORTAL--------------";
    cout<<"\n1.Register";
    cout<<"\n2.Login";
    cout<<"\nEnter your choice: ";
    switch(choice){
        case 1: cout<<"Enter username: ";
            cin>>name;
            cout<<"Enter a password: ";
            cin>>pswd;
            ofstream file;
            file.open("user.txt");
            file<<name<<","<<pswd;
            file.close();
            login.userLogin();
        case 2: 
            string nm,p;
            cout<<"\nEnter your login credentials: ";
            cout<<"\nEnter userid: ";
            cin>>name;
            cout<<"\nEnter password: ";
            cin>>pswd;
            ifstream file;
            file.open("user.txt");
            getline(file,nm);
            getline(file,p);
            if(nm==name && p=pswd){
                cout<<"Succesful Login"<<endl;
                system("PAUSE");
                login.userMenu();
            }
            else{
                cout<<"\nIncorrect Username or Password ";
                login.userLogin();
        }
    }
}
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
