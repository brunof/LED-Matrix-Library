/*
   Hecho por Bruno Fascendini(BrunoF) para el foro todopic, como parte del tutorial: Librería Matríz de LEDs Universal[compilador CCS]
   Url: http://www.todopic.com.ar/foros/index.php?topic=30658
   Comenzado en Mayo de 2010
   Colaboradores:

*/
#case                      //sensible a mayúsculas
#zero_ram                  //inicializar toda la RAM a 0x00

#include "main.h"          //incluir configuración de FOSC,FUSES y módulos especiales
#include "publik.c"

#use fast_io(ALL)          //configuracion manual de puertos para maxima velocidad

#int_TIMER0                //interrupción para refrescar la siguiente fila del publik
void  TIMER0_isr(void)
{

   set_timer0(PRECARGA_TMR0);
   Publik_Refrescar();
}


void main()
{
   char i;

   port_b_pullups(TRUE);
   setup_adc_ports(NO_ANALOGS | VSS_VDD);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_128 | RTCC_8_BIT);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED, 0, 1);
   setup_timer_3(T3_DISABLED | T3_DIV_BY_1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

   set_tris_a(0x00);
   set_tris_b(0x00);
   set_tris_c(0x00);

   Publik_Inicializar();

   cambiar_efecto(ROTA_IZQ);
   
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);

   ejecutando = TRUE;                 //comenzar funcionamiento del cartel!!!

   while(ejecutando)
   {
      Publik_Ejecutar();
   }
}
