# Lab05: Generación de Señal PWM con STM32 Blue Pill o ESP32

* Comprender y aplicar los principios del modulador por ancho de pulso (PWM) mediante la configuración y programación de periféricos en microcontroladores para el control de dispositivos electrónicos.

* Identificar los conceptos fundamentales del PWM y su aplicación en sistemas embebidos.

* Configurar un periférico generador de señales PWM en un microcontrolador (STM32, ESP32 u otro) usando herramientas de desarrollo adecuadas.

* Variar parámetros como frecuencia y ciclo de trabajo (duty cycle) para observar sus efectos sobre la señal generada.

* Visualizar y analizar la señal PWM generada mediante instrumentos de medición (como osciloscopios o analizadores lógicos).

* Aplicar señales PWM en tareas de control básicas como regulación de brillo en LEDs o velocidad en motores DC.

## Materiales 

* Placa de desarrollo STM32 Blue Pill (```STM32F103C8T6```) o ESP32.

* Puente H L298N.

* Motor DC.

* Fuente de voltaje externa para el motor.

* Protoboard y cables de conexión.

* Entorno de desarrollo.


## Fundamento teórico 

### PWM

PWM (*Pulse Width Modulation* o Modulación por Ancho de Pulsos) es una técnica ampliamente utilizada para controlar la potencia entregada a dispositivos eléctricos mediante la variación del ancho de los pulsos en una señal digital de alta frecuencia. Esta modulación se utiliza para controlar la cantidad de energía que se suministra a una carga, como un motor, un LED o incluso en sistemas de regulación de voltaje.

Esta técnica es esencial para controlar motores DC, permitiendo ajustar su velocidad y sentido de giro sin necesidad de variar físicamente el voltaje de alimentación. 

<div align="center">
 <img src="/labs/figs/lab05/PWM.png" alt="pwm" width="600" />
</div>

**Características clave de la señal PWM**:

1. **Frecuencia**:
Es la cantidad de ciclos completos de la señal por segundo. La frecuencia de la señal PWM determina cuántos pulsos por segundo se envían al dispositivo. La frecuencia es importante porque debe ser alta lo suficiente como para que el ojo humano no perciba el parpadeo o el zumbido de los dispositivos, como un LED o un motor. Sin embargo, debe ser lo suficientemente baja como para no generar interferencia o ruido eléctrico.

$$ f = \dfrac{1}{\text{período}(T)} = \dfrac{1}{f}$$

2. **Ciclo de trabajo (Duty Cycle)**:
 El ciclo de trabajo es el porcentaje del tiempo durante el cual la señal permanece en un nivel alto (encendida) durante un ciclo. Se calcula como la fracción del tiempo en que la señal está en estado alto con respecto al tiempo total del ciclo.


 $$ \text{Ciclo de trabajo} = \dfrac{\text{Tiempo en alto}}{\text{Período} (T)} \times 100 $$  


3. **Frecuencia y ciclo de trabajo**: La frecuencia y el ciclo de trabajo están relacionados, pero son independientes en cuanto al control. Mientras que la frecuencia controla cuántos ciclos se repiten por segundo, el ciclo de trabajo controla la cantidad de tiempo que la señal permanece "encendida" dentro de cada ciclo.


<div align="center">
 <img src="/labs/figs/lab05/PWM02.gif" alt="pwm" width="550" />
 </div>
 
 Tomado de **[1]**


 ## Explicación de la implementación de PWM en ESP32 y STM32

En este laboratorio, se implementa el control PWM en dos plataformas: **ESP32** usando el periférico **LEDC**, y **STM32** empleando el temporizador **TIM2**. A continuación, se explica cómo se implementa el control de PWM en dos plataformas seleccionadas para trabajar en este curso: ESP32 y STM32.

### 1. ESP32

El **ESP32** integra el periférico ```LEDC``` (*LED Controller*), capaz de generar señales PWM en múltiples pines ```GPIO```. Aunque está pensado para control de iluminación LED, su uso es completamente válido para motores controlados con puente H (como el que se va a usar en este laboratorio: L298N). El ```LEDC``` permite configurar:

* Frecuencia del PWM

* Resolución del ciclo útil (*duty cycle*)

* Selección de pines y canales independientes

<div align="center">
 <img src="/labs/figs/lab05/pwmesp32.png" alt="pwm" width="550" />
 </div>


En la imagen se evidencia:

* **Timer (Temporizador)**: Se configura con la frecuencia de PWM y la resolución del ciclo de trabajo.

* **Channel (Canal)**: Controla el ciclo de trabajo del PWM, que a su vez regula la intensidad de la señal enviada a los pines GPIO.

