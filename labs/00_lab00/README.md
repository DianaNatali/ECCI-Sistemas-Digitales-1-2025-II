# Lab 00: Instalación de herramientas 

En este laboratorio nos enfocaremos en la instalación y configuración de las herramientas esenciales para el desarrollo de este curso.

Índice:


1. [Visual Studio Code](#1-visual-studio-code)
2. [Git/Githuv](#2-git-y-github)
3. [STM32CubeIDE](#3-stm32cubeide) (IDE para el microncontraldor STM32)
4. [ESP-IDF](#4-esp-idf) (IDE para el microncontraldor ESP32)
4.1 [Windows](#windows)
4.2 [Linux](#linux)





## 1. Visual Studio Code 

```Visual Studio Code``` (```VS Code```) es un editor de código ligero pero potente, desarrollado por Microsoft. Es altamente personalizable y cuenta con una amplia gama de extensiones que lo hacen ideal para el desarrollo de software y hardware.

1. Descargar Visual Studio Code: [VS Code download](https://code.visualstudio.com/).

2. Seguir las instrucciones del instalador para completar la instalación.

3. Una vez instalado, abrir ```VS Code``` y explora las extensiones disponibles en el marketplace.


## 2. ```Git``` y GitHub

Git es un sistema de control de versiones ampliamente utilizado para gestionar proyectos de software y hardware. GitHub es una plataforma basada en Git que permite alojar repositorios y colaborar en proyectos.

1. Crear cuenta en [GitHub](https://github.com/).

2. Descargar Git en el computador a través del sitio oficial: [Git download](https://git-scm.com/downloads).

3. Seguir las instrucciones del instalador.

4. Configura ```Git``` de acuerdo al nombre de usuario y correo electrónico usados al crear la cuenta en Github:

    En una terminal del sistema operativo ejecutar:

    ```
    git config --global user.name "cuenta de usario"
    git config --global user.email correo@email.com
    ```

5. Aprender los comandos básicos de Git:

    * ```git init```: Inicializa un repositorio.
    * ```git clone <url>```: Clona un repositorio remoto.
    * ```git add <archivo>```: Añade archivos al área de preparación.
    * ```git commit -m "mensaje"```: Guarda los cambios en el repositorio.
    * ```git push```: Sube los cambios al repositorio remoto.
    * ```git pull```: Actualiza el repositorio local con los cambios remotos.


## 3. ```STM32CubeIDE```

STM32CubeIDE es un entorno de desarrollo integrado (IDE) diseñado para programar y depurar microcontroladores STM32. Ofrece herramientas completas para escribir código, compilar proyectos y gestionar periféricos, todo en una sola plataforma. Es ideal para trabajar con familias de microcontroladores como la STM32 Blue Pill (```STM32F1```), permitiendo desarrollar proyectos embebidos de manera eficiente y profesional.

### Partes de STM32CubeIDE

```STM32CubeIDE``` combina varias herramientas en un solo entorno. Las partes principales son:

1. ```STM32CubeMX``` (Configuración de Hardware): Permite configurar periféricos, asignar pines y generar código de inicialización.

    * Características:

        1. Interfaz gráfica para configurar GPIO, UART, ADC, PWM, I2C, SPI, etc.

        2. Generación automática de código en C para inicializar el hardware.

        3. Configuración del sistema de relojes (Clock Tree).

    * Integración: En versiones como ```1.12.1```, ```STM32CubeMX``` está completamente integrado en la IDE. En versiones más recientes (1.15.1 o superior), debe instalarse por separado.

2. Editor de código: Permite escribir y editar código en C/C++.


3. Compilador y enlazador: Convierte el código fuente en un archivo binario (firmware) que puede cargarse en el microcontrolador. Integra el compilador GCC para ARM.

4. Depurador: Permite depurar el código para encontrar y corregir errores.

5. Programador: Carga el firmware en el microcontrolador. Compatible con programadores como ST-Link y J-Link.



###  Descargar ```STM32CubeIDE```:

1. Versión ```1.12.1```: Incluye ```STM32CubeMX``` integrado, lo que permite configurar periféricos y generar código sin necesidad de herramientas adicionales.

    Pasos a seguir:

    1. Ir al sitio oficial de STMicroelectronics: [STM32CubeIDE Download](https://www.st.com/en/development-tools/stm32cubeide.html).

    2. Hacer clic en el botón ```Get Software```.

        ![get_sw](/labs/figs/lab00/get_sw.png)

    3. Descargar la versión ```1.12.1``` de acuerdo a su sistema operativo.

        ![get_sw](/labs/figs/lab00/version_12.png)

    4. Aceptar el *License Agreement*.

    5. Crear una cuenta o continuar como invitado *Download as a guest* si no desea crear la cuenta. 

        ![get_sw](/labs/figs/lab00/guest.png)


    5. Se descargará el ```.zip``` que contiene el instalador.

    4. Seguir las instrucciones de instalación:

        * Ejecutar el instalador.

        * Seleccionar la carpeta de instalación.

        * Configurar el workspace al abrir ```STM32CubeIDE``` por primera vez.

2. Versiones Posteriores (```1.15.1``` o Superior): STM32CubeMX no está integrado y debe instalarse por separado.

    Pasos a seguir:

    1. Para ```STM32CubeIDE``` se siguen los mismos pasos enlistados en la versión ```1.12.1``` pero seleccionando la versión superior deseada.

    2. Ir al sitio oficial de ```STM32CubeMX```: [STM32CubeMX Download](https://www.st.com/en/development-tools/stm32cubemx.html).

    3. Hacer clic en el botón ```Get Software```.

    4. Descargar la versión deseada.

    5. Integrar ```STM32CubeMX``` con STM32CubeIDE:

        1. Abrir ```STM32CubeIDE```.

        2. Ir a ```Window > Preferences > STM32Cube > STM32CubeMX```.

        3. Seleccionar la ruta donde se instaló ```STM32CubeMX```.

        4. Guardar los cambios.


## 4. ESP-IDF

```ESP-IDF``` (Espressif IoT Development Framework) es un entorno de desarrollo en ```C/C++``` diseñado para programar microcontroladores de Espressif, como el ```ESP32```. Ofrece un conjunto completo de herramientas, bibliotecas y componentes que permiten desarrollar firmware facilitando la creación de aplicaciones embebidas desde cero.


###  Componentes principales de ESP-IDF

* Drivers para periféricos como GPIO, ADC, UART, SPI, I2C y PWM

* Stack de red TCP/IP completo

* Soporte para Wi-Fi y Bluetooth

* RTOS integrado, basado en FreeRTOS

* Herramientas de construcción (```idf.py```, ```CMake```, ```Ninja```)

* SDK configurable mediante ```Kconfig``` / ```menuconfig``` (similar al kernel de Linux)


### Descargar ```ESP-IDF```:

### Windows:

1. **Revisar las indicaciones de la guía oficial de instalación de Espressif para Windows:** https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/windows-setup.html

2. **Descargar el instalador:** https://dl.espressif.com/dl/esp-idf/?idf=4.4. Se recomienda descargar únicamente el *toolchain*:

    <p align="center">
    <img src="/labs/figs/lab00/esp32_1.jpeg" alt="run3" width="350">
    </p>

3. **Ejecutar el instalador:**

    1. Ejecutar el archivo ```.exe``` que se descargó en el ítem anterior.

    2. Seleccionar el idioma de su preferencia y leer y aceptar el Acuerdo de Licencia y hacer clic en ```Next```:

    <p align="center">
    <img src="/labs/figs/lab00/esp32_2.jpeg" alt="esp2" width="320">
    </p>

    <p align="center">
    <img src="/labs/figs/lab00/esp32_3.jpeg" alt="esp3" width="360">
    </p>

    3. Solucionar errore encontrados por el intalador haciendo clic en ```Apply Fixes```, luego hacer clic en ```Sí``` en el cuadro de diálogo que se abre y, finalmente, luego de que el instalador haya finalizado la verificación, hacer clic en ```Next```:

    <p align="center">
    <img src="/labs/figs/lab00/esp32_4.jpeg" alt="esp4" width="360">
    </p>


    4. Elegir la carpeta de destino de la instalación:

    <p align="center">
    <img src="/labs/figs/lab00/esp32_5.jpeg" alt="esp5" width="360">
    </p>

    5. Seleccionar componentes, los que aparecen seleccionados por defecto son suficiente, y hacer clic en ```Next```:

    <p align="center">
    <img src="/labs/figs/lab00/esp32_6.jpeg" alt="esp6" width="360">
    </p>

    6. Empezará a ejecutarse la instalación.

    7. Durante la instalación de ```ESP-IDF Tools```, aparecerá una ventana emergente de Windows:

        <p align="center">
        <img src="/labs/figs/lab00/esp32_7.jpeg" alt="esp7" width="360">
        </p>

        Hacer clic en ```Instalar```. Esto instalará el *driver* ```WinUSB``` necesario para que Windows reconozca la placa **ESP32** como puerto de programación y depuración.

    8. Esperar a que finalice la instalación:

        <p align="center">
        <img src="/labs/figs/lab00/esp32_8.jpeg" alt="esp8" width="360">
        </p>


5. **Integrar ```ESP-IDF``` con Visual Studio Code (VSC):**

    * En VSC hacer clic en el ícono de Extensiones (barra izquierda).

    * Buscar la extensión oficial de Espressif para trabajar con sus chips desde VSC, llamada ```Espressif IDF``` y hacer clic en ```Install```.

        <p align="center">
        <img src="/labs/figs/lab00/esp32_9.jpeg" alt="esp9" width="320">
        </p>

    * Aparecerá el siguiente icono:

        <p align="center">
        <img src="/labs/figs/lab00/esp32_10.jpeg" alt="esp10" width="320">
        </p>


    

6. **Verificar la instalación:** En la terminal integrada de VSC (menú ```Terminal > New Terminal```), ejecutar:

    ```
    idf.py --version
    ```

    Esto debe mostrar la versión de ESP-IDF instalada.



### Linux:

1. Revisar las indicaciones de la guía oficial de instalación de Espressif para Linux: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html


2.  Instalar las dependencias del sistema:

    * En Ubuntu/Debian:

        ```
        sudo apt-get install git wget flex bison gperf python3 python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0
        ```

3. Clonar el repositorio de ```ESP-IDF```:

    ```
    mkdir -p ~/esp
    ```
    ```
    cd ~/esp
    ```
    ```
    git clone --recursive https://github.com/espressif/esp-idf.git
    ```

    ```ESP-IDF``` se descargará en ```~/esp/esp-idf```.

4. Configuración de las herramientas: Además de ```ESP-IDF```, también es necesario instalar las herramientas que utiliza ```ESP-IDF```, como el compilador, el depurador, los paquetes de Python, etc., para proyectos compatibles con ESP32:

    ```
    cd ~/esp/esp-idf
    ```

    ```
    ./install.sh esp32
    ```

5. Personalización de la ruta de instalación de las herramientas:

    ```
    export IDF_TOOLS_PATH="$HOME/required_idf_tools_path"
    ```
    ```
    ./install.sh
    ```

    ```
    . ./export.sh
    ```

6. Integrar ```ESP-IDF``` con Visual Studio Code:

    * En VSC hacer clic en el ícono de Extensiones (barra izquierda).

    * Buscar la extensión oficial de Espressif para trabajar con sus chips desde VSC, llamada ```Espressif IDF``` y hacer clic en ```Install```.

7. Verificar la instalación: En la terminal integrada de VSC (menú ```Terminal > New Terminal```), ejecutar:

    ```
    idf.py --version
    ```

    Esto debe mostrar la versión de ESP-IDF instalada.


        