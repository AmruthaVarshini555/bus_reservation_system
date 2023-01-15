#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include"header.h"
#include"logger.h"
#include "ticket.h"
#include "bus.h"
#include "utils.h"

using namespace std;

// GENERATE TICKET
void Ticket::generateTicket(char *n, Bus b)
{
    LOG_INFO("\nTicket Generation");
    strcpy(name, n);
    strcpy(pnrNo, generatePNR(99999).c_str());
    strcpy(date, getCurrentDate().c_str());
    bus = b;
}

// DISPLAY TICKET DETAILS
void Ticket::displayTicket()
{
    cout << "\n-----------DISPLAY TICKET-------------\n";
    cout << "\n\t Name:-> " << getName();
    cout << "\n\t PNR No:-> " << getPnrNo();
    cout << "\n\t Bus No:-> " << bus.getBusNo();
    cout << "\n\t Seat No.:-> " << bus.getBookedSeats();
    cout << "\n\t Date:-> " << getDate();
    cout << "\n\t Source:-> " << bus.getSource();
    cout << "\n\t Destination:-> " << bus.getDestination();
    cout << "\n\t Start Time:-> " << bus.getSourceTime();
    cout << "\n\t Destination Time:-> " << bus.getDestinationTime();
    cout << fixed << setprecision(2);
    cout << "\n\t Bus Fare:-> " << bus.getBusFare();
    LOG_INFO("\nDisplay Ticket");
    cout << "\n";
}

// BOOK TICKET
void Ticket::bookTicket()
{
    system("clear");
    char source[BUFFER_SIZE], destination[BUFFER_SIZE];
    int check = 0;
    Bus b;
    fstream bus, ticket, temp;
    cout<<"\n------------BOOK TICKET-------------";
    bus.open("buses.dat", ios::in | ios::app | ios::binary);
    if (bus.fail())
    {
        cout << "\n\tCan't Open File...!!\n";
    }
    else
    {
        cout << "\n\tEnter Source:-> ";
        cin.ignore();
        cin.getline(source,BUFFER_SIZE);
        cout << "\n\tEnter Destination:-> ";
        cin.getline(destination, BUFFER_SIZE);

        system("clear");
        cout<<"\n-----------------AVAILABLE BUSES-------------------";
        bus.read((char *)&b, sizeof(b));
        while (!bus.eof())
        {
            if (strcmp(b.getSource(), source) == 0 && strcmp(b.getDestination(), destination) == 0)
            {
                b.showBusDetails();
                check = 1;
            }
            bus.read((char *)&b, sizeof(b));
        }
        bus.close();

        if (check == 0)
        {
            cout << "\n\tNo Buses Found...!!\n";
        }
        else
        {
            char bNo[SIZE];
            int booked = 0;
            cout << "\n\tEnter Bus Number:-> ";
            cin.getline(bNo, SIZE);
            bus.open("buses.dat", ios::in | ios::app | ios::binary);
            temp.open("temp.dat", ios::out | ios::app | ios::binary);
            bus.read((char *)&b, sizeof(b));
            while (!bus.eof())
            {
                if (strcmp(b.getSource(), source) == 0 && strcmp(b.getDestination(), destination) == 0 && strcmp(b.getBusNo(), bNo) == 0)
                {
                    if (b.getBookedSeats() >= 32)
                    {
                        cout << "\n\tSeat not available...!!\n";
                        break;
                    }
                    else
                    {
                        system("clear");
                        cout<<"\n-------------BOOK TICKET------------";
                        char n[BUFFER_SIZE];
                        cout << "\n\tEnter Customer Name :-> ";
                        cin.getline(n, BUFFER_SIZE);
                        b.setBookedSeats();
                        generateTicket(n, b);
                        ticket.open("tickets.dat", ios::out | ios::app | ios::binary);
                        ticket.write((char *)this, sizeof(*this));
                        ticket.close();
                        temp.write((char *)&b, sizeof(b));
                        booked = 1;
                        system("clear");
                        cout<<"\n---------BOOKING DETAILS-------------";
                        displayTicket();
                        cout << "\n\tTicket Booked Successfully...!!\n";
                    }
                }
                else
                {
                    temp.write((char *)&b, sizeof(b));
                }
                bus.read((char *)&b, sizeof(b));
            }

            if (booked == 1)
            {
                bus.close();
                temp.close();
                remove("buses.dat");
                rename("temp.dat", "buses.dat");
            }
        }
        bus.close();
    }
    LOG_INFO("\nBook Ticket");
}

