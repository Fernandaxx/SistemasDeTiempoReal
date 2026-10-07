#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdint.h>

/* Orden completo de ejecución */
const uint8_t secuencia[] = {
    1, 3, 2,          // A
    2, 2, 3, 1,       // B
    3, 3, 3, 1, 2     // C
};

const uint8_t TOTAL_PASOS = 12;

/* Paso actual dentro de la secuencia global */
volatile uint8_t paso_actual = 0;

/* Un semáforo binario por tarea */
SemaphoreHandle_t semTareas[3];


void vTaskGenerica(void* pvParameters){
    uint8_t mi_id = (uint8_t) (uintptr_t) pvParameters;

    for (;;){
        /*
         * La tarea queda bloqueada hasta que
         * otra tarea libere su semáforo.
         */
        xSemaphoreTake(semTareas[mi_id - 1] , portMAX_DELAY);

        /* Encabezado de cada secuencia */
        if (paso_actual == 0){
            Serial.print("A. ");
        }
        else if (paso_actual == 3){
            Serial.print("\r\nB. ");
        }
        else if (paso_actual == 7){
            Serial.print("\r\nC. ");
        }


        /* Imprimir tarea */
        Serial.print("Tarea ");
        Serial.print(mi_id);


        /* Separador */
        if (paso_actual != 2 &&
            paso_actual != 6 &&
            paso_actual != 11){
            Serial.print(" - ");
        }

        vTaskDelay(pdMS_TO_TICKS(400));
        paso_actual++;


        //Si llegamos al final de C, volver al comienzo de A.
        if (paso_actual >= TOTAL_PASOS){
            paso_actual = 0;

            Serial.println();
        }


        // Determinar qué tarea debe ejecutarse a continuación.
        uint8_t id_siguiente = secuencia[paso_actual];

        // Liberar el semáforo correspondiente a la próxima tarea.
        xSemaphoreGive(semTareas[id_siguiente - 1]);
    }
}


void setup(){
    Serial.begin(9600);


    /* Crear semáforos binarios */
    semTareas[0] = xSemaphoreCreateBinary();
    semTareas[1] = xSemaphoreCreateBinary();
    semTareas[2] = xSemaphoreCreateBinary();


    /*
     * Crear las tres tareas.
     *
     * Todas tienen prioridad 1.
     */
    xTaskCreate(
        vTaskGenerica ,
        "T1" ,
        120 ,
        (void*) (uintptr_t) 1 ,
        1 ,
        NULL
    );

    xTaskCreate(
        vTaskGenerica ,
        "T2" ,
        120 ,
        (void*) (uintptr_t) 2 ,
        1 ,
        NULL
    );

    xTaskCreate(
        vTaskGenerica ,
        "T3" ,
        120 ,
        (void*) (uintptr_t) 3 ,
        1 ,
        NULL
    );


    /*
     * La primera posición de la secuencia es:
     * secuencia[0] = 1 -> liberamos Tarea 1.
     */
    xSemaphoreGive(semTareas[0]);
}


void loop(){}