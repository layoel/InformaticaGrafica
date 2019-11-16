//**************************************************************************
// @autor   Elvira Castillo @layoel
//**************************************************************************


//**************************************************************************
// Práctica 2 usando objetos
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor){

  unsigned int i;
  glPointSize(grosor);
  glColor3f(r,g,b);

  glBegin(GL_POINTS);
  for (i=0;i<vertices.size();i++){
    glVertex3fv((GLfloat *) &vertices[i]);
    }
  glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
  unsigned int i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glLineWidth(grosor);
  glColor3f(r,g,b);
  glBegin(GL_TRIANGLES);
  for (i=0;i<caras.size();i++){
  	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
  	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
  	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  	}
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b){
  unsigned int i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glColor3f(r,g,b);
  glBegin(GL_TRIANGLES);
  for (i=0;i<caras.size();i++){
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();

  _triangulos3D::draw_aristas(0.0,0.0,0.0,3);
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
  unsigned int i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glColor3f(r1,g1,b1);
  glBegin(GL_TRIANGLES);
  for (i=0;i<caras.size();i=i+2){
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();

  glColor3f(r2,g2,b2);
  glBegin(GL_TRIANGLES);
  for (i=1;i<caras.size();i=i+2){
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();

  _triangulos3D::draw_aristas(0.0,0.0,0.0,3);

}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{

//vertices
vertices.resize(8); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;//cuadrado abajo
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;

vertices[4].x=-tam;vertices[4].y=tam+tam;vertices[4].z=tam; //cuadrado arriba
vertices[5].x=tam;vertices[5].y=tam+tam;vertices[5].z=tam;
vertices[6].x=tam;vertices[6].y=tam+tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam+tam;vertices[7].z=-tam;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=5; //frente
caras[1]._0=0;caras[1]._1=4;caras[1]._2=5;

caras[2]._0=0;caras[2]._1=1;caras[2]._2=2; //abajo
caras[3]._0=0;caras[3]._1=2;caras[3]._2=3;

caras[4]._0=1;caras[4]._1=2;caras[4]._2=5; //derecha
caras[5]._0=2;caras[5]._1=5;caras[5]._2=6;

caras[6]._0=0;caras[6]._1=3;caras[6]._2=4; //izquierda
caras[7]._0=3;caras[7]._1=4;caras[7]._2=7;

caras[8]._0=2;caras[8]._1=3;caras[8]._2=6; //atrás
caras[9]._0=3;caras[9]._1=6;caras[9]._2=7;

caras[10]._0=4;caras[10]._1=5;caras[10]._2=6; //arriba
caras[11]._0=4;caras[11]._1=6;caras[11]._2=7;


}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);
caras.resize(n_car);

_vertex3f ver_aux;
_vertex3i car_aux;

for (int i=0;i<n_ver;i++)
  {ver_aux.x=ver_ply[i*3];
   ver_aux.y=ver_ply[i*3+1];
   ver_aux.z=ver_ply[i*3+2];
   vertices[i]=ver_aux;
  }

for (int i=0;i<n_car;i++)
  {car_aux.x=car_ply[i*3];
   car_aux.y=car_ply[i*3+1];
   car_aux.z=car_ply[i*3+2];
   caras[i]=car_aux;
  }

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, char eje) {
    int i,j;
    _vertex3f vertice_aux;
    _vertex3i cara_aux;
    int num_aux;

    

    // Compruebo si me meten los puntos de forma ascendente o descendente
    comprobar(perfil, eje);

    // tratamiento de los vértice

    num_aux=perfil.size();
    vertices.resize(num_aux*num);
    for (j=0; j<num; j++){

      for (i=0; i<num_aux; i++){
      
        if(perfil[i].x==0 && j>0){
      
             vertice_aux = vertices[i];
      
          }else{
                if (eje == 'y'){ //rotacion en eje y
                  vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
                                  perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));

                  vertice_aux.z = - perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
                                    perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));

                  vertice_aux.y = perfil[i].y;
                }
                if (eje == 'x'){ //rotacion en eje x
                  vertice_aux.y = perfil[i].y * cos(2.0 * M_PI * j / (1.0 * num)) +
                                  perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));

                  vertice_aux.z = - perfil[i].y * sin(2.0 * M_PI * j / (1.0 * num)) +
                                    perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));

                  vertice_aux.x = perfil[i].x;
                }
                if(eje == 'z'){ //rotación en eje z
                  vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
                                  perfil[i].y * sin(2.0 * M_PI * j / (1.0 * num));

                  vertice_aux.y = - perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
                                    perfil[i].y * cos(2.0 * M_PI * j / (1.0 * num));

                  vertice_aux.z = perfil[i].z;
                }
      
              }
            
        vertices[i + j * num_aux] = vertice_aux;
              
      }
    }

    // tratamiento de las caras 

    for (j=0; j<num; j++){

      for (i=0; i<num_aux-1; i++){

        cara_aux._0 = i + ((j + 1) % num) * num_aux;
        cara_aux._1 = i + 1 + ((j + 1) % num) * num_aux;
        cara_aux._2 = i + 1 + j *num_aux;
        caras.push_back(cara_aux);
        
        cara_aux._0 = i + 1 + j * num_aux;
        cara_aux._1 = i + j * num_aux;
        cara_aux._2 = i + ((j + 1) % num) * num_aux;
        caras.push_back(cara_aux);
      
      }
    }

    ////////////SI ROTO EN EL EJE Y
    if (eje == 'y'){

       // tapa inferior
      if (fabs(perfil[0].x)>0.0){

        vertice_aux.x = 0;
        vertice_aux.y = perfil[0].y;
        vertice_aux.z = 0;
        vertices.push_back(vertice_aux);

        for (j=0; j<num; j++){
          cara_aux._0 = j * num_aux;
          cara_aux._1 = vertices.size()-1;
          cara_aux._2 = ((j + 1) % num) * num_aux;
          caras.push_back(cara_aux);
        }

      }
       
       // tapa superior
      if (fabs(perfil[num_aux-1].x)>0.0){
        vertice_aux.x = 0;
        vertice_aux.y = perfil[num_aux-1].y;
        vertice_aux.z = 0;
        vertices.push_back(vertice_aux);
      
        for (j=0; j<num; j++){
          cara_aux._0 = (num_aux - 1) + j * num_aux;
          cara_aux._1 = (vertices.size() - 1);
          cara_aux._2 = (num_aux - 1) + ((j + 1) % num) * num_aux;
          caras.push_back(cara_aux);
        }

      }
    }// fin if eje y


    //////////////SI ROTO EN EJE X
    if (eje == 'x'){
     // tapa inferior
      if (fabs(perfil[0].x)>0.0){

        vertice_aux.y = 0;
        vertice_aux.x = perfil[0].x;
        vertice_aux.z = 0;
        vertices.push_back(vertice_aux);

        for (j=0; j<num; j++){
          cara_aux._0 = j * num_aux;
          cara_aux._1 = vertices.size()-1;
          cara_aux._2 = ((j + 1) % num) * num_aux;
          caras.push_back(cara_aux);
        }

      }
       
       // tapa superior
      if (fabs(perfil[num_aux-1].x)>0.0){
        vertice_aux.y = 0;
        vertice_aux.x = perfil[num_aux-1].x;
        vertice_aux.z = 0;
        vertices.push_back(vertice_aux);
      
        for (j=0; j<num; j++){
          cara_aux._0 = (num_aux - 1) + j * num_aux;
          cara_aux._1 = (vertices.size() - 1);
          cara_aux._2 = (num_aux - 1) + ((j + 1) % num) * num_aux;
          caras.push_back(cara_aux);
        }

      }
  }

  ///////// SI ROTO EN EJE Z
  if (eje == 'z'){
     // tapa inferior
      if (fabs(perfil[0].x)>0.0){

        vertice_aux.x = 0;
        vertice_aux.z = perfil[0].z;
        vertice_aux.y = 0;
        vertices.push_back(vertice_aux);

        for (j=0; j<num; j++){
          cara_aux._0 = j * num_aux;
          cara_aux._1 = vertices.size()-1;
          cara_aux._2 = ((j + 1) % num) * num_aux;
          caras.push_back(cara_aux);
        }

      }
       
       // tapa superior
      if (fabs(perfil[num_aux-1].x)>0.0){
        vertice_aux.x = 0;
        vertice_aux.z = perfil[num_aux-1].z;
        vertice_aux.y = 0;
        vertices.push_back(vertice_aux);
      
        for (j=0; j<num; j++){
          cara_aux._0 = (num_aux - 1) + j * num_aux;
          cara_aux._1 = (vertices.size() - 1);
          cara_aux._2 = (num_aux - 1) + ((j + 1) % num) * num_aux;
          caras.push_back(cara_aux);
        }

      }

  }