// CANCEL TICKET
void Ticket::cancelTicket()
{
    system("clear");
    char pnr[SIZE];
    int check = 0;
    fstream bus, ticket, temp, bus;

    cout<<"\n------------CANCEL TICKET--------------";
    cout << "\n\tEnter PNR Number:-> ";
    cin.ignore();
    cin.getline(pnr,SIZE);
    ticket.open("tickets.dat", ios::in | ios::app | ios::binary);
    temp.open("temp.dat", ios::out | ios::app | ios::binary);
    if (ticket.fail())
    {
        cout << "\n\tCan't Open File...!!\n";
    }
    else
    {
        ticket.read((char *)this, sizeof(*this));
        while (!ticket.eof())
        {
            if (strcmp(getPnrNo(), pnr) != 0)
            {
                temp.write((char *)this, sizeof(*this));
            }
            else
            {
                Bus b;
                bus.open("buses.dat", ios::in | ios::app | ios::binary);
                bus.open("bustemp.dat", ios::out | ios::app | ios::binary);
                bus.read((char *)&b, sizeof(b));
                while (!bus.eof())
                {
                    if (strcmp(b.getBusNo(), bus.getBusNo()) == 0)
                    {
                        b.setCancelTicket();
                        bus.write((char *)&b, sizeof(b));
                    }
                    else
                    {
                        bus.write((char *)&b, sizeof(b));
                    }
                    bus.read((char *)&b, sizeof(b));
                }
                bus.close();
                bus.close();
                remove("buses.dat");
                rename("bustemp.dat", "buses.dat");
                check = 1;
            }
            ticket.read((char *)this, sizeof(*this));
        }
        if (check == 0)
        {
            ticket.close();
            temp.close();
            cout << "\n\tTicket Not Found...!!\n";
        }
        else
        {
            ticket.close();
            temp.close();
            remove("tickets.dat");
            rename("temp.dat", "tickets.dat");
            cout << "\n\tTicket Cancelled...!!\n";
        }
    }
    LOG_INFO("\nTicket cancel");
}

// EDIT TICKET
void Ticket::editTicket()
{
    system("clear");

    char pnr[SIZE];
    int check = 0;
    fstream ticket, temp;
    cout<<"\n------------EDIT TICKET-------------");
    cout << "\n\tEnter PNR Number:-> ";
    cin.ignore();
    cin.getline(pnr,SIZE);

    ticket.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }
    else
    {
        temp.open("temp.dat", ios::out | ios::app | ios::binary);

        ticket.read((char *)this, sizeof(*this));
        while (!ticket.eof())
        {
            if (strcmp(getPnrNo(), pnr) == 0)
            {
                system("clear");
                cout<<"\n---------------EDIT TICKET-------------";
                displayTicket();
                char n[BUFFER_SIZE];
                cout << "\n\tEnter Passenger Name :-> ";
                cin.getline(n, BUFFER_SIZE);
                setName(n);
                temp.write((char *)this, sizeof(*this));
                check = 1;
            }
            else
            {
                temp.write((char *)this, sizeof(*this));
            }
            ticket.read((char *)this, sizeof(*this));
        }
        if (check = 1)
        {
            cout << "\n\tTicket Updated Successfully...!!\n";
        }
        else
        {
            cout << "\n\tTicket Not Found...!!\n";
        }

        ticket.close();
        temp.close();
        remove("tickets.dat");
        rename("temp.dat", "tickets.dat");
    }
    LOG_INFO("\nEdit Ticket");
}

// SHOW TICKET BY PNR
void Ticket::showTicketsByPNR()
{
    system("clear");
    char pnr[SIZE];
    int chk = 0;
    fstream ticket;

    cout<<"\n-------SHOW BOOKINGS BY PNR--------";
    cout << "\n\tEnter PNR Number:-> ";
    cin.ignore();
    cin.getline(pnr, SIZE);
    system("clear");
    cout<<"\n--------BOOKINGS----------";

    ticket.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticket.fail())
    {
        cout << "\n\tCan't Open File...!!\n";
    }
    else
    {
        ticket.read((char *)this, sizeof(*this));
        while (!ticket.eof())
        {
            if (strcmp(getPnrNo(), pnr) == 0)
            {
                displayTicket();
                check = 1;
            }
            ticket.read((char *)this, sizeof(*this));
        }
        if (check == 0)
        {
            cout << "\n\tNo Bookings...!!\n";
        }
        ticket.close();
    }
    LOG_INFO("\nTicket by PNR");
}

