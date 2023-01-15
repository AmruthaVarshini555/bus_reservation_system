#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include"logger.h"
#include"header.h"
#include "bus.h"

// CLASS TICKET
class Ticket
{
private:
    char name[BUFFER_SIZE], pnrNo[SIZE], date[BUFFER_SIZE];
    Bus bus;
public:
    Ticket(){
        LOG_INFO("\nTicket Default Constructor invoked");
    }
    void generateTicket(char *, Bus);
    void displayTicket();
    void bookTicket();
    void cancelTicket();
    void editTicket();
    void showTicketsByPNR();
    void showTicketsByName();
    void showTicketsByBus();
    void showTicketsBySource();
    void showTicketsByDestination();
    void showAllTickets();

    // GETTERS
    char *getName();
    char *getPnrNo();
    char *getDate();
    // SETTERS
    void setName(char*);
    
    ~Ticket(){
        LOG_INFO("\nDestructor of ticket invoked");
    }
};
#endif // !TICKET_H
