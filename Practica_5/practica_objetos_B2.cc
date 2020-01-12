//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B2.h"
#include "stdlib.h"
#include "stdio.h"

#if !defined(GLUT_WHEEL_UP)
#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4
#endif

using namespace std;


// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY,CILINDROX, CILINDROZ, ROTACION, CONO, ESFERA, ARTICULADO, POLLITO} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;
int estadoRaton[3], xc, yc, modo_selec[13], cambio = 0;
int vista_multiple = 0;
int Ancho =450, Alto = 450;
float factor = 1.0;
float anterior_xn;
int numCara;

struct color{
	double r;
	double g;
	double b;
};
void pick_color(int x, int y);


// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=450,UI_window_height=450;


// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply;
_objeto_ply  ply1;
_objeto_ply  ply2;
_rotacion rotacion; 
_cono cono(1.0,1.0,40);
_esfera esfera(1.0,30,30);
_tanque tanque;
_pollito pollo;

_tronco cuerpo;
_cabeza cabeza;
_piramide pico;
_ala alitaD, alitaI;
_pata pataD, pataI;

color cuerpoc,pico1c,pico2c,pico3c,pico4c,pico5c,pico6c, cabezac, alitaDc, alitaIc, pataDc, pataIc;
double rojo, verde, azul;
float giro_alaD;
float giro_alaI;
float giro_cabeza;
float giro_cabeza_min;
float giro_cabeza_max;
float giro_ala_min;
float giro_ala_max;
float giro_patas;
float giro_pata_max;
float giro_pata_min;
float giracuerpo;
float giramax;
float giramin;
// _objeto_ply *ply1;


//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{
	// posicion del observador
	change_projection();
	glViewport(0,0,Ancho,Alto);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-Observer_distance);
	glRotatef(Observer_angle_x,1,0,0);
	glRotatef(Observer_angle_y,0,1,0);
}

void clickRaton(int boton, int estado, int x, int y){

	if(boton == GLUT_RIGHT_BUTTON){
		if(estado == GLUT_DOWN){

			estadoRaton[2] = 1;
			xc = x;
			yc = y;
		}else{
			estadoRaton[2] = 1;
		}

	}
	if(boton == GLUT_LEFT_BUTTON){
		if(estado == GLUT_DOWN){

			estadoRaton[2] = 2;
			xc = x;
			yc = y;
			//cout << "los valores de xc "<< xc <<" yc "<<yc<<endl;
			pick_color(xc,yc);
		}
	}
	if(estado == GLUT_UP){
		if(boton == GLUT_WHEEL_UP){

			Observer_distance *= 1.2;
		}else if(boton == GLUT_WHEEL_DOWN){
			Observer_distance /= 1.2;
		}
		glutPostRedisplay();

	}

}

void getCamara(GLfloat *x, GLfloat * y){
	*x = Observer_angle_y;
	*y = Observer_angle_x;

}

void setCamara(GLfloat x, GLfloat y){

	Observer_angle_y = x;
	Observer_angle_x = y;
}


void RatonMovido( int x, int y ){
  float x0, y0, xn, yn; 
  if(estadoRaton[2]==1) { //click dereho raton
        // Perspectiva: mueve los angulos de la camara
        if(vista_multiple==0){      
          getCamara(&x0,&y0);
          yn=y0+(y-yc);
          xn=x0-(x-xc);
          setCamara(xn,yn);
          xc=x;
          yc=y;
          glutPostRedisplay();
        }else{
         //Planta: Zoom
          getCamara(&x0,&y0);
          xn=x0-(x-xc);
          
          if(anterior_xn >= xn)
            Observer_distance+=0.05;
          else
            Observer_distance-=0.05;

          anterior_xn = xn;
          glutPostRedisplay();
        }
	}
}
//**************************************************************************
// Funciones para la selección
//***************************************************************************

void procesar_color(unsigned char color[3]){
	int i, numCara=0;
	//cout<< "entro aqui"<<endl;
//cout <<"el color de p[0] es "<< (int)color[0] <<endl;
 switch (color[0]){

      	case 100: cout << "cuerpo" <<endl;
      		i=1;
                 if (modo_selec[0] == 0){
                      modo_selec[0] = 1;
                      cambio = 1;
                 }
                 else {
                      modo_selec[0] = 0;
                      cambio = 0;
                 }
                 break; 
        case 120: cout << "cabeza" <<endl;
        	i=2;
                 if (modo_selec[1] == 0){
                      modo_selec[1] = 1;
                      cambio = 1;
                 }
                 else {
                      modo_selec[1] = 0;
                      cambio = 0;
                 }
                  break;
         case 140: cout << "pico1" <<endl;
            i=3;
            numCara = 0;
                 if (modo_selec[2] == 0){
                      modo_selec[2] = 1;
                      cambio = 1;
                 }
                 else {
                      modo_selec[2] = 0;
                      cambio = 0;
                 }
                  break; 
        case 141: cout << "pico2" <<endl;
            i=4;
            numCara = 1;
                 if (modo_selec[3] == 0){
                      modo_selec[3] = 1;
                      cambio = 1;
                 }
                 else {
                      modo_selec[3] = 0;
                      cambio = 0;
                 }
                  break; 
        case 142: cout << "pico3" <<endl;
            i=5;
            numCara = 2;
                 if (modo_selec[4] == 0){
                      modo_selec[4] = 1;
                      cambio = 1;
                 }
                 else {
                      modo_selec[4] = 0;
                      cambio = 0;
                 }
                  break;
        case 143: cout << "pico4" <<endl;
            i=6;
            numCara=3;
                 if (modo_selec[5] == 0){
                      modo_selec[5] = 1;
                      cambio = 1;
                 }
                 else {
                      modo_selec[5] = 0;
                      cambio = 0;
                 }
                  break; 
        case 144: cout << "pico5" <<endl;
            i=7;
            numCara=4;
                 if (modo_selec[6] == 0){
                      modo_selec[6] = 1;
                      cambio = 1;
                 }
                 else {
                      modo_selec[6] = 0;
                      cambio = 0;
                 }
                  break; 
        case 145: cout << "pico6" <<endl;
            i=8;
            numCara=5;
                 if (modo_selec[7] == 0){
                      modo_selec[7] = 1;
                      cambio = 1;
                 }
                 else {
                      modo_selec[7] = 0;
                      cambio = 0;
                 }
                  break;    
        case 160: cout << "alitaD" <<endl;
            i=9;
                 if (modo_selec[8] == 0){
                      modo_selec[8] = 1;
                      cambio = 1;
                 }
                 else {
                      modo_selec[8] = 0;
                      cambio = 0;
                 }
                  break;
        case 180: cout << "alitaI" <<endl;
            i=10;
                 if (modo_selec[9] == 0){
                      modo_selec[9] = 1;
                      cambio = 1;
                 }
                 else {
                      modo_selec[9] = 0;
                      cambio = 0;
                 }
                  break;
        case 200: cout << "pataD" <<endl;
            i=11;
                 if (modo_selec[10] == 0){
                      modo_selec[10] = 1;
                      cambio = 1;
                 }
                 else {
                      modo_selec[10] = 0;
                      cambio = 0;
                 }
                  break;
        case 220: cout << "pataI" <<endl;
            i=12;
                 if (modo_selec[11] == 0){
                      modo_selec[11] = 1;
                      cambio = 1;
                 }
                 else {
                      modo_selec[11] = 0;
                      cambio = 0;
                 }
                  break;
              
        }    


        if (cambio==1) 
        	switch(i){
        		case 1:
        			cuerpoc.r = 0.3;
        			cuerpoc.g = 0.9;
        			cuerpoc.b = 0.3;
        		break;
        		case 2:
        			cabezac.r = 0.3;
        			cabezac.g = 0.9;
        			cabezac.b = 0.3;
        		break;
        		case 3:
        			pico1c.r = 0.3;
        			pico1c.g = 0.9;
        			pico1c.b = 0.3;
        		break;
        		case 4:
        			pico2c.r = 0.3;
        			pico2c.g = 0.9;
        			pico2c.b = 0.3;
        		break;
        		case 5:
        			pico3c.r = 0.3;
        			pico3c.g = 0.9;
        			pico3c.b = 0.3;
        		break;
        		case 6:
        			pico4c.r = 0.3;
        			pico4c.g = 0.9;
        			pico4c.b = 0.3;
        		break;
        		case 7:
        			pico5c.r = 0.3;
        			pico5c.g = 0.9;
        			pico5c.b = 0.3;
        		break;
        		case 8:
        			pico6c.r = 0.3;
        			pico6c.g = 0.9;
        			pico6c.b = 0.3;
        		break;
        		case 9:
        			alitaDc.r = 0.3;
        			alitaDc.g = 0.9;
        			alitaDc.b = 0.3;
        		break;
        		case 10:
        			alitaIc.r = 0.3;
        			alitaIc.g = 0.9;
        			alitaIc.b = 0.3;
        		break;
        		case 11:
        			pataDc.r = 0.3;
        			pataDc.g = 0.9;
        			pataDc.b = 0.3;
        		break;
        		case 12:
        			pataIc.r = 0.3;
        			pataIc.g = 0.9;
        			pataIc.b = 0.3;
        		break;
        	}    

       	if (cambio==0) 
        	switch(i){
        		case 1:
        			cuerpoc.r = 0.9;
        			cuerpoc.g = 0.6;
        			cuerpoc.b = 0.2;
        		break;
        		case 2:
        			cabezac.r = 0.9;
        			cabezac.g = 0.6;
        			cabezac.b = 0.2;
        		break;
        		case 3:
        			pico1c.r = 0.9;
        			pico1c.g = 0.6;
        			pico1c.b = 0.2;
        		break;
        		case 4:
        			pico2c.r = 0.9;
        			pico2c.g = 0.6;
        			pico2c.b = 0.2;
        		break;
        		case 5:
        			pico3c.r = 0.9;
        			pico3c.g = 0.6;
        			pico3c.b = 0.2;
        		break;
        		case 6:
        			pico4c.r = 0.9;
        			pico4c.g = 0.6;
        			pico4c.b = 0.2;
        		break;
        		case 7:
        			pico5c.r = 0.9;
        			pico5c.g = 0.6;
        			pico5c.b = 0.2;
        		break;
        		case 8:
        			pico6c.r = 0.9;
        			pico6c.g = 0.6;
        			pico6c.b = 0.2;
        		break;
        		case 9:
        			alitaDc.r = 0.9;
        			alitaDc.g = 0.6;
        			alitaDc.b = 0.2;
        		break;
        		case 10:
        			alitaIc.r = 0.9;
        			alitaIc.g = 0.6;
        			alitaIc.b = 0.2;
        		break;
        		case 11:
        			pataDc.r = 0.9;
        			pataDc.g = 0.6;
        			pataDc.b = 0.2;
        		break;
        		case 12:
        			pataIc.r = 0.9;
        			pataIc.g = 0.6;
        			pataIc.b = 0.2;
        		break;
        	}    

}

