#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include"logger.h"
#include"header.h"
#include "bus.h"
#include "ticket.h"
#include "utils.h"
using namespace std;

// GETTERS
char BUS:: *getBusNo()
{
    return busNo;
}

char BUS:: *getSource()
{
    return source;
}
char BUS:: *getDestination()
{
    return destination;
}
char BUS:: *getSourceTime()
{
    return sourceTime;
}
char BUS:: *getDestinationTime()
{
    return destinationTime;
}
int BUS:: getBookedSeats()
{
    return bookedSeats;
}
int BUS:: getMaxSeats()
{
    return maxSeats;
}
double BUS:: getBusFare()
{
    return busFare;
}
// SETTERS
void BUS:: setBookedSeats()
{
    bookedSeats++;
}
void BUS:: setCancelTicket()
{
    bookedSeats--;
}
void BUS:: setSource(char *s)
{
    if (s && s[0])
        strcpy(source, s);
}
void BUS:: setDestination(char *d)
{
    if (d && d[0])
        strcpy(destination, d);
}
void BUS:: setSourceTime(char *s)
{
    if (s && s[0])
      strcpy(sourceTime, s);
}
void BUS:: setDestinationTime(char *d)
{
    if (d && d[0])
        strcpy(destinationTime, d);
}
void BUS:: setBusFare(double f)
{
    if (f)
      busFare = f;
}

// ADD BUS
void Bus::addBus()
{
    fstream bus;
    system("clear");
    cout<<"\n--------ADD BUS---------";
    cout << "\n\tEnter Bus Number: ";
    cin.ignore();
    cin.getline(busNo, SIZE);
    cout << "\n\tEnter Source:-> ";
    cin.getline(source,BUFFER_SIZE);
    cout << "\n\tEnter Destination:-> ";
    cin.getline(destination,BUFFER_SIZE);
    cout << "\n\tEnter Source Time:-> ";
    cin.getline(sourceTime,BUFFER_SIZE);
    cout << "\n\tEnter Destination Time:-> ";
    cin.getline(destinationTime,BUFFER_SIZE);
    cout << "\n\tEnter Bus Fare:-> ";
    cin >> busFare;

    bus.open("buses.dat", ios::out | ios::app | ios::binary);
    bus.write((char *)this, sizeof(*this));
    bus.close();
    cout << "\n\tBus Added Successfully...!!\n";
    LOG_INFO("\nADDED THE BUS");
}

// SHOW BUS DETAILS
void Bus::showBusDetails()
{
    cout<<"\n-------------------BUS--------------------";
    cout << "\n\tBus No:-> " << getBusNo();
    cout << "\n\tSource:-> " << getSource();
    cout << "\n\tDestination:-> " << getDestination();
    cout << "\n\tTime:-> " << getSourceTime() << " - " << getDestinationTime();
    cout << "\n\tTotal Seats:-> " << getMaxSeats();
    cout << "\n\tSeats Remaining:-> " << (getMaxSeats() - getBookedSeats());
    cout << fixed << setprecision(2);
    cout << "\n\tBus Fare:-> " << getBusFare();
    LOG_INFO("SHOW BUS DETAILS");
}

// VIEW ALL BUS INFO
void Bus::showAllBus()
{
    system("clear");
    fstream bus;
    bus.open("buses.dat", ios::in | ios::app | ios::binary);
    if (!bus)
        cout << "\n\tFile Not Found...!!!";
    else
    {
        cout<<"\n-----------BUSES-----------";
        bus.read((char *)this, sizeof(*this));
        while (!bus.eof())
        {
            showBusDetails();
            bus.read((char *)this, sizeof(*this));
        }
        bus.close();
    }
    LOG_INFO("\nVIEW ALL BUS INFO"):
}

