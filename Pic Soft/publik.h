#ifndef    __publik_h__
#define    __publik_h__

#include "config.h"        //contiene la configuración del publik y ciertos cálculos/generacion de variables automáticos en base a ella

int1  ejecutando;          //variable global que controla la activacion general del cartel!
int1  nuevoFrame;          //variable global que indica si se acaba de completar un frame completo!

//Inicializa las variables del publik y demás configuración
void Publik_Inicializar(void)
{
   mascara = 0x01;         //primer fila
   nuevoFrame = FALSE;
   //falta...
}

void Publik_Refrescar(void)
{
   #ifdef mode16Bit
      unsigned int16 i, aux;
   #else
      unsigned int8 i, aux;
   #endif

   //ENVIO DE COLUMNAS A ENCENDER
   for(i = COLUMNAS; i > 0; i--)    //enviar información de las columnas una a una
   {
      #if(COLUMNAS_CATODO)
         if(buffer[i-1] & mascara) output_low(SHIFT_DATA); else output_high(SHIFT_DATA);    //enviar cada columna en alto o bajo segun corresponda.
      #else
         if(buffer[i-1] & mascara) output_high(SHIFT_DATA); else output_low(SHIFT_DATA);    //enviar cada columna en alto o bajo segun corresponda con logica invertida      
      #endif
      output_high(SHIFT_CLK);
      output_low(SHIFT_CLK);
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
   if(!nuevoFrame) return;
}

#endif
