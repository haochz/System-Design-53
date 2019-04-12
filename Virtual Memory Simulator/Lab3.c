//Yingxuan Chen  25755068
//Haochen Zhou 23567813
#include <stdio.h>
#include <string.h>
struct PageEntry{
    int Valid;
    int Dirty;
    int PageNum;
};
int order[4] = {0,1,2,3};
void putBottom(int num) {
    int index;
    int a;
    for(a=0;a<4;a++){
        if(order[a] == num){
            index=a;
            break;
        }
    }
    int temp[4];
    int b;
    for(b = 0; b<4; b++){
        if(b<index){
            temp[b] = order[b];
        }
        if(b>index){
            temp[b-1] = order[b];
        }
        else{
            temp[3] = num;
        }
    }
    int c;
    for(c = 0; c<4;c++){
        order[c] = temp[c];
    }
}
int findEmptyPN(struct PageEntry table[]){
    int i;
    for(i = 0; i<4; i++){
	int j;
        for(j =0; j<8;j++){
            if(i == table[j].PageNum && table[j].Valid==1){
                break;
            }
            if(j == 7 && table[j].Valid ==0){
                return i;
            }
        }
    }
    return -1;
}
void main(){
    char input[20];
    char read[20] = "read";
    char write[20] = "write";
    char showmain[20] = "showmain";
    char showdisk[20] = "showdisk";
    char showptable[20] = "showptable";
    char quit[20] = "quit";
    int diskmem[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int mainmem[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
    struct PageEntry table[8];
    int i;
    for(i = 0; i< 8;i++){
        table[i].Dirty =0;
        table[i].Valid = 0;
        table[i].PageNum = i;
    }
    int counter = 0;
    while(1){
        int value;
        int data;
        printf("$ ");
        scanf("%s",input);
       if(!strcmp(input,read)){
            scanf("%d",&value);
            int vaddr = value/2;
            if(table[vaddr].Valid == 1){
                putBottom(table[vaddr].PageNum);
                data = mainmem[table[vaddr].PageNum*2+value%2];
            }
            else{
                int PN = findEmptyPN(table);
                if(PN != -1){
                    table[vaddr].PageNum = PN;
                    mainmem[PN*2+value%2] = diskmem[value];
                    putBottom(PN);
                }
                else{
		    int i;
                    for(i =0; i<8;i++){
                        if(order[0] == table[i].PageNum && table[i].Valid==1){
                            if(table[i].Dirty == 1){
                                //copy to disk mem===================================
                                diskmem[i*2] = mainmem[order[0]*2];
                                diskmem[i*2+1] = mainmem[order[0]*2+1];
                            }
                            table[i].Valid = 0;
                            table[i].PageNum = i;
                            table[i].Dirty = 0;
                            break;
                        }
                    }
                    mainmem[order[0]*2] = diskmem[value-value%2];
                    mainmem[order[0]*2+1] = diskmem[value-value%2+1];
                    table[vaddr].PageNum = order[0];
                    putBottom(order[0]);
                }
                table[vaddr].Valid=1;
                data = mainmem[table[vaddr].PageNum*2+value%2];
            }
            printf("Address %d has value: %d \n",value,data);
        }
        else if(!strcmp(input,write)){
            int change;
            scanf("%d%d", &value,&change);
            int vaddr = value/2;
            if(table[vaddr].Valid == 1){
                mainmem[table[vaddr].PageNum*2+value%2] = change;
                table[vaddr].Dirty =1;
                putBottom(table[vaddr].PageNum);
            }
            else{
                int PN = findEmptyPN(table);
                if(PN != -1){
                    table[vaddr].PageNum = PN;
                    putBottom(PN);
                    mainmem[table[vaddr].PageNum*2+value%2] = change;
                }
                else{
		    int i;
                    for(i =0; i<8;i++){
                        if(order[0] == table[i].PageNum && table[i].Valid==1){
                            if(table[i].Dirty == 1){
                                diskmem[i*2] = mainmem[table[i].PageNum*2];
                                diskmem[i*2+1] = mainmem[table[i].PageNum*2+1];
                            }
                            table[i].Valid = 0;
                            table[i].PageNum = i;
                            table[i].Dirty = 0;
                            break;
                        }
                    }
                    mainmem[order[0]*2] = diskmem[value-value%2];
                    mainmem[order[0]*2+1] = diskmem[value-value%2+1];
                    mainmem[order[0]*2+value%2] = change;
                    table[vaddr].PageNum = order[0];
                    putBottom(order[0]);
                }
                table[vaddr].Valid=1;
                table[vaddr].Dirty =1;
            }

        }
       
        else if(!strcmp(input,showdisk)){
            scanf("%d", &value);
            printf("Address   Contents \n");
            printf("%d         %d\n",value*2,diskmem[value*2]);
            printf("%d         %d\n",value*2+1,diskmem[value*2+1]);
        }
    
        else if(!strcmp(input,showmain)){
            scanf("%d", &value);
            printf("Address   Contents \n");
            printf("%d         %d\n",value*2,mainmem[value*2]);
            printf("%d         %d\n",value*2+1,mainmem[value*2+1]);
        }
   
        else if(!strcmp(input,showptable)){
            printf("VPageNum   Valid     Dirty     PN    \n");
	    int i;
            for(i = 0; i< 8; i++){
                printf("%d          %d         %d         %d \n",i,table[i].Valid,table[i].Dirty,table[i].PageNum);
            }
        }
        else if(!strcmp(input,quit)){
            break;
        }
        else{
            printf("INVALID COMMAND!\n");
        }
    }
}
