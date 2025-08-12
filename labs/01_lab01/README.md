# Lab 02: Blinker en Bare-Metal vs HAL vs FreeRTOS con STM32CubeIDE y ESP-IDF

## 1. Objetivos de aprendizaje

1. Aprender a programar microcontroladores STM32 y ESP32 usando diferentes niveles de abstracción: Bare-Metal, HAL (API de alto nivel) y FreeRTOS.

2. Comparar ventajas y desventajas de cada enfoque en complejidad, portabilidad y consumo de recursos.

## 2. Materiales y herramientas

* STM32

    * STM32F103C8T6 ("Blue Pill").

    * ST-Link V2 (para programar y depurar el STM32).

    * ```STM32CubeIDE``` instalado.

    * Un LED (o usar el LED de la Blue Pill)

    * Resistencia $220$ Ω (si se usa LED externo).

* ESP32

    * ESP32 DevKitC o similar.

    * Cable USB para programación.

    * ESP-IDF instalado.

    * LED (o usar el LED de la placa)

    * Resistencia $220$ Ω (si se usa LED externo).

## 3. Procedimiento
* **Paso 1: Crear tres proyectos independientes para cada plataforma**

    * **Proyecto 1**: Bare-Metal
    Programar directamente sobre los registros del microcontrolador sin usar librerías adicionales. Permite entender el control de hardware a bajo nivel.

    * **Proyecto 2**: HAL / API de alto nivel
    Usar las librerías oficiales para configuración y control del hardware: STM32Cube HAL para STM32, y ESP-IDF para ESP32. Facilita el desarrollo y mejora la portabilidad.

    * **Proyecto 3**: FreeRTOS
    Implementar el parpadeo del LED como una tarea dentro del sistema operativo FreeRTOS, para gestionar temporización y multitarea de manera eficiente.

* **Paso 2: Configuración del LED**

    * Identificar el pin LED:

        * STM32: PC13 (LED integrado en Blue Pill).

        * ESP32: GPIO2 (generalmente LED integrado).

    * Configurar el pin como salida digital:

        * En Bare-Metal, configurar registros GPIO.

        * En HAL / API, usar funciones de la librería.

        * En FreeRTOS, realizar la configuración dentro de la tarea o antes de iniciar el scheduler.

* **Paso 3: Implementación del blinker**

    Aceptar la tarea en Gihub Classroom con códigos fuente para implementarlos en los proyectos previamente creados.

* **Paso 4: Pruebas y comparación**

    * Verificar que el LED parpadee correctamente en los tres proyectos.

    * Comparar:

        * Complejidad del código y número de líneas.

        * Facilidad de mantenimiento y portabilidad.

        * Consumo de memoria (flash y RAM).

        * Flexibilidad para cambiar frecuencia o agregar más tareas.

## 4. Entregables

* Código fuente para cada proyecto y plataforma.

* Informe comparativo con observaciones, resultados y conclusiones.

* Evidencias de la implementación.