void pick_color(int x, int y){
	GLint viewport[4];
	unsigned char pixel[3];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadBuffer(GL_BACK);
	glReadPixels(x,viewport[3]-y,1,1,GL_RGB, GL_UNSIGNED_BYTE, (GLubyte *)&pixel[0]);
	int r = pixel[0];
	int g = pixel[1];
	int b = pixel[2];

	cout << "valor x " << x << " valor y " << y << " color " << r << " " << g << " " << b << endl;
	
	procesar_color(pixel);
	glutPostRedisplay();
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects(){

switch (t_objeto){
	case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
    case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
    case CILINDROX: ply1.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
    case CILINDROZ: ply2.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
    case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
    case CONO: cono.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case ESFERA: esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case ARTICULADO: tanque.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2);break;
	case POLLITO: 
		glPushMatrix();
	  //para poner el pollito en posicion inicial con el tamaño que quepa en pantalla
	    glRotatef(30,1,0,0);
	    glScalef(0.4,0.4,0.4);

	    glPushMatrix();
	      glRotatef(giracuerpo,1,0,0);
	      
	      glPushMatrix();
	      cuerpo.draw(EDGES, 0,0,0, 0.0, 0.0, 0.0, 3);
	      cuerpo.draw(SOLID, cuerpoc.r, cuerpoc.g, cuerpoc.b, 0.0, 0.0, 0.0, 3);
	      glPopMatrix();
	      
	      //cabeza   
	 
	      glPushMatrix();
	      glRotatef(giro_cabeza,0,1,0);
	      cabeza.draw(EDGES, 0,0,0, 0.0, 0.0, 0.0, 3);
	      cabeza.draw(SOLID, cabezac.r, cabezac.g, cabezac.b, 0.0, 0.0, 0.0, 3);
	      glPopMatrix();
	      //pico*/

	      glPushMatrix();
	        glTranslatef(0.0,2.5,1.0);
	        glRotatef(90.0,1,0,0);
	        glScalef(0.5,1.0,0.5);
	        pico.draw(EDGES, 0,0,0, 0.0, 0.0, 0.0, 3);
	       // cout<<"en el draw_objects "<<pico1c.r<<" "<<pico1c.g<< " "<<pico1c.b<<endl;
	        
	        pico.draw(CARA, pico1c.r, pico1c.g, pico1c.b, 0.0, 0.0, 0.0, 0);
	        pico.draw(CARA, pico2c.r, pico2c.g, pico2c.b, 0.0, 0.0, 0.0, 1);
	        pico.draw(CARA, pico3c.r, pico3c.g, pico3c.b, 0.0, 0.0, 0.0, 2);
	        pico.draw(CARA, pico4c.r, pico4c.g, pico4c.b, 0.0, 0.0, 0.0, 3);
	        pico.draw(CARA, pico5c.r, pico5c.g, pico5c.b, 0.0, 0.0, 0.0, 4);
	        pico.draw(CARA, pico6c.r, pico6c.g, pico6c.b, 0.0, 0.0, 0.0, 5);
	      	pico.draw(SOLID, 0.9,0.6,0.2,0,0,0,3);
	      glPopMatrix();

	    //alas
	      glPushMatrix();
	      glRotatef(giro_alaD,1,0,0);
	      glTranslatef(1.5,-0.5,0.0);
	      
	      glRotatef(20,0,0,1);
	      alitaD.draw(EDGES, 0,0,0, 0.0, 0.0, 0.0, 3);
	      alitaD.draw(SOLID, alitaDc.r, alitaDc.g, alitaDc.b, 0.0, 0.0, 0.0, 3);
	      glPopMatrix();
	      
	      glPushMatrix();
	      
	      glRotatef(giro_alaI,1,0,0);
	      glTranslatef(-1.5,-0.5,0.0);
	      glRotatef(-20,0,0,1);
	      alitaI.draw(EDGES, 0,0,0, 0.0, 0.0, 0.0, 3);
	      alitaI.draw(SOLID, alitaIc.r, alitaIc.g, alitaIc.b, 0.0, 0.0, 0.0, 3);
	      glPopMatrix();
	    glPopMatrix();
	      //patas
	      glPushMatrix();
	        glTranslatef(0.5,-1.0,0.0);
	        glRotatef(giro_patas,1,0,0);
	        pataD.draw(EDGES, 0,0,0, 0.0, 0.0, 0.0, 3);
	        pataD.draw(SOLID, pataDc.r, pataDc.g, pataDc.b, 0.0, 0.0, 0.0, 3);
	      glPopMatrix();

	      glPushMatrix();
	        glTranslatef(-0.5,-1.0,0.0);
	        glRotatef(giro_patas,1,0,0);
	        pataI.draw(EDGES, 0,0,0, 0.0, 0.0, 0.0, 3);
	        pataI.draw(SOLID, pataIc.r, pataIc.g, pataIc.b, 0.0, 0.0, 0.0, 3);
	      glPopMatrix();


	    glPopMatrix();
	 break;
	}
}

