#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <complex.h>
#include <stdbool.h>
#include <math.h>


typedef struct Element{
struct Element *next;
struct Element *prev;
char name[8],n1[8],n2[8],n3[8],n4[8],vname[8],value[8];
double val;
int b;
} Element;

typedef struct List {
Element *head ;
Element *tail ;
int count;
}List ;

typedef struct Node{
 char name[8];
 complex g[100];
 }Node;
 Node node[100];


void add(List *list,Element *node ) {
list->tail->next=node;
node->prev = list->tail ;
list->tail = node ;
node->next=NULL;
list->count += 1 ;
}

void freeup(Element* e,List* list){
	while(1){
		e=e->next;
		free(e->prev);
		if(e->next==NULL){
			free(e);
			break;
			}
	}
	free(list);
}

FILE* checkargs(int argc, char **argv){
	if(argc != 4){								/* Program expects a filename.check that argument was passed */
	printf("Usage ./a.out <filename>");
	exit(1); 
	}                                                               /* Open file while checking for existence */
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL){
	printf("File could not be opened");
	exit(2);
}
return fp;
}

int row(char rowname[8],int count){
	int q;
	for(q=0;q<count;q++){
		if((strcmp(rowname,node[q].name))==0)
			return q;
	}return -1;
}
bool ifvs(int i,int v,int vs[200]){
	int q;
	for(q=0;q<v;q++){
		if(i==vs[q])
			return true;
	}return false;
}

void print(complex m[200][200],int count,bool aci)
{
	int x,y;
	//printf("MATRIX IN UPPER TRIANGULAR FORM (some elements in the lower half maynot be exactly zero but have a small value and can be neglected\n\n");
	if(aci){
		for(x=0;x<count;x++){
		for(y=0;y<count+1;y++){
		printf("%.2e+ %.2ei   ",creal(m[x][y]),cimag(m[x][y]));
		}printf("\n");
		}printf("\n");
		}
	else
	{
		for(x=0;x<count;x++){
		for(y=0;y<count+1;y++){
		printf("%.2e  ",creal(m[x][y]));
		}printf("\n");
		}printf("\n");
		}
		
}
int max(int n, complex m[200][200],int count){
	int i;
	for(i=n;i<count;i++)
		{
		if(m[i][n]!=0)
			return i;
		}
		return -1;
}
void solve(complex m[200][200],int count,bool aci,char* n1,char* n2,float w,FILE *fo,complex vs)
{
	if((w!=(float)50*(float)2*(float)3.14)||(!aci))
	{
	int x,y,r=1,i;
	//print(m,count,aci);
	for(r=1;r<count;r++)
	{int s =max(r-1,m,count);
		if(s!=-1)
		for(i=0;i<200;i++){
			complex temp= m[r-1][i];
			m[r-1][i]=m[s][i];
			m[s][i]=temp;
			char tem[5];
			strcpy(tem,node[r-1].name);
			strcpy(node[r-1].name,node[s].name);
			strcpy(node[s].name,tem);
			}
		else
			continue;

	for(x=r;x<count;x++){
		for(y=count+1;y>=0;y--){
		m[x][y]-=(m[r-1][y]*(m[x][r-1]/m[r-1][r-1]));
		//print(m,count);
		}
		}//print(m,count,aci);
		}
	complex c[count+1];
	c[count]=1;
	for(i=0;i<count;i++)
		c[i]=0;
	for(x=count-1;x>=0;x--){
	for(i=1;i<=count-x;i++){
	c[x]-=m[x][x+i]*c[x+i];}
	c[x]/=m[x][x];
	}//print(m,count,aci);
	/*for(i=0;i<count;i++)
		printf("%s\n",node[i].name);*/
	if(aci){
		for(i=0;i<count;i++)
			printf("%s = %.2e+ %.2ei  \n",node[i].name,creal(c[i]),cimag(c[i]));
		    complex vn1 = c[row(n1,count)];
		    complex vn2 = c[row(n2,count)];
			//printf("\nv at %s = %.2e+ %.2ei  ",n1,creal(vn1),cimag(vn1));
			//printf("\nv at %s = %.2e+ %.2ei  ",n2,creal(vn2),cimag(vn2));
			fprintf(fo, "%f\t", log10(w) );
			//printf("vs = %.2e+ %.2ei  ",creal(vs),cimag(vs));
			fprintf(fo, "%f \t %f \n",log10(cabs((vn1-vn2))),carg((vn1-vn2)));
		}
	else
	{
		for(i=0;i<count;i++)
		printf("%s = %.2e\n",node[i].name,creal(c[i]));
		for(i=0;i<count;i++)
		fprintf(fo,"%.2e\t",creal(c[i]));
		fprintf(fo, "\n");
	}
	printf("\n--------------------------------------------------------------------------------");
	printf("\n\n");
	//return m;
	}
}

