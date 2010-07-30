/*
   Hecho por Bruno Fascendini(BrunoF) para el foro todopic, como parte del tutorial: Librería Matríz de LEDs Universal[compilador CCS]
   Url: http://www.todopic.com.ar/foros/index.php?topic=30658
   Comenzado en Mayo de 2010
   Colaboradores:

*/
#ifndef    __efectos_c__
#define    __efectos_c__

//Lista de efectos.
#define     ROTA_IZQ      0


#ifdef modo16Bit
   unsigned int16 efAux1;
#else
   unsigned int8 efAux1;
#endif

void efecto_rota_izq()
{
   if(ProximoElementoLetra())                                     //intentar obtener proximo elemento de la lectra actual...
   {
      if(++BufferInicio >= COLUMNAS) BufferInicio=0;              //rotar...
      if(BufferInicio>0) efAux1= BufferInicio-1; else efAux1=COLUMNAS - 1;     //calcular la ultima columna actual...
      buffer[efAux1] = letraData;                                 //e inyectarle el valor leido
   }else{
      //buffer[efAux1] = 0;                                        //inyectarle 0
      if(!nuevoEfecto) archivoPosicionActual++;
      nuevoEfecto = FALSE;
      if(demo[archivoPosicionActual] == 0) archivoPosicionActual = 0;
      CargarLetra(demo[archivoPosicionActual]);
   }
}

void cambiar_efecto(unsigned int8 nmr)
{
   efecto = nmr;
   nuevoEfecto = TRUE;
}

#endif
