# Lab 06: Comunicación UART con STM32 Blue Pill y ESP32

## Objetivos de aprendizaje

* Comprender el funcionamiento básico de la comunicación serial UART.
* Configurar y utilizar el periférico UART para enviar y recibir datos.
* Implementar una interacción básica con el usuario mediante comandos enviados por puerto serial.
* Controlar un LED a partir de comandos recibidos vía UART.
* Desarrollar habilidades de programación embebida en **C** utilizando:
  - **STM32CubeIDE** (Blue Pill)
  - **ESP-IDF** (ESP32)

---

## Materiales

* STM32 Blue Pill (STM32F103C8T6) **o** ESP32.
* Conversor USB – TTL (3.3 V) para comunicación UART.
* Cable mini USB – USB si el conversor lo requiere.
* Jumpers y protoboard.
* Entorno de desarrollo:
  - STM32CubeIDE (STM32)
  - ESP-IDF (ESP32)
* Monitor serial terminal serial (PuTTY, CoolTerm, screen, minicom, etc.)

---

## Fundamento teórico

### ¿Qué es UART?

UART (**Universal Asynchronous Receiver/Transmitter**) es un protocolo de comunicación serial asíncrono que permite enviar información bit a bit por dos líneas:

* **TX (Transmit)**
* **RX (Receive)**

Al ser asíncrono, no requiere línea de reloj. En cambio, tanto el emisor como el receptor deben usar la misma configuración:

* Baud rate (en este laboratorio, **9600 baudios**)
* 8 bits de datos
* Sin paridad
* 1 bit de stop  → **8N1**

### Flujo básico de comunicación

1. El microcontrolador envía datos a otro dispositivo (puede ser otro microcontrolador, un periférico o el PC) usando TX.
2. El dispositivo responde enviando datos a RX.
3. El microcontrolador interpreta el carácter recibido y ejecuta alguna acción.
4. Esta respuesta puede visualizarse en un terminal serial.

---

## Procedimiento

### Parte 1: "Hola! UART funcionando"

En esta primera actividad:

* Se configura el periférico UART.
* El microcontrolador envía periódicamente un mensaje al PC.
* El estudiante podrá visualizar el mensaje en un terminal serial.

Archivos disponibles:

| Plataforma | Código fuente |
|------------|----------------|
| STM32 Blue Pill | [`/parte1/stm32/main.c`](link_a_tu_archivo) |
| ESP32 | [`/parte1/esp32/main.c`](link_a_tu_archivo) |

Objetivo de esta parte:  
✅ Verificar la comunicación unidireccional UART (microcontrolador → PC).

---

### Parte 2: Envío y recepción con control de LED

En esta segunda actividad:

* Se habilita recepción de caracteres desde el puerto serie.
* El microcontrolador interpreta los comandos recibidos.
* Según el comando:
  - `'1'` → LED encendido  
  - `'0'` → LED apagado
* El sistema también envía confirmación por UART.

Archivos disponibles:

| Plataforma | Código fuente |
|------------|----------------|
| STM32 Blue Pill | [`/parte2/stm32/main.c`](link_a_tu_archivo) |
| ESP32 | [`/parte2/esp32/main.c`](link_a_tu_archivo) |

Objetivo de esta parte:  
* Verificar comunicación bidireccional UART (PC ↔ microcontrolador).  
* Aplicar control por comandos.

---

## Configuración mínima del hardware

### 1. Conexión UART para Blue Pill

| USB–TTL | Blue Pill |
|---------|-----------|
| TX →    | PA10 (RX1) |
| RX →    | PA9 (TX1)  |
| GND →   | GND        |
| 3.3V →  | 3.3V       |

<p align="center">
    <img src="/labs/figs/lab06/STM32.png" alt="alt text" width=600 >
</p>

> **Nota:** El LED integrado en la Blue Pill está conectado al pin **PC13** (activo en bajo).

### 2. Conexión UART para ESP32

| USB–TTL | ESP32 |
|---------|-------|
| TX →    | RX (GPIO3) |
| RX →    | TX (GPIO1) |
| GND →   | GND        |


<p align="center">
    <img src="/labs/figs/lab06/ESP32.png" alt="alt text" width=600 >
</p>

> **Nota:** En el ESP32, el LED integrado varía según la placa. 

---

## Pruebas con terminal serial

1. Conectar el microcontrolador al PC.
2. Abrir un programa de terminal serial:
   * 9600 baudios
   * 8 bits de datos
   * Sin paridad
   * 1 bit de stop (8N1)
3. Observar el mensaje inicial (“Hola! UART funcionando”).
4. Enviar `'1'` y `'0'` para controlar el LED.

Resultado esperado:

