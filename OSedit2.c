#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h>

#define queue_size 1000
int count1=0,count2=0,count4=0;
long queue[queue_size];
int seat[] = {1,2,4};
pthread_mutex_t lock;
int currentQueueIndex=0;

int getQueue(){
    
}
void addQueue(int seatNumber){
    queue[currentQueueIndex] = seatNumber;
    currentQueueIndex++;
}
void addNewQueueAfterSeatComplete(){
    int seatNumber = getQueue();
    addToSeat(seatNumber);
}

void sleepThreadBySeat(int seatNumber){
    int minute;
    if(seatNumber == 4){
        minute = 15; // 15;
     }else if(seatNumber == 2){
        minute = 10; //10;
    }else if(seatNumber == 1){
        minute = 5; // 5
    }
    sleep(minute);
    printf("Finish from %d minute\n", minute);
    addNewQueueAfterSeatComplete();
}

void * bakery(void *number){
  pthread_mutex_lock(&lock); 
  int  seatNumber = (int *) number;

  // printf("%d ",*num);
    if(seatNumber == 1){
        if(count1 < 4){
            count1++;
            sleepThreadBySeat(seatNumber);
        }else{
            addQueue(seatNumber);
        }
    }else if(seatNumber == 2){
        if(count2 < 2){
            count2++;
            sleepThreadBySeat(seatNumber);
        }else{
            addQueue(seatNumber);
        }
    }else if(seatNumber == 4){
        if(count4 < 1){
            count4++;
            sleepThreadBySeat(seatNumber);
        }else{
            addQueue(seatNumber);
        }
    }
  return NULL;
}

int main(void)
{
    pthread_t tid;
    int i= 0;
    while(i<120){
      //  printf("adawd");
        int num = seat[(rand()%3)];
        pthread_create(&tid, NULL, bakery,&num);
         sleep(10);
        i=i+10;
    }
    return 0;
}