* **GPIO (Pin de salida)**: El pin que genera la señal PWM.

El diagrama también menciona el *Fade Control* y la posibilidad de usar interrupciones, lo cual es útil para controlar transiciones suaves (desvanecimiento) y realizar acciones específicas cuando cambiar los valores de ciclo útil PWM, pero en el paqute de trabajo de Github Classroom no se emplean.


En el código propuesto en Github Classroom, se genera una señal PWM en dos pines diferentes, alternando cuál está activo para invertir el sentido de giro del motor.

* **Configuración del temporizador PWM**: Se utiliza la función ```ledc_timer_config``` para definir el temporizador que produce la base de tiempo del PWM:

    ```
    ledc_timer_config_t timer_conf = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_10_BIT,
        .timer_num        = LEDC_TIMER_0,
        .freq_hz          = 5000,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ```

    * Frecuencia: 5 kHz

    * Resolución: $10$ bits → el *duty* varía entre $0$ y $1023$

* **Configuración de canales PWM**: La señal PWM se asocia a un pin ```GPIO``` mediante ```ledc_channel_config```, donde se define el canal, el modo de salida y el ciclo de trabajo inicial.


* Canal $0$ en ```GPIO25``` → IN1 del L298N

    ```
    ledc_channel_config_t ch1_conf = { ... };
    ```

* Canal $1$ en ```GPIO26``` → IN2 del L298N

    ```
    ledc_channel_config_t ch2_conf = { ... };
    ```

    Ambos canales usan el mismo temporizador, pero pueden habilitarse o apagarse de forma independiente.

* **Control del ciclo de trabajo**: 

    El motor cambia de sentido alternando el pin que recibe PWM:

    ```
    // Adelante
    ledc_set_duty(... CH0, DUTY_SMOOTH);
    ledc_set_duty(... CH1, 0);

    // Atrás
    ledc_set_duty(... CH0, 0);
    ledc_set_duty(... CH1, DUTY_SMOOTH);

    ```

    * ```DUTY_SMOOTH``` determina la potencia aplicada (por defecto $500$ ≈ $49$%).

    * Cuando ambos canales están en $0$, el motor se detiene.


* **Resultado**:

    | IN1 (GPIO25) | IN2 (GPIO26) | Motor               |
    | ------------ | ------------ | ------------------- |
    | PWM          | 0            | Gira hacia adelante |
    | 0            | PWM          | Gira hacia atrás    |
    | 0            | 0            | Stop   |



**Se recomienda consultar: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/ledc.html**


 #### Conexiones

 <!-- <div align="center">
 <img src="/laboratorios/figs/lab05/esp32.png" alt="pwm" width="450" />
 </div> -->

 | L298N          | ESP32                | Descripción                                                      |
| -------------- | -------------------- | ---------------------------------------------------------------- |
| **IN1**        | GPIO 25              | Señal PWM para giro en un sentido                                |
| **IN2**        | GPIO 26              | Señal PWM para giro en sentido contrario                         |
| **ENA**        | Jumper colocado o 5V | Habilita el canal A del puente H (no se controla desde el ESP32) |                                     |
| **OUT1, OUT2** | Motor                | Mueve el motor con inversión de polaridad                        |
| **+12V / +6V** | Alimentación motor   | Fuente externa adecuada según el motor      
| **GND**        | GND ESP32            | Tierra común obligatoria                         |





### 2. STM32

En la plataforma **STM32** se emplea el temporizador TIM2, utilizando los canales ```CH3``` y ```CH4```, que corresponden a los pines ```PA2``` y ```PA3``` respectivamente.

* **Includes y prototipo**:

    ```
    #include "stm32f103xb.h"
    #include <stdint.h>
    ```

    ✔  Incluye el archivo de definiciones de registros del microcontrolador (```GPIO```, ```TIM```, ```RCC```).
    ✔  Permite usar tipos como ```uint32_t```.


* **Función de retardo**

    ```
    void delay_ms(uint32_t ms) {
        for(uint32_t i=0;i<ms*8000;i++) __NOP();
    }
    ```

    ✔ Retardo por software (no usa SysTick).
    ✔ ```__NOP()``` es una instrucción de ensamblador que “no hace nada”, para evitar que el compilador optimice el ```for``` vacío.
    ✔ El lazo se repite aprox. ```ms * 8000 ``` veces → $~1$ ms por iteración (aproximado a $72$ MHz).


