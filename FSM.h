/*
 * File						: FSM.h
 * Description		: Used in main.c
 * 													fsm.c
 *
 * Author : ALEXANDER     
 * Date		: December 7, 2016 
 */      

#ifndef FSM_H
#define FSM_H

#include <stdlib.h> 					// For malloc
#include <string.h>						// For memcpy and memset
#include "basicDefs.h"

/*
 * --------------------------------------------------------------
 *	Structures and Function pointers
 * --------------------------------------------------------------
 */
typedef u8 (*fsm_action)(void* pData);
typedef  struct
{
	u8							nextState;
	fsm_action			action;	
} fsm_node_t;



typedef	void (*fsm_eventActivation_t)(u8 *currState, u8 event, void* data);
typedef struct
{
	fsm_node_t*			state;		/* Next state and action pointer */
	u8							NoOfStates;			
	u8							NoOfEvents;	
  u8							mlme_currentState;
	fsm_eventActivation_t	transitionFunc;			/**< State transition function */
} fsm_t;


/*
 * --------------------------------------------------------------
 *	Function declarations
 * --------------------------------------------------------------
 */

u8 fsm_Create(fsm_t **pFsm, u8 MaxNoOfStates, u8 MaxNoOfEvents);

u8 fsm_Delete(fsm_t *pFsm);

u8 fsm_init(fsm_t *pFsm, u8 ActiveNoOfStates, u8 ActiveNoOfEvents, 
							fsm_node_t* pMatrix, fsm_eventActivation_t	transFunc);


u8 fsm_Event(fsm_t	*pFsm, u8 *currentState, u8 event, void *pData);

u8 fsm_GetNextState(fsm_t *pFsm, u8 currentState, u8 event, u8	*nextState);


//u8 action_nop(void *pData);


#endif 	//FSM_H
