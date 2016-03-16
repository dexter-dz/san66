#include <graphics.h>
#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
// These Files are also included in SAN.h 
#define ENTER 13
#define SPACE 32
#define BACK 8
#define ESC 0x1b
#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d
#define F1 0x3b
#define F2 0x3c
#define F3 0x3d
#define F4 0x3e
#define F5 0x3f
#define F6 0x40
#define F7 0x41
#define F8 0x42
#define F9 0x43
#define F10 0x44
//You can delete this part and link SAN.h instead
/*********************** GLOBAL VARIABLES **********************************/

int y1,y2,xb,yb,xb_dir=1,yb_dir=1,del=10,lvl=4,mode,ast=0,ric,ric1;
int xb1,yb1,xb_dir1,yb_dir1,twoball=0,score1=0,score2=0,scoremax=5;
long k=1;

/*********************** PROTOTYPES ****************************************/

void drawball(int i,int j,int c1,int c2);
void drawbrick1(int i,int c);
void drawbrick2(int i,int c);
void drawborder();
void drawscores();
void graphinit();
void display();
void intro();
void start();
void menu();
void move();
void dif();
void ai1();
void ai2();
void win();

/*********************** M A I N *******************************************/

main() { intro(); menu(); start(); move(); }

/*********************** FUNCTIONS *****************************************/

void graphinit()
{
   int driver=DETECT,mode;
   initgraph(&driver,&mode,"..\\bgi");
}

void intro()
{
   graphinit();
   cout<<"   Press any key to continue...";
   settextstyle(1,0,9); setcolor(9);
   outtextxy(80,140,"PING-PONG"); getch();
   settextstyle(1,0,4); setcolor(12);
   outtextxy(350,270,"By SanDZ66"); getch();
   closegraph();
}

void menu()
{
   char opt;
   _setcursortype(_NOCURSOR); st: clrscr();
   gotoxy(31,5); textcolor(9); cprintf("P I N G - P O N G by SanDZ66");
   gotoxy(33,9); textcolor(12); cprintf("S");
   gotoxy(34,9); textcolor(10); cprintf("ingle Player");
   gotoxy(34,12); textcolor(12); cprintf("M");
   gotoxy(35,12); textcolor(10); cprintf("ultiplayer");
   gotoxy(32,15); textcolor(12); cprintf("L");
   gotoxy(33,15); textcolor(10); cprintf("imit score: %d",scoremax);
   gotoxy(32,18); textcolor(12); cprintf("G");
   gotoxy(33,18); textcolor(10); cprintf("ame speed: %d",del);
   gotoxy(30,21); textcolor(12); cprintf("T");
   gotoxy(31,21); textcolor(10); cprintf("wo-ball mode: ");
   if(twoball) cprintf("ON"); else cprintf("OFF");
   gotoxy(37,24); textcolor(12); cprintf("Q");
   gotoxy(38,24); textcolor(10); cprintf("uit");
   for(;;)
   {
      opt=getch();
      if(opt=='G'||opt=='g') { del++; if(del==21) del=3; goto st; }
      if(opt=='L'||opt=='l')
      { scoremax+=5; if(scoremax==205) scoremax=0; goto st; }
      if(opt=='Q'||opt=='q')
      { clrscr(); cout<<"   Bye!"; delay(500); exit(0); }
      if(opt=='s'||opt=='S') { mode=1; dif(); return; }
      if(opt=='m'||opt=='M') { mode=2; return; }
      if(opt=='t'||opt=='T')
      { if(twoball) twoball=0; else twoball=1; goto st; }
   }
}

void dif()
{
   char dif[14],assist[5],opt;
   sta: clrscr();
   if(lvl==6) strcpy(dif,"Very Easy");
   if(lvl==5) strcpy(dif,"Easy");
   if(lvl==4) strcpy(dif,"Normal");
   if(lvl==3) strcpy(dif,"Hard");
   if(lvl==2) strcpy(dif,"Very Hard");
   if(lvl==1) strcpy(dif,"R U Crazy?!?");
   if(ast==0) strcpy(assist,"None");
   if(ast==4) strcpy(assist,"High");
   if(ast==8) strcpy(assist,"Med.");
   if(ast==12) strcpy(assist,"Low");
   gotoxy(32,16); textcolor(12); cprintf("D");
   gotoxy(33,16); textcolor(10); cprintf("ifficulty: %s",dif);
   gotoxy(38,6); textcolor(12); cprintf("S");
   gotoxy(39,6); textcolor(10); cprintf("tart!");
   gotoxy(35,11); textcolor(12); cprintf("A");
   gotoxy(36,11); textcolor(10); cprintf("ssist: %s",assist);
   for(;;)
   {
      opt=getch();
      if(opt=='d'||opt=='D') { lvl--; if(lvl==0) lvl=6; goto sta; }
      if(opt=='a'||opt=='A') { ast+=4; if(ast==16) ast=0; goto sta; }
      if(opt=='s'||opt=='S') { return; }
   }
}
   

void start()
{
   int j; randomize(); j=random(100);
   yb_dir=-1; yb_dir1=1;
   if(j%2==0) { xb_dir=1; xb_dir1=-1; }
   else { xb_dir=-1; xb_dir1=1; }
   graphinit(); drawborder();
   xb=320; yb=400; xb1=320; yb1=80; y1=y2=200;
   drawbrick1(y1,2); drawbrick2(y2,2);
   drawball(xb,yb,4,1);
   if(twoball) drawball(xb1,yb1,14,9);
   getch();
}

void drawborder()
{ setcolor(1); rectangle(5,4,635,476); }

