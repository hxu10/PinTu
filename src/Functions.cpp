#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "Functions.h"

#define huo 2
#define N 250
#define MODE 1 //运行模式，如果为1显示详细信息，如果为2则不显示
#define DISPLAY 0 //1表示显示每一步的运行，0则不现实

extern FILE *fp;
extern FILE *fq;
extern FILE *fq1;
extern FILE *fr;

static int buzhou[5*N*N*N];
static int bu;
static int map[N][N];//静态变量
static int move[N+2][N+2];//记载状态，当1时为不可移动 (注意，和map相比，其边界横纵坐标都要加1)
static double E;
static double E2;
static int s;

struct graph;
struct graph*operate(struct graph*p,struct graph*tail);

//随机数产生器
int ran() {
    int  num;
    num=16807*(s%127773)-2836*(s/127773);
    if (num<0) num=num+2147483647;
    return num;
}

//打印地图
void printmap(FILE *fp) {
    int i,j;
    fprintf(fp,"-------------------\n");
    for(i=N-1;i>=0;i--) {
        for(j=N-1;j>=0;j--) {
            if(map[i][j]!=0) fprintf(fp,"%5d",N*N-map[i][j]);
            if(map[i][j]==0) fprintf(fp,"%5d",map[i][j]);
        }
    fprintf(fp,"\n");
    }
fprintf(fp,"-------------------\n");
}


//在显示器上打印地图
void printfmap() {
    int i,j;
    printf("-------------------\n");
    for(i=N-1;i>=0;i--) {
       for(j=N-1;j>=0;j--) {
          if(map[i][j]!=0)  printf("%5d",N*N-map[i][j]);
          if(map[i][j]==0)  printf("%5d",map[i][j]);
       }
       printf("\n");
    }
    printf("-------------------\n");
    system("cls");
}

//上下左右指令
void up(int i,int j) {
	if(map[i][j]!=0 || i+1>N  ) {printf("ERROR!!!\n");return;}
    map[i][j]=map[i+1][j];
    map[i+1][j]=0;
	buzhou[bu]=1;
	bu++;
}

void down(int i,int j) {
	if(map[i][j]!=0 || i-1<0 ) {printf("ERROR!!!\n");return;}
    map[i][j]=map[i-1][j];
    map[i-1][j]=0;
	buzhou[bu]=2;
	bu++;
}

void right(int i,int j) {
	if(map[i][j]!=0 || j+1>N ) {printf("ERROR!!!\n");return;}
    map[i][j]=map[i][j+1];
    map[i][j+1]=0;
	buzhou[bu]=3;
	bu++;
}

void left(int i,int j) {
	if(map[i][j]!=0 || j-1<0 ) {printf("ERROR!!!\n");return;}
    map[i][j]=map[i][j-1];
    map[i][j-1]=0;
	buzhou[bu]=4;
	bu++;
}

//go函数，将0处的空格从（i0,j0）移动到（i1,j1）
int step(int d1,int d2,int d3,int d4,int i,int j,int od) {
    i++;j++;
    if(DISPLAY==1) printfmap();
    add5:
        if(d1==1 && move[i+1][j]!=1 && od!=2) {up(i-1,j-1);return 1 ;}
        if(d1==2 && move[i-1][j]!=1 && od!=1) {down(i-1,j-1);return 2 ;}
        if(d1==3 && move[i][j-1]!=1 && od!=4) {left(i-1,j-1);return 3;}
        if(d1==4 && move[i][j+1]!=1 && od!=3) {right(i-1,j-1);return 4;}
        if(d2==1 && move[i+1][j]!=1 && od!=2) {up(i-1,j-1);return 1;}
        if(d2==2 && move[i-1][j]!=1 && od!=1) {down(i-1,j-1);return 2;}
        if(d2==3 && move[i][j-1]!=1 && od!=4) {left(i-1,j-1);return 3;}
        if(d2==4 && move[i][j+1]!=1 && od!=3) {right(i-1,j-1);return 4;}
        if(d3==1 && move[i+1][j]!=1 && od!=2) {up(i-1,j-1);return 1;}
        if(d3==2 && move[i-1][j]!=1 && od!=1) {down(i-1,j-1);return 2;}
        if(d3==3 && move[i][j-1]!=1 && od!=4) {left(i-1,j-1);return 3;}
        if(d3==4 && move[i][j+1]!=1 && od!=3) {right(i-1,j-1);return 4;}
        if(d4==1 && move[i+1][j]!=1 && od!=2) {up(i-1,j-1);return 1;}
        if(d4==2 && move[i-1][j]!=1 && od!=1) {down(i-1,j-1);return 2;}
        if(d4==3 && move[i][j-1]!=1 && od!=4) {left(i-1,j-1);return 3;}
        if(d4==4 && move[i][j+1]!=1 && od!=3) {right(i-1,j-1);return 4;}
 //printf("卡住了，出现错误。\n");
    od=0;
    goto add5;
}

