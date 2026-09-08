#include <vcd.h> 
AVR_MCU_VCD_FILE("simavr_trace.vcd", 10);
const struct avr_mmcu_vcd_trace_t _mytrace[] _MMCU_ = {

    // Ver todo el puerto D (entrada)
    { AVR_MCU_VCD_SYMBOL("PIND"), .what = (void*)&PIND },

    // Ver todo el puerto B (salida)
    { AVR_MCU_VCD_SYMBOL("PORTB"), .what = (void*)&PORTB },

    // Ver SOLO el LED (PB5)
    { AVR_MCU_VCD_SYMBOL("LED_PB5"), .mask = (1 << PB5), .what = (void*)&PORTB },

    // Ver SOLO el botón (PD2)
    { AVR_MCU_VCD_SYMBOL("BTN_PD2"), .mask = (1 << PD2), .what = (void*)&PIND },
};