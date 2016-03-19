# tinder

Proyecto para la materia 75.52 que consiste en el desarrollo de una aplicación clon de Tinder, según las especificaciones dadas.


## Branch Shared Server

En este branch se encuentran todos los sources, tests y otros archivos del Shared Server.
El Shared Server es un servidor desarrollado en [node.js](https://nodejs.org) que ofrece las operaciones de alta, baja, modificación y consulta de usuarios. Consta de una base de datos relacional para la cual se usa [postgreSQL](http://www.postgresql.org/) como administrador de base de datos.

### Clonar branch

Para descargar el branch y empezar a desarrollar sobre el mismo se debe ejecutar en la linea de comandos:

`git clone -b SharedServer https://github.com/juandausa/tinder.git nombre-del-directorio`

### Requerimientos para su uso

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


