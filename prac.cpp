/****************************************************************************/
/* Prac. 3A gluPerspective & glFrustum        */
/* use the Lookat function in the display callback to point                 */
/* the viewer                                                               */
/****************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
// OSX systems need their own headers
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif
// Use of degrees is deprecated. Use radians for GLM functions
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <time.h>

#define PI 3.14159265f

GLfloat btnX =0.0;
GLfloat btnY =8.0;
GLfloat btnZ =15.0;
GLfloat theta = 0;
GLfloat transQueenX=0.0;
int reflectionBishop=1;
GLfloat scalingX=0.7;
GLfloat scalingY=0.7;
GLfloat scalingZ=0.7;

void scalingXYZ()
{
  float m[]={
     scalingX,   0.0,   0.0,   0.0,
     0.0,   scalingY,   0.0,   0.0,
     0.0,   0.0,   scalingZ,   0.0,
     0.0,   0.0,   0.0,   1.0};
 glMultMatrixf(m);
}

void scale(float sx, float sy, float sz)
{
  float m[]={
     sx,   0.0,   0.0,   0.0,
     0.0,   sy,   0.0,   0.0,
     0.0,   0.0,   sz,   0.0,
     0.0,   0.0,   0.0,   1.0};
 glMultMatrixf(m);
}

void reflectionXY()
{
  float m[]={
     1.0,   0.0,   0.0,   0.0,
     0.0,   reflectionBishop,   0.0,   0.0,
     0.0,   0.0,   1.0,   0.0,
     0.0,   0.0,   0.0,   1.0};
 glMultMatrixf(m);
}

void matrixTranslationQueenX()
{
  float m[]={
     1.0,   0.0,   0.0,   0.0,
     0.0,   1.0,   0.0,   0.0,
     0.0,   0.0,   1.0,   0.0,
     transQueenX,   0.0,   0.0,   1.0};
 glMultMatrixf(m);
}

void matrixTranslation(float tx,float ty,float tz)
{
  float m[]={
     1.0,   0.0,   0.0,   0.0,
     0.0,   1.0,   0.0,   0.0,
     0.0,   0.0,   1.0,   0.0,
     tx,   ty,   tz,   1.0};
 glMultMatrixf(m);
}

void matrixRotationY()
{
  float m[]={
     cos(theta),   0.0,   sin(theta),   0.0,
     0.0,   1.0,  0.0,   0.0,
     -sin(theta),   0.0,   cos(theta),   0.0,
     0.0,   0.0,   0.0,   1.0};
 glMultMatrixf(m);
}

void matrixRotationZ()
{
  float m[]={
     cos(theta),   sin(theta),   0.0,   0.0,
     -sin(theta),   cos(theta),  0.0,   0.0,
     0.0,   0.0,   1.0,   0.0,
     0.0,   0.0,   0.0,   1.0};
 glMultMatrixf(m);
}

void matrixRotationX()
{
  float m[]={
     1.0,   0.0,   0.0,   0.0,
     0.0,    cos(theta),   -sin(theta),   0.0,
     0.0,   sin(theta),   cos(theta),   0.0,
     0.0,   0.0,   0.0,   1.0};
 glMultMatrixf(m);
}
 
// Global variables
int windowWidth  = 500;     // Initial Screen and viewport width 
int windowHeight = 500;     // Initil Screen and viewport height 

GLfloat windowXMax, windowXMin, windowYMax, windowYMin; // window bounds

// Projection window/clipping/work area
GLdouble windowAreaXLeft, windowAreaXRight, windowAreaYBottom, windowAreaYTop;
 
/* Initialize OpenGL Graphics */
void initGL() 
{
   glClearColor(0.59f, 0.58f, 0.58f,0.50f); // TODO: Set background (clear) color to black
}

 
void draw() // TODO: Create a draw sphere function
{



for(int j=0;j<=100;j=j+2){
    for(int i=0;i<=100;i++){
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0f,0.0f,0.0f);              // Color Red    
        glVertex3f( 1.0f+j, 1.0f+i, -10.0f);    // Top Right Of The Quad (Front)
        glVertex3f(-1.0f+j, 1.0f+i, -10.0f);    // Top Left Of The Quad (Front)
        glVertex3f(-1.0f+j,-1.0f+i, -10.0f);    // Bottom Left Of The Quad (Front)
        glVertex3f( 1.0f+j,-1.0f+i, -10.0f);    // Bottom Right Of The Quad (Front)
        glEnd();

        glBegin(GL_LINE_LOOP);
        glColor3f(1.0f,0.0f,0.0f);              // Color Red    
        glVertex3f( 1.0f-j, 1.0f+i, -10.0f);    // Top Right Of The Quad (Front)
        glVertex3f(-1.0f-j, 1.0f+i, -10.0f);    // Top Left Of The Quad (Front)
        glVertex3f(-1.0f-j,-1.0f+i, -10.0f);    // Bottom Left Of The Quad (Front)
        glVertex3f( 1.0f-j,-1.0f+i, -10.0f);    // Bottom Right Of The Quad (Front)
        glEnd();
    }
}

