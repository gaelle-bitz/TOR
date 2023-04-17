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
}