* **Inicialización del PWM**

    ```
    void pwm_init(void){
    ```

    1. **Habilitar relojes**

        * ```RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;``` → Activa el puerto A

            Pero... ¿qué significa realmente?

            * ```RCC``` = Reset and Clock Control

            * ```APB2ENR``` = APB2 Peripheral Clock Enable Register

            * ```IOPAEN``` = I/O Port A Enable

            Esta instrucción habilita el reloj del ```GPIOA```.
            
            Si no se activa este el reloj, el puerto A no recibe señal de reloj y por tanto no funciona aunque se configuren los registros.

            Se recomienda fuertemente:
            
            1. Revisar el diagrama de *Clock tree* (Figura 8) del [manual de referencia de 
            la blue pill](../01_lab01/stm32_reference_manual.pdf).

            2. Revisar el registro ```APB2 peripheral reset register (RCC_APB2RSTR)``` en el [manual de referencia de 
            la blue pill](../01_lab01/stm32_reference_manual.pdf).

        * ```RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;``` → Activa el Timer 2

            Pero... ¿qué significa realmente?

            * ```RCC``` = Reset and Clock Control

            * ```APB1ENR``` = APB1 Peripheral Clock Enable Register

            * ```TIM2EN``` = Timer 2 Enable

            Esta instrucción habilita el reloj del periférico ```TIM2``` (Timer 2). Si no se habilita su reloj, el Timer 2 estaría apagado y ninguno de sus registros funcionaría.

            Se usa ```TIM2``` porque puede generar PWM directamente en ```PA2``` y ```PA3```, es un timer general de fácil configuración y permite controlar dos señales PWM independientes para invertir el giro del motor.

            Se recomienda fuertemente:
        

            1. Revisar el registro ```APB1 peripheral clock enable register (RCC_APB1ENR)``` en el [manual de referencia de 
            la blue pill](../01_lab01/stm32_reference_manual.pdf).


* **Configuración de PA2 y PA3 como salida PWM (Alternate Function Push-Pull)** 

    * Limpia configuración previa:
      ```
      GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2); 
      ```

      ```
      GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);
      ```

    * Salida a 50 MHz:
        ```
        GPIOA->CRL |=  (GPIO_CRL_MODE2_1 | GPIO_CRL_MODE2_0);
        ```

        ```
        GPIOA->CRL |=  (GPIO_CRL_MODE3_1 | GPIO_CRL_MODE3_0)
        ```

        ¿Por qué? Resulta que en  los microcontroladores **STM32**, cuando se configura un pin como salida, se debe definir su velocidad máxima de conmutación, no la frecuencia real de la señal. NO significa que el PWM esté funcionando a $50$ MHz.
    
    * ```PA2``` y ```PA3``` se configura como pines *Alternate Function Output Push-Pull*. 

        ```
        GPIOA->CRL |=   GPIO_CRL_CNF2_1;
        ``` 

        ```
        GPIOA->CRL |=   GPIO_CRL_CNF3_1;
        ``` 
    
    
        Lo anterior significa que:
    
        | Parámetro              | Explicación                                                                      |
        | ---------------------- | -------------------------------------------------------------------------------- |
        | **Alternate Function** | El pin ya no es GPIO normal; ahora lo controla un periférico (TIM2 en este caso) |
        | **Push-Pull**          | La salida puede conducir corriente a nivel alto y bajo       |
                     

        <div align="center">
        <img src="/labs/figs/lab05/image.png" alt="pwm" width="550" />
        </div>

        **¿Por qué es necesario Push-Pull para PWM del motor?**

        1. Porque la señal PWM tiene que cambiar rápidamente entre:

            ✔ $1$ (alto, cerca de $3.3$ V)
            ✔ $0$ (tierra)

        2. El puente H  necesita una señal fuerte y clara:

            ✔ un alto firme

            ✔ un bajo firme


