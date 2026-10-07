# Ejercicio 1 — Creación y manejo de tareas en FreeRTOS

## Consigna

> Investigue y analice las posibilidades que brinda FreeRTOS para la creación y el manejo de tareas.
>
> Identifique cada una de las características que deben ser consideradas al momento de definir una tarea.

## Organización de una aplicación en tareas

FreeRTOS permite organizar una aplicación en varias **tareas concurrentes**. Cada tarea representa una actividad independiente del sistema y es administrada por el planificador del sistema operativo.

Una tarea en FreeRTOS se implementa mediante una función, generalmente con un ciclo infinito, por ejemplo:

```c
void Tarea1(void *pvParameters)
{
    while (1)
    {
        // Código de la tarea
    }
}
```

## Creación de una tarea

Para crear una tarea se utiliza la función `xTaskCreate()`. Al momento de definir una tarea se deben considerar principalmente las siguientes características:

| Característica | Descripción |
| --- | --- |
| **Función de la tarea** | Contiene el código que la tarea debe ejecutar. |
| **Nombre** | Identifica la tarea y facilita la depuración. |
| **Tamaño del stack** | Memoria reservada para la ejecución de la tarea. |
| **Parámetros** | Datos que pueden pasarse a la tarea cuando se crea. |
| **Prioridad** | Determina qué tarea tiene preferencia para utilizar la CPU cuando varias están listas para ejecutarse. |
| **Handle** | Referencia que permite identificar y manipular posteriormente a la tarea. |

## Estados de una tarea

Durante su ejecución, una tarea puede encontrarse en distintos estados:

| Estado | Descripción |
| --- | --- |
| **Running** | La tarea está ejecutándose en la CPU. |
| **Ready** | Está lista para ejecutarse, pero espera a que el planificador le asigne la CPU. |
| **Blocked** | Está esperando que ocurra un evento o que finalice un tiempo de espera. |
| **Suspended** | Fue suspendida explícitamente y no participa de la planificación hasta ser reanudada. |

## Administración de tareas

FreeRTOS también brinda funciones para administrar las tareas durante la ejecución, permitiendo:

- Crearlas y eliminarlas.
- Suspenderlas y reanudarlas.
- Modificar su prioridad.
- Bloquearlas temporalmente.

## Relación con la programación concurrente

El uso de tareas permite dividir un programa complejo en actividades más simples y concurrentes, lo cual facilita la organización del software y permite que diferentes partes del sistema progresen de manera independiente.

Esto se relaciona con el concepto de **programación concurrente** visto en la materia, donde varios procesos cooperan para realizar una tarea conjunta.
