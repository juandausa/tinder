.. Documentación Tinder documentation master file, created by Grupo 6
   sphinx-quickstart on Sat May 28 15:26:38 2016.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Bienvendio a la Documentación de Tinder
==============================================

Contenidos:

.. toctree::
   :maxdepth: 2

Indices and tables
==================

* :ref:`genindex`
* :ref:`search`

################
App Server
################
Aquí se describirá la documentación del App Server. Este modulo de la aplicación es el intermediario entre la aplicación móvil y el shared server.
También es el encargado de almacenar la información relacionada a las preferencias de usuario, sus likes, matches y conversaciones.

================================
Documentación de Instalación
================================
El App Server es un servidor desarrollado en `C++ <http://www.cplusplus.com>`_ que contiene la lógica del negocio del proyecto. Está conectado a una base de datos no relacional para la cual se usa `RocksDB <http://rocksdb.org>`_ como administrador de base de datos.
Este servidor es un servidor intermedio entre el cliente Android y el Shared Server, y recibe y envía requests desde y hacia ellos utilizando `Mongoose <https://www.cesanta.com/products/mongoose>`_. 

-------------------
Desarrolladores
-------------------

^^^^^^^^^^^^^^^^
Clonar Branch
^^^^^^^^^^^^^^^^
Para descargar el branch y empezar a desarrollar sobre el mismo se debe ejecutar en la linea de comandos:

* `git clone -b AppServer https://github.com/juandausa/tinder.git AppServer`

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Requerimientos Para su Uso
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Posicionarse en la carpeta AppServer/AppServer y ejecutar ``sudo install.sh`` . Eso instalará las herramientas y recursos necesarios.

^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Modos de Uso
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Generar los ejecutables:
   * Posicionarse sobre la carpeta AppServer/AppServer y ejecutar ``cmake .``.
   * Luego ejecutar ``make``.
* Para correr los tests por consola:
   * Puede correr los tests mediante ``./ar/fi/uba/tallerii/test/runTests`` .
* Para correr el servidor utilizar lo anterior pero iniciar el server mediante ``./ar/fi/uba/tallerii/main/Tinder_main`` .
   * El servidor lo puede finalizar con ``Ctrl+C`` o eviandole cualquier señal distinta de ``-9``.
   
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Configuración en CLion
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Importar el proyecto desde los fuentes desde la carpeta AppServer.
* Si le pregunta si desea crear nuevos archivos Cmake indique ``NO``.
* Los posibles targets son Tinder_Main y RunTests. El primero lanza el servidor y el segundo corre los tests.

^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Políticas de Commit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Correr valgrind sobre los tests, utilizando los flags ``--leak-check=full`` .
* Correr cpplint para verificar los estilos de codificación. Desde la carpeta AppServer ejecute los siguientes comando y verifique que no hay errores:
   * ``./cpplint/cpplint.py --extensions=cpp --linelength=140 ./ar/fi/uba/tallerii/src/*``
   * ``./cpplint/cpplint.py --extensions=cpp --linelength=140 ./ar/fi/uba/tallerii/main/*``

-------------------
Usuarios
-------------------

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Ejecutar Utilizando Docker
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Instale `Docker <https://www.docker.com>`_ des la web oficial.
* Descargue una copia del repositirio mediante ``git clone -b AppServer https://github.com/juandausa/tinder.git AppServer``.
* En la raiz ejecute el script ``startDocker.sh`` .
   * Esto le abrirar una terminal con todas las dependencias necesarias para ejecutar el servidor.
   * Descargue el último release mediante ``wget https://github.com/juandausa/tinder/archive/v0.1.1AppServer.tar.gz`` y ejecute la aplicación mediante lo descrito en `Modos de Uso <#modos-de-uso>`_ .

-------------------
API Web
-------------------

* Consultar `interfaz web App Server <https://docs.google.com/document/d/1lUKozaD6EfZabGmE2GwwCftcE25IU0Tyd3ERx7IhXPM/edit?usp=sharing>`_ .

Documentación Técnica
================================

#################################
Shared Server
#################################
El Shared Server es un servidor desarrollado en `node.js <https://nodejs.org>`_ que ofrece las operaciones de alta, baja, modificación y consulta de usuarios. Consta de una base de datos relacional para la cual se usa `postgreSQL <http://www.postgresql.org/>`_ como administrador de base de datos.

================================
Documentación de Instalación
================================
-------------------
Desarrolladores
-------------------
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Como Probar el Shared Server
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Actualmente se encuentra subido y corriendo en `Heroku <https://enigmatic-scrubland-75073.herokuapp.com/>`_ .
Se puede correr tambien de manera local como está indicado en el item "Ambiente local" de este archivo.
Se puede probar utilizando la API establecida en el enunciado del trabajo, o se puede tambien, probar utilizando el front end realizado (justamente para probar la API). A dicho front end se puede llegar con la ruta “/”.
Entonces, para acceder al frontend del shared server subido a Heroku basta con acceder a: https://enigmatic-scrubland-75073.herokuapp.com/ .

^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Clonar Branch
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Para descargar el branch y empezar a desarrollar sobre el mismo se debe ejecutar en la linea de comandos: ``git clone -b SharedServer https://github.com/juandausa/tinder.git SharedServer`` .

^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Probar Antes de Pushear
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
* Correr el comando ``npm test`` para probar el código y pasarle pruebas de estilo y chequeo de sintaxis.
* Correr el comando ``npm start`` para correr el server y ver que ande normalmente. 

^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Pushear a Repositorio
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
* ``git push origin SharedServer``

^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Pushear a Heroku
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* ``git push heroku SharedServer:master``

-------------------
Heroku
-------------------
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Ver Logs
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
* Ejecutar en la consola ``heroku logs --tail`` .

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Entrar a Postgres en Heroku
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
* Ejecutar en la consola ``heroku pg:psql`` .

-------------------
Ambiente Local
-------------------
En esta sección se indica todo lo necesario para probar el server localmente.

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Requerimientos para Uso Local
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Instalar node.js así como su manejador de paquetes, `npm <https://www.npmjs.com/>`_ mediante el siguiente comando: ``sudo apt-get update; sudo apt-get install nodejs; sudo apt-get install npm;``
* Instalar postgreSQL ``sudo apt-get install postgresql-9.4```.
* Abrir postgres, ejecutando el comando: ``psql -U postgres`` .
* Crear la base de datos **users**, ejecutando dentro del interprete de postgres ``CREATE DATABASE users`` .
* Crear las tablas necesarias ejecutando el script ``create_table.sql`` .

^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Correr Server Local
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Para correr el server localmente se debe ejecutar el comando: ``heroku local``

-------------------
API Web
-------------------
* Consultar `interfaz web Shared Server <https://docs.google.com/document/d/1xRC2wTo4CRqe-7736FFCgLUOsSzKJn2EOubYEawvf50/edit?usp=sharing>`_ .