//go函数，将空格从一个位置移到另一个位置
void go(int i0,int j0,int i1,int j1) {
    int i=i0,j=j0,d=0,r=0;
    if(map[i0][j0]!=0) {
	    printf("ERROR2!!!\n");
	    return;
    
        for(i=0;i<N;i++) {
	        for(j=0;j<N;j++) {
		        if(map[i][j]==0) goto add3;
	        }
        }  
    }

    add3:
    if(i0==i1 && j0==j1) return ;
    if(i1-i==2 && j1==0 && j!=j1) {
	    if(move[i+2][j+1]!=1) {up(i,j);i++;}
	}
    
    while(i!=i1 || j!=j1) {
    if(i<i1 && j<j1) d=step(4,1,3,2,i,j,d); 
    if(i>i1 && j<j1) d=step(2,4,1,3,i,j,d); 
    if(i<i1 && j>j1) d=step(3,1,2,4,i,j,d); 
    if(i>i1 && j>j1) d=step(3,2,4,1,i,j,d);
    if(i==i1 && j>j1) d=step(3,1,2,4,i,j,d);
    if(i==i1 && j<j1) d=step(4,2,1,3,i,j,d);
    if(i>i1 && j==j1) d=step(2,4,3,1,i,j,d);
    if(i<i1 && j==j1) d=step(1,4,3,2,i,j,d);
    if(d==1) i++;
    if(d==2) i--;
    if(d==3) j--;
    if(d==4) j++;
    r++;

    if(r>2*N) {
        printf("由于程序陷入死循环，被迫终止\n");
        printmap(fp);
        exit(0);
        }
    }
}

//功能函数，要求把制定的格子向上移动
void moveup(int i,int j,int i1,int j1) {
  //(i,j)是空格所在的坐标，(i1,j1)是要移动的块的所在的坐标
  move[i1+1][j1+1]=1;
  go(i,j,i1+1,j1);
  down(i1+1,j1);
  move[i1+1][j1+1]=0;
}

void movedown(int i,int j,int i1,int j1) {
  //(i,j)是空格所在的坐标，(i1,j1)是要移动的块的所在的坐标
  move[i1+1][j1+1]=1;
  go(i,j,i1-1,j1);
  up(i1-1,j1);
  move[i1+1][j1+1]=0;
}

void moveleft(int i,int j,int i1,int j1) {
  //(i,j)是空格所在的坐标，(i1,j1)是要移动的块的所在的坐标
  move[i1+1][j1+1]=1;
  go(i,j,i1,j1-1);
  right(i1,j1-1);
  move[i1+1][j1+1]=0;
}

//功能函数，要求把制定的格子向右移动
void moveright(int i,int j,int i1,int j1) {
  //(i,j)是空格所在的坐标，(i1,j1)是要移动的块的所在的坐标
  move[i1+1][j1+1]=1;
  go(i,j,i1,j1+1);
  left(i1,j1+1);
  move[i1+1][j1+1]=0;
}

