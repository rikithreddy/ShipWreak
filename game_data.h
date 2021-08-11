#ifndef GAME_DATA_H_
#define GAME_DATA_H_

#define REFRESH_RATE 30  

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
float xSpeed = 0;      
float ySpeed = 0;

float sunRadius=250;
struct enemys {
    float x;
    float y;
    int direction;
};

struct point {
float x;
float y;
};
int points=4;
struct point p1[5],p2[5],p3[5];

struct enemys en[100];
int sink=0;

#endif