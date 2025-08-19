# Lab 01: Blinker: Bare Metal, API y RTOS

## 1. Objetivos de aprendizaje


1. Comprender la diferencia entre programación de bajo nivel (bare metal) y programación con APIs de alto nivel.

2. Identificar el impacto de un RTOS en la estructura y ejecución del programa.

3. Implementar un mismo ejemplo (blinker) en tres niveles de abstracción:

    * Bajo nivel (acceso directo a registros).

    * API de periféricos.

    * Multitarea con RTOS.


## 2. Fundamentos teóricos

* Consultar la siguiente [documentación](/labs/01_lab01/presentacion1.pdf).

* Consultar los manuales de los microcontroladores:

    * [STM32](/labs/01_lab01/stm32_reference_manual.pdf)

    * [ESP32 datasheet](/labs/01_lab01/esp32_reference_manual.pdf) y [ESP32 programming guide](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html)

## 3. Materiales y herramientas

* Para ```STM32```

    * ```STM32F103C8T6``` (**"Blue Pill"**).

    * ```ST-Link V2``` (para programar y depurar el ```STM32```).

    * ```STM32CubeIDE``` instalado.


* Para ```ESP32```

    * ```ESP32 DevKitC``` o similar.

    * Cable USB para programación.

    * ```ESP-IDF``` instalado.


## 3. Procedimiento

#### Con STM32

1. **Bare Metal Puro**

    * Aceptar la tarea en ```Github Classroom``` para este laboratorio, en la tabla ```Cronograma``` de la página principal del repositorio del curso en la columna ```Entrega (Github Classroom)```.  

    * Crear un proyecto vacío en ```CubeIDE``` como se explica en el tutorial [Introducción a STM32CubeIDE](/labs/01_lab01/tutorial_cubeIDE.md).

    * En el ```main.c``` implementar el código que se descarga al aceptar la tarea en ```Github Classroom```.

    * Compilar y cargar el binario a la blue pill según las indicaciones dadas en [Introducción a STM32CubeIDE](/labs/01_lab01/tutorial_cubeIDE.md).

2. **API HAL mínima** (En construcción ⚠️)


    * Crear un proyecto vacío en ```CubeIDE``` como se explica en el tutorial [Introducción a STM32CubeIDE](/labs/01_lab01/tutorial_cubeIDE.md).

    * Seguir los pasos en de la sección[]()

3. **FreeRTOS con tarea** (En construcción ⚠️)

    * Activar FreeRTOS en CubeMX.

    * Crear tarea que alterne el LED cada $500$ ms usando ```vTaskDelay()```.

#### Con ESP32 

##### En linux:

#### Pruebas y comparación**

* Verificar que el LED parpadee correctamente y cambiar la frecuencia del parpadeo.

* Documentar detalladamente en el archivo ```README.md``` cada uno de las implementaciones a nivel de registros y funciones, según corresponda a cada enfoque.

* Comparar:

    * Complejidad del código y número de líneas.

    * Facilidad de mantenimiento y portabilidad.

    * Consumo de memoria (flash y RAM).

    * Flexibilidad para cambiar frecuencia o agregar más tareas.

## 4. Entregables

* Código fuente para cada proyecto.W

* Documentación en repositorios con descripción de cada implementación, comparación y conclusiones.

* Evidencias de la implementación.