// VIEW BUS INFO
void Bus::viewBusDetails()
{
    system("clear");
    char bNo[SIZE];
    int check = 0;
    fstream bus;
    cout<<"\n-------------VIEW BUS INFO---------------";
    cout << "\n\tEnter Bus Number:-> ";
    cin.ignore();
    cin.getline(bNo,SIZE);
    
    system("clear");
    cout<<"\n-------------BUS INFO------------";
    bus.open("buses.dat", ios::in | ios::app | ios::binary);
    if (bus.fail())
    {
        cout << "\n\tCan't Open File...!!\n";
    }
    else
    {
        bus.read((char *)this, sizeof(*this));
        while (!bus.eof())
        {
            if (strcmp(getBusNo(), bNo) == 0)
            {
                showBusDetails();
                check = 1;
            }
            bus.read((char *)this, sizeof(*this));
        }
        if (check == 0)
        {
            cout << "\n\tBus Not Found...!!\n";
        }
        bus.close();
    }
    LOG_INFO("\nVIEW BUS INFO");
}

// EDIT BUS
void Bus::editBus()
{
    system("clear");
    char bNo[SIZE];
    int check = 0;

    fstream bus, temp;
    cout<<"\n----------EDIT BUS-----------";
    cout << "\n\tEnter Bus Number:-> ";
    cin.ignore();
    cin.getline(bNo,SIZE);
    bus.open("buses.dat", ios::in | ios::app | ios::binary);
    if (bus.fail())
    {
        cout << "\n\tCan't Open File...!!\n";
    }
    else
    {
        temp.open("temp.dat", ios::out | ios::app | ios::binary);

        bus.read((char *)this, sizeof(*this));
        while (!bus.eof())
        {
            if (strcmp(getBusNo(), bNo) == 0)
            {
                system("clear");
                cout<<"\n-----------EDIT BUS-------------";
                showBusDetails();
                char s[BUFFER_SIZE], d[BUFFER_SIZE], sTime[BUFFER_SIZE], dTime[BUFFER_SIZE];
                double fare;
                cout << "\n\tEnter Source:-> ";
                cin.getline(s, BUFFER_SIZE);
                cout << "\n\tEnter Destination:-> ";
                cin.getline(d,BUFFER_SIZE);
                cout << "\n\tEnter Source Time:-> ";
                cin.getline(sTime,BUFFER_SIZE);
                cout << "\n\tEnter Destination Time:-> ";
                cin.getline(dTime,BUFFER_SIZE);
                cout << "\n\tEnter Bus Fare:-> ";
                cin.ignore();
                cin >> fare;
                setSource(s);
                setDestination(d);
                setSourceTime(sTime);
                setDestinationTime(dTime);
                setBusFare(fare);
                temp.write((char *)this, sizeof(*this));
                check = 1;
            }
            else
            {
                temp.write((char *)this, sizeof(*this));
            }
            bus.read((char *)this, sizeof(*this));
        }

        if (check = 1)
        {
            cout << "\n\tBus Updated Successfully...!!\n";
        }
        else
        {
            cout << "\n\tBus Not Found...!!\n";
        }
        bus.close();
        temp.close();
        remove("buses.dat");
        rename("temp.dat", "buses.dat");
    }
    LOG_INFO("\nVIEW BUS");
}

// DELETE BUS
void Bus::deleteBus()
{
    system("clear");
    char bNo[SIZE];
    int check = 0;
    fstream bus, temp;
    cout<<"-----------DELETE BUS--------------";
    cout << "\n\tEnter Bus No:-> ";
    cin.ignore();
    cin.getline(bNo,SIZE);
    bus.open("buses.dat", ios::in | ios::app | ios::binary);
    if (bus.fail())
    {
        cout << "\n\tCan't Open File...!!";
        system("pause");
    }
    else
    {
        temp.open("temp.dat", ios::out | ios::app | ios::binary);
        bus.read((char *)this, sizeof(*this));
        while (!bus.eof())
        {
            if (strcmp(getBusNo(), bNo) != 0)
            {
                temp.write((char *)this, sizeof(*this));
            }
            else
            {
                check = 1;
            }
            bus.read((char *)this, sizeof(*this));
        }

        if (check == 0)
        {
            cout << "\n\tBus Not Found...!!\n";
        }
        else
        {
            cout << "\n\tBus Deleted...!!\n";
        }

        bus.close();
        temp.close();
        remove("buses.dat");
        rename("temp.dat", "buses.dat");
    }
    LOG_INFO("\nDELETE BUS");
}
