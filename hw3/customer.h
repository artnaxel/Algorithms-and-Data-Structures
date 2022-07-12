#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED

typedef struct{
	int serviceTime;
	int entryTime;
} Customer;

void customerSetServiceTime (Customer *target, int duration);

int customerGetServiceTime (Customer *target);

void customerSetEntryTime(Customer *target, int duration);

int customerGetEntryTime(Customer *target);
#endif