//Una vez defines los puntos en el main podemos crear el archivo ply con la funcion write
// _file_ply::write("Jarron.ply", vertices, caras);
}

void _rotacion::comprobar(vector<_vertex3f> perfil, char eje){

  switch (toupper(eje)){
    case 'Y':
        if (perfil[0].y > perfil[perfil.size()].y)
          reverse(perfil.begin(), perfil.end());
    break;
    case 'X':
      if (perfil[0].x > perfil[perfil.size()].x)
          reverse(perfil.begin(), perfil.end());
    break;
    case 'Z':
      if (perfil[0].z > perfil[perfil.size()].z)
          reverse(perfil.begin(), perfil.end());
    break;
  
  }
}


//************************************************************************
// objeto cono
//************************************************************************

_cono::_cono(float radio2, float altura2, int num_lados){

  num = num_lados;
  radio = radio2;
  altura = altura2;

  vector<_vertex3f> perfil1;
  
  _vertex3f aux;
  aux.x=radio;
  aux.y=-altura/2;
  aux.z=0;
  perfil1.push_back(aux);

  aux.x=0;aux.y=altura/2;aux.z=0;
  perfil1.push_back(aux);

  parametros(perfil1);


}

void _cono::parametros(vector<_vertex3f> perfil){
  int i,j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;

  // tratamiento de los vértices

  num_aux=perfil.size();
  vertices.resize(num_aux*num);
  for (j=0; j<num; j++){

    for (i=0; i<num_aux; i++){
      vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
                      perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));

      vertice_aux.z = - perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
                        perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));

      vertice_aux.y = perfil[i].y;
          
      vertices[i + j * num_aux] = vertice_aux;
            
    }
  }

