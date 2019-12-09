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


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY,CILINDROX, CILINDROZ, ROTACION, CONO, ESFERA, ARTICULADO, POLLITO} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;


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
bool iluminar=false;
float ang = 0.0;
int material_elegido = 0;

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
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
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

void draw_objects()
{
  _vertex4f ambiente_1(0.05, 0.0, 0.0, 1.0);
  _vertex4f esp_1({0.7, 0.04, 0.04, 1.0});

  _vertex4f ambiente_2(0.24725, 0.2245, 0.0645, 1.0);
  _vertex4f esp_2(0.797357, 0.723991, 0.208006, 1.0);

  _vertex4f ambiente_3(0.2215, 0.2745, 0.2215, 0.7);
  _vertex4f esp_3(0.133, 0.227811, 0.133, 0.35);

  _vertex4f materiales[3][2]={
		    {ambiente_1,esp_1},
		    {ambiente_2,esp_2},
		    {ambiente_3,esp_3}
	};

switch (t_objeto){
	case CUBO: 
		cubo.ambiente_difusa = materiales[material_elegido ][0];
    	cubo.especular = materiales[material_elegido ][1];
		cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
		break;
	case PIRAMIDE: 
		piramide.ambiente_difusa = materiales[material_elegido ][0];
    	piramide.especular = materiales[material_elegido ][1];
		piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
    case OBJETO_PLY: 
    	ply.ambiente_difusa = materiales[material_elegido ][0];
    	ply.especular = materiales[material_elegido ][1];
    	ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
    case CILINDROX: 
    	ply1.ambiente_difusa = materiales[material_elegido ][0];
    	ply1.especular = materiales[material_elegido ][1];
    	ply1.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
    case CILINDROZ: 
    	ply2.ambiente_difusa = materiales[material_elegido ][0];
    	ply2.especular = materiales[material_elegido ][1];
    	ply2.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
    case ROTACION: 
    	rotacion.ambiente_difusa = materiales[material_elegido ][0];
    	rotacion.especular = materiales[material_elegido ][1];
    	rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
    case CONO: 
    	cono.ambiente_difusa = materiales[material_elegido ][0];
    	cono.especular = materiales[material_elegido ][1];
    	cono.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case ESFERA: 
		esfera.ambiente_difusa = materiales[material_elegido ][0];
    	esfera.especular = materiales[material_elegido ][1];
		esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case ARTICULADO: 
		tanque.ambiente_difusa = materiales[material_elegido ][0];
    	tanque.especular = materiales[material_elegido ][1];
		tanque.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2);break;
	case POLLITO: 
		pollo.ambiente_difusa = materiales[material_elegido ][0];
    	pollo.especular = materiales[material_elegido ][1];
		pollo.draw(modo,0.0,0.0,0.0,0.0,1.0,0.0,2);break;
	}

}

void luz(float ang) {
	if(iluminar){
		GLfloat posicion[4] = {0.0, -5.0, 1.0, 1.0};
		GLfloat ambiente[4] = {0.2,0.2,0.2,1.0};
		GLfloat	intensidad[4] = {1.0,1.0,1.0,1.0};

		glLightfv(GL_LIGHT0, GL_POSITION, posicion);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, intensidad);
		glLightfv(GL_LIGHT0, GL_SPECULAR, intensidad);

		GLfloat posicion1[4] = {10.0, 0.0, 1.0, 1.0};
		GLfloat ambiente1[4] = {0.0,0.0,0.5,1.0};
		GLfloat	intensidad1[4] = {1.0,1.0,1.0,1.0};

		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(ang,0,1,0);
		glLightfv(GL_LIGHT1, GL_POSITION, posicion1);
		glPopMatrix();
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, intensidad1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, intensidad1);

	}else{
		glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
	}
}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{

clean_window();
change_observer();
luz(ang);
draw_axis();
draw_objects();
glutSwapBuffers();
pollo.animarPollito();
}




//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
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
		case '1':modo = POINTS;break;
		case '2':modo = EDGES;break;
		case '3':modo = SOLID;break;
		case '4':modo = SOLID_CHESS;break;
		case '5': if (iluminar) 
					iluminar = false; 
				else 
					iluminar = true;
		break;
		case '6':modo = SOLID_ILLUMINATED_FLAT;break;
		case '7':modo = SOLID_ILLUMINATED_GOURAUD;break;
		
		break;
	    case 'A':t_objeto = PIRAMIDE;break;
	    case 'S':t_objeto = CUBO;break;
	    case 'D':t_objeto = OBJETO_PLY;break;	
	    case 'F':t_objeto = ROTACION;break; //CILINDRO ROTANDO EN EJE Y
	    case 'G':t_objeto = CONO;break;
		case 'H':t_objeto = ESFERA;break;
		case 'J':t_objeto = CILINDROX;break;
		case 'K':t_objeto = CILINDROZ;break;
		case 'L':t_objeto = ARTICULADO;break;
		case 'W':t_objeto = POLLITO;break;
		case 'P':ang+=5;break;

		case 'Z': material_elegido = 0;break;
		case 'X': material_elegido = 1;break;
		case 'C': material_elegido = 2;break;
		break;

		
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
		//case GLUT_KEY_F1:tanque.giro_tubo+=1;
        //             if (tanque.giro_tubo>tanque.giro_tubo_max) tanque.giro_tubo=tanque.giro_tubo_max;
         //            break;
    	case GLUT_KEY_F2:tanque.giro_tubo-=1;
                     if (tanque.giro_tubo<tanque.giro_tubo_min) tanque.giro_tubo=tanque.giro_tubo_min;
                     break;
	    case GLUT_KEY_F3:tanque.giro_torreta+=5;break;
	    case GLUT_KEY_F4:tanque.giro_torreta-=5;break;

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

	// se inicalizan la ventana y los planos de corte
	Size_x=0.5;
	Size_y=0.5;
	Front_plane=1;
	Back_plane=1000;

	// se incia la posicion del observador, en el eje z
	Observer_distance=4*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

	// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1,1,1,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	change_projection();
	glViewport(0,0,Window_width,Window_high);
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
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 3 Elvira Castillo");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

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
