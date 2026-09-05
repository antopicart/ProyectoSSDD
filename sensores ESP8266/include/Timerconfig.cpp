#include "TimerConfig.h"

volatile bool banderaLectura = false;

// ICACHE_RAM_ATTR: obliga a que la ISR viva en RAM, no en Flash -- en el
// ESP8266 el acceso a Flash puede quedar bloqueado momentáneamente (por
// ejemplo durante operaciones internas de WiFi), y si la interrupción
// estuviera en Flash en ese instante, el micro se colgaría.
void ICACHE_RAM_ATTR isrTimer() {
  banderaLectura = true;
}

void configurarTimer() {
  // Timer1 del ESP8266: reloj base de 80MHz. Con divisor TIM_DIV256
  // queda en 312.500 cuentas/segundo. Para 3 segundos: 312.500*3 = 937.500
  // cuentas (dentro del límite de 23 bits del timer, 8.388.607).
  timer1_attachInterrupt(isrTimer);
  timer1_enable(TIM_DIV256, TIM_EDGE, TIM_LOOP); // TIM_LOOP = se reinicia solo
  timer1_write(937500);
}