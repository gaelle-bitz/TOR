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
	
	osMessageQueueId_t  queue_internMacS_id;
	const osMessageQueueAttr_t queue_internMacS_attr = {
		.name = "MAC_INTERN_QUEUE"  	
	};

	queue_internMacS_id = osMessageQueueNew(2,sizeof(struct queueMsg_t),&queue_internMacS_attr); 	

	//generate token
	osStatus_t sendStatus;
	struct queueMsg_t tmp;
	uint8_t *newTokenMem;
	struct queueMsg_t toSend;
	for(;;){
		osMessageQueueGet(queue_macS_id,&tmp,NULL, osWaitForever );
		switch (tmp.type)
		{
			case NEW_TOKEN:
				newTokenMem = osMemoryPoolAlloc(memPool,osWaitForever);
				for(uint32_t i = 0; i < 16; i++){
					newTokenMem[i]=0;
				}
				newTokenMem[0]=0xFF;
				newTokenMem[MYADDRESS-1]=2;
				toSend.type = TO_PHY;
				toSend.anyPtr = newTokenMem;
				toSend.addr = NULL;
				toSend.sapi = NULL;
				sendStatus = osMessageQueuePut(queue_phyS_id, &toSend, osPriorityNormal, osWaitForever);
				break;
			
			case TOKEN:
				//destack our queue + do stuff with it
				break;
			
			case DATABACK:
				//Checkre Read & ack
				break;
			
			case DATA_IND:
				break;
			
			
			default :
				//put msg in our queue
				break;
		}
		printf("Our case : %d\n", newTokenMem[MYADDRESS]);
		printf("Send status : %d\n", sendStatus);
	}
}
