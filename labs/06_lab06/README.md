# Lab 06: Comunicación UART con STM32 Blue Pill y ESP32

Índice:

1. [Objetivos de aprendizaje](#1-objetivos-de-aprendizaje)
2. [Materiales](#2-materiales)
3. [Fundamento teórico](#3-fundamento-teórico)
4. [Procedimiento](#4-procedimiento)

----


## 1. Objetivos de aprendizaje

* Comprender el funcionamiento básico de la comunicación serial UART.
* Configurar y utilizar el periférico UART para enviar y recibir datos.
* Implementar una interacción básica con el usuario mediante comandos enviados por puerto serial.
* Controlar un LED a partir de comandos recibidos vía UART.
* Desarrollar habilidades de programación embebida en **C** utilizando:
  - **STM32CubeIDE** (Blue Pill)
  - **ESP-IDF** (ESP32)

---

## 2. Materiales

* STM32 Blue Pill (STM32F103C8T6) **o** ESP32.
* Conversor USB – TTL para comunicación UART.

<p align="center">
    <img src="/labs/figs/lab06/conversor_serial.png" alt="alt text" width=600 >
</p>

* Cable mini USB – USB si el conversor lo requiere.
* Jumpers y protoboard.
* Entorno de desarrollo:
  - STM32CubeIDE (STM32)
  - ESP-IDF (ESP32)
* Monitor serial terminal serial (PuTTY, CoolTerm, screen, minicom, etc.)

---

## 3. Fundamento teórico


### ¿Qué es UART?

UART (**Universal Asynchronous Receiver/Transmitter**) es un protocolo de comunicación serial asíncrono que permite enviar información bit a bit por dos líneas:

* **TX (Transmit)**
* **RX (Receive)**

<p align="center">
    <img src="/labs/figs/lab06/UART.png" alt="alt text" width=600 >
</p>

El transmisor transforma datos paralelos en una secuencia serial, mientras que el receptor realiza la operación inversa, convirtiendo esa secuencia serial en datos paralelos para que el dispositivo destino pueda procesarlos.

A continuación se muestra un diagrama que ilustra el protocolo serial UART vs un protocolo paralelo:

<p align="center">
    <img src="/labs/figs/lab06/uartvsparallel.png" alt="alt text" width=600 >
</p>

* **Funcionamiento asíncrono**

  Una característica importante de UART es que trabaja de forma asíncrona.
  A diferencia de los protocolos síncronos, no requiere un reloj compartido entre el emisor y el receptor.
  Cada trama incluye sus propios bits de control, por lo que UART sigue funcionando incluso si ambos dispositivos tienen relojes distintos.

* **Bits de *start* y *stop***

  UART usa bits de inicio y de parada junto con una trama de datos para asegurar una transferencia confiable.
  Una trama suele estar formada por un bit de inicio, varios bits de datos (normalmente $8$), un bit de paridad opcional para verificación, y uno o más bits de parada.

  Cuando se envían datos, el bit de inicio marca el comienzo de la trama y el receptor se sincroniza con esa señal.
  
  Los bits de datos contienen la información enviada y la paridad opcional permite detectar errores.
  Al final, los bits de parada indican que la trama terminó.

* **Detección y corrección de Errores**
  Los mecanismos de detección y corrección de errores en UART se limitan al uso opcional de bits de paridad. Sin embargo, en este laboratorio no se utilizará paridad.

* **Velocidad en baudios y sincronización**

  Para que la comunicación sea correcta, transmisor y receptor deben configurarse con la misma velocidad en baudios (*baud rate*), que representa cuántos bits por segundo se envían.
Si ambas partes usan la misma velocidad, pueden interpretar los datos sin errores.

  Modificar el *baud rate* permite aumentar o reducir la velocidad de transferencia.
Sin embargo, tasas más altas pueden generar errores en distancias grandes o en ambientes con interferencia, por lo que se debe buscar un equilibrio entre velocidad y estabilidad.

Al ser asíncrono, no requiere línea de reloj. En cambio, tanto el emisor como el receptor deben usar la misma configuración:

* Baud rate (en este laboratorio, **9600 baudios**)
* 8 bits de datos
* Sin paridad

### Flujo básico de comunicación

1. El microcontrolador envía datos a otro dispositivo (puede ser otro microcontrolador, un periférico o el PC) usando TX.
2. El dispositivo responde enviando datos a RX.
3. El microcontrolador interpreta el carácter recibido y ejecuta alguna acción.
4. Esta respuesta puede visualizarse en un terminal serial.

---

## 4. Procedimiento

### Previo a la práctica:

Instalar y configurar un programa para comunicación serial. Se sugieren los siguientes, pero pueden usar el puerto serial de su preferencia:

* PuTTY (Windows)

* Monitor serial de Arduino

* CuteCom (Linux)

### Conexiones

#### 1. Conexión UART para Blue Pill

| USB–TTL | Blue Pill |
|---------|-----------|
| TX →    | PA10 (RX1) |
| RX →    | PA9 (TX1)  |
| GND →   | GND        |
| 3.3V →  | 3.3V       |

<p align="center">
    <img src="/labs/figs/lab06/STM32.png" alt="alt text" width=600 >
</p>

#### 2. Conexión UART para ESP32

| USB–TTL | ESP32 |
|---------|-------|
| TX →    | RX (GPIO3) |
| RX →    | TX (GPIO1) |
| GND →   | GND        |


<p align="center">
    <img src="/labs/figs/lab06/ESP32.png" alt="alt text" width=600 >
</p>


### Parte 1: "Hola! UART funcionando"

En esta primera actividad:

* Se configura el periférico UART.
* El microcontrolador envía periódicamente un mensaje al PC.
* El estudiante podrá visualizar el mensaje en un terminal serial.

Archivos disponibles en [Github Classroom](https://classroom.github.com/a/XtQ5B9vZ):

| Plataforma | Código fuente |
|------------|----------------|
| STM32 Blue Pill | `stm32/main1.c`|
| ESP32 | `esp32/main1.c` |

**Objetivo de esta parte:**  
✔ Verificar la comunicación unidireccional UART (microcontrolador → PC).

---

### Parte 2: Envío y recepción con control de LED

En esta segunda actividad:

* Se el puerto serial para enviar y recibir comandos.
* El microcontrolador interpreta los comandos recibidos Para este caso, según el comando:
  - `'1'` → LED encendido  
  - `'0'` → LED apagado
* El sistema también envía confirmación por UART.

Archivos disponibles en [Github Classroom](https://classroom.github.com/a/XtQ5B9vZ):

| Plataforma | Código fuente |
|------------|----------------|
| STM32 Blue Pill | [`stm32/main2.c`](link_a_tu_archivo) |
| ESP32 | [`esp32/main2.c`](link_a_tu_archivo) |

**Objetivo de esta parte:** 
✔ Verificar comunicación bidireccional UART (PC ↔ microcontrolador).  
✔ Aplicar control por comandos.




### Parte 3: Lectura de ADC y visualización por UART

Se integra la lectura del ADC, como se realizo en el [Lab03](/labs/03_lab03/README.md) pero, en este caso, no se utilizará la pantalla LCD para mostrar el valor, sino que el valor del voltaje leído por el ADC será enviado periódicamente por UART al PC.

El estudiante deberá ejecutar un [script de Python](/labs/06_lab06/serial_plot.py) que grafica en tiempo real el voltaje recibido desde el microcontrolador. **Deben adjuntar este script en el repositorio de Github Classrooom**


**Objetivo de esta parte:**
✔ Integrar periféricos: ADC + UART
✔ Visualizar en tiempo real el voltaje leído por el microcontrolador usando Python
✔ Reemplazar la visualización en LCD por transmisión serial