for(int j=0;j<=100;j++){
    for(int i=0;i<=100;i++){
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0f+j,0.0f,0.0f);          // Color Red    
        glVertex3f(0.0f+j,0.0f, -10.0f+i);    // Top Right Of The Quad (Bottom)
        glVertex3f(-10.0f+j,0.0f, -10.0f+i);    // Top Left Of The Quad (Bottom)
        glVertex3f(-10.0f+j,0.0f,-9.0f+i);    // Bottom Left Of The Quad (Bottom)
        glVertex3f(0.0f+j,0.0f,-9.0f+i);    // Bottom Right Of The Quad (Bottom)
        glEnd();

        glBegin(GL_LINE_LOOP);
        glColor3f(1.0f+j,0.0f,0.0f);          // Color Red    
        glVertex3f(0.0f-j,0.0f, -10.0f+i);    // Top Right Of The Quad (Bottom)
        glVertex3f(-10.0f-j,0.0f, -10.0f+i);    // Top Left Of The Quad (Bottom)
        glVertex3f(-10.0f-j,0.0f,-9.0f+i);    // Bottom Left Of The Quad (Bottom)
        glVertex3f(0.0f-j,0.0f,-9.0f+i);    // Bottom Right Of The Quad (Bottom)
        glEnd();

    }
}

glPushMatrix();
glPushMatrix();
glPushMatrix();
glPushMatrix();
glPushMatrix();
glPushMatrix();
glPushMatrix();
glPushMatrix();
glPushMatrix();
glPushMatrix();

#define BASE 1
glNewList(BASE,GL_COMPILE);
int newAngle=0;
float k=0;
float max = 360.0;
while(k<=max){

    matrixRotationY();
    theta=theta+0.001; 
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.0f, 1.5f);      
        glVertex3f(1.3f, 0.0f, 1.5f); 
        glVertex3f(1.3f, 0.25f, 1.5f);      
        glVertex3f(0.0f, 0.25f, 1.5f);              
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.0f, 1.5f);      
        glVertex3f(1.3f, 0.0f, 1.5f); 
        glVertex3f(1.3f, 0.25f, 1.5f);      
        glVertex3f(0.0f, 0.25f, 1.5f);              
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.25f, 1.5f);      
        glVertex3f(1.0, 0.25f, 1.5f); 
        glVertex3f(1.0, 0.40f, 1.5f);      
        glVertex3f(0.0f, 0.40f, 1.5f);   
    glEnd();
    float f=1;
    for(int i=0;i<=5;i++){
        glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.40f, 1.5f);      
        glVertex3f(f, 0.40f, 1.5f); 
        glVertex3f(f, 0.5f, 1.5f);      
        glVertex3f(0.0f, 0.5f, 1.5f);   
        f=f+0.09;
        glEnd();
    }
    float g=1;
    float h=0.5;
    for(int j=0;j<=50;j++){
        glBegin(GL_QUADS);
        glVertex3f(0.0f, h, 1.5f);      
        glVertex3f(g, h, 1.5f); 
        glVertex3f(g, h+0.01, 1.5f);      
        glVertex3f(0.0f, h+0.01, 1.5f); 
        h=h+0.01;
        g=g-0.01;          
        glEnd();
    }
    for(int j=0;j<=25;j++){
        glBegin(GL_QUADS);
        h=h+0.005;
        glVertex3f(0.0f, h, 1.5f);      
        glVertex3f(g, h, 1.5f); 
        glVertex3f(g, h+0.01, 1.5f);      
        glVertex3f(0.0f, h+0.01, 1.5f); 
        g=g+0.01;          
        glEnd();
    }
    
    
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0,1.0f);    // Color Yellow
    glVertex3f( 0.0f,h,0.0f);    // Top Right Of The Quad (Back)
    glVertex3f(0.0f,h,1.0f);    // Top Left Of The Quad (Back)
    glVertex3f(1.2f,h,1.0f);    // Bottom Left Of The Quad (Back)
    glVertex3f( 1.1f,h,0.0f);    // Bottom Right Of The Quad (Back)
    glEnd();



    k=k+0.01;
}
glEndList();

