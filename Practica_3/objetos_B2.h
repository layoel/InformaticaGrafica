//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
	void 	draw_aristas(float r, float g, float b, int grosor);
	void    draw_solido(float r, float g, float b);
	void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);

};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1, char eje
	);
void comprobar(vector<_vertex3f> perfil, char eje);

vector<_vertex3f> perfil; 
int num;
};

//************************************************************************
// clase objeto cono
//************************************************************************

class _cono: public _triangulos3D
{
private:
	vector<_vertex3f> perfil; 
	int num;
	float radio;
	float altura;
public:
	_cono(float radio, float altura,int num);
	void parametros(vector<_vertex3f> perfil);

};

//************************************************************************
// clase objeto esfera
//************************************************************************

class _esfera: public _triangulos3D
{
private:
	vector<_vertex3f> perfil; 
	int longitud;
	int latitud;
	float radio;
	void crearPerfil();

public:
	_esfera(float radio2, int longitud2,int latitud2);
	void parametros();

};

//************************************************************************
// objeto articulado: tanque
//************************************************************************

class _chasis: public _triangulos3D
{
public:
       _chasis();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;

protected:
_rotacion  rodamiento;
_cubo  base;
};


//************************************************************************

class _torreta: public _triangulos3D
{
public:
       _torreta();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;
float anchura;

protected:
_cubo  base;
_piramide parte_trasera;
};


//************************************************************************

class _tubo: public _triangulos3D
{
public:
       _tubo();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_rotacion tubo_abierto; // caña del cañón
};


//************************************************************************

class _tanque: public _triangulos3D
{
public:
       _tanque();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float giro_tubo;
float giro_torreta;

float giro_tubo_min;
float giro_tubo_max;

protected:
_chasis  chasis;
_torreta  torreta;
_tubo     tubo;
};


//************************************************************************
// objeto articulado: POLLITO
//************************************************************************
class _tronco: public _triangulos3D {

  public:
         _tronco();
        void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  protected:
        //tronco del cuerpo del pollito
        _rotacion  tronco; 

};


//////////////////////////////////////////////////////////////////////
//
//            OJO
//
//////////////////////////////////////////////////////////////////////


class _ojo: public _triangulos3D {

  public:

		float radio;
		int longitud2 ;
		int latitud2  ;

         _ojo();
        void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  protected:
        //tronco del cuerpo del pollito
        _rotacion  ojo; 

};

//////////////////////////////////////////////////////////////////////
//
//            CABEZA = OJOS + PICO
//
//////////////////////////////////////////////////////////////////////


class _cabeza: public _triangulos3D {

public:
      _cabeza();
      void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);


protected:

//los dos ojos
_ojo ojos;
_piramide pico;

};



//////////////////////////////////////////////////////////////////////
//
//           ALA
//
/////////////////////////////////////////////////////////////////////

class _ala: public _triangulos3D {

public:
      _ala();
      void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);


protected:

//alas
_rotacion alita;

};


//////////////////////////////////////////////////////////////////////
//
//            PATA = PIERNA + PIE
//
//////////////////////////////////////////////////////////////////////


class _pata: public _triangulos3D {

public:
      _pata();
      void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);


protected:

//alas
_rotacion pata;
_piramide pie;

};






class _pollito: public _triangulos3D {

public:
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
	
	bool animar;
	//booleanos para la animación

	  bool alamax ;
	  bool alamin ;
	  bool headmax;
	  bool headmin;
	  bool patasmax;
	  bool patasmin;
	  bool cuerpomin;
	  bool cuerpomax;
    
       _pollito();//(_cabeza head, _cuerpo body, _ala wing, _patas legs);
       void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
       void animarPollito();

protected:
	_tronco cuerpo;
	_cabeza cabeza;
	_ala alitaD;
	_ala alitaI;
	_pata piernaD;
	_pata piernaI;

};