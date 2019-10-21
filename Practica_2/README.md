# Informática Grafica

## Práctica 2 MODELOS PLY Y POLIGONALES

Modelado de objetos sólidos poligonales mediante la técnica de modelado por revolución alrededor de un eje de rotación:

Para cambiar los modos de visualizacion se usan las siguientes teclas:
 
- **1** Modo Puntos
- **2** Modo Aristas
- **3** Modo Solido (también se ven las aristas)
- **4** Modo Ajedrez (también se ven las aristas)

Las teclas para cambiar de figura son:

- **A** Pirámide
- **S** Cubo
- **D** Objeto ply
- **F** Objeto generado por rotación de puntos (el cilindro sobre eje Y)
- **G** Cono
- **H** Esfera
- **J** Cilindro generado sobre eje X
- **K** Cilindro generado sobre eje Z
- **Q** Para salir

Obtenemos las imágenes siguientes:

![Imagen](https://github.com/layoel/InformaticaGrafica/blob/master/imagenes/p2cono.JPG)

![Imagen](https://github.com/layoel/InformaticaGrafica/blob/master/imagenes/p2esfera.JPG)

Para generar los ply  de los objetos CilindroX CilindroY, CilindroZ y Jarron he usado la funcion write de ply (comentada en el código) y en **practica_objetos_B2** generando el objeto por rotación lo podemos cambiar descomentando y comentando el código del fichero y obtener un cilindro o un jarron. 

El cilindro lo podemos dibujar con **rotación** en el **eje Y** es el que se ejecuta por defecto al pulsar la tecla F, el que rota en **X** esta en la tecla J y el que rota en el **eje Z** esta en la tecla K. (tras descomentar cada uno de los perfiles en practica_objetos_b2 los he escrito en un ply con la funcion write que he implementado en la clase file_ply_stl, he añadido la llamda a función en el método parámetros de la clase rotación) Para la ejecución final uso directamente los ply generados.

![Imagen](https://github.com/layoel/InformaticaGrafica/blob/master/imagenes/p2cX.JPG)

![Imagen](https://github.com/layoel/InformaticaGrafica/blob/master/imagenes/p2cY.JPG)

![Imagen](https://github.com/layoel/InformaticaGrafica/blob/master/imagenes/p2cZ.JPG)

![Imagen](https://github.com/layoel/InformaticaGrafica/blob/master/imagenes/p2J.JPG)

Tambien he añadido una funcion en la clase rotación que se llama **comprueba** que permite introducir los puntos de la generatriz en orden ascendente o descendente y siempre pinta la imagen correcta.