glPopMatrix();

//BISHOP
#define BISHOP 2
glNewList(BISHOP,GL_COMPILE);
glColor3f(0.0f,0.0f,1.0f); 
float translate=0.01;
float angleBishop =0;
float translateHeadW=-3.6;
float translateHeadH=0.0;
float translateHeadZ=-1.0;
for(int i=0;i<=120;i++){
    glBegin(GL_POLYGON);
    glVertex3f(3.26f+translateHeadW,2.145f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(4.4f+translateHeadW,1.7f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(4.9f+translateHeadW,2.2f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(3.4f+translateHeadW,3.5f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.4f+translateHeadW,3.6f+translateHeadH,1.0f+translateHeadZ);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(2.0f+translateHeadW,0.0f+translateHeadH,1.0f+translateHeadZ);    
    glVertex3f(4.2f+translateHeadW,0.0f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(4.2f+translateHeadW,0.3f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(3.2f+translateHeadW,2.0f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(3.20f+translateHeadW,2.125f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(3.22f+translateHeadW,2.127f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(3.23f+translateHeadW,2.129f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(3.24f+translateHeadW,2.134f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(3.25f+translateHeadW,2.139f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(3.26f+translateHeadW,2.145f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.4f+translateHeadW,3.6f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.3f+translateHeadW,3.57f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.2f+translateHeadW,3.54f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.1f+translateHeadW,3.51f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.15f+translateHeadW,3.48f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.10f+translateHeadW,3.45f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.05f+translateHeadW,3.42f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.00f+translateHeadW,3.39f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.95f+translateHeadW,3.30f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.90f+translateHeadW,3.25f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.85f+translateHeadW,3.20f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.80f+translateHeadW,3.15f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.75f+translateHeadW,3.10f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.70f+translateHeadW,3.05f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.65f+translateHeadW,3.00f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.60f+translateHeadW,2.95f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.55f+translateHeadW,2.90f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.85f+translateHeadW,0.5f+translateHeadH,1.0f+translateHeadZ); 

    glVertex3f(1.40f+translateHeadW,1.2f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.85f+translateHeadW,0.5f+translateHeadH,1.0f+translateHeadZ);

    glVertex3f(1.38f+translateHeadW,1.6f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.80f+translateHeadW,0.9f+translateHeadH,1.0f+translateHeadZ); 

    glVertex3f(1.34f+translateHeadW,2.0f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.75f+translateHeadW,1.4f+translateHeadH,1.0f+translateHeadZ);

    glVertex3f(1.30f+translateHeadW,2.4f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.70f+translateHeadW,1.8f+translateHeadH,1.0f+translateHeadZ); 

    glVertex3f(1.26f+translateHeadW,2.8f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.65f+translateHeadW,2.3f+translateHeadH,1.0f+translateHeadZ); 

    glVertex3f(1.30f+translateHeadW,3.2f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.60f+translateHeadW,2.3f+translateHeadH,1.0f+translateHeadZ); 

    glVertex3f(1.34f+translateHeadW,3.4f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.64f+translateHeadW,2.7f+translateHeadH,1.0f+translateHeadZ);

    glVertex3f(1.45f+translateHeadW,3.5f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.74f+translateHeadW,2.9f+translateHeadH,1.0f+translateHeadZ); 

    glVertex3f(1.62f+translateHeadW,3.6f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.86f+translateHeadW,2.9f+translateHeadH,1.0f+translateHeadZ); 

    glVertex3f(1.74f+translateHeadW,3.6f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(1.98f+translateHeadW,2.9f+translateHeadH,1.0f+translateHeadZ); 

    glVertex3f(1.86f+translateHeadW,3.7f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.11f+translateHeadW,2.9f+translateHeadH,1.0f+translateHeadZ); 

    glVertex3f(2.00f+translateHeadW,3.7f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.19f+translateHeadW,2.9f+translateHeadH,1.0f+translateHeadZ);

    glVertex3f(2.10f+translateHeadW,3.8f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.32f+translateHeadW,2.9f+translateHeadH,1.0f+translateHeadZ);

    glVertex3f(2.22f+translateHeadW,3.8f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.44f+translateHeadW,2.9f+translateHeadH,1.0f+translateHeadZ);

    glVertex3f(2.32f+translateHeadW,3.8f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.54f+translateHeadW,2.9f+translateHeadH,1.0f+translateHeadZ);

    glVertex3f(2.42f+translateHeadW,3.8f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.64f+translateHeadW,2.9f+translateHeadH,1.0f+translateHeadZ);

    glVertex3f(2.52f+translateHeadW,3.8f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.74f+translateHeadW,2.9f+translateHeadH,1.0f+translateHeadZ);

    glVertex3f(2.62f+translateHeadW,3.8f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.84f+translateHeadW,2.9f+translateHeadH,1.0f+translateHeadZ);

    glVertex3f(2.72f+translateHeadW,3.8f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.94f+translateHeadW,2.9f+translateHeadH,1.0f+translateHeadZ);

    glVertex3f(2.82f+translateHeadW,3.7f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(3.04f+translateHeadW,2.9f+translateHeadH,1.0f+translateHeadZ);

    glVertex3f(3.08f+translateHeadW,3.9f,1.0f);
    glVertex3f(3.28f+translateHeadW,2.9f,1.0f);
    glEnd();
    matrixTranslation(0.0f,0.0f,translate);
}    
glEndList();

glPopMatrix();

//Circle
#define CIRCLE 3
glNewList(CIRCLE,GL_COMPILE);
    glColor3f(0.0f,0.0f,1.0f); 
     int nlatitud=200;
     int nlongitud=200;
     int radio=1;
     float inct, incf;
     int i, j;
     float vertice[3];
     inct = 2 * PI / nlatitud;
     incf = PI / nlatitud;
     glBegin( GL_LINE_LOOP );
     for( i = 0; i < nlatitud; i++ )
     {
          
          vertice[0] = vertice[1] = 0;
          vertice[2] =- radio;
          glVertex3fv( vertice );
          for( j = 1; j < nlongitud-1; j++ )
          {
               vertice[0] = radio * cos(i*inct) * cos(j*incf-0.5*PI);
               vertice[1] = radio * sin(i*inct) * cos(j*incf-0.5*PI);
               vertice[2] = radio * sin(j*incf-0.5*PI);
               glVertex3fv( vertice );
               vertice[0] = radio*cos((i+1)*inct)*cos(j*incf-0.5*PI);
               vertice[1] = radio*sin((i+1)*inct)*cos(j*incf-0.5*PI);
               glVertex3fv(vertice);
          }
          vertice[0] = vertice[1] = 0;
          vertice[2] = radio;
          glVertex3fv( vertice );
     }
     glEnd();
glEndList();

//KNIGHT
#define KNIGHT 4
glNewList(KNIGHT,GL_COMPILE);
glCallList(BASE);
float hKnight=1.1;
float iKnight=1.1;
int iK=0;
glColor3f(0.0f,0.0f,1.0f); 
while(iK<=max){
    matrixRotationY();
    glBegin(GL_QUADS);
        glVertex3f(0.0f, hKnight+2.8, 0.0f);      
        glVertex3f(0.7, hKnight+2.8, 0.0f); 
        glVertex3f(0.7, hKnight, 1.0f);      
        glVertex3f(0.0f, hKnight, 1.0f);   
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(0.0f, hKnight+2.8, 0.0f);      
        glVertex3f(0.7, hKnight+2.8, 0.0f); 
        glVertex3f(0.7, hKnight+0.3+2.8, 1.0f);      
        glVertex3f(0.0f, hKnight+0.3+2.8, 1.0f);   
    glEnd();
    iK++;
    theta=theta+0.001;  
}
    matrixTranslation(0.0f,5.0f,0.0);
    glCallList(CIRCLE);
glEndList();

glPopMatrix();

//KING
#define QUEEN 5
glNewList(QUEEN,GL_COMPILE);
glCallList(BASE);
float hKing =1.1;
float iKing =1.1;
int iKng =0;
glColor3f(0.0f,0.0f,1.0f); 
while(iKng<=max){
    matrixRotationY();
    glBegin(GL_QUADS);
        glVertex3f(0.0f, hKing +2.8, 0.0f);      
        glVertex3f(0.7, hKing +2.8, 0.0f); 
        glVertex3f(0.7, hKing, 1.0f);      
        glVertex3f(0.0f, hKing, 1.0f);   
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(0.0f, hKing +2.8, 0.0f);      
        glVertex3f(0.7, hKing +2.8, 0.0f); 
        glVertex3f(0.7, hKing +0.3+2.8, 1.0f);      
        glVertex3f(0.0f, hKing +0.3+2.8, 1.0f);   
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(0.0f, hKing +2.8+0.3*2, 0.0f);      
        glVertex3f(0.7, hKing +2.8+0.3*2, 0.0f); 
        glVertex3f(0.7, hKing, 1.0f);      
        glVertex3f(0.0f, hKing, 1.0f);   
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(0.0f, hKing +0.3+2.8, 0.0f);      
        glVertex3f(0.7, hKing +0.3+2.8, 0.0f); 
        glVertex3f(0.7, hKing +0.3+3.1, 1.0f);      
        glVertex3f(0.0f, hKing +0.3+3.1, 1.0f);   
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(0.0f, hKing +2.8+0.3*5, 0.0f);      
        glVertex3f(0.7, hKing +2.8+0.3*5, 0.0f); 
        glVertex3f(0.7, hKing, 1.0f);      
        glVertex3f(0.0f, hKing, 1.0f);   
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(0.0f, hKing +2.8+0.3*5, 0.0f);      
        glVertex3f(0.7, hKing +2.8+0.3*5, 0.0f); 
        glVertex3f(0.7, hKing +2.8+0.3*5+0.3, 1.0f);      
        glVertex3f(0.0f, hKing +2.8+0.3*5+0.3, 1.0f);   
    glEnd();    
    iKng++;
    theta=theta+0.001;  
}
    scale(0.5,0.5,0.5);
    matrixTranslation(0.0f,12.0,0.0);
    glCallList(CIRCLE);
glEndList();

glPopMatrix();        
matrixTranslation(6.0f,0.0,0.0);  
reflectionXY();      
glCallList(BISHOP);

glPopMatrix();  
matrixTranslationQueenX();
glCallList(QUEEN);

glPopMatrix();
matrixTranslation(-8.0f,0.0f,0.0);
scalingXYZ();
glCallList(KNIGHT);






} 
/* Callback handler for window re-paint event */
void display() 
{
      
   glClear (GL_COLOR_BUFFER_BIT); /* TODO: clear screen */
   glMatrixMode(GL_MODELVIEW);    // TODO: To operate on the model-view matrix
   glLoadIdentity();              // TODO: Reset model-view matrix
      
   gluLookAt(btnX,btnY,btnZ, 0.0,0.0,0.0, 0.0,1.0,0.0);      //TODO: Define camera settings
    
   //glColor3f(0.0f, 0.0f, 1.0f);  // TODO: Set the color of the object
   /* Draw a sphere */
   draw();        // TODO: Draw a Sphere, test using different primitives polygon/square/triangle/line STRIP/ what is the difference?, what does it happen with filled color?
   
   glFlush ();                   //TODO: Render Object
}
 
/* Call back when the windows is re-sized */
void reshape(GLsizei width, GLsizei height) {
   // Compute aspectRatio ratio of the new window
   GLfloat aspectRatio = (GLfloat)width / (GLfloat)height; //Compute aspect ratio
    
   glViewport(0, 0, width, height);  // Set the viewport to cover the new screen size
 
   // Set the aspectRatio ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // TODO: To operate on the Projection matrix
   glLoadIdentity();             // TODO: Reset the projection matrix
   if (width >= height) {
      windowAreaXLeft   = -windowWidth * aspectRatio;
      windowAreaXRight  = windowWidth * aspectRatio;
      windowAreaYBottom = -windowHeight;
      windowAreaYTop    = windowHeight;
   } else {
      windowAreaXLeft   = -windowWidth;
      windowAreaXRight  = windowWidth;
      windowAreaYBottom = -windowHeight / aspectRatio;
      windowAreaYTop    = windowHeight / aspectRatio;
   }
   
   //Adjust vision cone
   //gluOrtho2D(windowAreaXLeft, windowAreaXRight, windowAreaYBottom, windowAreaYTop);
   //glFrustum(0.0,10.0,0.0,10.0,5.0,500.0); 
   
   gluPerspective(90.0, GLfloat(width) / GLfloat(height), 0.5, 200.0); //   Define the shape of your viewing volume using glFrustum function 
    
   //Save new windowXMin, windowXMax, windowYMin, windowYMax (or called left, right, bottom, top respectively)
   windowXMin = windowAreaXLeft;
   windowXMax = windowAreaXRight;
   windowYMin = windowAreaYBottom;
   windowYMax = windowAreaYTop;
}
 
void mykey(unsigned char key, int x, int y)
{
	switch ( key )
  {
    case 27: // Escape key
      exit (0);
  }
	if(key == 'Q'){
        transQueenX=transQueenX+0.1;
    };

    if(key == 'q'){
        transQueenX=transQueenX-0.1;
    };

    if(key == 'B' | key == 'b'){
        reflectionBishop=reflectionBishop*(-1);
    };

    if(key == 'W' | key == 'w'){
        btnY=btnY-1.0f;
    };

    if(key == 'E' | key == 'e'){
        btnY=btnY+1.0f;
    };

    if(key == 'J' | key == 'j'){    
        btnX=btnX-1.0f;
    };

    if(key == 'L' | key == 'l'){
        btnX=btnX+1.0f;
    };    
       
    if(key == 'I' | key == 'i'){
        btnZ=btnZ-1.0f;
    };

    if(key == 'k' | key == 'k'){
        btnZ=btnZ+1.0f;
    };  

    if(key == 's' ){
        scalingX=scalingX-0.1;
        scalingY=scalingY-0.1;
        scalingZ=scalingZ-0.1;
        
    };
    if(key == 'S'){
        scalingX=scalingX+0.1;
        scalingY=scalingY+0.1;
        scalingZ=scalingZ+0.1;
        
    };   

    if(key == 'd' | key == 'D'){
        theta=theta-0.1;
    };          
    display();

}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
   glutCreateWindow("CHESS");      // Create window with given title
   glutDisplayFunc(display);     // Register callback handler for window re-paint
   glutReshapeFunc(reshape);     // Register callback handler for window re-shape
   glutKeyboardFunc(mykey);   		/* TODO keyboard callback invoked when mouse is used */
   initGL();                     // Our own OpenGL initialization
   glutMainLoop();               // Enter event-processing loop
   return 1;
}