// tratamiento de las caras

  for (j=0; j<num; j++){

    for (i=0; i<num_aux-1; i++){
      cara_aux._0 = i + 1 + j * num_aux;
      cara_aux._1 = i + j * num_aux;
      cara_aux._2 = i + ((j + 1) % num) * num_aux;
      caras.push_back(cara_aux);
    }
  }

  //la tapa inferior

  if (fabs(perfil[0].x)>0.0){
      vertice_aux.x = 0;
      vertice_aux.y = perfil[0].y;
      vertice_aux.z = 0;
      vertices.push_back(vertice_aux);

      for (j=0; j<num; j++){
        cara_aux._0 = j * num_aux;
        cara_aux._1 = vertices.size()-1;
        cara_aux._2 = ((j + 1) % num) * num_aux;
        caras.push_back(cara_aux);
      }
  }

}
     
//************************************************************************
// objeto esfera
//************************************************************************


_esfera::_esfera(float radio2, int longitud2,int latitud2){

  longitud = longitud2;
  latitud = latitud2*2;
  radio = radio2;
  crearPerfil();
  parametros();

}

void _esfera::crearPerfil(){
  
  _vertex3f vertice_aux;

  for(int i = (-latitud/4)+1; i < (latitud/4); i++){

    vertice_aux.x = radio * cos(2 * M_PI * i / latitud);
    vertice_aux.y = radio * sin(2 * M_PI * i / latitud);
    vertice_aux.z = 0;
    
    perfil.push_back(vertice_aux);

  } 
}

