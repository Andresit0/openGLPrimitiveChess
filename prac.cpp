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
// Definition chess pieces
#define BASE 1
#define BISHOP 2
#define CIRCLE 3
#define KNIGHT 4
#define QUEEN 5
#define KING 6
#define PAWN 7
#define ROOK 8
#define CROSS 9
#define BASEROOK 10
#define HEAD 11


GLfloat btnX =0.0;
GLfloat btnY =8.0;
GLfloat btnZ =15.0;
GLfloat btnX2=0.0;
GLfloat btnY2=1.0;
GLfloat theta = 0;
GLfloat beta = 0.0;
GLfloat gama = 0.0;
GLfloat shxy = 0.0f;
GLfloat transQueenX=0.0;
int reflectionBishop=1;
float max = 360.0;
GLfloat scalingX=0.7;
GLfloat scalingY=0.7;
GLfloat scalingZ=0.7;
GLfloat rookZ = 0.0;

// Transformations
void shear()
{
  float m[]={
     1.0,   0,  0.0, 0.0,
     shxy,  1.0,   0.0, 0.0,
     0.0,   0.0,    1.0, 0.0,
     0.0,   0.0,    0.0, 1.0};
 glMultMatrixf(m);
}

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

// Translation matrix with respect to x, y and z
void matrixTranslation(float tx,float ty,float tz)
{
  float m[]={
     1.0,   0.0,   0.0,   0.0,
     0.0,   1.0,   0.0,   0.0,
     0.0,   0.0,   1.0,   0.0,
     tx,   ty,   tz,   1.0};
 glMultMatrixf(m);
}

void matrixTranslationZ()
{
  float m[]={
     1.0,   0.0,   0.0,   0.0,
     0.0,   1.0,   0.0,   0.0,
     0.0,   0.0,   1.0,   0.0,
     0.0,   0.0,   rookZ,   1.0};
 glMultMatrixf(m);
}

void matrixRotationY()
{
  float m[]={
     cos(theta),   0.0,   -sin(theta),   0.0,
     0.0,   1.0,  0.0,   0.0,
     sin(theta),   0.0,   cos(theta),   0.0,
     0.0,   0.0,   0.0,   1.0};
 glMultMatrixf(m);
}


void rotationScenaY()
{
  float m[]={
     cos(beta),   0.0,   -sin(beta),   0.0,
     0.0,   1.0,  0.0,   0.0,
     sin(beta),   0.0,   cos(beta),   0.0,
     0.0,   0.0,   0.0,   1.0};
 glMultMatrixf(m);
}