//功能函数，将序号为n的块移到正确的位置
int moveto(int n,int i,int j,int mode,FILE *fp) {
   int x,y,k,r,l;
   if(map[n/N][n%N]==n) return 0;
	//注意这里x是纵坐标，y是横坐标，和习惯正好相反，不要弄混了！
   x,y,k,r,l=n%N;
  //(i,j)是空格所在的目标，n是要移动的块序号，mode是模式
	for(x=0;x<N;x++) {
        for(y=0;y<N;y++) {
		 if(map[x][y]==n) goto add1;
         }
    }
	//（x,y）表示要移动的块的起始坐标
   
    add1:  
     if(mode==1) {//第一模式，先横向移动后纵向移动
	    if(y>(n%N)) {
			for(k=y;k>(n%N);k--) {moveleft(i,j,x,k);i=x;j=k;}
			r=4;
		}
		
	    if(y<(n%N)) {
			for(k=y;k<(n%N);k++) {moveright(i,j,x,k);i=x;j=k;}
			r=3;
		}

	//	printmap(fp);
		for(k=x;k<(n/N);k++) {moveup(i,j,k,n%N);i=k;j=n%N;r=2;}
	}

	if(mode==2) { //第二模式，先纵向移动后横向移动
	    if(x>(n/N)) {
			for(k=x;k>(n/N);k--) {movedown(i,j,k,y);i=k;j=y;}
			r=1;
		}
	    
        if(x<(n/N)) {
			for(k=x;k<(n/N);k++) {moveup(i,j,k,y);i=k;j=y;}
			r=2;
		}
		
        for(k=y;k<(n%N);k++) {moveright(i,j,(n/N),k);i=n/N;j=k;r=3;}
	
    }
    
    if(mode==3) { //第三模式，把最上右边的格子插进去
        if(map[n/N-1][n%N]==n && i==n/N && j==n%N) {
		      down(i,j);i--;
        }

        for(k=y;k<(n%N);k++) {moveright(i,j,x,k);i=x;j=k;}
	    for(k=x;k<(n/N)-1;k++) {moveup(i,j,k,n%N);i=k;j=n%N;}
        go(i,j,n/N-1,l-2);
	    i=n/N-1;j=l-2;
	    up(i,j);i++;
	    right(i,j);j++;
	    right(i,j);j++;
	    down(i,j);i--;
	    left(i,j);j--;
	    up(i,j);i++;
	    left(i,j);j--;
	    down(i,j);i--;
    }
	  
    if(mode==4) { //第四模式，把最下右表的格子插进去
    printmap(fp);
		  
	    for(k=x;k>0;k--) {movedown(i,j,k,y);i=k;j=y;}
        for(k=y;k<(n%N)-1;k++) {moveright(i,j,0,k);i=0;j=k;}
	    if(map[i][j+1]==n) {up(i,j);i++;}
	    if(map[i][j-1]==n) {left(i,j);return 3;}
//	    printmap(fp);
	    go(i,j,2,l-1);i=2;j=l-1;
	    right(i,j);j++;
	    down(i,j);i--;
	    down(i,j);i--;
	    left(i,j);j--;
	    up(i,j);i++;
	    right(i,j);j++;
	    up(i,j);i++;
	    left(i,j);j--;
    }
return r;
}

