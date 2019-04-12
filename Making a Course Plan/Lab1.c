//Haochen Zhou 23567813
#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h>


int index_class=0;

struct class_offer{
    char name[21];
    int quart;
    int num_offer;};

struct class_prere{
    char name[21];
    char prere[6][21];
    int num_of_p;};

struct class_info{
    char name[21];
    char prere[6][21];
    int p_num;
    char back[6][21];
    int b_num;
    int year;
    int qua;
};


void read_offer(char *offer_file, struct class_offer c[21]){
    FILE *fp;
    char str[256];
    char *token;
    int i=0;
    char *search=" ";
    char tmp[2];

    fp=fopen(offer_file,"r");
    while(fgets(str,256,fp)!='\0'){
    char *rest=str;
    token=strtok(str,search);
    strcpy(c[i].name,token);
    token=strtok(NULL,search);
    strcpy(tmp,token);
    c[i].quart = atoi(tmp);  //quarter
     i++;
    }
    int n=0;
    for(n;n<i;++n){
	c[n].num_offer=i;
	}
}

int read_prere(char *prere_file, struct class_prere b[21]){ 
    FILE *fp;
    char str[256];
    char *token;
    int i=0;
    int k=0; //loop for check req(bool)
    
    fp=fopen(prere_file,"r");
    while(fgets(str,256,fp)!='\0'){
    char *rest=str;
	int j=0;
	while(token=strtok_r(rest," ",&rest)){	
		if(j==0){		
			strcpy(b[i].name,token);
			j++;
		}
		else{
			strtok(token,"\n");
			strcpy(b[i].prere[j],token);
		j++;}
	}
	b[i].num_of_p=j-1; 
	i++;
    }
    fclose(fp);
    return i;} 

int read_require(char *require_file,char a[21][21]){
    FILE *fp;
    char str[256];
    char *token;
    int i=0;
  //  int k=0;
   
    fp=fopen(require_file,"r");
    while(fgets(str,256,fp)!='\0'){
    char *rest=str;
        while(token=strtok_r(rest," ",&rest)){
		strtok(token,"\n");
		strcpy(a[i],token);
		i++;}}
   fclose(fp);
   return i;
}

int main(int argc, char *argv[]){
    char require_a[21][21];
    struct class_prere prere_s[21];
    struct class_offer offer_s[21];
    struct class_info info_s[21];
    int num_of_require;
    int num_of_prere;


    read_offer(argv[1],offer_s);
    num_of_prere = read_prere(argv[2],prere_s);
    num_of_require = read_require(argv[3],require_a);

    char allclass[21][21];
    int n_allclass=0;
    int a; //loop name of prere 
    for(a=0;a<num_of_prere;a++){  //7	
	if(n_allclass==0){
	    strcpy(info_s[index_class].name,prere_s[a].name);
	    strcpy(allclass[0],info_s[index_class].name);
	    n_allclass++;
	    }
	else{
	    strcpy(info_s[index_class].name,prere_s[a].name);
	    strcpy(allclass[index_class],info_s[index_class].name);	
	    n_allclass++;}    	   

	int b;
	for(b=0;b<prere_s[a].num_of_p;b++){ 	
            strcpy(info_s[index_class].prere[b],prere_s[a].prere[b+1]);
            info_s[index_class].p_num=prere_s[a].num_of_p;
	    info_s[index_class].b_num=0;
	    info_s[index_class].year=0;
	}
	index_class++;
}

    int c;
    for(c=0;c<num_of_prere;c++){
        int d;
	for(d=0;d<prere_s[c].num_of_p;d++){
	    int y=0;
	    for(y;y<21;y++){
		if(strcmp(prere_s[c].prere[d+1],info_s[y].name)==0){
			int n=info_s[y].b_num;
			strcpy(info_s[y].back[n],prere_s[c].name);
			info_s[y].b_num+=1;
			break;}
		if(y==20){
			strcpy(info_s[index_class].name,prere_s[c].prere[d+1]);
			info_s[index_class].p_num=0;
			strcpy(info_s[index_class].back[0],prere_s[c].name);
	  		info_s[index_class].b_num=1;
			info_s[index_class].year=0;
			index_class++;
		}	
    }
}}

    int h;
    for(h=0;h<index_class;h++){
	if(info_s[h].p_num==0)
	    info_s[h].year=1;
    }

    int e=0;
    for(e;e<index_class;e++){
    int f=0;
    for(f;f<offer_s[1].num_offer;f++){
	if(strcmp(info_s[e].name,offer_s[f].name)==0)
	    info_s[e].qua=offer_s[f].quart;}
    }

bool ft=true;
    while(ft){
	int p;
	for(p=0;p<index_class;p++){  
	    if(info_s[p].p_num!=0){
		int min=-1;
		float max=0;
		int yy=0;
		int i;
		for(i=0;i<info_s[p].p_num;i++){  
		   int j;
		   for(j=0;j<index_class;j++){
			if(strcmp(info_s[p].prere[i],info_s[j].name)==0){
			     if(info_s[j].year==0)
				{min=0;}
			     else{
				float py=info_s[j].year +info_s[j].qua*0.1;
				if(max<py)
				    max=py;
			      }
			    if(min!=0){
			        float hy= info_s[p].year+info_s[p].qua*0.1;
				 yy=info_s[p].year;
			   	 while(hy<=max){ 
				    hy=hy+1;
				    yy=yy+1;
				    info_s[p].year=yy;
				 }
			    }
			}
		    }
		}
	}}

    int lu;
    int yue=0;
    for(lu=0;lu<index_class;lu++){

        if(info_s[lu].year!=0){
	    yue++;}
    }
    if(yue==index_class) ft=false;
    }


int l;
for(l=0;l<num_of_require;l++){
    int u;
    for(u=0;u<21;u++){
	if(strcmp(require_a[l],info_s[u].name)==0)	
		break;
	if(u==19){
	strcpy(info_s[index_class].name,require_a[l]);
	info_s[index_class].p_num=0;
	info_s[index_class].b_num=0;
	info_s[index_class].year=1;
		
	int t;
	for(t=0;t<offer_s[t].num_offer;t++){
	    if(strcmp(info_s[index_class].name,offer_s[t].name)==0)
		info_s[index_class].qua=offer_s[t].quart;
		
	}
	index_class++;
	}		
		
}}

struct plan{
    int year;
    int qua;
    char name[21][21];
    int c;
};

struct plan p[21];

int count=0;

    int ye=1;
    for(ye;ye<11;ye++){
	int qu=1;
	for(qu;qu<4;qu++){
	    int be=0;
	    int s=0;
	    for(be;be<index_class;be++){
		if(info_s[be].year==ye && info_s[be].qua==qu){ 
		    p[count].year=info_s[be].year;
		    p[count].qua=info_s[be].qua;
		    strcpy(p[count].name[s],info_s[be].name);
		    s++;
		    p[count].c=s;
	   	}
	    }
count++;
	}
    }

int tt;
for(tt=0;tt<20;tt++){
  if(p[tt].year!=0 && p[tt].qua!=0){
    printf("%d ",p[tt].year);
    printf("%d ",p[tt].qua);
    int rr;
    for(rr=0;rr<p[tt].c;rr++)
    {
      printf("%s ",p[tt].name[rr]);
    }
    printf("\n");
}}

return 0;}









