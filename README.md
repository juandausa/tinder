# Branch App Server

[![Build Status](https://travis-ci.com/juandausa/tinder.svg?token=BQqpkHq7v8pQHzVJzZjB&branch=AppServer)](https://travis-ci.com/juandausa/tinder)

En este branch se encuentran todos los sources, tests y otros archivos del App Server.
El App Server es un servidor desarrollado en [C++](http://www.cplusplus.com/) que contiene la lógica del negocio del proyecto. Está conectado a una base de datos no relacional para la cual se usa [RocksDB](http://rocksdb.org/) como administrador de base de datos.
Este servidor es un servidor intermedio entre el cliente Android y el Shared Server, y recibe y envía requests desde y hacia ellos utilizando [Mongoose](https://www.cesanta.com/products/mongoose). 

### Clonar branch

Para descargar el branch y empezar a desarrollar sobre el mismo se debe ejecutar en la linea de comandos:

`git clone -b AppServer https://github.com/juandausa/tinder.git AppServer`

### Requerimientos para su uso

* Ejecutar ./AppServer/install.sh . Eso instalará las herramientas  recursos necesarios.


