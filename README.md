# Branch App Server

[![Build Status](https://travis-ci.com/juandausa/tinder.svg?token=BQqpkHq7v8pQHzVJzZjB&branch=AppServerRefactor)](https://travis-ci.com/juandausa/tinder)

En este branch se encuentran todos los sources, tests y otros archivos del App Server.
El App Server es un servidor desarrollado en [C++](http://www.cplusplus.com/) que contiene la lógica del negocio del proyecto. Está conectado a una base de datos no relacional para la cual se usa [RocksDB](http://rocksdb.org/) como administrador de base de datos.
Este servidor es un servidor intermedio entre el cliente Android y el Shared Server, y recibe y envía requests desde y hacia ellos utilizando [Mongoose](https://www.cesanta.com/products/mongoose). 

## Desarrolladores
### Clonar branch

Para descargar el branch y empezar a desarrollar sobre el mismo se debe ejecutar en la linea de comandos:

`git clone -b AppServerRefactor https://github.com/juandausa/tinder.git AppServerRefactor`

### Requerimientos para su uso

* Posicionarse en la carpeta AppServer/AppServer y ejecutar ```sudo install.sh``` . Eso instalará las herramientas y recursos necesarios.

### Modos de uso
* Generar los ejecutables:
   * Posicionarse sobre la carpeta AppServer/AppServer y ejecutar ```cmake .```.
   * Luego ejecutar ```make```.
* Para correr los tests por consola:
   * Puede correr los tests mediante ```./source/test/runTests``` .
* Para correr el servidor utilizar lo anterior pero iniciar el server mediante ```./source/main/Tinder_main``` .
   * El servidor lo puede finalizar con ```Ctrl+C``` o eviandole cualquier señal distinta de ```-9```.
   
### Configuración en CLion
* Importar el proyecto desde los fuentes desde la carpeta AppServer.
* Si le pregunta si desea crear nuevos archivos Cmake indique ```NO```.
* Los posibles targets son Tinder_Main y RunTests. El primero lanza el servidor y el segundo corre los tests.

### Políticas de Commit
* Correr valgrind sobre los tests, utilizando los flags --leak-check=full.
* Correr cpplint para verificar los estilos de codificación. Desde la carpeta AppServer ejecute los siguientes comando y verifique que no hay errores:
   * ./cpplint/cpplint.py --extensions=cpp --linelength=140 ./source/src/*
   * ./cpplint/cpplint.py --extensions=cpp --linelength=140 ./source/main/*

### API Web

* Consultar [interfaz](https://docs.google.com/document/d/1lUKozaD6EfZabGmE2GwwCftcE25IU0Tyd3ERx7IhXPM/edit?usp=sharing) web.

## Usuarios

### Ejecutar utilizando Docker
* Instale [Docker](https://www.docker.com/).
* Descargue una copia del repositirio mediante ```git clone -b AppServer https://github.com/juandausa/tinder.git AppServer```.
* En la raiz ejecute el script ```startDocker.sh``` .
   * Esto le abrirar una terminal con todas las dependencias necesarias para ejecutar el servidor.
   * Descargue el último release mediante ```wget https://github.com/juandausa/tinder/archive/v0.1.1AppServer.tar.gz``` y ejecute la aplicación mediante lo descrito en [Modos de Uso](https://github.com/juandausa/tinder/tree/AppServer#modos-de-uso) .
