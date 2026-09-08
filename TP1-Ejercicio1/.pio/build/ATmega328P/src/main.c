#define F_CPU 16000000UL // Necesario definirlo antes de <util/delay.h> para temporización exacta
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

void GPIO_Init(void){
	// Entradas: PD2 y PD3 (poner en '0' en DDRD)
	DDRD &= ~((1 << DDD2) | (1 << DDD3));

	// Activar resistencias Pull-Up (poner en '1' en PORTD)
	PORTD |= (1 << PORTD2) | (1 << PORTD3);

	// Salidas: PB0 y PB1 (poner en '1' en DDRB)
	DDRB |= (1 << DDB0) | (1 << DDB1);

	// Estado inicial: ambos LEDs encendidos
	PORTB |= (1 << PORTB0) | (1 << PORTB1);
}

int main(void){
	GPIO_Init();
	bool parpadeo = false;

	while (1){
		if (!parpadeo){
			// Con Pull-up activo, presionar el pulsador envía un 0 lógico al pin
			if (!(PIND & (1 << PIND2)) || !(PIND & (1 << PIND3))){
				parpadeo = true;
			}
		}
		else{
			// Estado 1: PB0 encendido, PB1 apagado (250 ms)
			PORTB = (PORTB & ~(1 << PORTB1)) | (1 << PORTB0);
			_delay_ms(250);

			// Estado 2: PB0 apagado, PB1 encendido (250 ms)
			PORTB = (PORTB & ~(1 << PORTB0)) | (1 << PORTB1);
			_delay_ms(250);
		}
	}

	return 0;
}