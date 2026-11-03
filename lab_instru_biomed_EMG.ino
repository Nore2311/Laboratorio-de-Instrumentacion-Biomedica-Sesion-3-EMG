#include "semg.h" // Incluye el archivo de la señal sEMG

const int PIN_DAC = 25; // GPIO25 salida DAC del ESP32
const uint32_t PERIODO_US = 488; // T = 1/2048 s ≈ 488 µs

uint16_t indice = 0;
uint32_t tiempo_siguiente = 0;

void setup() {
  tiempo_siguiente = micros();
}

void loop() {
  // Temporización precisa con micros() para evitar desvíos acumulativos
  if ((int32_t)(micros() - tiempo_siguiente) >= 0) {
    
    // Si tu versión del paquete ESP32 requiere dacWrite, usa dacWrite:
    dacWrite(PIN_DAC, SEMG[indice]);

    indice++;
    if (indice >= N_SEMG) {
      indice = 0; // Reiniciar bucle tras los 15 segundos
    }

    tiempo_siguiente += PERIODO_US; // Sumar período exacto
  }
}