//Yingxuan Chen  25755068
//Haochen Zhou 23567813
#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int read_file(char *file,int num_a[]){
    FILE *fp;
    char str[256];
    char *token;
    int i=0;
    int count=0;
    
    fp=fopen(file,"r");
    while(fgets(str,256,fp)!='\0'){
	char *rest=str;
	token=strtok(rest," ");
	while(token!=NULL){
   	    if((*token>='0'&&*token<='9')||*token=='-'||*token=='+'){
		if(*token=='-'){
		    token++;
		    num_a[count]=-atoi(token);
		    count++;
		}
		else if(*token=='+'){
		    token++;
		    num_a[count]=atoi(token);
		    count++;
		}
	        else{
		    num_a[count]=atoi(token);
		    count++;
		}
	    }
	i++;
	token=strtok(NULL," ");
    }}	
fclose(fp);
return count;
}


int merge(int array[],int b, int e,int key,int fd[]){
    int mid=(b+e)/2;

    pid_t pid1,pid2;

    if(b==e){
        if(key==array[b]){
            close(fd[0]);
	    write(fd[1],&b,sizeof(b));
        }
        printf("pid %d, ",getpid());
        printf("value: %d\n",array[b]);
	exit(0);
    }
    else{
        pid1=fork();
        if(pid1==0)
	{
            merge(array, b, mid, key,fd);
	    wait(NULL);
	    exit(0);
        }
        else
	{
	    wait(NULL);
	    pid2=fork();
	    if(pid2==0){
                merge(array, mid + 1, e, key,fd);
		wait(NULL);
	        exit(0);
	    }
        }
    }
}


int main(int argc, char *argv[]){

    int num_a[10];
    int fd[2];	
    int byt;
    int Read;
    int index;
    int key=atoi(argv[2]);


    int count = read_file(argv[1],num_a);


    if(count==1){
        if(key==num_a[0])
            printf("Search output: %d\n",0);

        else
            printf("Search output: %d\n",-1);
    }
else{
    pipe(fd);
    merge(num_a,0,count-1,key,fd);
    wait(NULL);
    close(fd[1]);


    byt=read(fd[0],&index,sizeof(index));

    if(byt>0){
	printf("Search output: %d\n", index);
    }
    else{
	printf("Search output: %d\n",-1);
    }
    close(fd[0]);
}
return 0;
}








