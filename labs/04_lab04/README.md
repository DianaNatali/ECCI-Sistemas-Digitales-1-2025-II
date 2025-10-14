# Actividad Evaluativa: Cronómetro con Control de Velocidad (FreeRTOS + ADC + LCD I²C + 3 Botones)


## Objetivo general

Implementar un cronómetro multitarea empleando ```FreeRTOS``` que mida horas, minutos y segundos,
controlado por tres botones (```START```, ```PAUSE```, ```RESET```) y un potenciómetro (```ADC```) que ajusta la velocidad del conteo.
El sistema debe visualizar el tiempo y la velocidad en una **LCD 16×2** mediante protocolo I2C y usar un LED para indicar el estado.


## Descripción general del sistema

El sistema consiste en un cronómetro digital con tres modos de operación:

1. ```RUN```: el cronómetro avanza.

2. ```PAUSE```: el cronómetro se detiene sin perder el tiempo actual.

3. ```RESET```: el cronómetro se detiene y vuelve a ```00:00:00```.

* El potenciómetro (```ADC```) ajusta la velocidad del conteo entre ```0.5×``` y ```1.5×```.
* La LCD muestra el tiempo y la velocidad.
* El LED indica si el cronómetro está corriendo o detenido.

## Tareas del sistema (FreeRTOS)
| Tarea           | Función                                                         |
| --------------- | --------------------------------------------------------------- |
| **TaskADC**     | Lee el potenciómetro (ADC) y calcula la velocidad (0.5×–1.5×).  |
| **TaskClock**   | Incrementa el tiempo (hh:mm:ss) cuando el estado es RUN.        |
| **TaskLCD**     | Muestra el tiempo y la velocidad o estado en el LCD.            |
| **TaskButtons** | Lee los tres botones y actualiza el estado (RUN, PAUSE, RESET). |
| **TaskLED**     | Indica con el LED el estado del cronómetro.                     |

## Estados del sistema:

| Estado        | Descripción                           | LED            | LCD         |
| ------------- | ------------------------------------- | -------------- | ----------- |
| **RESET (0)** | Cronómetro detenido y en cero.        | Apagado        | “RESET”     |
| **RUN (1)**   | El tiempo avanza según el ADC.        | Encendido fijo | “Vel: x.xx” |
| **PAUSE (2)** | Cronómetro detenido, conserva tiempo. | Parpadeo lento | “PAUSE”     |


## Funcionamiento de los botones

Los botones están configurados con resistencia de pull-up interna:

| Estado físico             | Voltaje | Valor lógico | Acción   |
| ------------------------- | ------- | ------------- | -------- |
| Sin presionar             | 3.3 V   | 1             | Inactivo |
| Presionado / Jumper a GND | 0 V     | 0             | Activo   |


## Conversión ADC → Velocidad

$$speed\_factor=0.5+1.0×\dfrac{ADC}{4095}$$


| ADC  | Velocidad | Descripción       |
| ---- | ---------- | ----------------- |
| 0    | 0.5×       | Cronómetro lento  |
| 2048 | ≈1.0×      | Velocidad normal  |
| 4095 | 1.5×       | Cronómetro rápido |

## Visualización esperada en la LCD

* Modo ```RUN```

    ```
    00:05:42
    Vel: 1.00x
    ```

* Modo ```PAUSE```
    ```
    00:05:42
    PAUSE
    ```

* Modo ```RESET```

    ```
    00:00:00
    RESET
    ```
