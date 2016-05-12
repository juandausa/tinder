# [Sprint 2](https://github.com/juandausa/tinder/milestones/Sprint%202)

## Objetivos del Sprint
 * Integrar las distintas partes del sistema. App, AppServer y SharedServer.
 * Completar la edición de los datos de usuario.
 * Realizar el ABM de preferencias de usuario.
 * Agregar datos de usuario faltantes.
 * Permitir la visualización de personas cercanas a traves de los filtros y preferencias.
 * Almacenar likes.

## Calendario
Duración del Sprint: 4 semanas.
Desde el 28/05/2016 hasta el 02/06/2016

## Equipo
* Graffe, Fabrizio Sebastián
* Sella Faena, Jasmina
* Rojas, Agustín
* Dausá, Juan Ángel

## Compromisos

### Historias de usuario
* Un usuario puede editar sus datos personales.
* Un usuario puede editar sus preferencias.
* Un usuario puede ver aquellas personas que se encuentren cerca y que cumplan con los filtros establecidos.
* Un usuario puede dar 'like' o no a sus candidatos.


### División de tareas


| Nombre                    | Area          | Id   | Descripción                           | Responsable | Costo |
|---------------------------|---------------|------|---------------------------------------|-------------|-------|
| Edición                   | App Server    | 5.4  | Manejo de request de edición          | Dausá       | 3     |
|                           |               | 5.5  | Manejo de request de edición de foto  | Dausá       | 3     |
| Mostrar candidato cercano | App Server    | 6.4  | Manejar request                       | Sella       | 2     |
|                           |               | 6.5  | Desarrollar algorimo de Match         | Sella       | 10    |
|                           |               | 6.6  | Aplicar filtros y enviar resultados   | Sella       | 6     |
| Ajustes                   | App           | 7.1  | Opción "Ajustes" en Menú              | Graffe      | 1     |
|                           |               | 7.2  | Pantalla de Ajustes                   | Graffe      | 4     |
|                           |               | 7.3  | Envío de request                      | Graffe      | 2     |
|                           | App Server    | 7.4  | Almacenamiento de ajustes             | Dausá       | 3     |
| Dar Like                  | App Server    | 8.2  | Almacenar Like                        | Sella       | 3     |
| Integración               | App           | 14.1 | Integrar App con App Server           | Graffe      | 15    |
|                           | App Server    | 14.2 | Integrar App Server con Shared Server | Rojas       | 5     |
| Correcciones              | App           | 15.1 | Agregar datos de usuario faltantes    | Graffe      | 2     |
|                           | App Server    | 15.2 | Agregar datos de usuario faltantes    | Dausá       | 2     |
|                           | Shared Server | 15.3 | Agregar datos de usuario faltantes    | Rojas       | 1     |

## Comentarios
 * Se incluyen tareas correspondientes al sprint pasado con la misma numeración. Por esto se puede observar que algunos números no son consecutivos.
