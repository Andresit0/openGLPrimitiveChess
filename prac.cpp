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

void matrixRotation()
{
  float m[]={
     cos(theta),   sin(theta),   0.0,   0.0,
     -sin(theta),   cos(theta),  0.0,   0.0,
     0.0,   0.0,   1.0,   0.0,
     0.0,   0.0,   0.0,   1.0};
 glMultMatrixf(m);
}

void matrixRotation2()
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

 
void draw(float radio, int nlatitud , int nlongitud) // TODO: Create a draw sphere function
{

glPushMatrix();

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


//matrixRotation();

int newAngle=0;
float k=0;
float max = 360.0;
while(k<=max){

    glRotatef(newAngle += k, 0.0f, 1.0f, 0.0f);
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

    glPopMatrix();

    glBegin(GL_POLYGON);
    glVertex3f(2.0f,0.0f,1.0f);    // Color Yellow
    glVertex3f(4.2f,0.0f,1.0f);
    glVertex3f(4.2f,0.3f,1.0f);
    glVertex3f(3.2f,2.0f,1.0f);
    glVertex3f(3.20f,2.125f,1.0f);
    glVertex3f(3.22f,2.127f,1.0f);
    glVertex3f(3.23f,2.129f,1.0f);
    glVertex3f(3.24f,2.134f,1.0f);
    glVertex3f(3.25f,2.139f,1.0f);
    glVertex3f(3.26f,2.145f,1.0f);
    glVertex3f(2.4f,3.6f,1.0f);
    glVertex3f(2.3f,3.57f,1.0f);
    glVertex3f(2.2f,3.54f,1.0f);
    glVertex3f(2.1f,3.51f,1.0f);
    glVertex3f(2.15f,3.48f,1.0f);
    glVertex3f(2.10f,3.45f,1.0f);
    glVertex3f(2.05f,3.42f,1.0f);
    glVertex3f(2.00f,3.39f,1.0f);
    glVertex3f(1.95f,3.30f,1.0f);
    glVertex3f(1.90f,3.25f,1.0f);
    glVertex3f(1.85f,3.20f,1.0f);
    glVertex3f(1.80f,3.15f,1.0f);
    glVertex3f(1.75f,3.10f,1.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(3.26f,2.145f,1.0f);
    glVertex3f(4.4f,1.7f,1.0f);
    glVertex3f(4.9f,2.2f,1.0f);
    glVertex3f(3.4f,3.5f,1.0f);
    glVertex3f(2.4f,3.6f,1.0f);
    glEnd();

     
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
   draw(50.0,200,100);        // TODO: Draw a Sphere, test using different primitives polygon/square/triangle/line STRIP/ what is the difference?, what does it happen with filled color?
   
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
	if(key == 'Q' | key == 'q') exit(0);

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

    if(key == 's' | key == 'S'){
        theta=theta+0.1;
        
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
   glutCreateWindow("Prac 3B");      // Create window with given title
   glutDisplayFunc(display);     // Register callback handler for window re-paint
   glutReshapeFunc(reshape);     // Register callback handler for window re-shape
   glutKeyboardFunc(mykey);   		/* TODO keyboard callback invoked when mouse is used */
   initGL();                     // Our own OpenGL initialization
   glutMainLoop();               // Enter event-processing loop
   return 1;
}