## Branch App

[![Build Status](https://travis-ci.com/juandausa/tinder.svg?token=BQqpkHq7v8pQHzVJzZjB&branch=App)](https://travis-ci.com/juandausa/tinder)


En este branch se encuentran todos los sources, tests y otros archivos del cliente Android del proyecto.
El cliente es una aplicación desarrollada en [android](https://www.android.com) que ofrece al usuario la posibilidad de:
* Loguearse mediante facebook (utilizando sus APIs).
* Dar Like o no a gente cercana que cumple con las caracteristicas establecidas por el usuario.
* Mostrar matches con personas.
* Establecer una comunicación con los matches.
* Configurar los filtros mediante los cuales se regula que personas se le son mostradas al usuario.
* Ver y editar el perfil del usuario.



### Clonar branch

Para descargar el branch y empezar a desarrollar sobre el mismo se debe ejecutar en la linea de comandos:

`git clone -b App https://github.com/juandausa/tinder.git App`

### Requerimientos para su uso

* Instalar el IDE [Android Studio](https://developer.android.com/sdk/)
* Instalar todas las librerias de la 23 en adelante desde el SDK Manager (dentro del Android Studio).


### Integración con Facebook

El login al cliente Android se realiza mediante facebook, por lo que es necesario realizar los siguientes pasos para lograr un login exitoso.

- Generar un **key hash** para el ambiente de desarrollo de cada desarrollador. Para esto:
    - Abrir la consola.
    - Ejecutar el comando: `keytool -exportcert -alias androiddebugkey -keystore ~/.android/debug.keystore | openssl sha1 -binary | openssl base64`
    - Darle **enter** cuando pida una contraseña.
- Dirigirse a la [sección de Ajustes del sitio web de la app en developers facebook](https://developers.facebook.com/apps/469716263220924/settings/).
- Copiar el código generado por el comando en el campo Key Hashes (sin borrar los que ya estén).
- Guardar cambios.
