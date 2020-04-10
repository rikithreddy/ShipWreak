#include <GL/glut.h> 
#include <math.h>    
#include <stdio.h>

#include "game_data.h"
#include "utils.h"

extern void handleGlutKeyboardFunc(unsigned char key, int x, int y);

float power(float base,float pow)
{
   if(pow==0)
      return 1;
   else 
      return base * power(base,pow-1);
}

float bez(float u,int k)
{
   return comb(points,k)*power(u,k)*power(1-u,points-k);
}

struct point sigmaG( float u)
{
   struct point temp;
   int z=0;
   temp.x=0;
   temp.y=0;
   for(z=0;z<=points;z++)
   {
      temp.x+=p1[z].x*bez(u,z);
      temp.y+=p1[z].y*bez(u,z);
   }
   return temp;
}

void drawSmoke()
{
   int u; 
   for(u=0;u<1000;u++)
   {
      struct point tem;
      tem = sigmaG(u/1000.0);
      glBegin(GL_POINTS); 
      glVertex2f(tem.x,tem.y);
      glEnd();
   }
}

void initEnemy()
{
   int i;
   for(i=0; i<numEnemys; i++)
   {
      en[i].direction = -1;
      en[i].x=(int)(rand()) % 1000;
      en[i].y=(int)(rand()) % (int) winYMax;
   }
}

void handleSpecialKeypress(int key, int x, int y)
{
    if(sink!=1)
    {
        if(key==GLUT_KEY_LEFT)
        {
            shipX-=10;
        }
        if(key==GLUT_KEY_RIGHT)
        {
            shipX+=10;
        }
        if(key==GLUT_KEY_UP)
        {
        }
        if(key==GLUT_KEY_DOWN)
        {
        }
    }
}

void handleSpecialKeyReleased(int key, int x, int y) {
   if(sink!=1)
   {
      if(key==GLUT_KEY_LEFT)
         shipX-=10;
      if(key==GLUT_KEY_RIGHT)
         shipX+=10;
      if(key==GLUT_KEY_UP)
      {}
      if(key==GLUT_KEY_DOWN)
      {}
   }
}

void drawSun(int r,int x1, int y1)
{			
   int x=0,y=r;
   glBegin(GL_POINTS);         // Each set of 4 vertices form a quad
   glColor3f(1.0f, .3f, 0.0f); // Red
   while(x<y)
   {
      if(((x+1)*(x+1) + (y-0.5)*(y-0.5) - r*r) < 0)
         x++;
      else {
         x++;
         y--;
      }
      glVertex2i(x+x1,y+y1);
      glVertex2i(-x+x1,y+y1);
      glVertex2i(x+x1,-y+y1);
      glVertex2i(-x+x1,-y+y1);
      glVertex2i(y+x1,x+y1);
      glVertex2i(y+x1,-x+y1);
      glVertex2i(-y+x1,x+y1);
      glVertex2i(-y+x1,-x+y1);
   }
   glEnd();
}

void moveEn()
{
   int i;
   for(i=0;i<numEnemys;i++)
   {
      en[i].y += en[i].direction * enemySpeed;
      // Check if the ball exceeds the edges
      if (en[i].y < enYMin) {
         en[i].y = enYMax;
         en[i].x = rand() %1000;
      }
   }
}

