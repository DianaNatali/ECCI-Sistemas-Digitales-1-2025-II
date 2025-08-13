# Tutorial: Introducción a ```STM32CubeIDE```

## Contenido

1. [Introducción](#1-introducción)
2. [Crear un proyecto](#2-crear-un-proyecto-en-en-cubeide)
3. [Compilar y cargar](#3-compilar-y-cargar-el-elf-en-la-blue-pill)


## 1. Introducción

### ¿Qué es STM32CubeIDE?

* Entorno de desarrollo integrado (IDE) de STMicroelectronics.

* Basado en Eclipse con soporte para compilación, depuración y simulación.

* Incluye ```STM32CubeMX``` (archivo ```.ioc```) para configuración de pines y periféricos.

### Características principales

* Editor de código con resaltado de sintaxis.
* Depuración con ```ST-Link``` y ```OpenOCD```.
* Soporte para proyectos escritos en  ```C``` y ```C++```.
* Generación automática de código con ```STM32CubeMX``` (archivo ```.ioc```).
* Integración con **HAL** y **CMSIS**.

## 2. Crear un proyecto en en CubeIDE

1. Abrir ```STM32CubeIDE```.

2. Menú: ```File → New → STM32 Project```.

    <p align="center">
    <img src="/labs/figs/lab01/proj1.png" alt="proj1" width="500">
    </p>

    Se desplegará la ventana ```Target Selection```.

3. En la sección **MCU/MPU Selector** escoger la referencia del microcontrolador que se va a usar, en la casilla ```Commercial Part Number```. Para el caso de la **blue pill**
la referencia es: ```STM32F103C8T6```.

    <p align="center">
    <img src="/labs/figs/lab01/MCU_sel.png" alt="MCU_sel" width="300">
    </p>


   A la izquierda se actualizará la tabla **MCUs/MPUs List** con items asociados a esa referencia.

4. En la tabla  **MCUs/MPUs List** seleccionar esta referencia:

    <p align="center">
    <img src="/labs/figs/lab01/MCU_sel1.png" alt="MCU_sel1" width="500">
    </p>


5.  Hacer clic en el botón ```Next``` y luego aparecerá una ventana para diligenciar el nombre, ubicación y otras opciones del proyecto.

6. En la seccion **Project** de la ventana, diligenciar el nombre del proyecto en la casilla ```Project Name:```.

7. También, en la seccion **Project**, es posible escoger la ruta a la ubicación en la que se desee guardar el proyecto, para ello se debe quitar el *check* de la caja de selección ```Use default location```, lo que habilitará la casilla ```Location```y allí se podrá seleccionar la ubicación deseada o si se desea usar la ubicación por defecto, no es necesario quitar el  *check* pero se recomienda tener presente la ubicación en la que quedarán almacenados en el PC los proyectos creados a  través de ```STM32CubeIDE```.

    Las demas opciones de configuración se muestran en la siguiente imágen:

    <p align="center">
    <img src="/labs/figs/lab01/proj2.png" alt="proj2" width="500">
    </p>


5.  Hacer clic en el botón ```Next``` y luego aparecerá una ventana ```Setup STM32 target's firmware```.

6. Se recomienda dejar las opciones por defecto configuradas en la ventana ```Setup STM32 target's firmware```.

7. Hacer clic en el botón ```Finish```.

8. En la ventana principal de ```STM32CubeIDE``` encontrará lo siguiente:

    <p align="center">
    <img src="/labs/figs/lab01/interface.png" alt="interface" width="600">
    </p>

    🔴 **Project Explorer:**

    * Muestra la estructura del proyecto con carpetas:
    
        * 📂 ```Binaries/```: (Binarios)
        Aquı́ se generan los archivos compilados (```.elf```, ```.bin```, ```.hex```)
        listos para cargar en la placa. **Si está vacı́o, es posible
        que no se haya compilado el proyecto**.   

        * ```Includes/```: No es una carpeta física, sino una lista de rutas de inclusión donde el compilador buscará archivos de cabecera o *headers* (```.h```) de las bibliotecas que usa el proyecto. Incluye archivos de **CMSIS** y **HAL**
(Hardware Abstraction Layer). 
        * 📂 ```Core/```: Contiene el código principal del proyecto. Inclye: 
            * 📂 ```Inc/```: Archivos de cabecera (```.h```) propios del proyecto y de configuración.
            * 📂 ```Src/```: Archivos fuente (```.c```) con la lógica de la aplicación y funciones de inicialización. El archivo principal ```main.c``` está en esta la carpeta, que permite iniciar la ejecución del programa. También tienea archivos
de inicialización (```stm32f1xx it.c```, ```system stm32f1xx.c```). 
            * 📂 ```Startup/```.
        * 📂 ```Drivers/```: Contiene código fuente y cabeceras, es decir, librerías, para interactuar con el hardware. Incluye:

            * 📂 ```CMSIS/```: Definiciones de registros y funciones estándar para la *Cortex Microcontroller Software Interface Standard* (**Cortex-M**). Definen los registros del micro (```stm32f103xb.h```), funciones básicas (```__enable_irq()```), y el *core startup*.

            * 📂 ```STM32F1xx_HAL_Driver/```: Archivos ```.c``` y ```.h``` de la **HAL**, que contienen funciones para usar periféricos como  ```HAL_GPIO_WritePin()```, ```HAL_UART_Transmit()```, etc.

            Si se usa bare metal, solo se usa **CMSIS** y no las funciones **HAL**.
        * 📂 ```Debug/```: Es creada automáticamente por ```CubeIDE``` cuando se compila en modo Debug. Contiene: 
        
            * El archivo ```.elf``` (ejecutable con información de depuración).

            * Archivos ```.o``` (objetos compilados, uno por cada .c).

            * Archivos de mapa de memoria (```.map```).

            * El ```.bin``` si está configurado para generarlo.

            * Metadatos para que el depurador pueda mostrar el código fuente línea por línea.

    * Contiene archivos clave como el ```.ioc``` (configuración de
    ```STM32CubeMX```)

    🟢 **Editor de Código:**

    * Espacio donde se escribe y edita el código fuente del proyecto.
    * Muestra la lógica del programa, incluyendo configuración de periféricos y bucles principales.
    * Permite agregar, modificar y depurar funciones del firmware del microcontrolador.

    🟣 **Outline:**

    Muestra un resumen de las funciones del archivo abierto en el <span style="color:#00FF1A;">Editor de Código</span>, en este caso ```main.c```.

    🔵 **Consola de Depuración:**

    * Cuando NO se está en modo ```Debug```, la Consola de ```CubeIDE``` actúa como una ventana de salida del compilador y herramientas de carga.
    * Informa sobre advertencias y errores.

    * Da retroalimentación del proceso de carga, es decir, muestra el resultado de la descarga del programa en la Blue Pill. 

    * Mensajes como *Download verified successfully* indican que la programación fue exitosa.

    🌸 **Build Analyzer:**

    Muestra detalles del uso de memoria en la **RAM** y **FLASH** del microcontrolador.

## 3. Compilar y cargar el ```.elf``` en la Blue Pill

### Requerimientos:

* Programador **ST-Link**.

* Drivers instalados para **ST-Link**.

### Procedimiento:

1. **Conexión física:** 

    * Conectar los pines del **ST-Link** a la placa:

    <p align="center">
    <img src="/labs/figs/lab01/stlink-connection.jpg" alt="interface" width="600">
    </p>

    * Conectar el **ST-Link** al PC por USB.

2. **Configuración en ```STM32CubeIDE:```**

    1. Abrir el proyecto.

    2. Hacer clic en ```Build```:

        <p align="center">
        <img src="/labs/figs/lab01/build.png" alt="run" width="330">
        </p>

        Esto creará el binario ```.elf``` a partir del código principal.

    3. Ir a ```Run Configurations...```:

        <p align="center">
        <img src="/labs/figs/lab01/run1.png" alt="run" width="530">
        </p>

        Se abrirá la ventana ```Create, manage, and run configurations```.

        <p align="center">
        <img src="/labs/figs/lab01/run2.png" alt="run2" width="600">
        </p>

    4. Verificar que en la pestaña ```Main``` de la ventana ```Create, manage, and run configurations``` aparezca el nombre del projecto en la casilla ```Project```y la ruta al archivo binario ```.elf``` en la casilla ```C/C++ Application```, si no, seleccionar la ruta dando clic en el botón ```Search Project...```.

    5. Verificar en la pestaña ```Debugger``` de la ventana ```Create, manage, and run configurations``` la siguiente configuración:

        <p align="center">
        <img src="/labs/figs/lab01/run3.png" alt="run3" width="600">
        </p>

    6. En esta misma pestaña en la sección ```Interface``` hacer clic en el botón ```Scan``` con lo cual ```STM32CubeIDE``` deberá identificar el número serial del programador ```ST-Link``` que aparecerá en la casilla  ```ST-LINK S/N```.

    7. Hacer clic en el botón ```Run```.

    8. En la 🔵 **Consola de Depuración** deberán ver lo siguiente:

        <p align="center">
        <img src="/labs/figs/lab01/run4.png" alt="run4" width="400">
        </p>

        y luego:

        <p align="center">
        <img src="/labs/figs/lab01/run5.png" alt="run5" width="400">
        </p>

    
## Forzar la programación de la Blue Pill:

En caso de que la programación no sea exitosa y ```STM32CubeIDE``` arroje errores que indican que no se puede establecer una comunicación ```ST-Link``` y la **Blue Pill** se recomienda:

1. Descargar ```STM32CubeProgrammer``` en https://www.st.com/en/development-tools/stm32cubeprog.html. Se recomienda descargar la versión ```2.19.1```.

2. Intalar ```STM32CubeProgrammer``` a través del ejecutable descargado.

3. Abrir ```STM32CubeProgrammer```.

4. Hacer clic en el botón ```Connect```.

    <p align="center">
    <img src="/labs/figs/lab01/programmer.png" alt="run5" width="280">
    </p>

    Deberá ver algo como:

    <p align="center">
    <img src="/labs/figs/lab01/programmer2.png" alt="run5" width="600">
    </p>



5. Ir a la ventana ```Erasing & Programming```

    <p align="center">
    <img src="/labs/figs/lab01/programmer3.png" alt="run5" width="600">
    </p>

6. En la casilla ```File path``` seleccionar la ruta al archivo ```.elf``` generado por la compilación, a travé del botón  ```Browse```.

7. Hacer clic en ```Start programming...```.


