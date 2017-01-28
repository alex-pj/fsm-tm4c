/*
 * File						: main.c
 * Description		: The operations with FSM are performed here
 *
 * Author : ALEXANDER     
 * Date		: December 7, 2016 
 */       

#include "basicDefs.h"
#include "light.h"
#include "fsm.h"

int main()
{
//	fsm_t *pMlme;
//	fsm_Create(&pMlme, MLME_SM_NUM_STATES, MLME_SM_NUM_EVENTS);

	void *pLight;
	if(fsm_Create((fsm_t **)pLight, LIGHT_SM_NUM_STATES, LIGHT_SM_NUM_EVENTS))
		fsm_Delete((fsm_t *)pLight);

	light_init(pLight);
	light_start(pLight);
	
	fsm_Delete((fsm_t *)pLight);
	
	return SUCCESS;
}