void draw_objects_seleccion(){
	int inc=0;
	glPushMatrix();
	  //para poner el pollito en posicion inicial con el tamaño que quepa en pantalla
	    glRotatef(30,1,0,0);
	    glScalef(0.4,0.4,0.4);

	    glPushMatrix();
	      glRotatef(giracuerpo,1,0,0);
	      
	      glPushMatrix();
	      cuerpo.draw(SELEC, 100, 100, 100,0,0,0,1);
	      glPopMatrix();
	       inc+=20;
	      
	      //cabeza   
	 
	      glPushMatrix();
	      glRotatef(giro_cabeza,0,1,0);
	      cabeza.draw(SELEC, 100+inc, 100+inc, 100+inc,0,0,0,1);
	      glPopMatrix();
	      inc+=20; 

	      //pico
	      glPushMatrix();
	        glTranslatef(0.0,2.5,1.0);
	        glRotatef(90.0,1,0,0);
	        glScalef(0.5,1.0,0.5);

	        pico.draw(SELEC_CARA, 140, 140, 140,0, 0, 0,numCara);

	      glPopMatrix();
	      inc+=20;

	    //alas
	      glPushMatrix();
	      glRotatef(giro_alaD,1,0,0);
	      glTranslatef(1.5,-0.5,0.0);
	      
	      glRotatef(20,0,0,1);
	      alitaD.draw(SELEC, 100+inc, 100+inc, 100+inc,0,0,0,1);
	      glPopMatrix();
	      inc+=20;

	      glPushMatrix();
	      
	      glRotatef(giro_alaI,1,0,0);
	      glTranslatef(-1.5,-0.5,0.0);
	      glRotatef(-20,0,0,1);
	      alitaI.draw(SELEC, 100+inc, 100+inc, 100+inc,0,0,0,1);
	      glPopMatrix();
	      inc+=20;

	    glPopMatrix();
	      //patas
	      glPushMatrix();
	        glTranslatef(0.5,-1.0,0.0);
	        glRotatef(giro_patas,1,0,0);
	        pataD.draw(SELEC, 100+inc, 100+inc, 100+inc,0,0,0,1);
	      glPopMatrix();
	      inc+=20;

	      glPushMatrix();
	        glTranslatef(-0.5,-1.0,0.0);
	        glRotatef(giro_patas,1,0,0);
	        pataI.draw(SELEC, 100+inc, 100+inc, 100+inc,0,0,0,1);
	      glPopMatrix();


	    glPopMatrix();

}

