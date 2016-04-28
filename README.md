# Branch Shared Server

[![Build Status](https://travis-ci.com/juandausa/tinder.svg?token=BQqpkHq7v8pQHzVJzZjB&branch=SharedServer)](https://travis-ci.com/juandausa/tinder)
[![Heroku](http://heroku-badge.herokuapp.com/?app=angularjs-crypto&style=flat&svg=1)](https://heroku-badge.herokuapp.com/?app=enigmatic-scrubland-75073)

[![Deploy](https://www.herokucdn.com/deploy/button.svg)](https://heroku.com/deploy?template=https://git.heroku.com/enigmatic-scrubland-75073)

En este branch se encuentran todos los sources, tests y otros archivos del Shared Server.
El Shared Server es un servidor desarrollado en [node.js](https://nodejs.org) que ofrece las operaciones de alta, baja, modificación y consulta de usuarios. Consta de una base de datos relacional para la cual se usa [postgreSQL](http://www.postgresql.org/) como administrador de base de datos.


### Como probar el Shared Server
Actualmente se encuentra subido y corriendo en heroku.
Se puede correr tambien de manera local como está indicado en el item "Ambiente local" de este archivo.
Se puede probar utilizando la API establecida en el enunciado del trabajo, o se puede tambien, probar utilizando el front end realizado (justamente para probar la API). A dicho front end se puede llegar con la ruta “/”.
Entonces, para acceder al frontend del shared server subido a Heroku basta con acceder a:
https://enigmatic-scrubland-75073.herokuapp.com/

### Clonar branch

Para descargar el branch y empezar a desarrollar sobre el mismo se debe ejecutar en la linea de comandos:

`git clone -b SharedServer https://github.com/juandausa/tinder.git SharedServer`

### Probar antes de pushear

* Correr el comando `npm test` para probar el código y pasarle pruebas de estilo y chequeo de sintaxis.
* Correr el comando `npm start` para correr el server y ver que ande normalmente. 

### Pushear a repositorio

`git push`

### Pushear a Heroku

`git push heroku SharedServer:master`


## Heroku

### Ver logs

Ejecutar `heroku logs --tail`

### Entrar a postgres desde heroku

Ejecutar en la consola `heroku pg:psql`



## Ambiente Local

En esta sección se indica todo lo necesario para probar el server localmente.

### Requerimientos para uso local

* Instalar node.js así como su manejador de paquetes, [npm](https://www.npmjs.com/)
``` 
sudo apt-get update
sudo apt-get install nodejs
sudo apt-get install npm
```

* Instalar postgreSQL
```
sudo apt-get install postgresql-9.4
```

* Abrir postgres, ejecutando el comando
```psql -U postgres```

* Crear la base de datos **users**, ejecutando dentro del interprete de postgres
```CREATE DATABASE users```

* Crear las tablas necesarias ejecutando el script **create_table.sql**

### Correr server localmente

Para correr el server localmente se debe ejecutar el comando:

`heroku local`

### API Web
* Consultar [interfaz](https://docs.google.com/document/d/1xRC2wTo4CRqe-7736FFCgLUOsSzKJn2EOubYEawvf50/edit?usp=sharing) web.

