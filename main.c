#include <GL/glut.h> 
#include <math.h>    
#include <stdio.h>
	
	
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

int factorial(int n)
{
	if(n==1||n==0)
           return 1;
	else 
 	   return n*factorial(n-1);
}

float power(float base,float pow)
{
if(pow==0)
 return 1;
else 
 return base*power(base,pow-1);

}

int comb(int n , int k)
{

int sum= factorial(n);
sum/=factorial(n-k);
sum/=factorial(k);
 //printf("%d-sum\n",sum);
return sum;
}

float bez(float u,int k)
{

   return comb(points,k)*power(u,k)*power(1-u,points-k);

}

struct point sigma( float u)
{
struct point temp;
temp.x=0;
temp.y=0;
int sum,z=0;
for(z=0;z<=points;z++)
 {
//printf("lol");

   temp.x+=p1[z].x*bez(u,z);
   temp.y+=p1[z].y*bez(u,z);



 }


return temp;
}

void drawSmoke(){

int u; 

for(u=0;u<1000;u++)
{
int sum=0;
struct point tem;
   tem=sigma(u/1000.0);
   glBegin(GL_POINTS); 
printf("%lf-%lf \n",tem.x,tem.y);
   glVertex2f(tem.x,tem.y);
   glEnd();



}
}




struct enemys en[100];
int refreshMillis = 30;    
int  sink=0;

void handleGlutKeyboardFunc(unsigned char key, int x, int y)
{
   if(key == 27)
     exit(0);



}

void handleSpecialKeypress(int key, int x, int y) {
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
//      ballY+=10;

  }
 if(key==GLUT_KEY_DOWN)
  {
  //    ballY-=10;

  }
}

}




void initEnemy(){
int i;
int b=1;
for(i=0;i<numEnemys;i++)
{
en[i].dir=-1;

en[i].x=(int)(rand()) % 1000;
en[i].y=(int)(rand()) % (int) winYMax;
}

}
void handleSpecialKeyReleased(int key, int x, int y) {
if(sink!=1)
{
 if(key==GLUT_KEY_LEFT    )
  {
      shipX-=10;
  }
 if(key==GLUT_KEY_RIGHT)
  {

      shipX+=10;
  }
 if(key==GLUT_KEY_UP)
  {
    //  ballY+=10;

  }
 if(key==GLUT_KEY_DOWN)
  {
      //ballY-=10;

  }
}
}






float drawSun(int r,int x1, int y1)
{			
			int i;
			int x=0,y=r;
	//		printf("%d%d",x,y);
			
  			glBegin(GL_POINTS);              // Each set of 4 vertices form a quad


		        glColor3f(1.0f, .3f, 0.0f); // Red
			

			while(x<y)
			{


			  if(  ((x+1)*(x+1) + (y-0.5)*(y-0.5) - r*r) < 0 )
				{
					x++;

				}
			  else{
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

   en[i].y += en[i].dir*enemySpeed;
   // Check if the ball exceeds the edges
    if (en[i].y < enYMin) {
      en[i].y = enYMax;
      en[i].x = rand() %1000;


   }
}

}


float drawShip(float x1, float y1)
{			
			float i;
//			float x=0,y=r;

/*
      glBegin(GL_POLYGON);            
                        glColor3f(1.0f, 0.8f, 1.0f); // Red
                        glVertex2f(x1-shipWidth/2,y1-shipHeight/2);
                        glVertex2f(x1+shipWidth/2,y1-shipHeight/2);
                        glVertex2f(x1+shipWidth/2,y1+shipHeight/2);
                        glVertex2f(x1-shipWidth/2,y1+shipHeight/2);
        
                        glEnd();
*/

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
p1[0].x=shipX;//+shipWidth/2;
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

float shX=x1-shipWidth*.1-shipWidth*.02;



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
/*
p1[0].x=shipX; //+shipWidth/2;
p1[0].y=shipY+shipHeight/2;
p1[1].x=shipX; //+shipWidth/2;
p1[1].y=1000;//shipY+shipHeight/2;
p1[2].x=1000;//shipX; //+shipWidth/2;
p1[2].y=1000;//shipY+shipHeight/2;
p1[3].x=1000;//shipX; //+shipWidth/2;
p1[3].y=1000;//shipY+shipHeight/2;
p1[4].x=1000;//shipX; //+shipWidth/2;
p1[4].y=1000;//shipY+shipHeight/2;
*/




}
float drawEnemy()
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
   if (shipX > winXMax) {
      shipX = winXMax;
   } else if (shipX < winXMin) {
      shipX = winXMin;
   }

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
//         shipX=0;
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


//   glVertex2f(winXMin,winYMax);


  // glVertex2f(winXMin,winYMin);
   //glVertex2f(winXMax,winYMin);


   //glVertex2f(winXMax,winYMax);
   glVertex2f(winXMin,winYMax);

   glEnd();
glDisable(GL_BLEND);



}


void drawEnv()
{

    int i;
    for(i=0;i<sunRadius;i++)
//      drawSun(i,sceneX/2,sceneY/2);


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


//   glVertex2f(winXMin,winYMax);


  // glVertex2f(winXMin,winYMin);
   //glVertex2f(winXMax,winYMin);


   //glVertex2f(winXMax,winYMax);
   glVertex2f(winXMin,winYMax);

   glEnd();




}

//GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
 
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
 

//printf("%f\n",ballY);

   glutSwapBuffers(); 


//glFlush();
}
 

void reshape(GLsizei width, GLsizei height) {




   if (height == 0) height = 1;                
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

//   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix

  gluOrtho2D(0, sceneX, 0 , sceneY);
  
   shipXMin = winXMin + ballRadius;
   shipXMax = winXMax - ballRadius;
   shipYMin = winYMin + ballRadius;
   shipYMax = winYMax - ballRadius;
   shipX = ballRadius;
   shipY = winYMax + shipHeight/2;
//printf("to");


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
