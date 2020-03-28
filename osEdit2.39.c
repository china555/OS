#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h>

#define queue_size 100
int count1=0,count2=0,count4=0;
long seat4[1],seat2[2],seat1[4]; 
long queue[queue_size];
int cid[100];
int tempcid =0;
int seat[] = {1,2,4};
pthread_mutex_t lock;
int currentQueueIndex=0;
void * bakery(void *number);
int getQueue(int seatNumber);
void addQueue(int seatNumber);
void addNewQueueAfterSeatComplete(int seatNum);
void sleepThreadBySeat(int seatNumber);

int getQueue(int seatNumber){
    for(int i=0;i<currentQueueIndex;i++){
        if(queue[i]==seatNumber){
            int temp = queue[i];
            tempcid = cid[i];
            for(int j=i;j<currentQueueIndex;j++){
                queue[j] = queue[j+1];
                cid[j] = cid[j+1];
            }
            currentQueueIndex--; 
            return temp;
        }
    }
}
void addQueue(int seatNumber,int Customer_id){
    queue[currentQueueIndex] = seatNumber;
    cid[currentQueueIndex] = Customer_id;
    currentQueueIndex++;
}
void addNewQueueAfterSeatComplete(int seatNum){
    int seatNumber = getQueue(seatNum);
    bakery(&seatNumber);
}

void sleepThreadBySeat(int seatNumber,int Customer_id){
    int minute1,minute2;
    if(seatNumber == 4){
        minute1 = 15; // 15;
        minute2 = 3;
     }else if(seatNumber == 2){
        minute1 = 10; //10;
        minute2 = 2;
    }else if(seatNumber == 1){
        minute1 = 5; // 5
        minute2 = 1;
    }
    sleep(minute2);
    printf("Customer: %d Finish from %d minute\n",Customer_id,minute1);
    addNewQueueAfterSeatComplete(seatNumber);
}
void showallseat(int tempcount, long tempseat[],int numseat){
    for(int i =0;i<tempcount;i++){
        printf("%d-seat at table number %d %ld \n",numseat,i+1,tempseat[i]);
    }
}

void * bakery(void *number){
    int  *seatNumber = (int *) number;
    int Customer_id
    if(*seatNumber == 0) return NULL;
    if(tempcid == 0){
        Customer_id =  (rand() % (99999 - 10000 +1))+10000;
    }
      printf("The customer %d need table have %d seat \n",Customer_id,*seatNumber);
    if(*seatNumber == 1){
        if(count1 < 4){
            seat1[count1] = pthread_self();
            count1++;
            sleepThreadBySeat(*seatNumber,Customer_id);
        }else{
            addQueue(*seatNumber,Customer_id);
        }
    }else if(*seatNumber == 2){
        if(count2 < 2){
            seat2[count2] = pthread_self();
            count2++;
            sleepThreadBySeat(*seatNumber,Customer_id);
        }else{
            addQueue(*seatNumber,Customer_id);
        }
    }else if(*seatNumber == 4){
        if(count4 < 1){
            seat4[count4] = pthread_self();
            count4++;
            sleepThreadBySeat(*seatNumber,Customer_id);
        }else{
            addQueue(*seatNumber,Customer_id);
        }
    }
  return NULL;
}
void amountOfQueue(){
    int countQueue =0;
    for(int i=0;i<currentQueueIndex;i++){
        countQueue++;
    }
    printf("Have %d Queue\n\n\n",countQueue);
}
int main(void)
{
    pthread_t tid;
    pthread_mutex_lock(&lock); 
    int i= 0,timeall =120,timecur =0;
    while(i<=120){
        printf("Time Remainning %d minute\n",timeall-timecur);
        int num = seat[(rand()%3)];
        pthread_create(&tid, NULL, bakery,&num);
         sleep(1); // 5 minute
        showallseat(count1,seat1,seat[0]);
        showallseat(count2,seat2,seat[1]);
        showallseat(count4,seat4,seat[2]);
        printf("IN QUENE ");
        amountOfQueue();
        sleep(1); // 5 minute
        i=i+10; // 10 minute
        timecur +=10;
    }
    pthread_mutex_unlock(&lock);
    pthread_join(tid, NULL);
    return 0;
}