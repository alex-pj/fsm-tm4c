/*
 * File						: MLME.h
 * Description		: Used in main.c
 * 													fsm.c
 *
 * Author : ALEXANDER     
 * Date		: December 7, 2016 
 */      

#ifndef LIGHT_H
#define LIGHT_H

#include "basicDefs.h"
#include "fsm.h"

/* LIGHT state machine states */
typedef enum 
{
    LIGHT_SM_STATE_IDLE       = 0,
		LIGHT_SM_STATE_BLINK		  = 1,
    LIGHT_SM_STATE_FADING     = 2,
    LIGHT_SM_STATE_DANCING 		= 3,
    LIGHT_SM_STATE_ALL_ON     = 4,
    LIGHT_SM_NUM_STATES
} light_smStates_t;

/* State machine inputs */
typedef enum 
{
    LIGHT_SM_EVENT_START             = 0,
    LIGHT_SM_EVENT_STOP              = 1,
    LIGHT_SM_EVENT_UP_BUTTON         = 2,
    LIGHT_SM_EVENT_DOWN_BUTTON       = 3,
    LIGHT_SM_EVENT_TIMER_TRIGGER     = 4,
    LIGHT_SM_NUM_EVENTS          
} light_smEvents_t;

typedef struct
{
	fsm_t*		fsm;		/* State machine pointer */
	u8			light_currentState;

} light_t;


/*
 * --------------------------------------------------------------
 *	Function declarations
 * --------------------------------------------------------------
 */
//extern void* light_smNOP(void *pMlme);
//extern void* light_smActionUnexpected(void *pMlme);
//extern void* light_smStartIdle(void *pMlme);
u8 light_init(void* pMlme);
u8 light_start(void* pMlme);

#endif 	// LIGHT_H