void drawShip(float x1, float y1)
{			
   //container 2			
   glBegin(GL_POLYGON);            
   glColor3f(1.0f, 0.3f, 0.2f); // Red
   glVertex2f(x1-shipWidth*.4,y1-shipHeight*.1);
   glVertex2f(x1+shipWidth*.4,y1-shipHeight*.1);
   glVertex2f(x1+shipWidth*.4,y1+shipHeight*.1);
   glVertex2f(x1-shipWidth*.4,y1+shipHeight*.1);			
   glEnd();

   //container 1
   glBegin(GL_POLYGON);            
   glColor3f(0.0f, .6f, 0.0f); // Red
   glVertex2f(x1-shipWidth*.3,y1+shipHeight*.15-shipHeight*.05);
   glVertex2f(x1+shipWidth*.3,y1+shipHeight*.15-shipHeight*.05);
   glVertex2f(x1+shipWidth*.3,y1+shipHeight*.15+shipHeight*.05);
   glVertex2f(x1-shipWidth*.3,y1+shipHeight*.15+shipHeight*.05);			
   glEnd();

   //Base
   glBegin(GL_POLYGON);            
   glColor3f(0.0f, 0.0f, .1f); 
   glVertex2f(x1-shipWidth*.4,y1-shipHeight*.3-shipHeight*.2);
   glVertex2f(x1+shipWidth*.4,y1-shipHeight*.3-shipHeight*.2);
   glVertex2f(x1+shipWidth/2,y1-shipHeight*.3+shipHeight*.2);
   glVertex2f(x1-shipWidth/2,y1-shipHeight*.3+shipHeight*.2);
   glEnd();

   //Smoke	
   //mid
   glBegin(GL_POLYGON);            
   glColor3f(.5f, .5f, 0.5f); // Red
   glVertex2f(x1-shipWidth*.02,y1+shipHeight*.35-shipHeight*.15);
   glVertex2f(x1+shipWidth*.02,y1+shipHeight*.35-shipHeight*.15);
   glVertex2f(x1+shipWidth*.02,y1+shipHeight*.35+shipHeight*.15);
   glVertex2f(x1-shipWidth*.02,y1+shipHeight*.35+shipHeight*.15);			
   glEnd();

   //2
   glBegin(GL_POLYGON);            
   glColor3f(.5f, .5f, .5); // Red
   glVertex2f(x1-shipWidth*.1-shipWidth*.02,y1+shipHeight*.35-shipHeight*.15);
   glVertex2f(x1-shipWidth*.1+shipWidth*.02,y1+shipHeight*.35-shipHeight*.15);
   glVertex2f(x1-shipWidth*.1+shipWidth*.02,y1+shipHeight*.35+shipHeight*.15);
   glVertex2f(x1-shipWidth*.1-shipWidth*.02,y1+shipHeight*.35+shipHeight*.15);			
   glEnd();

   //1
   glBegin(GL_POLYGON);            
   glColor3f(.5f, .5f, .5f); // Red
   glVertex2f(x1-shipWidth*.2-shipWidth*.02,y1+shipHeight*.35-shipHeight*.15);
   glVertex2f(x1-shipWidth*.2+shipWidth*.02,y1+shipHeight*.35-shipHeight*.15);
   glVertex2f(x1-shipWidth*.2+shipWidth*.02,y1+shipHeight*.35+shipHeight*.15);
   glVertex2f(x1-shipWidth*.2-shipWidth*.02,y1+shipHeight*.35+shipHeight*.15);			
   glEnd();

   if(sink!=1)
   {

      p1[0].x=shipX;
      p1[0].y=shipY+shipHeight/2;
      p1[1].x=shipX;
      p1[1].y=shipY+g*30+shipHeight/2+30;
      p1[2].x=shipX-20;
      p1[2].y=shipY-g*30+shipHeight/2+30;
      p1[3].x=shipX-40;
      p1[3].y=shipY+g*30+shipHeight/2+30;
      p1[4].x=shipX-60;
      p1[4].y=shipY+30+shipHeight/2;
      drawSmoke();
      float shX = x1-shipWidth*.1-shipWidth*.02;

      p1[0].x = shX;//+shipWidth/2;
      p1[0].y=shipY+shipHeight/2;
      p1[1].x=shX;
      p1[1].y=shipY+g*30+shipHeight/2+30;
      p1[2].x=shX-20;
      p1[2].y=shipY-g*30+shipHeight/2+30;
      p1[3].x=shX-40;
      p1[3].y=shipY+g*30+shipHeight/2+30;
      p1[4].x=shX-60;
      p1[4].y=shipY+30+shipHeight/2;
      drawSmoke();
      shX = x1-shipWidth*.2-shipWidth*.02;

      p1[0].x=shX;//+shipWidth/2;
      p1[0].y=shipY+shipHeight/2;
      p1[1].x=shX;
      p1[1].y=shipY+g*30+shipHeight/2+30;
      p1[2].x=shX-20;
      p1[2].y=shipY-g*30+shipHeight/2+30;
      p1[3].x=shX-40;
      p1[3].y=shipY+g*30+shipHeight/2+30;
      p1[4].x=shX-60;
      p1[4].y=shipY+30+shipHeight/2;
      drawSmoke();
   }
}

