/*
   Hecho por Bruno Fascendini(BrunoF) para el foro todopic, como parte del tutorial: Librería Matríz de LEDs Universal[compilador CCS]
   Url: http://www.todopic.com.ar/foros/index.php?topic=30658
   Comenzado en Mayo de 2010
   Colaboradores:

*/
#ifndef    __publik_c__
#define    __publik_c__

#include "config.h"        //contiene la configuración del publik y ciertos cálculos/generacion de variables automáticos en base a ella
#include "typos.c"         //contiene la información de las tipografias a utilizar 

const char demo[] = "HOLA FORO TODOPIC!";

int1  ejecutando;          //variable global que controla la activacion general del cartel!
int1  nuevoFrame;          //variable global que indica si se acaba de completar un frame completo!
int1  nuevoEfecto;         //Indica si es la primera vez que se ejecuta el efecto.

unsigned int16 archivoPosicionActual;
char vidaRestante, velocidad, velocidadTmp, efecto; 

//extern void efecto_rota_izq();

#include "efectos.c"       //contiene las funciones que definen el comportamiento de los efectos...



//Inicializa las variables del publik y demás configuración
void Publik_Inicializar(void)
{
   mascara = 0x01;         //primer fila
   nuevoFrame = FALSE;
   velocidad = 6;
   //falta...
}

void Publik_Refrescar(void)
{
   #ifdef mode16Bit
      unsigned int16 i, j, aux;
   #else
      unsigned int8 i, j, aux;
   #endif

   //ENVIO DE COLUMNAS A ENCENDER
   if(!BufferInicio) j = COLUMNAS - 1; else j = BufferInicio - 1;
   for(i =0; i < COLUMNAS; i++)
   {
      #if(COLUMNAS_CATODO)
         if(buffer[j] & mascara) output_low(SHIFT_DATA); else output_high(SHIFT_DATA);    //enviar cada columna en alto o bajo segun corresponda.
      #else
         if(buffer[j] & mascara) output_high(SHIFT_DATA); else output_low(SHIFT_DATA);    //enviar cada columna en alto o bajo segun corresponda con logica invertida      
      #endif
      output_high(SHIFT_CLK);
      output_low(SHIFT_CLK);
      
      if(!j) j = COLUMNAS - 1; else j--;
   }
   
   //ENVIO DE FILA A ENCENDER
   #if(FILAS_ANODO)
      aux = mascara;
   #else
      aux = ~mascara;
   #endif
   for(i = 0; i < FILAS; i++)
   {
      if(bit_test(aux, FILAS - 1)) output_high(SHIFT_DATA); else output_low(SHIFT_DATA);  
      output_high(SHIFT_CLK);
      output_low(SHIFT_CLK);
      aux*= 2;                                                                            //rotar 1 bit a la izquierda
   }

   output_high(SHIFT_STB);                                                                //efectivizar valores enviados en las salidas de los registros
   output_low(SHIFT_STB);            

   if(mascara >= MAX_VALOR_MASC)
   {
      mascara = 0x01;
      nuevoFrame = TRUE;
   }else{
      mascara*= 2;                                                                        //indicar proxima fila. Volver a la primera si estamos en la ultima
   }
}

void Publik_Ejecutar(void)
{
   if(!nuevoFrame) return; else nuevoFrame = FALSE;

   if(!velocidadTmp--) velocidadTmp = velocidad; else return;   

   switch(efecto)
   {
      case ROTA_IZQ:
         efecto_rota_izq();
      break;
      
      default:
      
      break;
   }
}

#endif