//**************************************************************************
//
//***************************************************************************

void draw(void)
{

	if(vista_multiple == 0){

		clean_window();
		change_observer();
		draw_axis();
		draw_objects();

		glDrawBuffer(GL_BACK);
		clean_window();
		change_observer();
		draw_objects_seleccion();
		glDrawBuffer(GL_FRONT);

		glFlush();
		
	}else{
		//vista alzado
		clean_window();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(Observer_distance*-1.0,Observer_distance*1.0,Observer_distance*-1.0,Observer_distance*1.0,-100.0,100.0);
		glViewport(0,0,Ancho,Alto);
		glRotatef(90,1,0,0);
		glScalef(factor,factor,1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		draw_axis();
		draw_objects();

		glFlush();
	}
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1){
	change_projection();
	Ancho = Ancho1;
	Alto = Alto1;
	draw();
}


//***************************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y){

	switch (toupper(Tecla1)){
		case 'Q':exit(0);
		case '1':modo=POINTS;break;
		case '2':modo=EDGES;break;
		case '3':modo=SOLID;break;
		case '4':modo=SOLID_CHESS;break;

	    case 'A':t_objeto=PIRAMIDE;break;
	    case 'S':t_objeto=CUBO;break;
	    case 'D':t_objeto=OBJETO_PLY;break;	
	    case 'F':t_objeto=ROTACION;break; //CILINDRO ROTANDO EN EJE Y
	    case 'G':t_objeto=CONO;break;
		case 'H':t_objeto=ESFERA;break;
		case 'J':t_objeto=CILINDROX;break;
		case 'K':t_objeto=CILINDROZ;break;
		case 'L':t_objeto=ARTICULADO;break;
		case 'W':t_objeto=POLLITO;break;
		case '+': factor*=0.9;break;
		case '-': factor*=1.1;break;
		
	}
	glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y){

	switch (Tecla1){
		case GLUT_KEY_LEFT:Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;break;
		case GLUT_KEY_UP:Observer_angle_x--;break;
		case GLUT_KEY_DOWN:Observer_angle_x++;break;
		case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
		case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
		case GLUT_KEY_F1:vista_multiple=1;break;
    	case GLUT_KEY_F2:vista_multiple=0;break;
	    case GLUT_KEY_F5:pollo.giro_alaD+=1;
			if (pollo.giro_alaD > pollo.giro_ala_max) 
				pollo.giro_alaD = pollo.giro_ala_max;
			break;
		case GLUT_KEY_F6:pollo.giro_alaD-=1;
			if (pollo.giro_alaD < pollo.giro_ala_min) 
				pollo.giro_alaD = pollo.giro_ala_min;
			break;
		case GLUT_KEY_F7:pollo.giro_alaI+=1;
			if (pollo.giro_alaI > pollo.giro_ala_max) 
				pollo.giro_alaI = pollo.giro_ala_max;
			break;
		case GLUT_KEY_F8:pollo.giro_alaI-=1;
			if (pollo.giro_alaI < pollo.giro_ala_min) 
				pollo.giro_alaI = pollo.giro_ala_min;
			break;
		case GLUT_KEY_F9:pollo.giro_cabeza+=1;
			if (pollo.giro_cabeza > pollo.giro_cabeza_max) 
				pollo.giro_cabeza = pollo.giro_cabeza_max;
			break;
		case GLUT_KEY_F10:pollo.giro_cabeza-=1;
			if (pollo.giro_cabeza < pollo.giro_cabeza_min) 
				pollo.giro_cabeza = pollo.giro_cabeza_min;
			break;
		case GLUT_KEY_F11:pollo.giro_patas+=1;
			if (pollo.giro_patas > pollo.giro_pata_max) 
				pollo.giro_patas = pollo.giro_pata_max;
			break;
		case GLUT_KEY_F12:pollo.giro_patas-=1;
			if (pollo.giro_patas < pollo.giro_pata_min) 
				pollo.giro_patas = pollo.giro_pata_min;
			break;
		case GLUT_KEY_HOME:
			if(pollo.animar)
				pollo.animar=false;
			else pollo.animar=true;
			break;
		case GLUT_KEY_INSERT:pollo.giracuerpo+=1;
		    if (pollo.giracuerpo > pollo.giramax) 
				pollo.giracuerpo = pollo.giramax;
			break;
		case GLUT_KEY_END:pollo.giracuerpo-=1;
		    if (pollo.giracuerpo < pollo.giramin) 
				pollo.giracuerpo = pollo.giramin;
			break;
		}
	glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void) {

	//valores del pollito para los movimientos:
	giro_alaD = 0;
	giro_alaI = 0;
	giro_ala_min= 0;
	giro_ala_max= 40;
	giro_cabeza = 0;
	giro_cabeza_min= -60;
	giro_cabeza_max= 60;
	giro_patas = -30;
	giro_pata_min= -70;
	giro_pata_max = 15;
	giracuerpo = 20;
	giramax = 25;
	giramin = 0;

	cabezac.r = 0.9;
	cabezac.g = 0.6;
	cabezac.b = 0.2;
	cuerpoc.r = 0.9;
	cuerpoc.g = 0.6;
	cuerpoc.b = 0.2;
	alitaDc.r = 0.9;
	alitaDc.g = 0.6;
	alitaDc.b = 0.2;
	alitaIc.r = 0.9;
	alitaIc.g = 0.6;
	alitaIc.b = 0.2;
	pataIc.r = 0.9;
	pataIc.g = 0.6;
	pataIc.b = 0.2;
	pataDc.r = 0.9;
	pataDc.g = 0.6;
	pataDc.b = 0.2;
	pico1c.r = 0.9;
	pico1c.g = 0.6;
	pico1c.b = 0.2;
	pico2c.r = 0.9;
	pico2c.g = 0.6;
	pico2c.b = 0.2;
	pico3c.r = 0.9;
	pico3c.g = 0.6;
	pico3c.b = 0.2;
	pico4c.r = 0.9;
	pico4c.g = 0.6;
	pico4c.b = 0.2;
	pico5c.r = 0.9;
	pico5c.g = 0.6;
	pico5c.b = 0.2;
	pico6c.r = 0.9;
	pico6c.g = 0.6;
	pico6c.b = 0.2;
	rojo = 0.9;
	verde = 0.6;
	azul = 0.2;

	// se inicalizan la ventana y los planos de corte
	Size_x=0.5;
	Size_y=0.5;
	Front_plane=1;
	Back_plane=1000;

	// se incia la posicion del observador, en el eje z
	Observer_distance=3*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

	// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1,1,1,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	change_projection();
	glViewport(0,0,UI_window_width,UI_window_height);

	for (int i=0; i<13; i++){
		modo_selec[i]=0;
	}
	glutPostRedisplay();
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char *argv[] )
{
 

vector<_vertex3f> perfil; 
_vertex3f aux;

/*ala*/
/*
	aux.x=0.3;aux.y=3.0;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=0.6;aux.y=2.9;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=0.8;aux.y=2.7;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.1;aux.y=2.4;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.4;aux.y=2.0;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.5;aux.y=1.5;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.4;aux.y=1.0;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=0.6;aux.y=-1.0;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=0.4;aux.y=-1.5;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=0.3;aux.y=-2.0;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=0.1;aux.y=-3.5;aux.z=0.0;
	perfil.push_back(aux);
*/
	

//*
aux.x=0.5;aux.y=3.5;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=0.8;aux.y=3.3;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.0;aux.y=3.0;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.15;aux.y=2.7;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.10;aux.y=2.4;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.0;aux.y=2.1;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=0.7;aux.y=1.9;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=0.9;aux.y=1.6;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.1;aux.y=1.3;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.25;aux.y=1.0;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.35;aux.y=0.7;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.45;aux.y=0.25;aux.z=0.0;
	perfil.push_back(aux);
	
	aux.x=1.55;aux.y=-0.0;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.65;aux.y=-0.5;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.6;aux.y=-1.0;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.5;aux.y=-1.5;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.4;aux.y=-2.05;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=1.2;aux.y=-2.3;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=0.7;aux.y=-2.5;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=0.6;aux.y=-2.6;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=0.3;aux.y=-2.7;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=0.25;aux.y=-5.0;aux.z=0.0;
	perfil.push_back(aux);

	aux.x=0.1;aux.y=-5.5;aux.z=0.0;
	perfil.push_back(aux);
//*/
rotacion.parametros(perfil,20, 'y');
///************************************///
/// cilindro generado rotanto en Y     ///
///************************************///

/*/ DESCOMENTAR PARA PROBAR
aux.x=1.0; aux.y=1.0; aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.0; aux.y=-1.0; aux.z=0.0;
perfil2.push_back(aux);

rotacion.parametros(perfil2,20, 'y');
/*/


///************************************///
/// cilindro generado rotanto en X     ///
///************************************///

/*/ DESCOMENTAR PARA PROBAR
aux.x=-1.0; aux.y=0.0; aux.z=1.0;
perfil2.push_back(aux);
aux.x=1.0; aux.y=0.0; aux.z=1.0;
perfil2.push_back(aux);

rotacion.parametros(perfil2,20, 'x');
/*/



///************************************///
/// cilindro generado rotanto en Z     ///
///************************************///

/*/ DESCOMENTAR PARA PROBAR
aux.x=1.0; aux.y=0.0; aux.z=-1.0;
perfil2.push_back(aux);
aux.x=1.0; aux.y=0.0; aux.z=1.0;
perfil2.push_back(aux);

rotacion.parametros(perfil2,20, 'z');
//*/


///************************************///
/// JARRON generado rotanto en x       ///
///************************************///

/*/ DESCOMENTAR PARA PROBAR

//*
aux.x= 0.6; aux.y=-3.0; aux.z=0.0;
perfil2.push_back(aux);
aux.x= 0.8; aux.y=-2.7; aux.z=0.0;
perfil2.push_back(aux);
aux.x= 1.2; aux.y=-2.4; aux.z=0.0;
perfil2.push_back(aux);
aux.x= 1.4; aux.y=-2.0; aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.5; aux.y=-1.5; aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.4; aux.y=-1.0; aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.6; aux.y=1.0; aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4; aux.y=1.5; aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.35; aux.y=2.0; aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.8; aux.y=2.6; aux.z=0.0;
perfil2.push_back(aux);

rotacion.parametros(perfil2,20, 'y');
//*/





// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 5 Elvira Castillo");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);
//eventos del raton
glutMouseFunc(clickRaton);
glutMotionFunc(RatonMovido);

// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);// el jarron
//ply1 = new _objeto_ply(argv[2]);
ply1.parametros(argv[2]);// el cilindro en X
//ply2 = new _objeto_ply(argv[3]);
ply2.parametros(argv[3]); // el cilindro en Z

//ply1 = new _objeto_ply(argv[1]);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