// SHOW TICKET BY NAME
void Ticket::showTicketsByName()
{
    system("clear");
    char n[BUFFER_SIZE];
    int check = 0;
    fstream ticket;
    cout<<"\n------SHOW BOOKINGS BY NAME------";
    cout << "\n\tEnter Passenger Name:-> ";
    cin.ignore();
    cin.getline(n,BUFFER_SIZE);
    system("clear");
    cout<<"\n--------BOOKINGS--------";
    ticket.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticket.fail())
    {
        cout << "\n\tCan't Open File...!!\n";
    }

    else
    {
        ticket.read((char *)this, sizeof(*this));
        while (!ticket.eof())
        {
            if (strcmp(getName(), n) == 0)
            {
                displayTicket();
                check = 1;
            }
            ticket.read((char *)this, sizeof(*this));
        }
        if (check == 0)
        {
            cout << "\n\tNo Bookings...!!\n";
        }
        ticket.close();
    }
    LOG_INFO("\nTicket by name");
}

// SHOW TICKET BY BUS
void Ticket::showTicketsByBus()
{
    system("clear");
    char bNo[SIZE];
    int check = 0;
    fstream ticket;

    cout<<"\n-----SHOW BOOKINGS BY NAME-------";
    cout << "\n\tEnter Bus Number:-> ";
    cin.ignore();
    cin.getline(bNo, SIZE);

    system("clear");
    cout<<"\n-----------BOOKINGS--------------";
    ticket.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticket.fail())
    {
        cout << "\n\tCan't Open File...!!\n";
    }

    else
    {
        ticket.read((char *)this, sizeof(*this));
        while (!ticket.eof())
        {
            if (strcmp(bus.getBusNo(), bNo) == 0)
            {
                displayTicket();
                check = 1;
            }
            ticket.read((char *)this, sizeof(*this));
        }
        if (check == 0)
        {
            cout << "\n\tNo Bookings...!!\n";
        }
        ticket.close();
    }
    LOG_INFO("\nTicket by bus");
}

// SHOW TICKET BY SOURCE
void Ticket::showTicketsBySource()
{
    system("clear");
    char s[BUFFER_SIZE];
    int check = 0;
    fstream ticket;

    cout<<"\n----SHOW BOOKINGS BY SOURCE----";
    cout << "\n\tEnter Source:-> ";
    cin.ignore();
    cin.getline(s, BUFFER_SIZE);
    system("clear");
    cout<<"\n-------BOOKINGS--------";

    ticket.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticket.fail())
    {
        cout << "\n\tCan't Open File...!!\n";
    }

    else
    {
        ticket.read((char *)this, sizeof(*this));
        while (!ticket.eof())
        {
            if (strcmp(bus.getSource(), s) == 0)
            {
                displayTicket();
                check = 1;
            }
            ticket.read((char *)this, sizeof(*this));
        }
        if (check == 0)
        {
            cout << "\n\tNo Bookings...!!\n";
        }
        ticket.close();
    }
    LOG_INFO("\nTicket by source");
}

// SHOW TICKET BY DESTINATION
void Ticket::showTicketsByDestination()
{
    system("clear");

    char d[BUFFER_SIZE];
    int check = 0;
    fstream ticket;

    cout<<"---SHOW BOOKINGS BY DESTINATION---";
    cout << "\n\tEnter Destination:-> ";
    cin.ignore();
    cin.getline(d, BUFFER_SIZE);
    system("clear");
    cout<<"\n-----------BOOKINGS---------";

    ticket.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticket.fail())
    {
        cout << "\n\tCan't Open File...!!\n";
    }
    else
    {
        ticket.read((char *)this, sizeof(*this));
        while (!ticket.eof())
        {
            if (strcmp(bus.getDestination(), d) == 0)
            {
                displayTicket();
                check = 1;
            }
            ticket.read((char *)this, sizeof(*this));
        }
        if (check == 0)
        {
            cout << "\n\tNo Bookings...!!\n";
        }
        ticket.close();
    }
    LOG_INFO("\nShow By Destination");
}

// SHOW ALL BOOKINGS
void Ticket::showAllTickets()
{
    system("clear");
    fstream ticket;
    system("clear");
    cout<<"\n--------BOOKINGS-------";
    ticket.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticket.fail())
    {
        cout << "\n\tCan't Open File...!!\n";
    }

    else
    {
        ticket.read((char *)this, sizeof(*this));
        while (!ticket.eof())
        {
            displayTicket();
            ticket.read((char *)this, sizeof(*this));
        }
        ticket.close();
    }
    LOG_INFO("\nShow All Bookings");
}
