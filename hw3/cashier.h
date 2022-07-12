#ifndef CASHIER_H
#define CASHIER_H

typedef struct{
    int numberOfCustomers;
	int busyTime;
	int inactiveTime;
	int remainingTime;
//	int present;
} Cashier;

void createCashier (Cashier *cashier);

void cashierNewCustomer (Cashier *cashier);

void setCashierRemainingTime (Cashier *cashier, int duration);

int getCashierCustomersNumber (Cashier *cashier);

int getCashierInactiveTime(Cashier *cashier);

int getCashierBusyTime(Cashier* cashier);

void cashierInactive (Cashier *cashier);

void cashierBusy (Cashier *cashier);

int cashierFree(Cashier * cashier);

#endif