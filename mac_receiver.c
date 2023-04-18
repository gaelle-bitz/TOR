#include "stm32f7xx_hal.h"

#include <stdio.h>
#include <string.h>

#include "main.h"

void MacReceiver(void *argument)
{
		/*
	*Wait on flag "From_Phy"
	*Check MacRQueue
	*Full ReadQueue + do stuff depending on messageType
	*reset flag "From_Phy"
	*dodo
	*/
	struct queueMsg_t tmp;
	for(;;){
		osMessageQueueGet(queue_macR_id,&tmp,NULL, osWaitForever );
		uint8_t* tmpPtr = tmp.anyPtr;
		if(tmpPtr[0] == 0xFF){
			// The frame is a token
			printf("Token received in macR\n");
		} else {
			// The frame is a message
		}
	}
}