void arrangeline(int l,int mode,FILE *fp) {

int i,j,k,t; //i,j记载空格的位置
for(i=0;i<N;i++)
{
  for(j=0;j<N;j++)
  {
	  if(map[i][j]==0) goto add2;
  }
}
add2:

//把第l行的前N-1个都平移来

 for(k=l*N;k<l*N+l;k++)
 {
  t=moveto(k,i,j,1,fp);
  if(k!=map[k/N][k%N]) {printf("第%d个图块移位出现错误!\n",k);printmap(fp);exit(0);}
  move[k/N+1][k%N+1]=1;
  if(t==1) {i=k/N+1;j=k%N;}
  if(t==2) {i=k/N-1;j=k%N;}
  if(t==3) {i=k/N;j=k%N-1;}
  if(t==4) {i=k/N;j=k%N+1;}
  
 //printmap(fp);
 }
//把第N个插入行内
 moveto(k,i,j,3,fp);
  if(k!=map[k/N][k%N]) {printf("第%d个图块移位出现错误!\n",k);printmap(fp);exit(0);}
 move[k/N+1][k%N+1]=1;
 for(i=0;i<N;i++)
{
  for(j=0;j<N;j++)
  {
	  if(map[i][j]==0) {t=1;break;}
  }
  if(t==1) break;
}

 //排列第l列
 //printmap(fp);

if(mode!=2)
{


for(k=(l-1)*N+l;k>l;k-=N)
 {
  t=moveto(k,i,j,2,fp);
   if(k!=map[k/N][k%N]) {printf("第%d个图块移位出现错误!\n",k);printmap(fp);exit(0);}
  move[k/N+1][k%N+1]=1;
  if(t==1) {i=k/N+1;j=k%N;}
  if(t==2) {i=k/N-1;j=k%N;}
  if(t==3) {i=k/N;j=k%N-1;}
  if(t==4) {i=k/N;j=k%N+1;}
  //插入第l列最后一个
// printmap(fp);
 }
 moveto(l,i,j,4,fp);
  if(l!=map[l/N][l%N]) {printf("第%d个图块移位出现错误!\n",l);printmap(fp);exit(0);}

move[l/N+1][l%N+1]=1;


}

return ;
}



//last函数，专门处理最后六步
void last() {
    int i,j,m;
    struct graph*tail;
    struct graph*p;
    tail=(struct graph*)malloc(sizeof(struct graph));
    p=tail;
    tail->step=0;
   for(i=0;i<2;i++) {
     for(j=0;j<3;j++) {
         tail->g[i][j]=map[i][j];
     }
   }

m=0;

    while(p->step<28) {

tail=operate(p,tail);
if(tail==NULL) break;

if(p->step>m) 
{
m=p->step;
}
p=p->next;
}

}

//成功函数
void success(int zong[],int step,int final) {
int i,j,k;
zong[step]=final;
for(i=0;i<2;i++)
{
 for(j=0;j<3;j++)
 {
 if(map[i][j]==0) goto add4;
 }
}
add4:
 for(k=1;k<=step;k++)
 {
	 
	 if(zong[k]==1) {up(i,j);i++;}
	 if(zong[k]==2) {down(i,j);i--;}
	 if(zong[k]==3) {left(i,j);j--;}
	 if(zong[k]==4) {right(i,j);j++;}

 }
return ;
}

//请为这个函数添加注释，谢谢
void modify() {
  int tmap[N][N],i,j;
  for(i=0;i<N;i++)
  {
	  for(j=0;j<N;j++)
	  {
		 if(map[i][j]==0) tmap[N-1-i][N-1-j]=map[i][j];
	     if(map[i][j]!=0) tmap[N-1-i][N-1-j]=16-map[i][j];         
	  }
  }
  for(i=0;i<N;i++)
  {
     for(j=0;j<N;j++)
	 {
	   map[i][j]=tmap[i][j];	 
	 }
  }

}

struct graph {
    int g[2][3];
    int step;
    int pre;
    int zong[20];
    struct graph*next;
};

//后面四个分别代表向上，向下，向左，向右操作
struct graph* up(int i,int j,struct graph*p) {
struct graph*q;
q=(struct graph*)malloc(sizeof(struct graph));
int i0,j0,temp;
for(i0=0;i0<2;i0++)
{
  for(j0=0;j0<3;j0++)
  {
   q->g[i0][j0]=p->g[i0][j0];
  }
}
 temp=q->g[i][j]=q->g[i+1][j];
 q->g[i+1][j]=0; //在p的基础上进行向上平移
 
