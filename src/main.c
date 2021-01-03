/*
 * main.c
 *  Created on: Dec 30, 2020
 *  Created on: Dec 29, 2020
 *      Author: AlaaElnagar
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MNVIC_interface.h"
#include "Timer_interface.h"
#include "DHT11_Interface.h"
#include "MSTK_interface.h"



int main(void)
{

	MRCC_voidInitSysClock();//Initialization System Clock Speed 8Mhz Crystel
	MRCC_voidEnablePerClock( MRCC_APB2 , MRCC_GPIOA_EN );//Enable GPIOA Peripheral Clock
	MRCC_voidEnablePerClock( MRCC_APB2 , MRCC_GPIOB_EN );//Enable GPIOA Peripheral Clock
	MRCC_voidEnablePerClock( MRCC_APB2 , MRCC_GPIOC_EN );//Enable GPIOA Peripheral Clock
//	MRCC_voidEnablePerClock( MRCC_APB2 , (u8)MRCC_ADC1_EN);//Enable GPIOA Peripheral Clock
	MRCC_voidEnablePerClock( MRCC_APB2 , MRCC_TIMER_1_EN) ;
	MSTK_voidInit();
	/*Timer 1 */
	TIM_ConfigType Loc_Stimer1;
	Loc_Stimer1.Counter_State     = Enable_CNT                ;
	Loc_Stimer1.PrescalerVal      = 8                         ;
	Loc_Stimer1.Direction_State = UpCounter                   ;
		TIM_vInit(TIMER1, &Loc_Stimer1)                      ;

		//MNVIC_voidEnablePeri(MNVIC_TMR1_UP_IRQ);
   /*Dhtx*/

	//DHT_t *Dht_sensor1_Data=NULL;
	MGPIO_t S1_dht11MGpio = {MGPIO_PORTA,MGPIO_PIN0} ;





	 while(1){

		 DHT_t volatile  *Dht_sensor1_Data=DHT11_VidReciveData(S1_dht11MGpio);

		 if (Dht_sensor1_Data != NULL){
				 Dht_sensor1_Data[DHT11_TEMP_I].data;
				 Dht_sensor1_Data[DHT11_HUMD_I].data ;

		 }


	       }

	return 0;

            }


