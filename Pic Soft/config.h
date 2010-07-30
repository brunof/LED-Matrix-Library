/*
   Hecho por Bruno Fascendini(BrunoF) para el foro todopic, como parte del tutorial: Librería Matríz de LEDs Universal[compilador CCS]
   Url: http://www.todopic.com.ar/foros/index.php?topic=30658
   Comenzado en Mayo de 2010
   Colaboradores:

*/
#ifndef    __config_h__
#define    __config_h__

#define     SHIFT_DATA  PIN_A1
#define     SHIFT_CLK   PIN_A2
#define     SHIFT_STB   PIN_A3

#define  FILAS       8     //defina la cantidad de filas a usar
#define  COLUMNAS    80    //defina la cantidad de columnas a usar

#define  FILAS_ANODO       FALSE    //establece si las FILAS controlaran los anodos en comun de los LEDs
#define  COLUMNAS_CATODO   FALSE    //establece si las COLUMNAS controlaran los catodos en comun de los LEDs

#if COLUMNAS > 255
   #define  modo16Bit
   unsigned int16 BufferInicio;
#else
   unsigned int8 BufferInicio;   
#endif

 //declarar el buffer que contendra los valores actuales de los LEDs y la mascara que servira para ir refrescando fila a fila
#if FILAS <= 8             
   unsigned int8 buffer[COLUMNAS], mascara;    
#elif FILAS <= 16
   unsigned int16 buffer[COLUMNAS], mascara;
   #define  mode16Bit
#else
   #error "La cantidad de filas excede el alcance de este generador"
#endif

//definir valor maximo de mascara segun cantidad de filas a usar
#if   FILAS == 7
   #define  MAX_VALOR_MASC       0x40
#elif FILAS == 8
   #define  MAX_VALOR_MASC       0x80
#elif FILAS == 9
   #define  MAX_VALOR_MASC       0x100
#elif FILAS == 10
   #define  MAX_VALOR_MASC       0x200
#elif FILAS == 11
   #define  MAX_VALOR_MASC       0x400
#elif FILAS == 12
   #define  MAX_VALOR_MASC       0x800
#elif FILAS == 13
   #define  MAX_VALOR_MASC       0x1000
#elif FILAS == 14
   #define  MAX_VALOR_MASC       0x2000
#elif FILAS == 15
   #define  MAX_VALOR_MASC       0x4000
#elif FILAS == 16
   #define  MAX_VALOR_MASC       0x8000
#endif

#define     HERTZ                60
#define     PRECARGA_TMR0        (256 - 1000000 / HERTZ / FILAS / 128 * (FOSC / 4000000))

#endif
