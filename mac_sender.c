#include "stm32f7xx_hal.h"

#include <stdio.h>
#include <string.h>

#include "main.h"

void MacSender(void *argument)
{
	
	/*
	*All the time : put MacS in queue_messages_id until we see a token
	*
	*Update list
	*get 1 message from queue_messages_id + do stuff depending on messageType
	*~eventually resend same
	*send token
	*/

	//generate token
	struct queueMsg_t* tmp;
	osMessageQueueGet(queue_macS_id,tmp,NULL, osWaitForever );
	
	switch (tmp->type)
	{
		case NEW_TOKEN:
				memPool[0]=255<<16&
		
	
			break;
		
		case TOKEN:
			break;
		
		default:
			break;
	}
	
}
