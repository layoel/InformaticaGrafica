#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>


void circle(GLfloat radio, GLfloat cx, GLfloat cy, GLint n, GLenum modo){
  float mPI = 3.1416;
  int i;

  if(modo==GL_LINE)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else if (modo==GL_FILL)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

  glBegin(GL_POLYGON);
   for (i=0; i<n;i++)
    glVertex2f(cx+radio*cos(2.0*mPI*i/n), cy+radio*sin(2.0*mPI*i/n));
  glEnd();
}


//numeracion de cuadrantes:
//1|4
//---
//2|3

void semiCircle(GLfloat radio, GLfloat cx, GLfloat cy, GLint n, GLenum modo /*,GLint cuadrante*/){
  float mPI = 3.1416;
  int i;

  if(modo==GL_LINE)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else if (modo==GL_FILL)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

  glBegin(GL_POLYGON);
   for (i=0; i<n;i++){
      float y = cy+radio*sin(2.0*mPI*i/n);
      float x = cx+radio*cos(2.0*mPI*i/n);
      
      /*if(cuadrante ==1)
        if (y>=cy && x<= cx)
          glVertex2f(x, y);
      
      if(cuadrante==2)
        if (y<=cy && x<= cx)
          glVertex2f(x, y);
      
      if(cuadrante==3)  
        if (y<=cy && x>= cx)
          glVertex2f(x, y);
      
      if(cuadrante==4)
        if (y>=cy && x>=cx)
          glVertex2f(x, y);
      */
      if (y<=cy)
          glVertex2f(x, y);
   }
    
  glEnd();
}




void Ejes (int width)
{   
    glLineWidth(width);
    glBegin(GL_LINES);
       glColor3f(1.0,0.0,0.0);
       glVertex3f(-1.0,0.0,0.0);
       glVertex3f(1.0,0.0,0.0);
       glColor3f(0.0,1.0,0.0);
       glVertex3f(0.0,-1.0,0.0);
       glColor3f(1.0,1.0,0.0);
       glVertex3f(0.0,1.0,0.0);   
    glEnd();
   
       
}


void Monigote ()
{
  
 
 
    //sombrero copa
    glColor3f(0.0,0.0,0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.70,0.0);
      glVertex3f(0.2,0.70,0.0);
      glVertex3f(0.2,1.0,0.5);
       glVertex3f(-0.2,1.0,0.5);
    glEnd();   
  //Sombrero ala
   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.3,0.55,0.0);
      glVertex3f(0.3,0.55,0.0);
      glVertex3f(0.3,0.70,0.5);
       glVertex3f(-0.3,0.70,0.5);
    glEnd();
// cara
   glLineWidth(1);
   glColor3f(1.0,0.8,0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 

   glColor3f(0.0,0.0,0.);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd();


  //oreja izq
   glLineWidth(1);
   glColor3f(1.0,0.8,0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.25,0.25,0.0);
      glVertex3f(-0.2,0.25,0.0);
      glVertex3f(-0.2,0.40,0.0);
      glVertex3f(-0.25,0.40,0.0);
   glEnd(); 

   glColor3f(0.0,0.0,0.);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.25,0.25,0.0);
      glVertex3f(-0.2,0.25,0.0);
      glVertex3f(-0.2,0.40,0.0);
      glVertex3f(-0.25,0.40,0.0);
   glEnd(); 

   //oreja derecha
   glLineWidth(1);
   glColor3f(1.0,0.8,0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(0.25,0.25,0.0);
      glVertex3f(0.2,0.25,0.0);
      glVertex3f(0.2,0.40,0.0);
      glVertex3f(0.25,0.40,0.0);
   glEnd(); 

   glColor3f(0.0,0.0,0.);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(0.25,0.25,0.0);
      glVertex3f(0.2,0.25,0.0);
      glVertex3f(0.2,0.40,0.0);
      glVertex3f(0.25,0.40,0.0);
   glEnd(); 

   //nariz
   glLineWidth(1);
   glColor3f(1.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.05,0.25,0.0);
      glVertex3f(0.05,0.25,0.0);
      glVertex3f(0.0,0.35,0.0);
      
   glEnd(); 

   glLineWidth(1);
   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.05,0.25,0.0);
      glVertex3f(0.05,0.25,0.0);
      glVertex3f(0.0,0.35,0.0);
      
   glEnd();

  //ojo izquierdo
   glLineWidth(1);
   glColor3f(0.0,0.0,0.5);
   circle(0.05, -0.09, 0.40, 10, GL_FILL);

    //ojo DERECHO
   glLineWidth(1);
   glColor3f(0.0,0.0,0.5);
   circle(0.05, 0.09, 0.40, 10, GL_FILL);

    //Boca
   glLineWidth(1);
   glColor3f(0.7,0.01,0.0);
   semiCircle(0.1, 0.0, 0.2, 100, GL_FILL/*,2*/);
   //semiCircle(0.1, 0.0, 0.2, 100, GL_FILL/*,3*/);

   //Bigote
    glLineWidth(1);
    glColor3f(0.7,0.0,0.7);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex3f(-0.1,0.2,0.0);
    glVertex3f(0.1,0.2,0.0);
    glVertex3f(0.1,0.24,0.0);
    glVertex3f(-0.1,0.24,0.0); 
    glEnd();
    //semiCircle(0.1, 0.0, 0.2, 100, GL_FILL/*,1*/);
    //semiCircle(0.1, 0.0, 0.2, 100, GL_FILL/*,2*/);

}


static void Init( )
{

   glShadeModel( GL_FLAT);
}


static void Reshape( int width, int height )
{
    glViewport(0, 0, (GLint)width, (GLint)height);
    glOrtho (-1.0, 1.0,-1.0, 1.0, -10, 10.0);
}

static void Display( )
{

  glClearColor(0.5,0.5,0.5,0.0);
  glClear( GL_COLOR_BUFFER_BIT );
   
  
   
   Ejes(6);
   Monigote();
   
   glFlush();
}


static void Keyboard(unsigned char key, int x, int y )
{
 
  if (key==27)
      exit(0);
  if (key=='a'){
    glShadeModel(GL_SMOOTH);
    Display();
  }
  if (key=='b'){
    glShadeModel(GL_FLAT);
    Display();
  }

}



int main( int argc, char **argv )
{
   glutInit(&argc,argv);
   glutInitDisplayMode( GLUT_RGB );

   glutInitWindowPosition( 20, 100 );
   glutInitWindowSize(500, 500 );
   glutCreateWindow("Practica 0 IG");


   Init();

   glutReshapeFunc(Reshape);
   glutDisplayFunc(Display);
   glutKeyboardFunc(Keyboard);
  
   glutMainLoop( );

   return 0;
}