void drawEnemy()
{			
   int i;
   for(i=0;i<numEnemys;i++)
   {
      glBegin(GL_POLYGON);            
      glColor3f(1.0f, .0f, .2f); 
      glVertex2f(en[i].x-enemyWidth/2,en[i].y-enemyHeight/2);
      glVertex2f(en[i].x+enemyWidth/2,en[i].y-enemyHeight/2);
      glVertex2f(en[i].x+enemyWidth/2,en[i].y+enemyHeight/2);
      glVertex2f(en[i].x-enemyWidth/2,en[i].y+enemyHeight/2);
      glEnd();
   }

}

void checkShip()
{
   if (shipX > winXMax)
      shipX = winXMax;
   else if (shipX < winXMin)
      shipX = winXMin;
}


void checkCollision()
{
   int i=0;
   for(i=0;i<numEnemys;i++)
   {
      float emax=en[i].x + enemyWidth/2;
      float emin=en[i].x - enemyWidth/2;
      float ebot=en[i].y - enemyHeight/2;
      float etop=en[i].y + enemyHeight/2;

      float smax=shipX + shipWidth/2;
      float smin=shipX - shipWidth/2;
      float sbot=shipY - shipHeight/2;
      float stop=shipY + shipHeight/2;

      if(emax>smin && emin < smax && ebot<stop && etop >sbot )
         sink=1;  
      if(sink==1)
         shipY-=1;
   }
}

void drawWater()
{
   glColor4f(0.0f, .4f, 1.0f,.8f);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
   glBegin(GL_POLYGON); 
   glVertex2f(winXMax,winYMax);
   glVertex2f(winXMax,winYMin);
   glVertex2f(winXMin,winYMin);
   glVertex2f(winXMin,winYMax);
   glEnd();
   glDisable(GL_BLEND);
}

void drawEnv()
{
    int i;
    for(i=0;i<sunRadius;i++)
       glColor3f(.3f, 0.0f, .0f);
    glBegin(GL_POLYGON); 
    glVertex2f(winXMin,winYMax);
    glVertex2f(sceneX/4,sceneY);
    glVertex2f(sceneX/2,winYMax);
    glEnd();

    glBegin(GL_POLYGON); 
    glVertex2f(sceneX/2,winYMax);
    glVertex2f((sceneX/4)*3,sceneY);
    glVertex2f(sceneX,winYMax);
    glEnd();
}

void drawSky()
{  
   glColor3f(.8f, .8f, 1.0f);
   glBegin(GL_POLYGON); 
   glVertex2f(0,0);
   glVertex2f(0,sceneY);
   glVertex2f(sceneX,sceneY);
   glVertex2f(sceneX,0);
   glVertex2f(winXMin,winYMax);
   glEnd();
}
 
void initGL() {
   glClearColor(0.0, 0.0, 0.0, 1.0); 
}

void display() {
	if(rand()%4==0)
   	g*=-1;
   glClear(GL_COLOR_BUFFER_BIT);  
   glMatrixMode(GL_MODELVIEW);    
   glLoadIdentity();              
   drawSky(); 
   checkCollision();
   checkShip();
   drawEnv();
   drawShip(shipX,shipY);
   drawWater();
   moveEn();
   drawEnemy(); 
   glutSwapBuffers(); 
}
 
void reshape(GLsizei width, GLsizei height) {
   if (height == 0)
      height = 1;                

   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   gluOrtho2D(0, sceneX, 0 , sceneY);

   shipXMin = winXMin + ballRadius;
   shipXMax = winXMax - ballRadius;
   shipYMin = winYMin + ballRadius;
   shipYMax = winYMax - ballRadius;
   shipX = ballRadius;
   shipY = winYMax + shipHeight/2;
}

/* Called back when the timer expired */
void Timer(int value) {
   glutPostRedisplay();    // Post a paint request to activate display()
   glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}

int main(int argc, char** argv) {

   initEnemy();
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
   glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
   glutCreateWindow("OpenGL Setup Test");      
   glutSpecialFunc(handleSpecialKeypress);
   glutSpecialUpFunc(handleSpecialKeyReleased);
   glutKeyboardFunc(handleGlutKeyboardFunc);
   glutDisplayFunc(display);     // Register callback handler for window re-paint
   glutReshapeFunc(reshape);     // Register callback handler for window re-shape
   glutTimerFunc(0, Timer, 0);   // First timer call immediately
   initGL();                     // Our own OpenGL initialization
   glutMainLoop();               // Enter event-processing loop
   return 0;
}
