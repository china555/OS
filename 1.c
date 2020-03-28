#include <stdio.h>
int queue[100];
int count =0;
void get1Queue(int number){
    for(int i=0;i<count;i++){
        if(queue[i]==number){
          // printf("%d %d ",queue[i],i);
            for(int j=i;j<100;j++){
                queue[j] = queue[j+1];
            }
            count--; 
        }
    }
}

int main(){
    for(int i=0;i<50;i++){
        queue[i] =i+1;
        printf("%d ",queue[i]);
        count++;
    }
     printf("\n");

    get1Queue(20);
        for(int i=0;i<100;i++){
        printf("%d ",queue[i]);
    }
    return 0;
}