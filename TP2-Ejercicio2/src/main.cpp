#include <Arduino.h>
#include <avr/io.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>

#define BAUD 9600
#define BRC ((F_CPU / 16 / BAUD) - 1)


void uart_init(void){
    UCSR0A = 0;

    UBRR0H = (uint8_t) (BRC >> 8);
    UBRR0L = (uint8_t) BRC;

    // Habilitar transmisión
    UCSR0B = (1 << TXEN0);

    // 8 bits, sin paridad, 1 bit de stop
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}


void UART_SendChar(char c){
    while (!(UCSR0A & (1 << UDRE0))){
    }

    UDR0 = c;
}


void UART_SendString(const char* str){
    while (*str){
        UART_SendChar(*str);
        str++;
    }
}


void vTaskImprimirMensaje(void* pvParameters){
    const char* nombreTarea = (const char*) pvParameters;

    for (;;){
        UART_SendString("Hola desde ");
        UART_SendString(nombreTarea);
        UART_SendString("\r\n");

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}


void setup(){
    uart_init();

    xTaskCreate(
        vTaskImprimirMensaje ,
        "T1" ,
        100 ,
        (void*) "Tarea 1" ,
        1 ,
        NULL
    );

    xTaskCreate(
        vTaskImprimirMensaje ,
        "T2" ,
        100 ,
        (void*) "Tarea 2" ,
        1 ,
        NULL
    );

    xTaskCreate(
        vTaskImprimirMensaje ,
        "T3" ,
        100 ,
        (void*) "Tarea 3" ,
        1 ,
        NULL
    );
}


void loop(){}