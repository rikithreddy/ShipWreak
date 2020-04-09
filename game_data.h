#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_


int windowWidth  = 1300;     
int windowHeight = 700;    
int windowPosX   = 00;      
int windowPosY   = 00; 
int g=-1;

float shipX ;         
float shipY ;
float sceneX=1000;
float sceneY=1000;
float shipHeight=80;
float shipWidth=120;
float winXMin=1;
float winYMin=1;
float winXMax=999;
float winYMax=300;
float ballRadius = 40	;   
float shipXMax, shipXMin, shipYMax, shipYMin; 
float enYMax=750, enYMin=250; 
float xSpeed = 0;      
float ySpeed = 0;
float enemySpeed=30;
float enemyHeight=30;
float enemyWidth=5;
float sunRadius=300;
int numEnemys=3;
struct enemys {
float x;
float y;
int dir;
};

struct point {
float x;
float y;
};
int points=4;
struct point p1[5],p2[5],p3[5];

struct enemys en[100];
int refreshMillis = 30;    
int sink=0;

#endif