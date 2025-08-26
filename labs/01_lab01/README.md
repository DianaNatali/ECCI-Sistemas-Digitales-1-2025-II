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

    * Crear un proyecto vacío en ```STM32CubeIDE``` como se explica en el tutorial [Introducción a STM32CubeIDE](/labs/01_lab01/tutorial_cubeIDE.md).

    * En el ```main.c``` implementar el código que se descarga al aceptar la tarea en ```Github Classroom```.

    * Compilar y cargar el binario a la blue pill según las indicaciones dadas en [Introducción a STM32CubeIDE](/labs/01_lab01/tutorial_cubeIDE.md).

2. **API/HAL mínima**


    * Crear un proyecto en vacío en ```STM32CubeIDE``` como se explica en el tutorial [Introducción a STM32CubeIDE](/labs/01_lab01/tutorial_cubeIDE.md).

    * Usar ```CubeMx``` para construir el proyecto como se detalla a continuación: 

        1. Abrir el archivo con extensión ```.ioc``` generado junto con las carpetas del proyecto:

            <p align="center">
            <img src="/labs/figs/lab00/hal1.png" alt="hal1" width="300">
            </p>

        2. Se mostrará el circuito integrado del microcontrolador seleccionado (en este caso, la **Blue Pill** con el ```STM32F103C8T6```). Esta vista gráfica de ```CubeMX```, en la pestaña ```Pinout & Configuration``` representa el encapsulado del microcontrolador y permite configurar cada uno de sus pines según la función deseada (entrada, salida, periférico, etc.):

            <p align="center">
            <img src="/labs/figs/lab00/hal2.png" alt="hal2" width="450">
            </p>

        3. Hacer clic en el pin ```PC13``` (LED de la Blue Pill) y configurarlo como ```GPIO_Output```.

            <p align="center">
            <img src="/labs/figs/lab00/hal3.png" alt="hal2" width="310">
            </p>

        4. Guardar el archivo de configuración (```.ioc```) usando ```Ctrl + S```. Esto asegura que ```CubeMX``` almacene los cambios realizados en los pines antes de generar el código.

        5. Aparecerá el siguiente cuadro de diálogo:

            <p align="center">
            <img src="/labs/figs/lab00/hal4.png" alt="hal2" width="310">
            </p>

            **Dar clic en el botón ```Yes```, con lo cual CubeMX regenerará automáticamente el código fuente necesario (archivos de inicialización y funciones HAL). De esta forma, la configuración del ```pin PC13``` como salida queda reflejada en el archivo ```main.c``` y en los módulos generados por HAL.**

        6. En el archivo ```main.c``` se encontrará la estructura básica del programa generada por ```CubeMX```:
            - Funciones de inicialización ya creadas, como ```MX_GPIO_Init()``` y ```SystemClock_Config()```.

            - Un bucle infinito ```while(1)``` vacío, listo para agregar el código de la aplicación.

        7. En el archivo main.c, dentro del bucle infinito (```while (1)```), agregar el código para alternar el estado del LED:

            ```
            while (1)
            {
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); 
                HAL_Delay(500);
            }
            ```

            Con esto, el LED conectado al pin ```PC13``` de la Blue Pill parpadeará cada $500$ ms.
            Se puede modificar el valor de ```HAL_Delay()``` para cambiar la frecuencia de parpadeo.


    * Compilar y cargar el binario a la blue pill según las indicaciones dadas en [Introducción a STM32CubeIDE](/labs/01_lab01/tutorial_cubeIDE.md).

3. **FreeRTOS con tarea** 

    * Crear un proyecto vacío en ```CubeIDE``` como se explica en el tutorial [Introducción a STM32CubeIDE](/labs/01_lab01/tutorial_cubeIDE.md) y en clase.

    * Usar ```CubeMx``` para construir el proyecto  como se hizo en la sección de esta guía **API/HAL mínima**:

        1. Configurar el pin ```PC13``` como ```GPIO_Output``.
        2. En la categoría ```Middleware``` de la pestaña ```Pinout & Configuration```, escoger ```FreeRTOS```:

            <p align="center">
            <img src="/labs/figs/lab00/rtos1.png" alt="rtos1" width="310">
            </p>

            <p align="center">
            <img src="/labs/figs/lab00/rtos2.png" alt="rtos2" width="310">
            </p>


        3. Se abrirá la secciṕn ```FREERTOS Mode and Configuration```. En ```Interface```seleccionar ```CMSIS_V2```, lo que hará que en la sección ```Configuration```
        aparezcan varios *widgets* para establecer los parámetros del sistema operativo:

            <p align="center">
            <img src="/labs/figs/lab00/rtos3.png" alt="rtos3" width="310">
            </p>


            * ```Config parameters```: Configuración del Kernel (modo de planificación, prioridad de interrupciones, tamaño mínimo de stack, etc.).

            * ```Tasks and Queues```: permite agregar tareas, definir su prioridad, nombre y tamaño de pila.

            * ```Mutexes``` y ```Events```: para sincronización entre tareas.

            * ```Timers and Semaphores```: para tareas periódicas con *callbacks*.

        4. Ir a la pestaña ```Tasks and Queues```, aparecerán dos secciones ```Task```y ```Queues``` dar clic en ```Add``` para crear una nueva tarea:

            <p align="center">
            <img src="/labs/figs/lab00/rtos4.png" alt="rtos4" width="310">
            </p>


        5. Aparecerá la ventana ```New Task```, en ella asignar las siguientes propiedades:

            <p align="center">
            <img src="/labs/figs/lab00/rtos5.png" alt="rtos5" width="310">
            </p>

            * ```Name:``` BlinkTask

            * ```Priority:``` osPriorityLow (suficiente para este ejemplo simple).

            * ```Stack Size:``` 128

            * ```Function:``` StartBlinkTask.

            y dar clic en el botón ```OK```.

        6. Guardar los cambios (```Ctrl + S```) y aceptar la regeneración de código (```Yes```), como se hizo en la sección de esta guía **API/HAL mínima**.

        7. Aparecerá el siguiente cuadro de diálogo:

            <p align="center">
            <img src="/labs/figs/lab00/rtos6.png" alt="rtos6" width="310">
            </p>

            dar clic en el botón ```Yes```.

        7. ```CubeMX``` generará el archivo ```freertos.c```, donde aparecerá la plantilla de la tarea ```StartBlinkTask()```.

            <p align="center">
            <img src="/labs/figs/lab00/rtos7.png" alt="rtos7" width="310">
            </p>




#### Con ESP32 

##### En linux:

##### En windows



### Pruebas y comparación

* Verificar que el LED parpadee correctamente y cambiar la frecuencia del parpadeo.

* Documentar detalladamente en el archivo ```README.md``` cada uno de las implementaciones a nivel de registros y funciones, según corresponda a cada enfoque.

* Comparar:

    * Complejidad del código y número de líneas.

    * Facilidad de mantenimiento y portabilidad.

    * Consumo de memoria (flash y RAM).

    * Flexibilidad para cambiar frecuencia o agregar más tareas.

## 4. Entregables

* Código fuente de cada proyecto.

* Documentación en repositorios con descripción de cada implementación, comparación y conclusiones.

* Evidencias de la implementación.