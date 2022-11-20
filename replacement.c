#include<stdio.h>
#include<stdlib.h>

int pageHit(int* b,int a,int size){
    for(int i=0 ;i<size;i++){
        if( b[i]==a )
            return 1;
    }
    return 0;
}

void display(int* b,int size){
    for(int i=0 ; i<=size; i++){
        printf(" %d",b[i]);
    }
}

int leastRecent(int* a,int recent,int* b,int frames){
    int min = 0, lr = 0;
    for(int i=0; i<frames; i++){
        int count = 0;
        for(int j=recent-1; j>=0; j--){
            if( b[i]==a[j] ){
                if(count > min){
                    min = count;
                    lr = i;
                }
                break;
            }
            count++;
        }
    }
    return lr;
}

void fifo(int* a,int pages,int* b,int frames){
    int pagehit=0,pagemiss=0;
    int i = 0;
    int front = 0;
    while( i!=pages ){
        printf("\nFor %d :",a[i]);
        if(pageHit(b,a[i],frames)){
            printf(" no page fault ");
            pagehit++;
        }
        else{
            b[front] = a[i];
            pagemiss++;
            if( i<3 )
            display(b,front);
            else
            display(b,frames-1);
            front = (front+1)%frames;
        }
        i++;
    }
    printf("\n\nPage Hit Ratio = %d/%d",pagehit,pages);
}

void lru(int* a,int pages,int* b,int frames){
    int pagehit=0,pagemiss=0;
    int i = 0;
    int front = 0;
    while( i!=pages ){
        printf("\nFor %d :",a[i]);
        if(pageHit(b,a[i],frames)){
            printf(" no page fault ");
            pagehit++;
        }
        else{
            pagemiss++;
            if(front <= frames-1){
                b[front] = a[i];
                front++;
                display(b,front-1);
            }
            else{
                int k = leastRecent(a,i,b,frames);
                b[k] = a[i];
                display(b,front-1);  
            }
        }
        i++;
    }
    printf("\n\nPage Hit Ratio = %d/%d",pagehit,pages);
}

int main(){
    int n;
    printf("\nEnter the number of pages in page trace: ");
    scanf("%d",&n);
    int* a;
    a = (int*)malloc(n*sizeof(int));
    printf("\nEnter the page trace in the sequence: ");
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    int frames;
    printf("\nEnter the no of frames: ");
    scanf("%d",&frames);
    int* b;
    b = (int*)malloc(n*sizeof(int));
    printf("\nPress for 1.FIFO and 2.LRU");
    int num;
    scanf("%d",&num);
    switch(num){
        case 1:{
            printf("\nBy FIFO method\n");
            fifo(a,n,b,frames);
            break;
        }
        case 2:{
            printf("\nBy FIFO method\n");
            lru(a,n,b,frames);
            break;
        }
    }
}