void _esfera::parametros(){
  int i,j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;

  // tratamiento de los vértices

  num_aux=perfil.size();
  vertices.resize(num_aux*longitud);
  for (j=0; j<longitud; j++){

    for (i=0; i<num_aux; i++){

      vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * longitud)) +
                      perfil[i].z * sin(2.0 * M_PI * j / (1.0 * longitud));

      vertice_aux.z = - perfil[i].x * sin(2.0 * M_PI * j / (1.0 * longitud)) +
                        perfil[i].z * cos(2.0 * M_PI * j / (1.0 * longitud));

      vertice_aux.y = perfil[i].y;
          
      vertices[i + j * num_aux] = vertice_aux;
            
    }
  }

  // tratamiento de las caras 
      
   for (j=0; j<longitud; j++){

      for (i=0; i<num_aux-1; i++){

        cara_aux._0 = i + ((j + 1) % longitud) * num_aux;
        cara_aux._1 = i + 1 + ((j + 1) % longitud) * num_aux;
        cara_aux._2 = i + 1 + j *num_aux;
        caras.push_back(cara_aux);
        
        cara_aux._0 = i + 1 + j * num_aux;
        cara_aux._1 = i + j * num_aux;
        cara_aux._2 = i + ((j + 1) % longitud) * num_aux;
        caras.push_back(cara_aux);
      
      }
    }
    
  // tapa inferior
  if (fabs(perfil[0].x)>0.0){

    vertice_aux.x = 0;
    vertice_aux.y = -radio;
    vertice_aux.z = 0;
    vertices.push_back(vertice_aux);
    
    for (j=0; j<longitud; j++){

      cara_aux._0 = j * num_aux;
      cara_aux._1 = vertices.size() - 1;
      cara_aux._2 = ((j + 1) % longitud) * num_aux;
      caras.push_back(cara_aux);
    
    }
  }


  // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0)
  {
    vertice_aux.x = 0;
    vertice_aux.y = radio;
    vertice_aux.z = 0;
    vertices.push_back(vertice_aux);

    for (j=0; j<longitud; j++){

      cara_aux._0 = (num_aux - 1) + j * num_aux;
      cara_aux._1 = (vertices.size() - 1);
      cara_aux._2 = (num_aux - 1) + ((j + 1) % longitud) * num_aux;
      caras.push_back(cara_aux);
    
    }

  }
}


//************************************************************************
// objeto articulado: tanque
//************************************************************************

_chasis::_chasis()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.107;aux.y=-0.5;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.107;aux.y=0.5;aux.z=0.0;
perfil.push_back(aux);
rodamiento.parametros(perfil,12,'y');
altura=0.22;
};

void _chasis::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(1.0,0.22,0.95);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

//************************************************************************

_torreta::_torreta()
{
altura=0.18;
anchura=0.65;
};


void _torreta::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(0.65,0.18,0.6);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.325,0,0);
glRotatef(90.0,0,0,1);
glScalef(0.18,0.16,0.6);
parte_trasera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

//************************************************************************

_tubo::_tubo()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.04;aux.y=-0.4;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.04;aux.y=0.4;aux.z=0.0;
perfil.push_back(aux);
tubo_abierto.parametros(perfil,12,'y');
};

void _tubo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

glPushMatrix();
glTranslatef(0.4,0,0);
glRotatef(90.0,0,0,1);
tubo_abierto.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}


//************************************************************************

_tanque::_tanque()
{
giro_tubo=2.0;
giro_torreta=0.0;
giro_tubo_min=-9;
giro_tubo_max=20;
};

void _tanque::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor);