void drawball(int i,int j,int c1,int c2)
{
   setcolor(c1); circle(i,j,10);
   setfillstyle(1,c2); fillellipse(i,j,9,9);
}

void drawbrick2(int i,int c)
{
   setcolor(c);
   int brick2[10]={6,i,28,i,28,i+100,6,i+100,6,i};
   setfillstyle(8,c); fillpoly(4,brick2);
}

void drawbrick1(int i,int c)
{
   setcolor(c);
   int brick1[10]={634,i,634,i+100,611,i+100,611,i,634,i};
   setfillstyle(7,c); fillpoly(4,brick1);
}

void drawscores()
{
   gotoxy(70,1); cout<<"         ";
   gotoxy(70,1); cout<<"Score1 :"<<score1;
   gotoxy(3,1); cout<<"         ";
   gotoxy(3,1); cout<<"Score2  :"<<score2;
}

void win()
{
   if((xb<24&&xb_dir==-1&&xb>15)&&!ric)
   {
      sound(2500); delay(1); nosound();
      score1++; drawscores(); ric=1;
      if(scoremax)
       if(score1==scoremax)
        { gotoxy(33,15); cout<<"Player 1 wins!"; delay(2000); exit(0); }
   }
   if((xb>611&&xb_dir==1&&xb<616)&&!ric)
   {
      sound(2500); delay(1); nosound();
      score2++; drawscores(); ric=1;
      if(scoremax)
       if(score2==scoremax)
        { gotoxy(33,15); cout<<"Player 2 wins!"; delay(2000); exit(0); }
   }
   if((xb1<24&&xb_dir1==-1&&xb>15)&&!ric1)
   {
      sound(2500); delay(1); nosound();
      score1++; drawscores(); ric1=1;
      if(scoremax)
       if(score1==scoremax)
        { gotoxy(33,15); cout<<"Player 1 wins!"; delay(2000); exit(0); }
   }
   if((xb1>611&&xb_dir1==1&&xb1<616)&&!ric1)
   {
      sound(2500); delay(1); nosound();
      score2++; drawscores(); ric1=1;
      if(scoremax)
       if(score2==scoremax)
        { gotoxy(33,15); cout<<"Player 2 wins!"; delay(2000); exit(0); }
   }
}

void move()
{
   char a;
   while(a!=ESC)
   {
      a=0;
      if(kbhit())
      {
         a=getch();
         if(a==UP&&y1>15)
         { drawbrick1(y1+1,0); y1-=10; drawbrick1(y1,2); }
         if(a==DOWN&&y1<365)
         { drawbrick1(y1,0); y1+=10; drawbrick1(y1,2); }
         if(mode==2)
         {
            if(a=='w'&&y2>15)
            { drawbrick2(y2+1,0); y2-=10; drawbrick2(y2,2); }
            if(a=='s'&&y2<365)
            { drawbrick2(y2,0); y2+=10; drawbrick2(y2,2); }
         }
      }
      drawball(xb,yb,0,0);
      if(twoball) drawball(xb1,yb1,0,0);
      xb+=xb_dir*5; yb+=yb_dir*3;
      if(twoball) { xb1+=xb_dir1*4; yb1+=yb_dir1*2; }
      drawball(xb,yb,4,1);
      if(twoball) drawball(xb1,yb1,14,9);
      win(); drawscores();
      if(k%lvl==0) if(mode!=2) ai1();
      if(ast) if(k%ast==0) ai2();
      k++; if(ric) ric++; if(ric>110) ric=0;
      if(ric1) ric1++; if(ric1>110) ric1=0;
      delay(del);
      if(yb>462||yb<18) { sound(1500); delay(1); nosound(); yb_dir*=-1; }
      if(xb>619||xb<21||(xb==40&&(yb-y2<100&&yb-y2>0))||
        (xb==600&&(yb-y1<100&&yb-y1>0)))
      { sound(1500); delay(1); nosound(); xb_dir*=-1; }
      if(twoball)
      {
         if(yb1>462||yb1<18) { sound(1500); delay(1); nosound(); yb_dir1*=-1; }
         if(xb1>619||xb1<21||(xb1==40&&(yb1-y2<100&&yb1-y2>0))||
           (xb1==600&&(yb1-y1<100&&yb1-y1>0)))
         { sound(1500); delay(1); nosound(); xb_dir1*=-1; }
         if((xb-xb1<21&&xb-xb1>-21)&&(yb-yb1<21&&yb-yb1>-21))
         { xb_dir*=-1; yb_dir*=-1; xb_dir1*=-1; yb_dir1*=-1;
           sound(2500); delay(1); nosound(); }
      }
   }
}

void ai1()
{
   if(yb>y2+25&&xb<320&&xb_dir==-1&&y2<365)
   { drawbrick2(y2,0); y2+=10; drawbrick2(y2,2); }
   if(yb<y2+25&&xb<320&&xb_dir==-1&&y2>15)
   { drawbrick2(y2+1,0); y2-=10; drawbrick2(y2,2); }
   if(xb_dir==1)
   {
       if(y2+50>240) { drawbrick2(y2+1,0); y2-=10; drawbrick2(y2,2); }
       if(y2+50<238) { drawbrick2(y2,0); y2+=10; drawbrick2(y2,2); }
   }
}

void ai2()
{
   if(yb>y1+50 && xb>320 && xb_dir==1&&y1<365)
   { drawbrick1(y1,0); y1+=10; drawbrick1(y1,2); }
   if(yb<y1+50 && xb>320 && xb_dir==1&&y1>15)
   { drawbrick1(y1+1,0); y1-=10; drawbrick1(y1,2); }
}
// THe End ..