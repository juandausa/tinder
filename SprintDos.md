# [Sprint 2](https://github.com/juandausa/tinder/milestones/Sprint%202)

## Objetivos del Sprint
 * Integrar las distintas partes del sistema. App, AppServer y SharedServer.
 * Completar la edición de los datos de usuario.
 * Realizar el ABM de preferencias de usuario.
 * Agregar datos de usuario faltantes.
 * Permitir la visualizaión de personas cercanas a traves de los filtros y preferencias.
 * Almacenar likes.
 * Proveer al usuario el listado de sus 'Matches'.

## Calendario
Duración del Sprint: 4 semanas.
Desde el 05/05/2016 hasta el 26/05/2016

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


### División de tareas

| Nombre                    | Area       | Id  | Descripción                          | Responsable | Costo |
|---------------------------|------------|-----|--------------------------------------|-------------|-------|
| Edición                   | App Server | 5.4 | Manejo de request de edición         | Dausá       | 3     |
|                           |            | 5.5 | Manejo de request de edición de foto | Sella       | 3     |
| Mostrar personas cercanas | App Server | 6.4 | Manejar request                      | Sella       | 2     |
|                           |            | 6.5 | Aplicar filtros y enviar resultados  | Rojas       | 6     |
| Ajustes                   | App        | 7.1 | Opción "Ajustes" en Menú             |             | 1     |
|                           |            | 7.2 | Pantalla de Ajustes                  |             | 3     |
|                           |            | 7.3 | Envío de request                     |             | 1     |
|                           | App Server | 7.4 | Almacenamiento de ajustes            |             | 3     |
| Dar Like                  | App Server | 8.2 | Almacenar Like                       |             | 2     |
| Match                     | App        | 9.1 | Request (pedir matches)              |             | 2     |
|                           |            | 9.2 | Notificar match                      |             | 5     |
|                           |            | 9.3 | Pantalla de Matches                  |             | 8     |
|                           | App Server | 9.4 | Request: Enviar Matches Viejos       |             | 4     |
|                           |            | 9.5 | Request: Enviar Matches Nuevos       |             | 5     |
|Integración|	App	|14.1	|Integrar App con App Server	| |	15|
| |	App Server	|14.2	|Integrar App Server con Shared Server	| |	5|
|Correcciones	|App	|15.1	|Agregar datos de usuario faltantes	|	| 2|
	| | App Server	|15.2	|Agregar datos de usuario faltantes	| |	2|
	| | Shared Server	| 15.3	| Agregar datos de usuario faltantes	| |	1|

## Comentarios
 * Se incluyen tareas correspondientes al sprint pasado con la misma numeración. Por esto se puede observar que algunos números no son consecutivos.