glRotatef(giro_torreta,0,1,0);
glPushMatrix();
glTranslatef(0.0,(chasis.altura+torreta.altura)/2.0,0.0);
torreta.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(torreta.anchura/2.0,(chasis.altura+torreta.altura)/2.0,0.0);
glRotatef(giro_tubo,0,0,1);
tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
glPopMatrix();

};



//***********************************************************************
// objeto articulado: POLLITO
//************************************************************************

//////////////////////////////////////////////////////////////////////
//
//         CUERPO
//
//////////////////////////////////////////////////////////////////////

_tronco::_tronco(){
  
  // perfil para cuerpo
  vector<_vertex3f> perfil;
  _vertex3f aux;

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
  aux.x=1.55;aux.y=-0.1;aux.z=0.0;
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


  tronco.parametros(perfil,20,'y');

}



void _tronco::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  
//color cuerpo
  r1 = 1.0;   g1 = 0.0;  b1 = 0.5;
  r2 = 0.5;   g2 = 0.0;   b2 = 0.5;

  r1 = 0.0;   g1 = 1.0;  b1 = 0.5;
  r2 = 0.5;   g2 = 0.0;   b2 = 0.5;

  glPushMatrix();
  tronco.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

}
//////////////////////////////////////////////////////////////////////
//
//            OJOS
//
//////////////////////////////////////////////////////////////////////

_ojo::_ojo(){

radio = 1.0;
longitud2 = 10;
latitud2 = 10;

  vector<_vertex3f> perfil;
//creo el perfil del ojo
 _vertex3f vertice_aux1;

  for(int i = (-latitud2/4)+1; i < (latitud2/4); i++){

    vertice_aux1.x = radio * cos(2 * M_PI * i / latitud2);
    vertice_aux1.y = radio * sin(2 * M_PI * i / latitud2);
    vertice_aux1.z = 0;
    
    perfil.push_back(vertice_aux1);

  } 

  ojo.parametros(perfil, 20, 'y');

}

void  _ojo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){

  //color azul y negro para los ojos
  r1 = 0.0;   g1 = 0.0;  b1 = 1.0;
  r2 = 0.0;   g2 = 0.0;  b2 = 0.0;

  glPushMatrix();
  glTranslatef(0.5,3.0,0.5);
  glRotatef(90.0,1,0,0);
  glScalef(0.3,0.7,0.3);
  ojo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.5,3.0,0.5);
  glRotatef(90.0,1,0,0);
  glScalef(0.3,0.7,0.3);
  ojo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}


//////////////////////////////////////////////////////////////////////
//
//            CABEZA = OJOS + PICO
//
//////////////////////////////////////////////////////////////////////


_cabeza::_cabeza(){

}

void  _cabeza::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){

        glPushMatrix();
        ojos.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
        glPopMatrix();
//color naranja y negro para el pico
  r1 = 1.0;   g1 = 0.2;  b1 = 0.0;
  r2 = 0.0;   g2 = 0.0;  b2 = 0.0;
      glPushMatrix();
        glTranslatef(0.0,2.5,1.0);
        glRotatef(90.0,1,0,0);
        glScalef(0.5,1.0,0.5);
        pico.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
      glPopMatrix();

};




//////////////////////////////////////////////////////////////////////
//
//        ALA
//
//////////////////////////////////////////////////////////////////////

_ala::_ala(){
vector<_vertex3f> perfil; 
_vertex3f aux;

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
  aux.x=0.4;aux.y=-1.6;aux.z=0.0;
  perfil.push_back(aux);
  aux.x=0.1;aux.y=-3.5;aux.z=0.0;
  perfil.push_back(aux);
  
  alita.parametros(perfil,20, 'y');
  
}


void _ala::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){

//color naranja y negro para el pico
  r1 = 1.0;   g1 = 0.0;  b1 = 0.3;
  r2 = 0.5;   g2 = 0.0;  b2 = 0.5;

  glPushMatrix();
  //glTranslatef(0.0,0.0,0.0);
  glScalef(0.5,0.7,0.9);
  alita.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}