* **Configuración del timer 2**:

    ```
    TIM2->PSC = 7;
    TIM2->ARR = 1999;
    ```

    * ```PSC``` es el prescaler: divide la frecuencia del reloj para ajustar la velocidad a la que cuenta el timer.

    * ```ARR``` es el valor máximo del contador: cuando el contador llega a ```ARR```, se reinicia.

    El ciclo PWM se basa en este contador:

    * Si el contador va de $0$ a $1999$, el período completo tiene $2000$ pasos.

    * Eso significa que un valor de ```CCR``` $= 500$ representa:

    $$ \dfrac{500}{2000} = 0.25 → 25\% \text{ de ciclo útil} $$


    Entre más grande sea ```CCR```, mayor será el tiempo en que la salida se mantiene en nivel alto → más potencia para el motor. 

    Posteriormente se debe:

    1. **Limpiar configuración previa**

        ```
        TIM2->CCMR2 &= ~(TIM_CCMR2_OC3M | TIM_CCMR2_OC3PE);
        ```

        ```
        TIM2->CCMR2 &= ~(TIM_CCMR2_OC4M | TIM_CCMR2_OC4PE);
        ```
    2. **Seleccionar modo PWM1**

        ```
        TIM2->CCMR2 |=  (6 << TIM_CCMR2_OC3M_Pos);
        ```

        ```
        TIM2->CCMR2 |=  (6 << TIM_CCMR2_OC4M_Pos);
        ```

        Entonce, se tiene que:

        $6$ (binario $110$) configura el canal en PWM modo 1, donde:

        * La salida es alta cuando el contador está debajo del valor de ```CCR3$```

        * La salida es baja cuando lo supera 
        
        → eso genera una señal PWM real


    3. **Habilitar Preload (OC3PE)**

        Permite cambiar el duty ($CCR3$) sin que la señal se distorsione.

        El nuevo valor se aplica al final del ciclo, evitando “saltos” o parpadeos en el PWM.

        ```
        TIM2->CCMR2 |=   TIM_CCMR2_OC3PE;
        ```

        ```
        TIM2->CCMR2 |=   TIM_CCMR2_OC4PE;
        ```

* **Activación de la salida PWM**

    Para que el PWM llegue físicamente al pin, el canal debe habilitarse:

    * Activa salida PWM en ```CH3``` (```PA2```):
        ```
        TIM2->CCER |= TIM_CCER_CC3E;  
        ``` 
    
    * Apaga salida PWM en ```CH4``` (```PA3```)
        ```
        TIM2->CCER &= ~TIM_CCER_CC4E;  
        ```

    Entonces:

    * ```CC3E``` habilita el canal $3$ del timer → eso hace que la señal PWM se refleje en el pin ```PA2```.

    * ```CC4E``` hace lo mismo, pero para el canal $4$ (```PA3```).

    Lo anterior quiere decir que:

    * Si ```CC3E``` está encendido y ```CC4E``` apagado → el motor recibe PWM por ```IN1``` y gira hacia un lado.
    * Si ```CC3E``` apagado y ```CC4E``` encendido → la señal está en ```IN2``` y el motor gira al lado contrario.
    * Si ambos están apagados, no hay PWM en ninguna salida → el motor se detiene.

#### Conexiones:

| L298N          | STM32                | Descripción                      |
| -------------- | -------------------- | -------------------------------- |
| **IN1**        | PA2 (TIM2_CH3)       | PWM hacia motor (sentido 1)      |
| **IN2**        | PA3 (TIM2_CH4)       | PWM hacia motor (sentido 2)      |
| **ENA**        | Jumper colocado o 5V | Habilita el canal A del puente H |      |
| **OUT1, OUT2** | Motor                | Motor DC                         |
| **+12V / +6V** | Alimentación motor   | Fuente externa                   |
| **GND**        | GND STM32            | Tierra común obligatoria   


## ¿Qué deben hacer en el laboratorio?

1. **Aceptar la tarea en GitHub Classroom**
    
    Descargar el código base correspondiente a la plataforma que usarán (STM32 o ESP32).

2. **Crear el proyecto y compilar**

    * Para **STM32 Blue Pill**: ```STM32CubeIDE```.

    * Para **ESP32**: ```ESP-IDF```.

    * Para este laboratorio, el proyecto no debe quedar en un solo archivo ```.c```. Debe dividirse en al menos 3 archivos:

        * ```main.c```
        * ```pwm.c```
        * ```pwm.h```


3. **Realizar el montaje físico**

    Conectar la tarjeta al puente H L298N y al motor según las tablas de conexión.


3. **Probar el código inicial**

    * Verificar que el motor gira en un sentido, se detiene y cambia al sentido contrario.

    * Subir un vídeo a Github Classroom

4. **Experimentar con el ciclo útil (duty)**

    * Cambiar el valor del ```CCR``` (**STM32**) o el ```DUTY_SMOOTH``` (**ESP32**).

    * Registrar cómo cambia la velocidad (más lento, más rápido).

    * Probar duty en: $10$%, $30$%, $50$%, $80$% y $100$%.

5. **Visualizar la señal PWM**

    * Usar un osciloscopio y capturar una imagen de la señal para al menos 2 valores de duty.

    * Identificar el periodo ($1/f$) y medir tiempo en alto y calcular el ciclo útil para cada imagen.

6. **Documentar**

    * Explicar cada función usada y los registros empleados en ellas según corresponda.

    * Describir el efecto del ciclo útil en el motor.

    * Incluir capturas del osciloscopio.




