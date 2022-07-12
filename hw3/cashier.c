#include "cashier.h"

void createCashier(Cashier *cashier){
    cashier->numberOfCustomers = 0;
    cashier->busyTime = 0;
    cashier->inactiveTime = 0;
    cashier->remainingTime = 0;
  //  cashier->present = 0;
}

void cashierNewCustomer(Cashier *cashier){
    cashier->numberOfCustomers++;
}

void setCashierRemainingTime(Cashier *cashier, int duration){
    cashier->remainingTime = duration;
}

int getCashierCustomersNumber(Cashier *cashier){
    return cashier->numberOfCustomers;
}

int getCashierInactiveTime(Cashier * cashier){
	return cashier->inactiveTime;
}
int getCashierBusyTime(Cashier * cashier){
	return cashier->busyTime;
}

void cashierInactive (Cashier *cashier){
    cashier->inactiveTime++;
}

void cashierBusy(Cashier *cashier){
    cashier->busyTime++;
   // cashier->remainingTime--;
}

int cashierFree(Cashier * cashier){
	return cashier->remainingTime == 0;
}