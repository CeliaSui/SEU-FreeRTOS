# FreeRTOS — Conceptos y guía de implementación

Este repositorio contiene documentación y ejemplos detallados sobre el uso de **FreeRTOS**, con foco en la **gestión de tareas**, **colas** y la **arquitectura del sistema** para entornos empotrados.

---

## Descripción general

**FreeRTOS** es un sistema operativo de tiempo real (RTOS) diseñado para microcontroladores. Esta guía abarca desde los fundamentos de la **planificación de tareas** hasta la **comunicación entre procesos** mediante colas.

---

## Contenidos principales

### 1. Gestión de tareas

- **Creación de tareas**: uso de la API para instanciar procesos con diferentes niveles de prioridad.
- **Estados de las tareas**: descripción de los estados `Running`, `Ready`, `Blocked` y `Suspended`.
- **Planificador (*Scheduler*)**: configuración del planificador y comportamiento según la prioridad.

### 2. Comunicación y sincronización

- **Implementación**: cómo crear y gestionar colas para el paso de mensajes entre tareas.
- **Sincronización**: uso de colas para coordinar la ejecución de múltiples procesos.

### 3. Algoritmos de planificación

- Detalles sobre parámetros críticos como `configUSE_PREEMPTION` para habilitar la expulsión (*preemption*) de tareas.
- Manejo de cambios de contexto, tanto en llamadas desde tareas como desde interrupciones (ISR), mediante la variable `pxHigherPriorityTaskWoken`.

### 4. Temporizadores

- El sistema distingue entre:
  - **Temporizadores hardware** (vinculados al chip)
  - **Temporizadores software** (gestionados por el kernel)

### 5. Gestión de interrupciones

En FreeRTOS, las interrupciones tienen prioridad absoluta sobre cualquier tarea. Una **ISR** siempre desalojará a la tarea en ejecución, independientemente de la prioridad de esta última.

---

## Configuración y uso

Para utilizar estos conceptos en un proyecto de sistemas empotrados:

1. Asegúrate de incluir los archivos de cabecera de FreeRTOS necesarios.
2. Configura el archivo `FreeRTOSConfig.h` según los requisitos de tu hardware.
3. Define las tareas y colas siguiendo los patrones de diseño descritos en la documentación adjunta.

---

## Autoría

Documentación elaborada por **Julio Molleda**, del Área de Arquitectura y Tecnología de Computadores, **Universidad de Oviedo**.

> [!NOTE]
> Este contenido forma parte del material docente para el **Máster Universitario en Ingeniería Informática** (*Sistemas Empotrados y Ubicuos*).
```
