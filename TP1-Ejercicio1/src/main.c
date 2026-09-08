//#define F_CPU 16000000UL
#include <avr/io.h> // Definicion de Registros del microcontrolador
#include <util/delay.h> 


void GPIO_Init(void){
	DDRD &= ~((1 << PORTD2) & (1 << PORTD3)); // pulsadores (entrada)
	PORTD |= (1 << PORTD2) & (1 << PORTD3); // Resistencias Pull-UP

	DDRB |= (1 << PORTB0) & (1 << PORTB1); // Leds (salidas)
	PORTB |= (1 << PORTB0) & (1 << PORTB1); // Estado inicial encendido
}
int main(void){

	GPIO_Init();
	uint8_t parpadeo = 0;
	while (1){
		if (!parpadeo){
			if (!(PIND & (1 << PORTD2)) | !(PIND & (1 << PORTD3))){
				parpadeo = 1;
			}
		}
		else{
			PORTB ^= (1 << PORTB1);
			_delay_ms(250);
			PORTB ^= (1 << PORTB0);
		}

	}
}
