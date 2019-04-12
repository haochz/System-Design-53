//Yingxuan Chen  25755068
//Haochen Zhou 23567813

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
int allocation(char* heap, int bytes, int count){
    int check=0;
    int free_size=0;
    char *end=heap+127;
    while(heap<end){
        free_size=((unsigned char)(*(heap+1)) >> 1)+1;

        if(!(*(heap+1)&1) && (bytes+2<=free_size)){
            check=1;
            int new_size = bytes+2;
            *heap=count+1; // update block num
            if(free_size-new_size>2){   //split
                *(heap+1)=((bytes+1)<<1)|1; //first size
                *(heap+1+new_size)=(free_size-new_size-1)<<1;  //second size
            }
            else if (free_size-new_size==0) {    //don't split
                *(heap+1)=(bytes+1)<<1|1;
            }
            else{
                *(heap+1)=((free_size-1)<<1)|1; //size
            }
            break;
        }
        else{
            heap+=free_size;
        }}
    return check;
}

int free_block(char*heap,int b_num){
    int free_size=0;
    char *end=heap+127;
    while(heap<end){
        free_size=((unsigned char)(*(heap + 1)) >> 1) + 1;
        if((b_num==*heap) && (*(heap + 1) & 1)){
            *heap=0;
            *(heap+1)&=-2;
            break;
        }
        else{
            heap+=free_size;
        }
    }
    return b_num;
}

void block_list(char*heap){
    printf("Size  Allocated   Start      End\n");
    int free_size=0;
    int index = 0;
    int start_i=0;
    int end_i=0;
    char* end=heap+126;
    while(heap<end){

        free_size=((unsigned char)(*(heap + 1)) >> 1)+1;

        end_i+=free_size;
        if(end_i>=127){
            printf("%-6d",free_size-1);
        } else{
            printf("%-6d",free_size);
        }

        if((*(heap + 1) & 1))
            printf("   yes       ");
        else
            printf("   no        ");

        printf("%-10d",start_i);
        start_i+=free_size-1;
        if(start_i==127){
            printf("%d\n",start_i-1);
        } else{
            printf("%d\n",start_i);
            start_i+=1;
        }

        heap+=free_size;
    }
}

void write_heap(char*heap, char c, int times, int b_num){
    int free_size=0;
    char* end=heap+126;
    while(heap<end){
        free_size=((unsigned char)(*(heap + 1) & -2) >> 1) + 1;
        if(b_num==*heap){
            if(times<=free_size-2){
                int a;
                for(a=0;a<times;a++){
                    *(heap+2+a)=c;
                }
            }
            else{
                printf("ERROR: Write too big\n");
            }
            break;
        }
        else{
            heap+=free_size;
        }
    }
}

void print_heap(char*heap,int bytes,int b_num){
    int free_size=0;
    char* end=heap+126;
    while(heap<end){
        free_size=((unsigned char)(*(heap + 1) & -2) >> 1) + 1;
        if(b_num == *heap){

            if(bytes<=free_size-2){
                int a;
                for(a=0;a<bytes;a++){
                    printf("%c",*(heap+2+a));
                }
                printf("\n");
            }
            else{
                int a;
                for(a=0;a<free_size-2;a++){
                    printf("%c",*(heap+2+a));
                }
                printf("\n");
            }
            break;
        }
        else{
            heap+=free_size;
        }
    }
}

void print_header(char*heap,uint8_t b_num){
    uint8_t  *ptr=heap;
    int free_size=0;
    char* end=heap+127;
    while(heap<end){
        free_size=((unsigned char)(*(heap + 1) & -2) >> 1) + 1;
        if(b_num == *heap){
            printf("%02x%02x\n",ptr[0], ptr[1]+2);
            break;
        }
        else{
            heap+=free_size;
            ptr+= free_size;
        }
    }
}

int main() {

    char input[20];
    int count = 0;
    char *heap = (char*) malloc(126* sizeof(char));

    int i;
    for(i=0;i<127;i++){
        heap[i]=0;
    }
    *heap=0;
    *(heap+1) = -2;

    while(1){
        int bytes;
        int block_num;
        char write;
        int copy_time;

        printf("> ");
        scanf("%s",input);

        if(!strcmp(input,"allocate")){
            scanf("%d",&bytes);
            if(bytes>125||bytes<=0){
                printf("ERROR: cannot allocate such number of bytes!\n");
            }
            else{
                int s = allocation(heap,bytes,count);
                if(s==1) {
                    count++;
                    printf("%d\n", count); //output block numbers
                }
            }
        }

        else if(!strcmp(input,"free")){
            scanf("%d",&block_num);
            free_block(heap,block_num);
        }

        else if(!strcmp(input,"blocklist")){
            block_list(heap);
        }

        else if(!strcmp(input,"writeheap")){
            scanf("%d %c %d",&block_num,&write,&copy_time);


            write_heap(heap,write, copy_time,block_num);

        }

        else if(!strcmp(input,"printheap")){
            scanf("%d %d",&block_num,&bytes);

            print_heap(heap,bytes,block_num);
        }

        else if(!strcmp(input,"printheader")){
            scanf("%d",&block_num);

            print_header(heap,block_num);
        }

        else if(!strcmp(input,"quit")){
            break;
        }
        else{
            printf("invalid command\n");
        }
    }

    return 0;
}
