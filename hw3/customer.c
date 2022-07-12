#include "customer.h"

void customerSetServiceTime (Customer *target, int duration){
	target->serviceTime = duration;
}

int customerGetServiceTime (Customer *target){
	return target->serviceTime;
}
void customerSetEntryTime (Customer *target, int duration){

	target->entryTime = duration;

}
int customerGetEntryTime(Customer *target){
	return target->entryTime;
}