 q->step=p->step+1;
 if(q->g[0][0]==0 && q->g[0][1]==1 && q->g[0][2]==2 && q->g[1][0]==N) {success(q->zong,q->step,1);return NULL ;}
 q->pre=1;//上一步记为向上
 for(i0=1;i0<q->step;i0++) q->zong[i0]=p->zong[i0];
 q->zong[q->step]=1;//记录具体的路径数
 return q;
}

struct graph* down(int i,int j,struct graph*p) {
  struct graph*q;
  q=(struct graph*)malloc(sizeof(struct graph));
  int i0,j0,temp;
  for(i0=0;i0<2;i0++) {
    for(j0=0;j0<3;j0++) {
   q->g[i0][j0]=p->g[i0][j0];
  }
}
 temp=q->g[i][j]=q->g[i-1][j];
 
 q->g[i-1][j]=0; //在p的基础上进行向下平移
 q->step=p->step+1; //步数加1

 if(q->g[0][0]==0 && q->g[0][1]==1 && q->g[0][2]==2 && q->g[1][0]==N) {success(p->zong,q->step,2);return NULL ;}

 q->pre=2; //上一步的方向记为向下
 for(i0=1;i0<q->step;i0++) q->zong[i0]=p->zong[i0];
 q->zong[q->step]=2;//记录具体的路径数

 return q;
}

struct graph* left(int i,int j,struct graph*p) {
struct graph*q;
q=(struct graph*)malloc(sizeof(struct graph));
int i0,j0,temp;
for(i0=0;i0<2;i0++)
{
  for(j0=0;j0<3;j0++)
  {
   q->g[i0][j0]=p->g[i0][j0];
  }
}
 temp=q->g[i][j]=q->g[i][j-1];
 q->g[i][j-1]=0; //在p的基础上进行向左平移
 
 q->step=p->step+1;//步数加1
  if(q->g[0][0]==0 && q->g[0][1]==1 && q->g[0][2]==2 && q->g[1][0]==N) {success(p->zong,q->step,3);return NULL ;}
 q->pre=3; //上一步的方向记为向左
 for(i0=1;i0<q->step;i0++) q->zong[i0]=p->zong[i0];
 q->zong[q->step]=3;//记录具体的路径数

 return q;
 
}

struct graph* right(int i,int j,struct graph*p)
{
struct graph*q;
q=(struct graph*)malloc(sizeof(struct graph));
int i0,j0,temp;
for(i0=0;i0<2;i0++)
{
  for(j0=0;j0<3;j0++)
  {
   q->g[i0][j0]=p->g[i0][j0];
  }
}
 temp=q->g[i][j]=q->g[i][j+1];
 q->g[i][j+1]=0; //在p的基础上进行向右平移

 q->step=p->step+1;//步数加1
  if(q->g[0][0]==0 && q->g[0][1]==1 && q->g[0][2]==2 && q->g[1][0]==N && q->g[1][1]==N+1) {success(p->zong,q->step,4);return NULL ;}
 q->pre=4; //上一步的方向记为向右
 for(i0=1;i0<q->step;i0++) q->zong[i0]=p->zong[i0];
 q->zong[q->step]=4;//记录具体的路径数
 return q;
}

//operate函数，功能p是展开操作的指针，tail是该队列的尾巴指针.
struct graph* operate(struct graph*p,struct graph*tail) {
  int i,j,k=0;
  for(i=0;i<2;i++)
  {
   for(j=0;j<3;j++)
   {
	   if(p->g[i][j]==0) {k=1;break;}
   }
   if(k==1) break;
  }
 

  struct graph*q;

  if(i!=1 && p->pre!=2) //当i不是最上一行的时候，并且上一步的操作方向不是向下的时候，向上操作
  {
  q=up(i,j,p);
  if(q==NULL) return NULL;
  tail->next=q;
  tail=q;
  }
 
