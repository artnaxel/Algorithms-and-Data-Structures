/* VIP BANK SIMULATION

Aleksandra Kondratjeva

Problem:
Make a simulation and comparison of two banks.
One with usual cashiers that serve VIP clients out of queue, and one with both usual and
VIP cashiers with separate queue for VIP clients.

Evaluate and compare:
1) Total cashiers' inactive time
2) 2x total cashiers' extra work minutes
3) 3x average usual customers' waiting time
4) 10x VIP customer's max waiting time
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "customer.h"
#include "cashier.h"
#include "queue.h"
#include "pqueue.h"

#define CASHIER 3
#define VIP_CASHIER 2

#define VIP_SERVICE_TIME 20
#define SERVICE_TIME 10

#define SIM_TIME 70

int main(){
    float VIParrival = 0.3;
    float arrival = 0.5;
    time_t t;

    int clock = 0;
    int extra_pq = 0;
    int extra_queue = 0;

    int standby_pq_VIP = 0;
    int standby_pq = 0;
    int standby = 0;
    int standby_VIP = 0;
    int maxVIPpQueue = 0;
    int maxVIPqueue = 0;

    int served_pq_VIP = 0;
    int served_pq = 0;
    int served = 0;
    int served_VIP = 0;
    
    float average_pq;
    float average_pq_VIP;
    float average;
    float average_VIP;

    int inactiveTime_pq = 0;
    int inactiveTime_q = 0;

    int customer_in = 0;
    int VIP_customer_in = 0;
    int first_process_customers = 0;
    int second_process_customers = 0;

    Cashier cashier_pq[CASHIER + VIP_CASHIER];

    Cashier cashier[CASHIER];
    Cashier VIPcashier[VIP_CASHIER];
    Customer customer;

    //QUEUE FOR FIRST BANK
    pQueue* pqueue;

    //TWO SEPARATE QUEUES FOR SECOND BANK
    Queue *queue;
    Queue *VIPqueue;


    printf("Simulation runs %d minutes.\n", SIM_TIME);
    printf("Service time for usual client: %d\n", SERVICE_TIME);
    printf("Service time for VIP client: %d\n", VIP_SERVICE_TIME);
    printf("Number 1 bank has %d cashiers that serve VIP clients with high priority.\n", CASHIER);
    printf("Number 2 bank has %d cashiers that serve VIP clients in the separate queue.\n", VIP_CASHIER);
    printf("Customer arrival probability is: %0.1f\n", arrival);
    printf("VIP customer arrival probability is: %0.1f\n", VIParrival);

    //CREATING CASHIERS
    for (int i = 0; i < CASHIER + VIP_CASHIER; i++){
        createCashier(&cashier_pq[i]);
    }

    for (int i = 0; i < CASHIER; i++){
        createCashier(&cashier[i]);
    }

    for (int i = 0; i < VIP_CASHIER; i++){
        createCashier(&VIPcashier[i]);
    }

    //CREATING QUEUES
    pqueue = newpQueue();
    queue = createQueue();
    VIPqueue = createQueue();

    srand(time(&t));

    /*Banks will work until all queues will be empty and the simulation time has passed
    If there are customers that are being served at the moment, remaining time will be added to total busy time
    of the cashier and calculated as extra*/

    while(clock < SIM_TIME || !isEmptyQueue(queue) || !isEmptyQueue(VIPqueue) || !isEmptyPQueue(pqueue)){

       /*If the bank isn't close, then a customer can arrrive.
       Generating a random number between 0 and 1. If the random number is less than the VIP arrival
       rate, it creates a VIP customer and adds it to the priority queue and the VIP queue. If the
       random number is less than the arrival rate, it creates a regular customer and adds it to the
       priority queue and the regular queue. */

        if (clock < SIM_TIME){
            float randArrival = (float)rand() / (float)RAND_MAX;
            printf("\nrand: %f", randArrival);

            //IF VIP CUSTOMER ARRIVED
            if (randArrival < VIParrival){
                customerSetServiceTime(&customer, VIP_SERVICE_TIME);
                customerSetEntryTime(&customer, clock);

                //PUTTING VIP CUSTOMER TO QUEUE WITH HIGH PRIORITY
                push(pqueue, &customer, 1);                

                //PUTTING VIP CUSTOMER TO VIP QUEUE
                enqueue(VIPqueue, &customer);

                VIP_customer_in++;
            }
            

            //IF USUAL CLIENT ARRIVED
            else if (randArrival < arrival){
                customerSetServiceTime(&customer, SERVICE_TIME);
                customerSetEntryTime(&customer, clock);

                //PUTTING USUAL CUSTOMER TO QUEUE WITH LOW PRIORITY
                push(pqueue, &customer, 0);
                
                //PUTTING USUAL CUSTOMER TO QUEUE
                enqueue(queue, &customer);
                customer_in++;
            }
        }

        //FIRST PROCESS
        /*Loop for the first Bank with the priority queue. Searching for a free cashier and assigning customers
        using priority. If the cashier is busy, then incrementing busy time and decrementing remaining time. */
        for (int i = 0; i < CASHIER + VIP_CASHIER; i++){
            if (cashierFree(&cashier_pq[i])){
                if (!isEmptyPQueue(pqueue)){

                    int priority = pop(pqueue);

                    if (priority){
                        standby_pq_VIP += clock - customerGetEntryTime(&customer);
                        if((clock - customerGetEntryTime(&customer)) > maxVIPpQueue){
                            maxVIPpQueue = clock - customerGetEntryTime(&customer);
                        }

                        served_pq_VIP++;
                        setCashierRemainingTime(&cashier_pq[i], VIP_SERVICE_TIME - 1);
                    }

                    else{
                        standby_pq += clock - customerGetEntryTime(&customer);
                        served_pq ++;
                        setCashierRemainingTime(&cashier_pq[i], SERVICE_TIME - 1);
                    }

                    cashierBusy(&cashier_pq[i]);
                    cashierNewCustomer(&cashier_pq[i]);
                }
                else if(clock < SIM_TIME){
                    cashierInactive(&cashier_pq[i]);
                }
            }
            else{
                cashier_pq[i].remainingTime--;
                cashierBusy(&cashier_pq[i]);
                
            }
        }

        //SECOND PROCESS

        /*The same logic as for first proccess, but two separate loops. The first one is for the usual customers
        and the second is for VIP customers */
        for (int i = 0; i < CASHIER; i++){
            if (cashierFree(&cashier[i])){
                if (!isEmptyQueue(queue)){
                    standby += clock - customerGetEntryTime(&customer);
                    served++;
                    dequeue(queue);
                    cashierNewCustomer(&cashier[i]);
                    setCashierRemainingTime(&cashier[i], SERVICE_TIME - 1);
                    cashierBusy(&cashier[i]);
                }
                else if(clock < SIM_TIME){
                    cashierInactive(&cashier[i]);
                }
            }
            else{
                cashier[i].remainingTime--;
                cashierBusy(&cashier[i]);
            }
        }

        for (int i = 0; i < VIP_CASHIER; i++){
            if (cashierFree(&VIPcashier[i])){
                if(!isEmptyQueue(VIPqueue)){
                    standby_VIP  += clock - customerGetEntryTime(&customer);
                    if((clock - customerGetEntryTime(&customer)) > maxVIPqueue){
                            maxVIPqueue = clock - customerGetEntryTime(&customer);
                        }
                    served_VIP++;
                    dequeue(VIPqueue);
                    cashierNewCustomer(&VIPcashier[i]);
                    setCashierRemainingTime(&VIPcashier[i], VIP_SERVICE_TIME -1);
                    cashierBusy(&VIPcashier[i]);
                }
                else if (clock < SIM_TIME){
                    cashierInactive(&VIPcashier[i]);
                }
            }
            else{
                VIPcashier[i].remainingTime--;
                cashierBusy(&VIPcashier[i]);
            }
        }
            clock++;
    }

    /* Calculating average waiting time */
    if (served_pq == 0){
        average_pq = 0.0;
    }
	else{
        average_pq = ((float)standby_pq) / ((float)served_pq);
    }

    if (served_pq_VIP == 0){
         average_pq_VIP = 0.0;
    }
    else{
        average_pq_VIP = ((float)standby_pq_VIP) / ((float)served_pq_VIP);
    }
    
    if (served == 0){
        average = 0.0;
    }
    else{
        average = ((float)standby) / ((float)served);
    }
    if(served_VIP == 0){
        average_VIP = 0.0;
    }
    else{
        average_VIP = ((float)standby_VIP) / ((float)served_VIP);
    }

    printf("\n--------------------------------------------SIMULATION ENDED SUCCESFULLY----------------------------------------\n");
    printf("\nWith %f arrival probability came %d customers.\n", arrival, customer_in);
    printf("\nWith %f arrival probability came %d VIP customers.\n", VIParrival, VIP_customer_in);

    //......................................................................................//
    printf("\n\n-----------BANK NUMBER 1 (pqueue)-----------\n");
        for(int i = 0; i < CASHIER + VIP_CASHIER; i++){
            printf("\nThe cashier %d:", i+1);
            printf("\nWas inactive for %d minutes.", getCashierInactiveTime(&cashier_pq[i]));
		    printf("\nWas busy for %d minutes.", getCashierBusyTime(&cashier_pq[i]) + cashier_pq[i].remainingTime);
		    printf("\nHas served %d customers.", getCashierCustomersNumber(&cashier_pq[i]));
            if ((getCashierBusyTime(&cashier_pq[i])+ cashier_pq[i].remainingTime - SIM_TIME) > 0){
                extra_pq +=getCashierBusyTime(&cashier_pq[i])+ cashier_pq[i].remainingTime - SIM_TIME;
                printf("\nCashier worked for %d extra minutes after closing bank.", getCashierBusyTime(&cashier_pq[i]) + cashier_pq[i].remainingTime - SIM_TIME);
            }
		    printf("\n------------------------------------------------------------------------------");
            inactiveTime_pq += getCashierInactiveTime(&cashier_pq[i]);
            first_process_customers += getCashierCustomersNumber(&cashier_pq[i]);
            
        }
    printf("\nThe waiting average time for a usual customer is %0.2f minutes.", average_pq);
    printf("\nThe waiting average time for a VIP customer is %0.2f minutes.", average_pq_VIP);
    printf("\nThe max waiting time for a VIP customer is: %d", maxVIPpQueue);
        
    printf("\n%d Usual customers were served.", served_pq);
    printf("\n%d VIP customers were served.", served_pq_VIP);

    printf("\n%d Total customers were served.\n", first_process_customers);
    printf("\n%d Total inactive time.", inactiveTime_pq);
	printf("\n%d Total extra minutes.",extra_pq);
    printf("\nIs priority queue empty: %d", isEmptyPQueue(pqueue));


