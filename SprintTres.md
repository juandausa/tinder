# [Sprint 3](https://github.com/juandausa/tinder/milestones/Sprint%203)

## Objetivos del Sprint
 * Integrar las distintas partes del sistema. App, AppServer y SharedServer.
 * Permitir la visualización de personas cercanas a traves de los filtros y preferencias.
 * Informar Matches a usuarios.
 * Permitir el chat entre usuarios que matchearon.
 * Completar manuales de usuario para el Shared Server y la App.
 * Completar manuales técnicos para el App Server.
 * Completar manuales técnicos básicos para el Shared Server y la App.

## Calendario
Duración del Sprint: 3 semanas.
Desde el 02/05/2016 hasta el 23/06/2016

## Equipo
* Graffe, Fabrizio Sebastián
* Sella Faena, Jasmina
* Rojas, Agustín
* Dausá, Juan Ángel

## Compromisos

### Historias de usuario
* Un usuario puede buscar candidatos relacionados con sus intereses.
* Un usuario puede indicar si le gusta o no un candidatos.
* Un usuario puede verificar con cuales usuarios ha tenido match.
* Un usuario puede chatear con otro con que haya hecho match.

### División de tareas

| Nombre                    | Area          | Id   | Descripción                               | Responsable | Costo |
|---------------------------|---------------|------|-------------------------------------------|-------------|-------|
| Mostrar candidato cercano | App Server    | 6.5  | Desarrollar algorimo de Match             | Sella       | 5     |
|                           |               | 6.6  | Aplicar filtros y enviar resultados       | Sella       | 3     |
| Match                     | App           | 9.1  | Request (pedir matches)                   | Graffe      | 2     |
|                           |               | 9.2  | Notificar match                           | Graffe      | 3     |
|                           |               | 9.3  | Pantalla de Matches                       | Graffe      | 3     |
|                           | App Server    | 9.4  | Request: Enviar Matches Viejos            | Rojas       | 9     |
|                           |               | 9.5  | Request: Enviar Matches Nuevos            | Dausá       | 3     |
| Chat                      | App           | 10.1 | Pantalla de Chat, contactos               | Graffe      | 5     |
|                           |               | 10.2 | Requests para mensajes (entrada y salida) | Graffe      | 3     |
|                           | App Server    | 10.3 | Almacenamiento de mensajes                | Dausá       | 5     |
|                           |               | 10.4 | Envio de mensajes almacenados             | Rojas       | 3     |
|                           |               | 10.5 | Envio del listado de contactos(Matches)   | Rojas       | 2     |
| Integración               | App           | 14.1 | Integrar App con App Server               | Graffe      | 10    |
| Correcciones              | App           | 15.1 | Agregar datos de usuario faltantes        | Graffe      | 2     |
|                           | Shared Server | 15.3 | Agregar datos de usuario faltantes        | Rojas       | 1     |
| Manuales                  | App           | 16.1 | De Usuario                                | Dausá       | 3     |
|                           |               | 16.2 | De Instalación / Técnica                  | Sella       | 1     |
|                           | Shared Server | 16.3 | De Usuario                                | Dausá       | 3     |
|                           |               | 16.4 | De Instalación / Técnica                  | Dausá       | 3     |
|                           | App Server    | 16.5 | De Administrador                          | Sella       | 1     |
|                           |               | 16.6 | Técnica                                   | Dausá       | 5     |

## Comentarios
 * Se incluyen tareas correspondientes al sprint pasado con la misma numeración. Por esto se puede observar que algunos números no son consecutivos.
