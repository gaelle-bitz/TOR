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
			// Send to mac sender
			// TODO
		} else {
			// The frame is a message
			/* First case : Message's not for us
			* Second case : Chat
			* Third case : Time
			* Fourth case : Databack
			*/
			
			// First case : Message's not for us
			uint8_t srcAddress = tmpPtr[0] >> 3;
			uint8_t destAddress = tmpPtr[1] >> 3;
			
			if(srcAddress == MYADDRESS || destAddress == MYADDRESS || destAddress == 16){ //add broadcast condition (define)
				// Read checksum from frame
				uint16_t length = tmpPtr[2];
				uint32_t checkSumPos = 3 + length;
				uint8_t checkSumReceived = tmpPtr[checkSumPos]>>2;
				
				// Calcluate checksum to compare;
				uint8_t checkSumCreated = 0;
				for(uint16_t i = 0; i < checkSumPos; i++){
					checkSumCreated += tmpPtr[i];
				}
				checkSumCreated = checkSumCreated <<2;
				
				// Conpare checksums
				if(checkSumCreated == checkSumReceived){
								
				/* 
					*  Second case : Chat : send to chat lcd + resend 
					*  Third case : Time : same
					*  Fourth case : Databack h 
				*/
				} else {
					printf("Checksums are not equal\n");
					printf("Checksum rec : %d", checkSumReceived);
					printf("Checksum cre : %d", checkSumCreated);
				}
			} else {
				
				//? : do we need to change the place of the pointer ?
				tmp.type = TO_PHY;
				osMessageQueuePut(
				queue_phyS_id,
				&tmp,
				osPriorityNormal,
				osWaitForever);
				printf("Message not for us\n");
			}
		}
	}
}