  if(i!=0 && p->pre!=1) 
  {
  if(q==NULL) return NULL;
  q=down(i,j,p);tail->next=q;tail=q;
  }
  if(j!=0 && p->pre!=4)
  {
   if(q==NULL) return NULL;
  q=left(i,j,p);tail->next=q;tail=q;
  }
 
if(j!=2 && p->pre!=3)
  {
   if(q==NULL) return NULL;
  q=right(i,j,p);tail->next=q;tail=q;
  }
return tail;//返回尾指针
}

int mainProgram() {
    fp=fopen("xuhao.txt","w");
fq=fopen("空格移动方向.txt","w");
fq1=fopen("图块移动方向.txt","w");
fr=fopen("original.txt","r");

int i,j,k=0,m,l,mo,repeat;
int initialE,preE,cha;
double T=100;
int pre;
int start,finish;
int sui[N*N]={0};//这是随机数产生的对应数组，可以将1-N*N之间所有数打乱
for(i=0;i<N+2;i++) move[0][i]=1;
for(i=0;i<N+2;i++) move[N+1][i]=1;
for(i=1;i<N+1;i++) move[i][0]=1;
for(i=0;i<N+2;i++) move[i][N+1]=1; 

printf("请你输入一个种子值，输入0则是自动输入初始地图\n");
scanf("%d",&s);
if(s==0)
{
  printf("请你自动输入地图。");
  for(i=0;i<N;i++)
  {
     for(j=0;j<N;j++)
	 {
        fscanf(fr,"%d",&map[i][j]);
	 }
  }
  modify();
}


if(s!=0)
{
s=ran();
printf("%d\n",s);

for(i=0;i<N;i++)
{
  for(j=0;j<N;j++)
  {
  map[i][j]=i*N+j;
  }
}
i=0;j=0;
printf("正在打乱地图.....\n");
while(k<5*N*N*N)
{
	s=ran();
 m=(s*1.0/2147483647)*4+1;
 if(m==1 && i<N-1) {up(i,j);i++;}
 if(m==2 && i>0) {down(i,j);i--;}
 if(m==3 && j>0) {left(i,j);j--;}
 if(m==4 && j<N-1) {right(i,j);j++;}
 k++;
}

}


if(MODE==1)
{
printf("初始地图如下：\n");
printmap(fp);
printfmap();
}
//在N*N的方格中产生1到N*N-1的随机数，并存放在除了（0,0）以外的其他格子中
bu=0;
printf("地图已被打乱，正在还原.......\n");
E=0;E2=0;
start=clock();

for(l=N-1;l>2;l--)
{
arrangeline(l,1,fp);
if(l%2==0) printf("完成进度%d/%d\n",N*N-l*l,N*N);
}
arrangeline(2,2,fp);
//只剩下最后的六个了
last();
finish=clock();

if(MODE==1)
{
printf("最终地图如下：\n");
printmap(fp);
printfmap();
}
printf("分层移动法一共移动%d步，用时%4.3f秒\n",bu,(finish-start)*1.0/1000);
printf("具体的还原过程请见“空格移动方向.txt”和“图块移动方向.txt”的两个文件\n");

if(MODE==1)
{
for(i=1;i<=bu;i++)
{
if(buzhou[i-1]==1) fprintf(fq,"%7d,上 ",i);
if(buzhou[i-1]==2) fprintf(fq,"%7d,下 ",i);
if(buzhou[i-1]==3) fprintf(fq,"%7d,左 ",i);
if(buzhou[i-1]==4) fprintf(fq,"%7d,右 ",i);

if(i%5==0) fprintf(fq,"\n");
}
for(i=1;i<=bu;i++)
{
if(buzhou[i-1]==1) fprintf(fq1,"%7d,下 ",i);
if(buzhou[i-1]==2) fprintf(fq1,"%7d,上 ",i);
if(buzhou[i-1]==3) fprintf(fq1,"%7d,右 ",i);
if(buzhou[i-1]==4) fprintf(fq1,"%7d,左 ",i);

if(i%5==0) fprintf(fq,"\n");
}
}

printf("输入任意数字结束。\n");
scanf("%d",&i);
return 0;
}