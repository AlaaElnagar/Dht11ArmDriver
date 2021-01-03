/*

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
#include "MSTK_interface.h"
#include "DHT11_Interface.h"
#include "DHT11_Config.h"




void DHT11_VidSendRequest(MGPIO_t Copy_StMGpioPin){

MGPIO_voidSetPinDirection(Copy_StMGpioPin.DHT11_PORT,Copy_StMGpioPin.DHT11_PIN,MGPIO_OUTPUT_10MHZ_PP);
/*Send request to Dht11 built in controller */
MGPIO_voidSetPinValue(Copy_StMGpioPin.DHT11_PORT,Copy_StMGpioPin.DHT11_PIN,MGPIO_HIGH);
MGPIO_voidSetPinValue(Copy_StMGpioPin.DHT11_PORT,Copy_StMGpioPin.DHT11_PIN,MGPIO_LOW);
/*Delay 18 ms*/
//TIM_vSetBusyWait(TIMER_Address,18, (u16)  TIM_TICKS_MS)  ;
MSTK_voidSetBusyWait(18000);
/*Set dht pin as high */
MGPIO_voidSetPinValue(Copy_StMGpioPin.DHT11_PORT,Copy_StMGpioPin.DHT11_PIN,MGPIO_HIGH);

//TIM_vSetBusyWait(TIMER_Address,20, (u16)  TIM_TICKS_US)  ;
MSTK_voidSetBusyWait(30);



}


/*DHt11 speaks now (: */
void DHT11_VidReciveResponse(MGPIO_t Copy_StMGpioPin){


	MGPIO_voidSetPinDirection(Copy_StMGpioPin.DHT11_PORT,Copy_StMGpioPin.DHT11_PIN,MGPIO_INPUT_FLOATING);

	//TIM_vSetBusyWait(TIMER_Address,40, (u16)  TIM_TICKS_US)  ;
	MSTK_voidSetBusyWait(10);

	while(!MGPIO_u8GetPinValue(Copy_StMGpioPin.DHT11_PORT,Copy_StMGpioPin.DHT11_PIN)){

		//TIM_vSetBusyWait(TIMER_Address,80, (u16)  TIM_TICKS_US)  ;
		MSTK_voidSetBusyWait(80);

	}

	while (MGPIO_u8GetPinValue(Copy_StMGpioPin.DHT11_PORT,Copy_StMGpioPin.DHT11_PIN));
	//while (!MGPIO_u8GetPinValue(Copy_StMGpioPin.DHT11_PORT,Copy_StMGpioPin.DHT11_PIN));

}


Checksum_enut DHT11_enuCheckSum(DHT_t DHTX[] ){


	u16 Loc_U8Sum=0;

	for (u8 i=0 ; i <4 ; i++){

		Loc_U8Sum +=DHTX[i].data ;
	}

	if (Loc_U8Sum == DHTX[4].data){
		return Sum_ok ;
	}

	else {
		return Sum_Nok ;
	}

}


DHT_t *DHT11_VidReciveData(MGPIO_t Copy_StMGpioPin){

	DHT11_VidSendRequest(Copy_StMGpioPin) ;
	DHT11_VidReciveResponse(Copy_StMGpioPin);
	static DHT_t DHTX[5]={0};
	u8 Loc_U8Data = 0;
	/*store four different types of data*/
	for (u8 i = 0 ; i < 5 ; i++){
		/*recive 1 byte of data */
		for (u8 j =0 ; j < 8 ; j++){
/*wait until sending low signal */
			while (!MGPIO_u8GetPinValue(Copy_StMGpioPin.DHT11_PORT,Copy_StMGpioPin.DHT11_PIN));
/*Preparing output data delay */
			MSTK_voidSetBusyWait(40);
/*Encoding the coming signal*/
			if (MGPIO_u8GetPinValue(Copy_StMGpioPin.DHT11_PORT,Copy_StMGpioPin.DHT11_PIN)){
				DHTX[i].data|=(1<<(7-j));
			}
			else{
				DHTX[i].data&= ~(1<<(7-j));
			}
			/*Wait the pin to go low */
			while (MGPIO_u8GetPinValue(Copy_StMGpioPin.DHT11_PORT,Copy_StMGpioPin.DHT11_PIN));


		}


	}

	/*check the data */

	if ( DHT11_enuCheckSum(DHTX) ==  Sum_ok){
		return (DHTX) ;
	}

	else 		{

		return (NULL) ;
	}






}