//////////////////////////////////////////////////////////////////////
//
//       PATA = PIERNA + PIE 
//
//////////////////////////////////////////////////////////////////////


_pata::_pata(){
vector<_vertex3f> perfil; 
_vertex3f aux;

aux.x=1.0; aux.y=1.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=1.0; aux.y=-1.0; aux.z=0.0;
perfil.push_back(aux);

pata.parametros(perfil,10, 'y');

}


void  _pata::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  //color pata
  r1 = 0.0;   g1 = 0.0;  b1 = 1.0;
  r2 = 0.0;   g2 = 0.0;  b2 = 0.0;
  glPushMatrix();
  glTranslatef(0.0,-1.5,0.6);
  glScalef(0.5,1.0,0.5);
  pata.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

//color pie
  r1 = 0.5;   g1 = 0.0;  b1 = 0.5;
  r2 = 0.0;   g2 = 0.0;  b2 = 0.0;
  glPushMatrix();
  glTranslatef(0.0,-2.8,0.6);
  glScalef(0.8,0.8,0.8);
  pie.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}


//////////////////////////////////////////////////////////////////////
//
//            EL POLLITOOOOOOOO
//
//////////////////////////////////////////////////////////////////////



_pollito::_pollito(){
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
animar = false;
}

/*void _pollito::animarPollito(){
  bool alamax = false;
  bool alamin = true;
  bool headmax = false;
  bool headmin = true;
  bool patasmax = false;
  bool patasmin = true;


  if (animar){

      
      if (!alamax && giro_alaD < giro_ala_max){ 
        giro_alaD+=1;
        giro_alaI+=1;
      }else{
        alamax = !alamax;
        alamin = !alamin;
      }
      
      if (!headmax && giro_cabeza < giro_cabeza_max) 
        giro_cabeza+=1;
      else{
        headmax = !headmax ;
        headmin = !headmin ;
      }

      if (!patasmax && giro_patas < giro_pata_max) 
        giro_patas+=1;
      else{
        patasmax = !patasmax;
        patasmin = !patasmin;
      }

      
       if (!patasmin && giro_patas > giro_pata_min) 
        giro_patas-=1;
      else{
        patasmax = !patasmax;
        patasmin = !patasmin;
      }

      if (!alamin && giro_alaD > giro_ala_min){
        giro_alaD-=1; 
        giro_alaI-=1;
      }else{
        alamax = !alamax;
        alamin = !alamin;
      }

      if (!headmin && giro_cabeza > giro_cabeza_min) 
        giro_cabeza-=1;
      else{
        headmax = !headmax ;
        headmin = !headmin ;
      }

  }

}*/

void  _pollito::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
//cuerpo
  glPushMatrix();

    glRotatef(30,1,0,0);


    glPushMatrix();
    cuerpo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
  //cabeza   
  r1 = 0.5; 
  g1 = 0.5;
  b1 = 0.0;

  r2 = 0.0; 
  g2 = 1.0;
  b2 = 1.0; 
    glPushMatrix();
    glRotatef(giro_cabeza,0,1,0);
    cabeza.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

  //alas
    glPushMatrix();
    glRotatef(giro_alaD,1,0,0);
    glTranslatef(1.5,-0.5,0.0);
    
    glRotatef(20,0,0,1);
    alitaD.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
    
    glPushMatrix();
    
    glRotatef(giro_alaI,1,0,0);
    glTranslatef(-1.5,-0.5,0.0);
    glRotatef(-20,0,0,1);
    alitaI.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

  //patas
    glPushMatrix();
      glTranslatef(0.5,-1.0,0.0);
      glRotatef(giro_patas,1,0,0);
      piernaD.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-0.5,-1.0,0.0);
      glRotatef(giro_patas,1,0,0);
      piernaI.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();


    glPopMatrix();

}