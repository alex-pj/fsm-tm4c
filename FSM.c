/*
 * File						: FSM.c
 * Description		: FSM function implementations
 *											fsm_Create()
 *											fsm_Remove()
 *											fsm_init()
 *											fsm_Event() 
 *											fsm_GetNextState() 
 *											action_nop() 
 *										
 * Author : ALEXANDER     
 * Date		: December 7, 2016 
 */                    

#include "basicDefs.h"
#include "fsm.h"
/*
 * --------------------------------------------------------------
 *	Global variables
 * --------------------------------------------------------------
 */



/*
 * --------------------------------------------------------------
 *	Function defenitions
 * --------------------------------------------------------------
 */
 

/**
 * function 			fsm_Create
 *
 * Description
 * 			Creates a Finite State Machine
 * Called by
 *      main()
 */ 
u8 fsm_Create(fsm_t **pFsm, u8 MaxNoOfStates, u8 MaxNoOfEvents)
{
	if ((!pFsm) || (MaxNoOfStates == 0) || (MaxNoOfEvents == 0))
	{
		return ARG_FAIL;
	}

	*pFsm = (fsm_t *)malloc(sizeof(fsm_t));																									// fsm_SM_t
	if (!(*pFsm))
	{
		return MEMFAIL;
	}
	memset((*pFsm), 0, sizeof(fsm_t));

	(*pFsm)->state = (fsm_node_t *)malloc(MaxNoOfStates * MaxNoOfEvents * sizeof(fsm_node_t));		// fsm_node_t
	if (!((*pFsm)->state))
	{
		free(*pFsm);
		return MEMFAIL;
	}
	memset((*pFsm)->state, 0, MaxNoOfStates * MaxNoOfEvents * sizeof(fsm_node_t));

	(*pFsm)->NoOfStates = MaxNoOfStates;
	(*pFsm)->NoOfEvents = MaxNoOfEvents;

	return SUCCESS;
}

/**
 * function 			fsm_Delete
 *
 * Description
 * 			Freeing the Finite State Machine created
 * Called by
 *      main()
 */ 
u8 fsm_Delete(fsm_t *pFsm)
{
	if (!pFsm)
	{
		return ARG_FAIL;
	}

	if (!(pFsm->state))
	{
		free(pFsm->state);
	}

	free(pFsm);

	return SUCCESS;
}

/**
 * function 			fsm_init
 *
 * Description
 * 			Init The FSM structure
 * Called by
 *      mlme()
 */ 
u8 fsm_init(fsm_t	*pFsm, u8	ActiveNoOfStates, u8 ActiveNoOfEvents,
											fsm_node_t* pMatrix, fsm_eventActivation_t transFunc)
{
	if (!pFsm || !pMatrix)
	{
		return ARG_FAIL;
	}

	if ((ActiveNoOfStates > pFsm->NoOfStates) || (ActiveNoOfEvents > pFsm->NoOfEvents))
	{
		return FAILURE;
	}

	memcpy( (void *)pFsm->state, (void *)pMatrix,
				  ActiveNoOfStates * ActiveNoOfEvents * sizeof(fsm_node_t));

	pFsm->NoOfStates = ActiveNoOfStates;
	pFsm->NoOfEvents = ActiveNoOfEvents;
	pFsm->transitionFunc = transFunc;
	return SUCCESS;
}

/**
 * function 			fsm_Event
 *
 * Description
 * 			Performs matrix's event transition
 * Called by
 *      main()
 */ 
u8 fsm_Event(fsm_t	*pFsm, u8	*currentState, u8	event, void	*pData)
{
	u8		oldState;
	u8  status;

	if (!pFsm || !currentState)
	{
		return ARG_FAIL;
	}

	if ((*currentState >= pFsm->NoOfStates) || (event >= pFsm->NoOfEvents))
	{
		return FAILURE;
	}
	
	oldState = *currentState;
	/* update current state */
	*currentState = pFsm->state[(*currentState * pFsm->NoOfEvents) + event].nextState;

	
  if (!(*pFsm->state[(oldState * pFsm->NoOfEvents) + event].action)) 
  {
      return FAILURE;
  }
	status = (*pFsm->state[(oldState * pFsm->NoOfEvents) + event].action)(pData);

	return status;
}


/**
 * function 			fsm_GetNextState
 *
 * Description
 * 			Retrun the next state for a given current state and an event.
 * Called by
 *      main()
 */ 
u8 fsm_GetNextState(fsm_t		*pFsm,
						u8					currentState,
						u8					event,
						u8					*nextState)
{
	if (!pFsm)
	{
		return MEMFAIL;
	}
	if ((currentState < pFsm->NoOfStates) && (event < pFsm->NoOfEvents))
	{
		*nextState = pFsm->state[(currentState * pFsm->NoOfEvents) + event].nextState;
		return SUCCESS;
	}	
	return FAILURE;
}

u8 action_nop(void *pData)
{
	return SUCCESS;
}

