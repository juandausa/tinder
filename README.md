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


### Como ejecutar y probar la aplicación
La aplicación android se ha probado bajo las siguientes condiciones:
* Corriendo en un smartphone con Android con una versión igual o superior a la 4.0. (Cerca del 90% de los teléfonos en el mercado cumplen con esto según la documentación de Android).
* El teléfono sobre el que se corre la aplicación tiene una conexión a internet disponible.
* El teléfono está conectado a la misma red wifi que la computadora donde se está corriendo el servidor al que le envía requests.
* El servidor al que le envía requests es un MockServer que corre en localhost y tiene respuestas predefinidas para probar la aplicación. 
* Para poder correr este servidor se necesita instalar las dependencias, por lo que dentro de la carpeta /MockServer se debe ejecutar el comando sudo npm install.
* El servidor debe estar corriendo en la dirección ip de la red 192.168.1.106 o en su defecto, se deberá cambiar dicha dirección ip en el archivo Constants.java en el atributo publico IP_SERVER. (Esto se debe hacer así por el momento debido a la falta de conocimiento de cómo tener un archivo de configuración para la aplicación).

Para instalar y correr la aplicación en un teléfono, se debe copiar el apk disponible en el repositorio a alguna carpeta del teléfono e instalarlo.


### Clonar branch

Para descargar el branch y empezar a desarrollar sobre el mismo se debe ejecutar en la linea de comandos:

`git clone -b App https://github.com/juandausa/tinder.git App`

### Requerimientos para su uso

* Instalar el IDE [Android Studio](https://developer.android.com/sdk/)
* Instalar todas las librerias de la 23 en adelante desde el SDK Manager (dentro del Android Studio).


### Correr scripts para chequeo de estilos, bugs, linter, etc.

Para chequear que todo este correcto antes de subir código al repositorio realizar los siguientes pasos:

* Situarse con la consola en `App/app/`
* Ejecutar el comando `./gradlew build`
* Verificar si realizó el build correctamente. De haber fallado, observar que fué lo que falló leyendo el archivo de reportes indicado por la salida del comando que acabamos de ejecutar.
* Corregir el problema, repetir los pasos anteriores y subir al repositorio.


### Integración con Facebook

El login al cliente Android se realiza mediante facebook, por lo que es necesario realizar los siguientes pasos para lograr un login exitoso.

- Generar un **key hash** para el ambiente de desarrollo de cada desarrollador. Para esto:
    - Abrir la consola.
    - Ejecutar el comando: `keytool -exportcert -alias androiddebugkey -keystore ~/.android/debug.keystore | openssl sha1 -binary | openssl base64`
    - Darle **enter** cuando pida una contraseña.
- Dirigirse a la [sección de Ajustes del sitio web de la app en developers facebook](https://developers.facebook.com/apps/469716263220924/settings/).
- Copiar el código generado por el comando en el campo Key Hashes (sin borrar los que ya estén).
- Guardar cambios.