void matrixRotationZ()
{
  float m[]={
     cos(gama),   sin(gama),   0.0,   0.0,
     -sin(gama),   cos(gama),  0.0,   0.0,
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
 

void grid(void){
    
    for(int i=0;i<=7;i++){

        for(int j=0;j<=7;j++){
            if(i%2>0){
                if( j%2 > 0 ){
                    glColor3f(1.0f,1.0f,1.0f); 
                }else{
                    glColor3f(0.0f,0.0f,0.0f); 
                } 
            }else{
                if( j%2 == 0 ){
                    glColor3f(1.0f,1.0f,1.0f); 
                }else{
                    glColor3f(0.0f,0.0f,0.0f); 
                }
            }
                       
            glBegin(GL_QUADS);                         
            glVertex3f(-20.0f+j*4.3,0.0f, -20.0f+i*4.3);    
            glVertex3f(-15.7f+j*4.3,0.0f, -20.0f+i*4.3);    
            glVertex3f(-15.7+j*4.3,0.0f, -15.7f+i*4.3);   
            glVertex3f(-20.0f+j*4.3,0.0f, -15.7f+i*4.3);    
            glEnd();
        }
    }    
} 

void drawBishop(void){
glColor3f(0.0f,0.0f,1.0f); 
float translate=0.01;
float angleBishop =0;
float translateHeadW=-3.6; //Start position in X
float translateHeadH=0.0;  //Start alture of figure
float translateHeadZ=-1.0; //Start z postion of figure
for(int i=0;i<=120;i++){

    //Horne of horse

    glBegin(GL_POLYGON);
    glVertex3f(3.26f+translateHeadW,2.145f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(4.4f+translateHeadW,1.7f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(4.9f+translateHeadW,2.2f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(3.4f+translateHeadW,3.5f+translateHeadH,1.0f+translateHeadZ);
    glVertex3f(2.4f+translateHeadW,3.6f+translateHeadH,1.0f+translateHeadZ);
    glEnd();

    //Superface of horse

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

    //Hair of the horse

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
}

//
void drawKnight(void){
glCallList(BASE);
float hKnight=1.1;
float iKnight=1.1;
int iK=0;
glColor3f(0.0f,0.0f,1.0f); 
while(iK<=max){
    matrixRotationY();

    //Principal Cone
    glBegin(GL_QUADS);
        glVertex3f(0.0f, hKnight+2.8, 0.0f);      
        glVertex3f(0.7, hKnight+2.8, 0.0f); 
        glVertex3f(0.7, hKnight, 1.0f);      
        glVertex3f(0.0f, hKnight, 1.0f);   
    glEnd();

    //Ring
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
}

//Queen draw
void drawQueen(void){
float hKing = 1.0f;
float iKing = 1.1;
int iKng = 0;

glCallList(BASE);
while(iKng <= max){
    matrixRotationY();

    //Principal cone
    glBegin(GL_QUADS);
        glVertex3f(0.0f, hKing +5.8, 0.0f);      
        glVertex3f(0.5, hKing +5.8, 0.0f); 
        glVertex3f(0.9, hKing, 0.1f);      
        glVertex3f(0.0f, hKing, 0.1f);   
    glEnd();

    //Down ring
    glBegin(GL_QUADS);
        glVertex3f(0.0f, hKing +3.9, 0.0f);      
        glVertex3f(0.7, hKing +3.9, 0.0f); 
        glVertex3f(0.7, hKing +4.3, 0.8f);      
        glVertex3f(0.0f, hKing +4.3, 0.8f);   
    glEnd();

    //Midle ring
    glBegin(GL_QUADS);
        glVertex3f(0.0f, hKing +4.2, 0.0f);      
        glVertex3f(0.7, hKing +4.2, 0.0f); 
        glVertex3f(0.7, hKing +3.9, 0.8f);      
        glVertex3f(0.0f, hKing +3.9, 0.8f);   
    glEnd();

    //App ring
   glBegin(GL_QUADS);
        glVertex3f(0.0f, hKing +3.2, 0.0f);      
        glVertex3f(1.3, hKing +3.2, 0.0f); 
        glVertex3f(1.3, hKing +3.5, 0.0f);      
        glVertex3f(0.0f, hKing +3.5, 0.0f);   
    glEnd();

    //Up cone
    glBegin(GL_QUADS);
        glVertex3f(0.0f, hKing +5.8, 0.0f);      
        glVertex3f(1.2, hKing +5.8, 0.0f); 
        glVertex3f(0.7, hKing+4.3, 0.1f);      
        glVertex3f(0.0f, hKing+4.3, 0.1f);   
    glEnd();

    iKng++;
    theta=theta+0.001;  
}
   //Top sphere 
   matrixTranslation(0.0f,7.0,0.0);
    scale(0.5,0.5,0.5);
    glCallList(CIRCLE);
    
    
}


void drawBase(void){

int newAngle=0;
float k=0;
while(k<=max){

    matrixRotationY();
    theta = theta+0.001; 

     glColor3f(0.0,0.0,1.0);
//  glColor3ub( (char) rand()%256, (char) rand()%256, (char) rand()%256);
// Bottom Part
    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.0f, 1.5f);      
        glVertex3f(1.3f, 0.0f, 1.5f); 
        glVertex3f(1.3f, 0.25f, 1.5f);      
        glVertex3f(0.0f, 0.25f, 1.5f);              
    glEnd();
/*
	 glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.0f, 1.5f);      
        glVertex3f(1.3f, 0.0f, 1.5f); 
        glVertex3f(1.3f, 0.25f, 1.5f);      
        glVertex3f(0.0f, 0.25f, 1.5f);              
    glEnd();
*/
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
// glColor3f(1.0,0.0,0.0);

// Part cone upsidedown (like blocks)
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

// Part cone 
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
    
// Top of the base
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0,1.0f);    
    glVertex3f( 0.0f,h,0.0f);    
    glVertex3f(0.0f,h,1.0f);    
    glVertex3f(1.2f,h,1.0f);    
    glVertex3f( 1.1f,h,0.0f);    
    glEnd();
	

    k=k+0.01;
	}
}

// Function to draw the base rook
void drawBaseTower(void){

int newAngle=0;
float k=0;
while(k<=max){

    matrixRotationY();
    theta = theta+0.001; 

     glColor3f(0.0,0.0,1.0);
	
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

// glColor3f(1.0,0.0,0.0);

// Part cone upsidedown (like blocks)
    float g=1;
    float h=0.5;

    for(int j=0;j<=50;j++){

        glBegin(GL_QUADS);
        glVertex3f(0.0f, h, 1.5f);      
        glVertex3f(g, h, 1.5f); 
        glVertex3f(g, h+0.015, 1.5f);      
        glVertex3f(0.0f, h+0.015, 1.5f); 
        h=h+0.015;
        g=g-0.015;          
        glEnd();

    }

// Top of the base

    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0,1.0f);    
    glVertex3f( 0.0f,h,0.0f);    
    glVertex3f(0.0f,h,1.0f);    
    glVertex3f(1.2f,h,1.0f);    
    glVertex3f( 1.1f,h,0.0f);    
    glEnd();
	

    k=k+0.01;
	}

}
// Function to draw the king cross
void drawCross(void){

float translate=0.01;
float h = 0, g = 0;
	for(int i=0;i<=2000;i++){
	// glColor3f((char) rand()%256, (char) rand()%256, (char) rand()%256);
	glColor3f(0.0f,0.0f,1.0f);
    glBegin(GL_QUADS);
	glVertex3f( 0.0f,h,0.0f); 
	glVertex3f( 0.3f,h,0.0f); 
	glVertex3f( 0.3f,h,0.5f); 
	glVertex3f( 0.0f,h,0.5f); 
	glEnd();

		h = h + 0.0006;
	}

	
	for(int j=0;j<=1200;j++){
	
    glBegin(GL_POLYGON);

	glVertex3f( 0.0f, g + 0.3, -0.3f); 
	glVertex3f( 0.3f, g + 0.3, -0.3f); 
	glVertex3f( 0.3f, g + 0.3, 0.8f); 
	glVertex3f( 0.0f, g + 0.3, 0.8f); 
	glEnd();

		g = g + 0.0006;
	}
}
// Function to draw the sphere
void drawSphere(void){
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
}

// Function to draw the rook
void drawTower(void){
float k = 0.0f;
float hTower = 1.3f;

glPushMatrix();
scale(0.9, 0.9, 0.9);
glCallList(BASEROOK);
glPopMatrix();

while(k<=max){

    matrixRotationY();
    theta = theta+0.001; 
    glBegin(GL_LINE_LOOP);

		
		glVertex3f(0.0f,hTower + 3.5f, 0.0f);
		glVertex3f(1.1f,hTower + 3.5f, 0.0f);

		glVertex3f(1.1f,hTower + 2.7f, 0.0f);
		glVertex3f(0.8f,hTower + 2.7f, 0.0f);
		
		
		glVertex3f(0.8f,hTower + 2.5f, 0.0f);
		glVertex3f(0.7f,hTower + 2.5f, 0.0f);
		glVertex3f(1.3f,hTower + 0.0f, 0.0f);
		glVertex3f(0.0f,hTower + 0.0f, 0.0f);
             
    glEnd();
    k=k+0.01;     
}
}

// Function to draw the pawn
void drawPawn(void){

float k = 0.0f;
float hPawn = 1.1f;

glPushMatrix();
scale(0.8, 0.8, 0.8);
glCallList(BASE);
glPopMatrix();

glPushMatrix();
matrixTranslation(0.0f,3.5f,0.0f);
glCallList(HEAD);
glPopMatrix();

glPushMatrix();

matrixTranslation(0.0f,5.8f,0.0f);
scale(0.35, 0.35, 0.35);
glCallList(CIRCLE);
glPopMatrix();


while(k<=max){

    matrixRotationY();
    theta = theta+0.001; 
    glBegin(GL_LINE_LOOP);

		glVertex3f(0.0f,hPawn + 2.5f, 0.0f);
		glVertex3f(1.1f,hPawn + 2.5f, 0.0f);
		glVertex3f(0.9f,hPawn + 2.5f, 0.0f);
		glVertex3f(0.8f,hPawn + 2.5f, 0.0f);
		glVertex3f(0.8f,hPawn + 2.3f, 0.0f);
		glVertex3f(1.0f,hPawn + 2.3f, 0.0f);
		glVertex3f(1.0f,hPawn + 2.1f, 0.0f);

		glVertex3f(1.3f,hPawn + 2.1f, 0.0f);
		glVertex3f(1.3f,hPawn + 1.9f, 0.0f);
		
		
		glVertex3f(0.5f,hPawn + 1.9f, 0.0f);
		glVertex3f(0.7f,hPawn + 0.3f, 0.0f);
		glVertex3f(1.2f,hPawn + 0.0f, 0.0f);
		glVertex3f(0.0f,hPawn + 0.0f, 0.0f);
             
    glEnd();
    k=k+0.01;    
 
}

}


// Function to draw the pawn head
void drawHeadPawn(void){
float rx= 0.7, ry=2.1, rz= 0.7;
float nlatitude = 10, nlongitude = 10;
float varSlicesLatitude = PI/ (2*nlatitude);
float varSlicesLongitude = (2*PI) / nlongitude;
float vertex[3];
for(int i =0; i<= nlatitude ; i++){
		glColor3f(0.0f,0.0f,1.0f);
		glBegin(GL_TRIANGLE_STRIP);
	for(int j =0; j<= nlongitude ; j++){
			vertex[0] = rx*cos((i+1)*varSlicesLatitude) * cos(j*varSlicesLongitude);
			vertex[1] = ry*sin((i+1)*varSlicesLatitude);			
			vertex[2] = rz*cos((i+1)*varSlicesLatitude) * sin(j*varSlicesLongitude);
			
			
			glVertex3fv(vertex);
			vertex[0] = rx*cos((i)*varSlicesLatitude) * cos(j*varSlicesLongitude);
			vertex[1] = ry*sin((i)*varSlicesLatitude );			
			vertex[2] = rz*cos((i)*varSlicesLatitude) * sin(j*varSlicesLongitude);
			
			glVertex3fv(vertex);
		}
		glEnd();
}


}

// Function to draw the king
void drawKing(void){

glPushMatrix();
glTranslatef(0.0f,6.5f,0.0f);

glCallList(CROSS);
glPopMatrix();

float k = 0.0f;
float hking = 1.1f;


glCallList(BASE);
while(k<=max){

    matrixRotationY();
    theta = theta+0.001; 
    glBegin(GL_LINE_LOOP);

		glVertex3f(0.6f,hking+5.2f ,0.0f);  
        glVertex3f(0.6f,hking+5.4f ,0.0f);      
        glVertex3f(0.6f,hking+ 5.2f, 0.0f);
        glVertex3f(1.1f,hking+ 5.2f, 0.0f);
        glVertex3f(0.7f,hking+ 3.8f, 0.0f);
        glVertex3f(0.9f,hking+ 3.8f, 0.0f);
        glVertex3f(0.9f,hking+ 3.6f, 0.0f);
        glVertex3f(0.7f,hking+ 3.6f, 0.0f);
		glVertex3f(0.7f,hking+ 3.3f, 0.0f);
		glVertex3f(1.0f,hking+ 3.3f, 0.0f);

		glVertex3f(1.0f,hking+ 3.1f, 0.0f);
		glVertex3f(1.3f,hking+ 3.1f, 0.0f);
		
		
		glVertex3f(1.3f,hking+ 2.9f, 0.0f);
		glVertex3f(0.5f,hking+ 2.9f, 0.0f);
		glVertex3f(0.8f,hking+ 0.0f, 0.0f);
		glVertex3f(0.0f,hking+ 0.0f, 0.0f);
             
    glEnd();
    k=k+0.01;     
}
}

// Create the list to all the six pieces
void createList(void){

    glNewList(BISHOP,GL_COMPILE);
    drawBishop();
    glEndList();

    glNewList(KNIGHT,GL_COMPILE);
    drawKnight();
    glEndList();

    glNewList(QUEEN, GL_COMPILE);	
	drawQueen();
	glEndList();

	// King piece
    glNewList(KING, GL_COMPILE);	
	drawKing();
	glEndList();

	glNewList(BASE,GL_COMPILE);
	drawBase();
	glEndList();

	// Sphere to queen and pawn
	glNewList(CIRCLE,GL_COMPILE);
	drawSphere();
	glEndList();

	// King cross
	glNewList(CROSS,GL_COMPILE);
	drawCross();
	glEndList();

	// Base Rook
	glNewList(BASEROOK,GL_COMPILE);
	drawBaseTower();
	glEndList();

	// Rook piece
    glNewList(ROOK,GL_COMPILE);
	drawTower();
	glEndList();

	// Pawn piece
	glNewList(PAWN,GL_COMPILE);
	drawPawn();
	glEndList();

	// Head pawn
	glNewList(HEAD, GL_COMPILE);
	drawHeadPawn();
	glEndList();

}

void DrawAxis(void){
    glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(250.0, 0.0, 0.0); 
        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex3f(-250.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);


        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0, 250.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glColor3f(0.0f, 0.3f, 0.0f);
        glVertex3f(0.0, -250.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);


        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0, 0.0, 250.0);
        glVertex3f(0.0, 0.0, 0.0);
        glColor3f(0.0f, 0.0f, 0.3f);
        glVertex3f(0.0, 0.0, -250.0);
        glVertex3f(0.0, 0.0, 0.0);
    glEnd();
}


void drawSixPieces(){
   //KING
	glPushMatrix();
    matrixTranslation(-9.0f,0.0f,0.0);
   // Transformation used is rotation in Z
	matrixRotationZ();
    glCallList(KING);  
	glPopMatrix();   	
  
    //BISHOP
	glPushMatrix();       
    matrixTranslation(4.0f,0.0,0.0);  
    //Reflection XY
    reflectionXY();      
    glCallList(BISHOP);
    glPopMatrix();

    //QUEEN
    glPushMatrix(); 
	matrixTranslation(-1.0f,0.0f,0.0);
    //Translation in X
    matrixTranslationQueenX();
    glCallList(QUEEN);
    glPopMatrix();

    //KNIGHT
    glPushMatrix();
    matrixTranslation(-5.0f,0.0f,0.0);
    //Scaling in XYZ
    scalingXYZ();
    glCallList(KNIGHT);
    glPopMatrix();

    //ROOK
	glPushMatrix();
	matrixTranslation(8.0f,0.0f,0.0);
	// Transformation used is translation in Z
	matrixTranslationZ();
	glCallList(ROOK);
	glPopMatrix(); 

	// PAWN
	glPushMatrix();
	matrixTranslation(12.0f,0.0f,0.0);
	// Transformation used is shear x with respect to y
	shear();
	glCallList(PAWN);
	glPopMatrix(); 
}

//Keyboard  options
void printInformation(void){
    puts("To move the camera in y. Please press r or f key \n"
    "To move the camera in x. Please press w or e key \n"
    "To move the camera in z. Please press d or c key \n"
    "To apply reflection at bishop. Please press b or B key \n"
    "To apply rotation at king. Please press k or K key \n"
    "To apply scaling  at knight. Please press n or N key \n"
    "To apply shear at pawn. Please press p or P key \n"
    "To apply translation in X at queen. Please press q or Q key \n"
    "To apply translation in Z at rook. Please press t or T key \n"
    "Press 5 to top view \n"
    "Press 2 to front view\n"
    "Press 8 to back view \n"
    "Press 4 to left view \n"
    "Press 6 to right view \n"
    "Press 7 and 9 to rotate all\n");
}

/* Initialize OpenGL Graphics */
void initGL() 
{
   glClearColor(0.58f, 0.58f, 0.58f,1.0f); // TODO: Set background (clear) color to gray
   createList();
   printInformation();	
}

/* Callback handler for window re-paint event */
void display() 
{
      
   glClear (GL_COLOR_BUFFER_BIT); /* TODO: clear screen */
   glMatrixMode(GL_MODELVIEW);    // TODO: To operate on the model-view matrix
   glLoadIdentity();              // TODO: Reset model-view matrix
      
   gluLookAt(btnX,btnY,btnZ, 0.0,0.0,0.0, btnX2,btnY2,0.0);      //TODO: Define camera settings
   
	// Draw axis	
	DrawAxis();

	// Scene rotation
   rotationScenaY();
   
   // Draw the grid  
   grid();
  
  // Draw pieces
   drawSixPieces();

   glFlush ();               
}
 
/* Call back when the windows is re-sized */
void reshape(GLsizei width, GLsizei height) {
   // Compute aspectRatio ratio of the new window
   GLfloat aspectRatio = (GLfloat)width / (GLfloat)height; //Compute aspect ratio
    
   glViewport(0, 0, width, height);  // Set the viewport to cover the new screen size
 
   // Set the aspectRatio ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset the projection matrix
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
   
   gluPerspective(90.0, GLfloat(width) / GLfloat(height), 0.5, 200.0); //   Define the shape of your viewing volume using glFrustum function 
    
   //Save new windowXMin, windowXMax, windowYMin, windowYMax (or called left, right, bottom, top respectively)
   windowXMin = windowAreaXLeft;
   windowXMax = windowAreaXRight;
   windowYMin = windowAreaYBottom;
   windowYMax = windowAreaYTop;
}
 
void mykey(unsigned char key, int x, int y)
{
	

    //rotate all
	if(key == '7'){
        beta=beta+0.1;
    };

    //rotate all
	if(key == '9'){
        beta=beta-0.1;
    };

    //up view
	if(key == '5'){
        beta=0.0;
        btnX =0.0;
        btnY =30.0;
        btnZ =0.0;
        btnX2=1.0;
        btnY2=0.0;
    };

    //front view
	if(key == '2'){
        
        btnX =0.0;
        btnY =5.0;
        btnZ =30.0;
        btnX2=0.0;
        btnY2=1.0;
    };

    //back view
	if(key == '8'){
      
        btnX =0.0;
        btnY =5.0;
        btnZ =-30.0;
        btnX2=0.0;
        btnY2=1.0;
    };

    //left view
	if(key == '4'){
       
        btnX =-30.0;
        btnY =5.0;
        btnZ =0.0;
        btnX2=0.0;
        btnY2=1.0;
    };

    //right view
	if(key == '6'){
        beta=0.0;
        btnX =30.0;
        btnY =5.0;
        btnZ =0.0;
        btnX2=0.0;
        btnY2=1.0;
    };
	display();
    for(int k = 0 ; k < 4 ; k++){

    if(key == 'Q'){
        transQueenX=transQueenX+0.1;
    };
    if(key == 'q'){
        transQueenX=transQueenX-0.1;
    };

    //Transformation to Bishop
    if(key == 'B' | key == 'b'){
        reflectionBishop=reflectionBishop*(-1);
    };

    // Move in the y negative direction
    if(key == 'F' | key == 'f'){
        btnY=btnY-1.0f;
    };

	// Move in the y positive direction
    if(key == 'R' | key == 'r'){
        btnY=btnY+1.0f;
    };
	// Move in the x negative direction
    if(key == 'W' | key == 'w'){    
        btnX=btnX-1.0f;
    };
	// Move in the x positive direction
    if(key == 'E' | key == 'e'){
        btnX=btnX+1.0f;
    };    
     // Move in the z negative direction
    if(key == 'D' | key == 'd'){
        btnZ=btnZ-1.0f;
    };
	// Move in the z positive direction
    if(key == 'C' | key == 'c'){
        btnZ=btnZ+1.0f;
    };   

    if(key == 'n' ){
        scalingX=scalingX-0.1;
        scalingY=scalingY-0.1;
        scalingZ=scalingZ-0.1;      
    };

    //Transformation knight
    if(key == 'N'){
        scalingX=scalingX+0.1;
        scalingY=scalingY+0.1;
        scalingZ=scalingZ+0.1;
        
    };   

	// When the key t is pressed it is applied the transformation to the rook
	if(key == 't' | key == 'T'){
		rookZ = rookZ + 1.0f;	
	}

	// When the key k is pressed it is applied the transformation to the king
	if(key == 'k' | key == 'K'){
		gama = gama - 0.05;
	};  

	// When the key p is pressed it is applied the transformation to the pawn
	if(key == 'P' | key == 'p'){
		shxy = shxy + 0.1;
	};       
 	
	display();
}
  

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
