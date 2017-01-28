/*
 * File						: light.c
 * Description		: The modules like light state machine are implemented here
 *
 * Author : ALEXANDER     
 * Date		: December 27, 2016 
 */ 
 
#include "light.h"
#include "fsm.h"
#include "portF.h"

static void Delay(void){
	unsigned long volatile time;
  time = 727240*200/91;  // 0.1sec
  while(time){
		time--;
  }
}

void* light_idle(void *pMlme)
{
    return SUCCESS;
}

void* light_blink(void *pMlme)
{
    return SUCCESS;
}

void* light_fade(void *pMlme)
{
    return SUCCESS;
}

void* light_dance(void *pMlme)
{
    return SUCCESS;
}

void* light_all_on(void *pMlme)
{
    return SUCCESS;
}


/**
 * function 			light_smEvent
 *
 * Description
 * 			Checks for the validity of next state.
 *			Executes the event in the current state.
 * Called by
 *      This function is passed as handle in fsm_config
 */ 
void light_smEvent(u8 *currentState, u8 event, void* hMlme)				
{
   fsm_t *pMlme = (fsm_t *)hMlme;
    u8        nextState;

    if (!fsm_GetNextState(pMlme, *currentState, event, &nextState))
    {
     //   printf( "MLME_SM: ERROR - failed getting next state \n");

        return ;
    }

	//printf("light_smEvent: <currentState = %d, event = %d> --> nextState = %d\n", *currentState, event, nextState);

    fsm_Event(pMlme, currentState, event, (void *)pMlme);

    return ;
}

u8 light_start(void* hMlme)
{
    fsm_t *pMlme = (fsm_t *)hMlme;			//light_t = Our operational structure
 //   light_t

    if (!pMlme)
    {
        return MEMFAIL;
    }

//    light_smEvent(&pMlme->light_currentState, LIGHT_SM_EVENT_START, pMlme);
		return SUCCESS;
}

/**
 * function 			light_init
 *
 * Description
 * 			Initializes the hardware's portF
 *			Attaches the light SM to the FSM module
 * Called by
 *      main()
 */ 
u8 light_init(void* hMlme)
{
    fsm_t *pHandle = (fsm_t *)hMlme;
    
    /* STATE MACHINE MATRIX */
    fsm_node_t    light_smMatrix[LIGHT_SM_NUM_STATES][LIGHT_SM_NUM_EVENTS] =
    {

        /* 			NEXT-STATE									action 																		Event		*/
		/*====================================================================================*/
		/* Present State : IDLE state */
        {{LIGHT_SM_STATE_BLINK,		(fsm_action)light_blink},             	/* LIGHT_SM_EVENT_START */
         {LIGHT_SM_STATE_IDLE, 		(fsm_action)light_idle},                /* LIGHT_SM_EVENT_STOP  */
         {LIGHT_SM_STATE_IDLE, 		(fsm_action)light_idle},                /* LIGHT_SM_EVENT_UP_BUTTON  */
         {LIGHT_SM_STATE_IDLE, 		(fsm_action)light_idle},              	/* LIGHT_SM_EVENT_DOWN_BUTTON  */
				 {LIGHT_SM_STATE_IDLE, 		(fsm_action)light_idle},                /* LIGHT_SM_EVENT_TIMER_TRIGGER  */
        },
        /* Present State : BLINK state */
        {{LIGHT_SM_STATE_BLINK, 	(fsm_action)light_blink},      			/* LIGHT_SM_EVENT_START */
         {LIGHT_SM_STATE_IDLE, 		(fsm_action)light_idle},           		/* LIGHT_SM_EVENT_STOP  */
         {LIGHT_SM_STATE_FADING, 	(fsm_action)light_fade},   				/* LIGHT_SM_EVENT_UP_BUTTON */
         {LIGHT_SM_STATE_BLINK, 	(fsm_action)light_all_on},      		/* LIGHT_SM_EVENT_DOWN_BUTTON */
         {LIGHT_SM_STATE_IDLE, 		(fsm_action)light_idle},      			/* LIGHT_SM_EVENT_TIMER_TRIGGER */
        },
        /* Present State  : FADE state */
        {{LIGHT_SM_STATE_BLINK, 	(fsm_action)light_blink},      			/* LIGHT_SM_EVENT_START */
         {LIGHT_SM_STATE_IDLE, 		(fsm_action)light_idle},           		/* LIGHT_SM_EVENT_STOP  */
         {LIGHT_SM_STATE_DANCING, 	(fsm_action)light_dance},   			/* LIGHT_SM_EVENT_UP_BUTTON */
         {LIGHT_SM_STATE_BLINK, 	(fsm_action)light_blink},      			/* LIGHT_SM_EVENT_DOWN_BUTTON */
         {LIGHT_SM_STATE_IDLE, 		(fsm_action)light_idle},      			/* LIGHT_SM_EVENT_TIMER_TRIGGER */

        },
		/* Present State : DANCE state */
        {{LIGHT_SM_STATE_BLINK, 	(fsm_action)light_blink},      			/* LIGHT_SM_EVENT_START */
         {LIGHT_SM_STATE_IDLE, 		(fsm_action)light_idle},           		/* LIGHT_SM_EVENT_STOP  */
         {LIGHT_SM_STATE_ALL_ON, 	(fsm_action)light_all_on},   			/* LIGHT_SM_EVENT_UP_BUTTON */
         {LIGHT_SM_STATE_FADING, 	(fsm_action)light_fade},      			/* LIGHT_SM_EVENT_DOWN_BUTTON */
         {LIGHT_SM_STATE_IDLE, 		(fsm_action)light_idle},      			/* LIGHT_SM_EVENT_TIMER_TRIGGER */

        },
		/* Present State : ALL-ON state */
        {{LIGHT_SM_STATE_BLINK, 	(fsm_action)light_blink},      			/* LIGHT_SM_EVENT_START */
         {LIGHT_SM_STATE_IDLE, 		(fsm_action)light_idle},           		/* LIGHT_SM_EVENT_STOP  */
         {LIGHT_SM_STATE_IDLE, 		(fsm_action)light_blink},   				/* LIGHT_SM_EVENT_UP_BUTTON */
         {LIGHT_SM_STATE_DANCING, (fsm_action)light_dance},      			/* LIGHT_SM_EVENT_DOWN_BUTTON */
         {LIGHT_SM_STATE_IDLE, 		(fsm_action)light_idle},      			/* LIGHT_SM_EVENT_TIMER_TRIGGER */

		},

    };
		/* Initialising the hardware register */
		PortF_Init();
		
    fsm_init(pHandle, LIGHT_SM_NUM_STATES, LIGHT_SM_NUM_EVENTS, &light_smMatrix[0][0], light_smEvent);
    return SUCCESS;
}