//------------------------------------------------------------------------------------------------------------------------
    printf("\n\n-----------BANK NUMBER 2 (separate queues)-----------\n");
    for(int i = 0; i < CASHIER; i++){
        printf("\nThe cashier %d:", i + 1);
        printf("\nWas inactive for %d minutes.", getCashierInactiveTime(&cashier[i]));
        printf("\nWas busy for %d minutes.", getCashierBusyTime(&cashier[i]) + cashier[i].remainingTime);
        printf("\nHas served %d customers.\n", getCashierCustomersNumber(&cashier[i]));
        if ((getCashierBusyTime(&cashier[i])+ cashier[i].remainingTime - SIM_TIME) > 0){
            extra_queue += getCashierBusyTime(&cashier[i])+ cashier[i].remainingTime - SIM_TIME;
            printf("\nCashier worked for %d minutes after closing bank.", getCashierBusyTime(&cashier[i]) + cashier[i].remainingTime - SIM_TIME);
        }
        printf("\n------------------------------------------------------------------------------");
        second_process_customers += getCashierCustomersNumber(&cashier[i]);
        inactiveTime_q += getCashierInactiveTime(&cashier[i]);
    }

    for(int i = 0; i < VIP_CASHIER; i++){
        printf("\nThe VIP cashier %d:", i + 1);
        printf("\nWas inactive for %d minutes.", getCashierInactiveTime(&VIPcashier[i]));
        printf("\nWas busy for %d minutes.", getCashierBusyTime(&VIPcashier[i]) + VIPcashier[i].remainingTime);
        printf("\nHas served %d customers.\n", getCashierCustomersNumber(&VIPcashier[i]));
        if ((getCashierBusyTime(&VIPcashier[i]) + VIPcashier[i].remainingTime - SIM_TIME) > 0){
            extra_queue += getCashierBusyTime(&VIPcashier[i])+ VIPcashier[i].remainingTime - SIM_TIME;
            printf("\nCashier worked for %d extra minutes after closing bank.", getCashierBusyTime(&VIPcashier[i]) + VIPcashier[i].remainingTime - SIM_TIME);
        }
        printf("\n------------------------------------------------------------------------------");
        second_process_customers += getCashierCustomersNumber(&VIPcashier[i]);
        inactiveTime_q += getCashierInactiveTime(&VIPcashier[i]);
    }
    printf("\nThe waiting average time for a usual customer is %0.2f minutes.", average);
    printf("\nThe waiting average time for a VIP customer is %0.2f minutes.", average_VIP);
    printf("\nThe max waiting time for a VIP customer is: %d", maxVIPqueue);
    
    printf("\n%d Usual customers were served.", served);
    printf("\n%d VIP customers were served.", served_VIP);

    printf("\n%d Total customers were served.\n", second_process_customers);
    printf("\n%d Total inactive time.", inactiveTime_q);
    printf("\n%d Total extra minutes.", extra_queue);

    printf("\nIs the queue empty: %d", isEmptyQueue(queue));
    printf("\nIs the VIP queue empty: %d", isEmptyQueue(VIPqueue));

    printf("\n\n----------------------------------------------------------------------PRINTING STATS----------------------------------------------------------------------\n\n");
    printf("                 inactive time     2x extra time           3x average usual customer waiting time              10x VIP max waiting time\n");
    printf("BANK 1 (pqueue)       %d                %-4d                                %0.2f                                            %-4d\n", inactiveTime_pq, 2*extra_pq, 3*average_pq, 10*maxVIPpQueue);
    printf("BANK 2 (queue)        %d                %-4d                                %0.2f                                            %-4d\n", inactiveTime_q, 2*extra_queue, 3*average, 10*maxVIPqueue);

    return 0;
}