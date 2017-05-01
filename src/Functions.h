#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define huo 2
#define N 250
#define MODE 1 //运行模式，如果为1显示详细信息，如果为2则不显示
#define DISPLAY 0 //1表示显示每一步的运行，0则不现实

FILE *fp;
FILE *fq;
FILE *fq1;
FILE *fr;

struct graph* down(int i, int j, struct graph*p);
int ran();
void printmap(FILE *fp);
void printfmap();
void up(int i,int j);
void down(int i,int j);
void right(int i,int j);
void left(int i,int j);
int step(int d1,int d2,int d3,int d4,int i,int j,int od);
void go(int i0,int j0,int i1,int j1);
void moveup(int i,int j,int i1,int j1);
void movedown(int i,int j,int i1,int j1);
void moveleft(int i,int j,int i1,int j1);
void moveright(int i,int j,int i1,int j1);
int moveto(int n,int i,int j,int mode,FILE *fp);
void arrangeline(int l,int mode,FILE *fp);
void last();
void success(int zong[],int step,int final);
void modify();
int mainProgram();
