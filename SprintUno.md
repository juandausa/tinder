# [Sprint 1](https://github.com/juandausa/tinder/milestones/Sprint%201)

## Objetivos del Sprint
 * Crear el entorno de proyecto.
 * Conecer las herramientas a utilizar.
 * Hacer una estimación de alto nivel del proyecto.
 * Por medio de la construcción unas pocas funcionalidades generar la estructura necesaria para agregar facilmente el resto de las mismas.

## Calendario
Duración del Sprint: 6 semanas.
Desde el 10/03/2016 hasta el 21/04/2016

## Equipo
* Graffe, Fabrizio Sebastián
* Sella Faena, Jasmina
* Rojas, Agustín
* Dausá, Juan Ángel

## Compromisos

### Historias de usuario
* Un usuario se puede registrar en la aplicación
* Un usuario registrado puede ingresar a la aplicación
* Un usuario registrado puede ingresar y editar sus intereses
* Un usuario puede ver aquellas personas que se encuentren cerca y cumplan con los filtros establecidos.


### División de tareas
| Nombre                    | Area          | Id  | Descripción                                                     | Responsable | Costo |
|---------------------------|---------------|-----|-----------------------------------------------------------------|-------------|-------|
| Creación del ambiente     | App           | 1.1 | Armar una aplicación en android en incluirla en Travis          | Graffe      |   20  |
| Creación del ambiente     | App Server    | 1.2 | Armar una aplicación en android en incluirla en Travis          | Dausá       |   20  |
| Creación del ambiente     | Shared Server | 1.3 | Armar una aplicación en android en incluirla en Heroku          | Graffe      |   20  |
| Registro                  | App           | 2.1 | Construir pantalla de registro                                  | Graffe      |   7   |
|                           |               | 2.2 | Manejo de Request de registro                                   | Sella       |   6   |
|                           | App Server    | 2.3 | Manejo de Request de registro                                   | Dausá       |   6   |
|                           | Shared Server | 2.4 | Alta de usuario                                                 | Graffe      |   4   |
| Login                     | App           | 3.1 | Obtener ubicación                                               | Graffe      |   4   |
|                           |               | 3.2 | Enviar request de Login                                         | Sella       |   4   |
|                           | App Server    | 3.3 | Manejar request de Login                                        | Sella       |   4   |
| Pantallas                 | App           | 4.1 | Construir estructura de las pantallas de la aplicacion (vacias) | Graffe      |   8   |
|                           |               | 4.2 | Construir menu desplegable                                      | Rojas       |   5   |
| Edicion                   | App           | 5.1 | Pantalla para ver perfil                                        | Graffe      |   5   |
|                           |               | 5.2 | Pantalla para editar perfil                                     | Rojas       |   8   |
|                           |               | 5.3 | Enviar request de modificación de perfil                        | Rojas       |   4   |
|                           | App Server    | 5.4 | Manejo de request de edición                                    | Dausá       |   3   |
|                           | Shared Server | 5.5 | Frontend (HTML+Bootstrap+CSS)                                   | Rojas       |   5   |
|                           |               | 5.6 | Backend (ABM Node.js)                                           | Rojas       |   12  |
| Mostrar personas cercanas | App           | 6.1 | Request                                                         | Graffe      |   2   |
|                           |               | 6.2 | Pantalla principal: mostrar sliding cards de personas           | Graffe      |   5   |
|                           | App           | 6.3 | Ver detalle de persona                                          | Graffe      |   5   |
|                           | App Server    | 6.4 | Manejar request                                                 | Graffe      |   2   |
|                           |               | 6.5 | Aplicar filtros y enviar resultados                             | Graffe      |   6   |
|                           | Shared Server | 6.6 | Responder requests                                              | Graffe      |   1   |
| Chat                      | App           | 7.1 | Pantalla de chat                                                | Graffe      |   10  |
|                           |               | 7.2 | Requests para mensajes (entrada y salida)                       | Sella       |   8   |
|                           | App Server    | 7.3 | Controlador Mock para mensajes                                  | Sella       |   8   |

## Comentarios
* La funcionalidad de chat que se desarrollará consistirá en mostrar un ejemplo de conversación almacenado en el App Server a través de la pantalla de conversaciones que se implementará en el cliente android. Tambien permitirá generar nuevos mensajes y agregarlos a la conversación.