int main(int argc, char **argv)
{
	int vn=-1;
	int y=0;
	bool esc=true,eg=false;
	bool is = false,com =false;
	char n1[8];
	char n2[8];
	strcpy(n1,argv[2]);
	strcpy(n2,argv[3]);
	char ac[5],vname[5],p1[5],p2[5],p10[20],p20[20];
	float vmin,vmax,wstep,step,vstep;
	int i,j,s=0,p=0,x=0,n,count=0,v=0;
	float w= (float)50*(float)2*(float)3.14;
	int vs[200];
	double c[500];
	List *list = (List*)malloc (sizeof(List));
	char buf[60];
	complex m[200][200],d[200][200];
	int vv=0;
	int no=0;
	bool aci=true;
	 FILE *fo = fopen("spice.out", "w");
	while(esc){
		no++;
		FILE* fp = checkargs(argc,argv);
	list->count=0;
	if(w!=(float)50*(float)2*(float)3.14)
	printf("w = %f\n",w);
	Node sam[100];
	int ghj;
	while(fgets(buf, 60, fp)){
		eg=false;
	if(is&&!com){
		if(buf[0]=='.')
		{
			if(buf[1]=='c'&&buf[2]=='o'&&buf[3]=='m'&&buf[4]=='m'&&buf[5]=='a'&&buf[6]=='n'&&buf[7]=='d'){
			com=true;
			continue;
			}
			else if(buf[1]=='e'&&buf[2]=='n'&&buf[3]=='d')
			{
				break;
			}
		}
		else continue;
		}
	if(com){
			int z=sscanf(buf,"%s %s %s %s %f",ac,vname,p10,p20,&vstep);
			//printf("sscanf = %d\n",z );
			int z1 = sscanf(p10,"%f%s",&vmin,p1);
			int z2 = sscanf(p20,"%f%s",&vmax,p1);
			//printf("%s %s %f %s %f %s %d\n",ac,vname,vmin,p1,vmax,p2,vstep);
			
			switch(p1[0]){
					case 'n':
						vmin*=0.000000001;
						break;
					case 'u':
						vmin*=0.000001;
						break;
					case 'm':
						if(p1[1]=='e'&&p1[2]=='g'&&p1[3]=='\0')
							p*=1000000;
						else
						vmin*=0.001;
						break;
					case 'k':
						vmin*=1000;
						break;
					case 'p':
						vmin*=0.000000000001;
						break;
					}
			switch(p2[0]){
					case 'n':
						vmax*=0.000000001;
						break;
					case 'u':
						vmax*=0.000001;
						break;
					case 'm':
						if(p2[1]=='e'&&p2[2]=='g'&&p2[3]=='\0')
							p*=1000000;
						else
						vmax*=0.001;
						break;
					case 'k':
						vmax*=1000;
						break;
					case 'p':
						vmax*=0.000000000001;
						break;
					}
					//printf("vmin = %f\n",vmin );
					//printf("vmax = %f\n",vmax );
					if(strcmp(ac,"dc")==0)
				aci=false;
			else
				{
					step = (log10(vmax)-log10(vmin))*vstep+2;
					//printf("step = %f\n",step );
					wstep=(log10(vmax)-log10(vmin))/(float)(step-2);
					//printf("wstep = %f\n",wstep );
				}
			com=false;
			continue;
		}
	if(buf[0]=='*')
		continue;
	if(buf[0]=='.')
		{
		if(buf[1]=='e'&&buf[2]=='n'&&buf[3]=='d'){
		is = true;
		continue;
		}
		else
		continue;
		}

	Element *e1= (Element*)malloc(sizeof(Element));
	p=0;s=0;
	for(i=0;i<60;i++){
		if(buf[i]==32||buf[i]=='\0'||buf[i]=='\n')
		{
			s=i;
			char cc[14]="";
			for(j=0;j<s-p;j++)
			{
				if(buf[p+j]>40&&buf[p+j]<123)
				cc[j]=buf[p+j];
			}
		
		if((s-p)>0){
		//printf("%s",cc);
				switch(x){
				case 0:
					strcpy(e1->name,cc);
					if(e1->name[0]=='e'||e1->name[0]=='E'||e1->name[0]=='G'||e1->name[0]=='g') 
						eg=true;
					break;
				case 1:
					strcpy(e1->n1,cc); 
					break;
				case 2:
					strcpy(e1->n2,cc); 
					break;
				case 3:
					strcpy(e1->value,cc);
					break;
				case 4:
					strcpy(e1->vname,e1->value); 
					strcpy(e1->value,cc); 
					break;
				case 5:
					strcpy(e1->n3,e1->vname);
					strcpy(e1->n4,e1->value);
					strcpy(e1->value,cc);
					break;
				}
		x++;
		}	
		p=s+1;
		}if(buf[i]=='\n'||buf[i]==0) break;
	}
	for(i=0;i<60;i++) buf[i]=0;
	if(x>0){
			if(list->count==0){
				char s[5];
				long double p;
				int z=sscanf(e1->value,"%Lf%s",&p,s);
				switch(s[0]){
					case 'n':
						p*=0.000000001;
						break;
					case 'u':
						p*=0.000001;
						break;
					case 'm':
						if(s[1]=='e'&&s[2]=='g'&&s[3]=='\0')
							p*=1000000;
						else
						p*=0.001;
						break;
					case 'k':
						p*=1000;
						break;
					case 'p':
						p*=0.000000000001;
						break;
					}
				e1->val=p;
				e1->prev=NULL;
				list->head=e1;
				list->tail=e1;
				list->count++;
				int r1=0;
				int r2=1;
				int r3=2;
				int r4=3;
				if((strcmp(e1->n1,"GND")==0)||(strcmp(e1->n1,"gnd")==0))
				r1=-1;
				else{
				strcpy(node[0].name,e1->n1);count++;
				}
				if((strcmp(e1->n2,"GND")==0)||(strcmp(e1->n2,"gnd")==0))
				r2=-1;
				else{
				strcpy(node[1].name,e1->n2);count++;
				}
				if(eg){
				if((strcmp(e1->n3,"GND")==0)||(strcmp(e1->n3,"gnd")==0))
				r3=-1;
				else{
				strcpy(node[2].name,e1->n3);count++;
				}
				if((strcmp(e1->n4,"GND")==0)||(strcmp(e1->n4,"gnd")==0))
				r4=-1;
				else{
				strcpy(node[3].name,e1->n4);count++;
				}
				}
				switch(e1->name[0]){
				case 'R':
				case 'r':
				if(r1!=-1)
				node[r1].g[r1]+=((double)1/e1->val);
				if((r1!=-1)&&(r2!=-1))
				node[r1].g[r2]-=((double)1/e1->val);
				if(r2!=-1)
				node[r2].g[r2]+=((double)1/e1->val);
				if((r1!=-1)&&(r2!=-1))
				node[r2].g[r1]-=((double)1/e1->val);
				break;
				case 'L':
				case 'l':
				if(r1!=-1)
				node[r1].g[r1]+=((double)1/(e1->val*w))*(-I);
				if((r1!=-1)&&(r2!=-1))
				node[r1].g[r2]-=((double)1/(e1->val*w))*(-I);
				if(r2!=-1)
				node[r2].g[r2]+=((double)1/(e1->val*w))*(-I);
				if((r1!=-1)&&(r2!=-1))
				node[r2].g[r1]-=((double)1/(e1->val*w))*(-I);
				break;
				case 'C':
				case 'c':
				if(r1!=-1)
				node[r1].g[r1]+=w*(e1->val)*I;
				if((r1!=-1)&&(r2!=-1))
				node[r1].g[r2]-=w*(e1->val)*I;
				if(r2!=-1)
				node[r2].g[r2]+=w*(e1->val)*I;
				if((r1!=-1)&&(r2!=-1))
				node[r2].g[r1]-=w*(e1->val)*I;
				break;
				case 'I':
				case 'i':
				if(r1!=-1)
				c[r1]+=e1->val;
				if(r2!=-1)
				c[r2]-=e1->val;
				break;
				case'V':
				case 'v':
					if(strcmp(e1->name,vname)==0){
						vn = count;
					}
					strcpy(node[count].name,e1->name);
					if(r1!=-1)
					node[count].g[r1]=1;
					if(r2!=-1)
					node[count].g[r2]=-1;
					if(r1!=-1){
					//b[r1]=1;
					node[r1].g[count]=1;
					}
					if(r2!=-1){
					//b[r2]=-1;
					node[r2].g[count]=-1;
					}
					c[count]+=e1->val;
					vs[v]=count;
					count++;
					v++;
					break;
				case 'E':
				case 'e':
					if(strcmp(e1->name,vname)==0){
						vn = count;
					}
					strcpy(node[count].name,e1->name);
					if(r1!=-1)
					node[count].g[r1]=1;
					if(r2!=-1)
					node[count].g[r2]=-1;
					if(r3!=-1)
					node[count].g[r3]=-e1->val;
					if(r4!=-1)
					node[count].g[r4]=+e1->val;
					if(r1!=-1){
					node[r1].g[count]=1;
					}
					if(r2!=-1){
					node[r2].g[count]=-1;
					}
					vs[v]=count;
					count++;
					v++;
					break;
				case 'H':
				case 'h':
				if(strcmp(e1->name,vname)==0){
						vn = count;
					}
					strcpy(node[count].name,e1->name);
					if(r1!=-1)
					node[count].g[r1]=1;
					if(r2!=-1)
					node[count].g[r2]=-1;
					if(r1!=-1){
					node[r1].g[count]=1;
					}
					if(r2!=-1){
					node[r2].g[count]=-1;
					}
					node[count].g[row(e1->vname,count)]=-e1->val;
					vs[v]=count;
					count++;
					v++;
					break;
				case 'F':
				case 'f':
					if(r1!=-1)
					node[r1].g[row(e1->vname,count)]=e1->val;
					if(r2!=-1)
					node[r2].g[row(e1->vname,count)]=-e1->val;
					break;
				case 'G':
				case 'g':
					if((r1!=-1)&&(r3!=-1))
						node[r1].g[r3]+=e1->val;
					if((r2!=-1)&&(r4!=-1))
						node[r2].g[r4]-=e1->val;
					break;
				}
				n=1;
			}else{
				char s[5];
				long double p;
				int z=sscanf(e1->value,"%Lf%s",&p,s);
				//printf("%d     %f  %s",z,p,s);
				switch(s[0]){
					case 'n':
						p*=0.000000001;
						break;
					case 'u':
						p*=0.000001;
						break;
					case 'm':
						if(s[1]=='e'&&s[2]=='g'&&s[3]=='\0')
							p*=1000000;
						else
						p*=0.001;
						break;
					case 'k':
						p*=1000;
						break;
					case 'p':
						p*=0.000000000001;
						break;
					}
				e1->val=p;
				e1->prev=NULL;
				e1->next=NULL;
				int r1,r2,r3,r4;
				
				if((row(e1->n1,count)==-1)&&(strcmp(e1->n1,"GND")!=0)&&(strcmp(e1->n1,"gnd")!=0)){
					strcpy(node[count].name,e1->n1);
					r1=count;
					count++;
					}
				else
					r1=row(e1->n1,count);
				if((row(e1->n2,count)==-1)&&(strcmp(e1->n2,"GND")!=0)&&(strcmp(e1->n2,"gnd")!=0)){
					strcpy(node[count].name,e1->n2);
					r2=count;
					count++;
					}
				else
					r2=row(e1->n2,count);
				if(eg){
				if((row(e1->n3,count)==-1)&&(strcmp(e1->n3,"GND")!=0)&&(strcmp(e1->n3,"gnd")!=0)){
					strcpy(node[count].name,e1->n3);
					r3=count;
					count++;
					}
				else
					r3=row(e1->n3,count);
				if((row(e1->n4,count)==-1)&&(strcmp(e1->n4,"GND")!=0)&&(strcmp(e1->n4,"gnd")!=0)){
					strcpy(node[count].name,e1->n4);
					r4=count;
					count++;
					}
				else
					r4=row(e1->n4,count);
				}
				switch(e1->name[0]){
				case 'R':
				case 'r':
				if(r1!=-1)
				node[r1].g[r1]+=((double)1/e1->val);
				if((r1!=-1)&&(r2!=-1))
				node[r1].g[r2]-=((double)1/e1->val);
				if(r2!=-1)
				node[r2].g[r2]+=((double)1/e1->val);
				if((r1!=-1)&&(r2!=-1))
				node[r2].g[r1]-=((double)1/e1->val);
				break;
				case 'L':
				case 'l':
				if(r1!=-1)
				node[r1].g[r1]+=((double)1/(e1->val*w))*(-I);
				if((r1!=-1)&&(r2!=-1))
				node[r1].g[r2]-=((double)1/(e1->val*w))*(-I);
				if(r2!=-1)
				node[r2].g[r2]+=((double)1/(e1->val*w))*(-I);
				if((r1!=-1)&&(r2!=-1))
				node[r2].g[r1]-=((double)1/(e1->val*w))*(-I);
				break;
				case 'C':
				case 'c':
				if(r1!=-1)
				node[r1].g[r1]+=w*(e1->val)*I;
				if((r1!=-1)&&(r2!=-1))
				node[r1].g[r2]-=w*(e1->val)*I;
				if(r2!=-1)
				node[r2].g[r2]+=w*(e1->val)*I;
				if((r1!=-1)&&(r2!=-1))
				node[r2].g[r1]-=w*(e1->val)*I;
				break;
				case 'I':
				case 'i':
				if(r1!=-1)
				c[r1]+=e1->val;
				if(r2!=-1)
				c[r2]-=e1->val;
				break;
				case'V':
				case 'v':
					if(strcmp(e1->name,vname)==0){
						vn = count;
					}
					strcpy(node[count].name,e1->name);
					if(r1!=-1)
					node[count].g[r1]=1;
					if(r2!=-1)
					node[count].g[r2]=-1;
					if(r1!=-1){
					node[r1].g[count]=1;
					}
					if(r2!=-1){
					node[r2].g[count]=-1;
					}
					c[count]+=e1->val;
					//printf("e#%e#",e1->val);
					vs[v]=count;
					count++;
					v++;
					break;
				case 'E':
				case 'e':
					if(strcmp(e1->name,vname)==0){
						vn = count;
					}
					strcpy(node[count].name,e1->name);
					if(r1!=-1)
					node[count].g[r1]=1;
					if(r2!=-1)
					node[count].g[r2]=-1;
					if(r3!=-1)
					node[count].g[r3]=-e1->val;
					if(r4!=-1)
					node[count].g[r4]=+e1->val;
					if(r1!=-1){
					node[r1].g[count]=1;
					}
					if(r2!=-1){
					node[r2].g[count]=-1;
					}
					vs[v]=count;
					count++;
					v++;
					break;
				case 'H':
				case 'h':
				if(strcmp(e1->name,vname)==0){
						vn = count;
					}
					strcpy(node[count].name,e1->name);
					if(r1!=-1)
					node[count].g[r1]=1;
					if(r2!=-1)
					node[count].g[r2]=-1;
					if(r1!=-1){
					node[r1].g[count]=1;
					}
					if(r2!=-1){
					node[r2].g[count]=-1;
					}
					node[count].g[row(e1->vname,count)]=-e1->val;
					vs[v]=count;
					count++;
					v++;
					break;
				case 'F':
				case 'f':
					if(r1!=-1)
					node[r1].g[row(e1->vname,count)]=e1->val;
					if(r2!=-1)
					node[r2].g[row(e1->vname,count)]=-e1->val;
					break;
				case 'G':
				case 'g':
					if((r1!=-1)&&(r3!=-1))
						node[r1].g[r3]+=e1->val;
					if((r2!=-1)&&(r4!=-1))
						node[r2].g[r4]-=e1->val;
					break;

				}
				//n=max(n,r1);
				//n=max(n,r2);
				//printf("$%d$\n",count);
				add(list,e1);
			}
			}
			x=0;
	}	

	for(i=0;i<v;i++){
		if(strcmp(node[vs[i]].name,vname)==0){
						vn = vs[i];
						//printf("c#%e#",c[vn]);
					}
	}
	printf("\n");
	for(i=0;i<count;i++){
	for(j=0;j<count;j++)
	{
		m[i][j]= node[i].g[j];
	}
	}
	for(i=0;i<count;i++)
		m[i][count]=-c[i];
	//print(m,count,aci);
	if(aci){
	if(no==1)
			fprintf(fo,"log(w)        \tlog(v1-v2) \tPhase angle\n");
	solve(m,count,aci,n1,n2,w,fo,-m[vn][count]);
	}
	if(!aci){
		esc = false;
		break;}
	else
		{
			//printf("#%f#\n",w);
			w=pow(10,(log10(vmin)+y*wstep));
			y++;
			count=0;
			s=0;p=0;x=0;count=0;vv=0;v=0;
			is=false;com=false;
			int gg;
			for(gg=0;gg<100;gg++)
				{//b[gg]=0;
				c[gg]=0;}
			for(ghj=0;ghj<100;ghj++)
			node[ghj]=sam[ghj];
			//Element *e= (Element*)malloc(sizeof(Element));
			//e=list->head;
			//freeup(e,list);
			if(y==step+1)
				{
				esc=false;
				break;
				}
		}
	}
	for(i=0;i<count;i++){
	for(j=0;j<count;j++)
	{
		m[i][j]= node[i].g[j];
	}
	}
	for(i=0;i<count;i++)
		m[i][count]=-c[i];
	//printf("*%d*\n",vn);
	m[vn][count]=-vmin;
	//printf("%f\n",vstep );
	float h=(float)(vmax-vmin)/(float)vstep;
	//printf("pp%fpp\n",h );
	int abc;
	//float step = (vmax-vmin)/(float)(vstep+1);
	//printf("%f\n",step);
	if(!aci){
		for(i=0;i<count;i++)
		fprintf(fo,"%s\t",node[i].name);
		fprintf(fo, "\n");	
	for(abc=0;abc<h+1;abc++){
	m[vn][count]=-vmin-abc*vstep;
	//print(m,count,aci);
	printf("%s = %f\n\n",vname,creal(m[vn][count]));
	solve(m,count,aci,n1,n2,-1,fo,0);
	for(i=0;i<count;i++){
	for(j=0;j<count;j++)
	{
		m[i][j]= node[i].g[j];
	}
	}
	for(i=0;i<count;i++)
		m[i][count]=-c[i];
	}
	}
	Element *e= (Element*)malloc(sizeof(Element));
	e=list->head;
	freeup(e,list);
}

			
			
