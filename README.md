# Tinder

[![Build Status](https://travis-ci.com/juandausa/tinder.svg?token=BQqpkHq7v8pQHzVJzZjB&branch=App)](https://travis-ci.com/juandausa/tinder)
[![Build Status](https://travis-ci.com/juandausa/tinder.svg?token=BQqpkHq7v8pQHzVJzZjB&branch=AppServer)](https://travis-ci.com/juandausa/tinder)
[![Build Status](https://travis-ci.com/juandausa/tinder.svg?token=BQqpkHq7v8pQHzVJzZjB&branch=SharedServer)](https://travis-ci.com/juandausa/tinder)


Proyecto para la materia 75.52 que consiste en el desarrollo de una aplicación clon de Tinder, según las especificaciones dadas.


## Branches del proyecto

Actualmente hay 4 branches en el repositorio. Los cuales son:

* **master:** el branch actual con información general del proyecto.
* **App:** branch que contiene el proyecto del cliente Android.
* **AppServer:** branch que contiene el proyecto del servidor C++ que posee la lógica de negocio.
* **SharedServer:** branch que contiene el proyecto del servidor node.js el cual es un ABM de usuarios.

## Clonar proyecto

Esta es una recomendación de como clonar los branches de manera de tenerlos organizados localmente.
Pasos:

* Crear directorio **Tinder** en alguna ubicación, tal como podría ser en **Escritorio** para su rapido acceso.
`mkdir Tinder`
* Ubicarse dentro del directorio **Tinder**
`cd Tinder`
* Clonar el branch App
* Clonar el branch AppServer
* Clonar el branch SharedServer

#### Cómo clonar branch App

Para clonar el branch y empezar a desarrollar sobre el mismo, desde la linea de comandos ubicarse en el directorio **Tinder** y ejecutar:

`git clone -b App https://github.com/juandausa/tinder.git App`

#### Cómo clonar branch AppServer

Para clonar el branch y empezar a desarrollar sobre el mismo, desde la linea de comandos ubicarse en el directorio **Tinder** y ejecutar:

`git clone -b AppServer https://github.com/juandausa/tinder.git AppServer`


#### Cómo clonar branch SharedServer

Para clonar el branch y empezar a desarrollar sobre el mismo, desde la linea de comandos ubicarse en el directorio **Tinder** y ejecutar:

`git clone -b SharedServer https://github.com/juandausa/tinder.git SharedServer`


### Pull y Push desde branches

Para pullear desde un branch basta con ejecutar, desde el directorio donde se encuentran los archivos del branch:
`git pull`

Para push desde un branch basta con ejecutar, desde el directorio donde se encuentran los archivos del branch:
`git push`

### Acceso a la Documentación 
En cada rama del proyecto existe un instructivo para construir el ambiente de desarrollo. A su vez se volcó este contenido e información técnica adicional en un [documento](https://github.com/juandausa/tinder/blob/master/documentacion/index.rst) único para mayor comodidad. El mismo se encuentra en formato [Sphinx](http://www.sphinx-doc.org/en/stable/) y puede ser compilado en diversos formatos.
