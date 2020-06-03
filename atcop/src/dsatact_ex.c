/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                D A T A   S E R V I C E S

                A T   C O M M A N D   
                ( C O M M O N   A C T I O N  
                  C O M M A N D S )

                P R O C E S S I N G

GENERAL DESCRIPTION
  This module executes the AT commands. It mainly executes the common 
  (across all modes) action commands.

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS


Copyright (c) 2001 - 2018 by Qualcomm Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/


/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //commercial/MPSS.HI.1.0.c8/Main/modem_proc/datamodem_r/interface/atcop/src/dsatact_ex.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/23/18   skc     Added support for +CCFCU.
12/15/17   skc     Added enhancement on supplementary service for IP Call.
09/13/17   skc     Added support for VT Call.
08/01/17   skc     Made changes to handle CHLD and CLCC for SRVCCed MPTY Call.
12/08/16   skc     Added enhancement on CHLD and CLCC for VoLTE MPTY Call.
06/27/14   tk      Initial revision (created file for Dynamic ATCoP).

===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "datamodem_variation.h"
#include "comdef.h"
#include "customer.h"

#include <stringl/stringl.h>


#include <stdio.h>
#include <string.h>

#include "dsati.h"
#include "dsatact.h"
#include "dsatctab.h"
#include "dsatdl.h"
#include "dsatparm.h"
#include "dsatvoice.h"
#include "dsatcmif.h"
#include "ds_cap.h" /* ITC_SPEECH */
#include "ds3gmgr.h"
#include "dstask.h"
#include "dstaski.h"
#include "err.h"
#include "mobile.h"
#include "msg.h"
#include "ds3gsiolib_ex.h"

#ifdef FEATURE_DSAT_ETSI_MODE
#include "dsatetsime.h"
#include "dsatetsicall.h"
#include "dsatetsicmif.h"
#include "dsatetsictab.h"

#ifdef FEATURE_DSAT_ETSI_DATA
#include "dsumts_rmsm.h"
#include "dsatetsipkt.h"
#endif /* FEATURE_DSAT_ETSI_DATA*/
#endif /* FEATURE_DSAT_ETSI_MODE */

#if defined(FEATURE_DATA_GCSD) || defined(FEATURE_DATA_WCDMA_CS) 
#include "dsucsdhdlr.h"
#endif /* defined(FEATURE_DATA_GCSD) || defined(FEATURE_DATA_WCDMA_CS) */

#ifdef FEATURE_DATA_IS707
#include "dsat707util.h"
#include "dsat707extctab.h"
#include "ds707_rmsm.h"
#include "snm.h"
#include "cai.h"
#include "ds707_roaming.h"
#include "ds707_pkt_mgr.h"
#endif /* FEATURE_DATA_IS707 */

#ifdef FEATURE_DATA_MUX
#error code not present
#endif /* FEATURE_DATA_MUX */
#include "ds3gdsdif.h"

/*===========================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

  This section contains local definitions for constants, macros, types,
  variables and other items needed by this module.

===========================================================================*/
/*-------------------------------------------------------------------------
            Constants:
-------------------------------------------------------------------------*/

/*-------------------------------------
  Local Variables
---------------------------------------*/

/*-------------------------------------
  Regional Variables
---------------------------------------*/
/* Regional variable that is used to retain the */
/* call back function pointers for ATD, ATA     */
/* ATH,+CGANS and abort handlers for ATA,       */
/* ATD and +CGANS                               */
dsat_dial_string_type dial_string_handler = {0};

#ifdef FEATURE_DATA_MUX
#error code not present
#endif /* FEATURE_DATA_MUX */
/*-------------------------------------------------------------------------
    Protypes for local functions:
-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
            Function Definitions:
-------------------------------------------------------------------------*/

#ifdef FEATURE_DATA_MUX
#error code not present
#endif /* FEATURE_DATA_MUX */


/*===========================================================================

FUNCTION DSAT_REGISTER_HANDLERS

DESCRIPTION
  This function is used to register a call back functions.
  It is used to register call back funtions for ATA and ATH.

  The call back handler can be NULL. If it is not an incoming call, 
  then ATA handler will be NULL.

DEPENDENCIES
  None

RETURN VALUE
  DSAT_OK :  if successfully registered.
  DSAT_ERROR: if dsat_cgauto_val == 2(only in ETSI mode)
  
SIDE EFFECTS
  None

===========================================================================*/
dsat_result_enum_type dsat_register_handlers
(
  dsat_incom_answer_cb_type  call_answer_cb, /* Answer call back */
  dsat_call_hangup_cb_type   call_hangup_cb  /* Hangup call back */
)
{
  dsat_result_enum_type result = DSAT_OK;

#ifdef FEATURE_DATA_TE_MT_PDP
  dsati_mode_e_type             current_mode;
  current_mode = dsatcmdp_get_current_mode();
  
  /* +CGAUTO val setting is not applicable for 1x data calls. 
     Only MT CS data calls should not be answered if +CGAUTO == 2.
     Allow MO CSD calls. For MO CSD calls answer call back will be NULL.
  */
  if( ( IS_ETSI_MODE(current_mode) ) 
      &&((dsat_num_item_type)dsatutil_get_val( DSATETSI_EXT_CGAUTO_IDX,0,0,
                          NUM_TYPE) == DSAT_CGAUTO_MDM_COMPAT_PKT_DMN_ONLY ) 
      &&( NULL != call_answer_cb ) )
  {
    DS_AT_MSG0_HIGH("MT CSD calls cannot be manually answered when +CGAUTO=2");
    result = DSAT_ERROR;
  }
#endif /* FEATURE_DATA_TE_MT_PDP */

  /* ATA Handler */
  dial_string_handler.answer_cb = call_answer_cb; 
  /* ATH Handler */
  dial_string_handler.hangup_cb = call_hangup_cb;

  return result ;
} /* dsat_register_handlers */

#ifdef FEATURE_DATA_TE_MT_PDP

/*===========================================================================

FUNCTION DSAT_PDP_REGISTER_HANDLERS

DESCRIPTION
  This function is used to register a call back functions.
  It is used to register call back funtions for ATA ,ATH and
  +CGANS for MT PDP calls. The call back handlers can be NULL.

DEPENDENCIES
  None

RETURN VALUE
  DSAT_OK: if registered successfully
  DSAT_ERROR: if trying to register when +CGAUTO=1

SIDE EFFECTS
  None

===========================================================================*/
dsat_result_enum_type dsat_register_pdp_handlers
(
  dsat_pdp_incom_answer_cb_type  pdp_call_answer_cb, /* Answer call back */
  dsat_call_hangup_cb_type   call_hangup_cb  /* Hangup call back */
)
{
  dsat_result_enum_type result = DSAT_OK;

  /* Incoming MT PDP register handlers should not be honoured
     when +CGAUTO=1 */
  if ( (dsat_num_item_type)dsatutil_get_val(DSATETSI_EXT_CGAUTO_IDX,
                                 0,0,NUM_TYPE) == DSAT_CGAUTO_AUTO_ANS_ON )
  {
    DS_AT_MSG0_HIGH("ATA/ATH handlers cannot be registered as +CGAUTO=1");
    return DSAT_ERROR;
  }

  /* ATA Handler and +CGANS handler */
  dial_string_handler.pdp_answer_cb = pdp_call_answer_cb; 
  /* ATH Handler */
  dial_string_handler.pdp_hangup_cb = call_hangup_cb;

  return result;
} /* dsat_register_pdp_handlers */

/*===========================================================================

FUNCTION DSAT_DEREGISTER_PDP_HANDLERS

DESCRIPTION
  This function is used to deregister the MT PDP call back functions.
  It resets all the registered MT PDP handlers to NULL.

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void dsat_deregister_pdp_handlers ( void )
{
  /* +CGANS / ATA Handler for MT PDP */
  dial_string_handler.pdp_answer_cb = NULL;
  /* +CGANS / ATH handler for MT PDP */
  dial_string_handler.pdp_hangup_cb = NULL;
  return;
} /* dsat_deregister_pdp_handlers */

#endif /* FEATURE_DATA_TE_MT_PDP */

/*===========================================================================

FUNCTION DSAT_DEREGISTER_HANDLERS

DESCRIPTION
  This function is used to deregister the call back functions.
  It resets all the registered handlers to NULL.

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void dsat_deregister_handlers ( void )
{
  /* ATA Handler */
  dial_string_handler.answer_cb = NULL; 
  /* ATH Handler */
  dial_string_handler.hangup_cb = NULL;
  return;
} /* dsat_deregister_handlers */


/*===========================================================================

FUNCTION DSAT_REG_ATZ_CB

DESCRIPTION
  This function is used to register a call back function for ATZ.

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void dsat_reg_atz_cb
(
  dsat_atz_cb_type atz_cb  /* atz call back */
)
{
  dial_string_handler.atz_cb = atz_cb;
  return;
} /* dsat_reg_atz_cb */



/*===========================================================================

FUNCTION DSAT_INIT_CB_HANDLERS

DESCRIPTION
  Initialize all the registered call handlers to NULL
  Called from dsat_init() after every reset.

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void dsat_init_cb_handlers(void)
{
  /* Reset all the CB handlers to NULL */
  memset ( &dial_string_handler, 0, sizeof(dsat_dial_string_type) );

  return;
}

/*===========================================================================

FUNCTION DSAT_IS_SEQUENCE_NUMBER_AVAILABLE

DESCRIPTION
  Function check whether sequence number is available or not for new call.

DEPENDENCIES
  None

RETURN VALUE
  Return TRUE or FALSE
  TRUE if sequence number available
  FALSE if sequence number is no available

SIDE EFFECTS
  None

===========================================================================*/

boolean dsatact_is_sequence_number_available()
{
  int j = 0;
  sys_modem_as_id_e_type subs_id = dsat_get_current_subs_id(FALSE);
  dsatetsicall_call_state_da_info  *call_da_val = NULL;

  call_da_val = dsat_get_base_addr_per_subs(DSAT_CALL_DA_VALS, subs_id, FALSE);
  
  if (NULL == call_da_val)
  {
    return FALSE;
  }
  //Check for sequence number available
  for(j = 0; j < CM_CALL_ID_MAX; j++)
  {
    if(call_da_val->dsat_seqnum_callid[j].call_id == CM_CALL_ID_INVALID)
    {
      return TRUE;
    }	  
  }
  return FALSE;
}

/*===========================================================================

FUNCTION DSATACT_GET_CALL_NUMBER_FROM_URI

DESCRIPTION
  Function to extract call number from SIP URI.

DEPENDENCIES
  None

RETURN VALUE
  Return TRUE or FALSE
  TRUE if call number is extracted properly
  FALSE otherwise

SIDE EFFECTS
  None

===========================================================================*/
boolean dsatact_get_call_number_from_uri
(
  const uint16     *user_uri,
  uint8             user_uri_len,
  uint8            *call_num,
  uint8            *call_num_len
)
{
#define SIP_STRING_LENGTH 4
  uint8 i = 0;
  const char sip_string[SIP_STRING_LENGTH + 1] = "SIP:";

  if(user_uri == NULL || call_num == NULL ||
     call_num_len == NULL)
  {
    return FALSE;
  }
  
  for(i = 0; i < (uint8)MIN(SIP_STRING_LENGTH, user_uri_len); i++)
  {
    if(UPCASE(*(user_uri + i)) != sip_string[i])
    {
      return FALSE;
    }
  }

  /* String is starting with SIP:, now collect number information:
     Number can be ended by ';' or '@' */
  while( (i < user_uri_len) &&
        *(user_uri + i) != '\0' && 
        *(user_uri + i) != ';' && 
        *(user_uri + i) != '@')
  {
    *(call_num + i - SIP_STRING_LENGTH) = *(user_uri + i);
    i++;
    if(i >= (uint8)CM_MAX_NUMBER_CHARS)
    {
      return FALSE;
    }
  }

  *call_num_len = i - SIP_STRING_LENGTH;

  return TRUE;
}


/*===========================================================================

FUNCTION DSATACT_GET_NUMBER_FROM_URI

DESCRIPTION
  Function to extract number from SIP/TEL URI.

DEPENDENCIES
  None

RETURN VALUE
  Return TRUE or FALSE
  TRUE if call number is extracted properly
  FALSE otherwise

SIDE EFFECTS
  None

===========================================================================*/
boolean dsatact_get_number_from_uri
(
  const byte       *user_uri,
  byte             user_uri_len,
  byte             *call_num,
  byte             *call_num_len
)
{
#define MAX_PROTOCOL_STRING_LENGTH 4
#define MAX_PROTOCOL_COUNT 2
  uint8 i = 0;
  const byte protocol_string[MAX_PROTOCOL_COUNT][MAX_PROTOCOL_STRING_LENGTH + 1] = {"SIP:","TEL:"};
  boolean found;

  if(user_uri == NULL || call_num == NULL ||
     call_num_len == NULL || 
     user_uri_len <= MAX_PROTOCOL_STRING_LENGTH)
  {
    return FALSE;
  }

  for(i = 0; i < MAX_PROTOCOL_COUNT; i++)
  {
    found = FALSE;
    if(0 == dsatutil_strncmp_ig_sp_case(&protocol_string[i][0], user_uri, MAX_PROTOCOL_STRING_LENGTH))
    {
      found = TRUE;
      break;
    }
  }

  if(!found)
    return FALSE;

  i = MAX_PROTOCOL_STRING_LENGTH;
  /* String is starting with SIP: or TEL:, now collect number information:
     Number can be ended by ';' or '@' */
  while( (i < user_uri_len) &&
        *(user_uri + i) != '\0' && 
        *(user_uri + i) != ';' && 
        *(user_uri + i) != '@')
  {
    *(call_num + i - MAX_PROTOCOL_STRING_LENGTH) = *(user_uri + i);
    i++;
    if(i >= (uint8)CM_MAX_NUMBER_CHARS)
    {
      return FALSE;
    }
  }

  *call_num_len = i - MAX_PROTOCOL_STRING_LENGTH;
  *(call_num + *call_num_len) = '\0';

  return TRUE;
}

/*===========================================================================

FUNCTION DSATACT_TRACK_SEQUENCE_NUMBER

DESCRIPTION
  Track the sequence number (as described in 3GPP TS 22.030 section 6.5.5.1) 
  for this call ID and event: Set in call sequence number indexed array 
  dsat_seqnum_callid[] on call incoming or connected event and clear on call 
  end event.
  3GPP TS 22.030 section 6.5.5.1 reads - "X" is the numbering (starting with 1)
  of the call given by the sequence of setting up or receiving the calls 
  (active, held or waiting) as seen by the served subscriber. Calls hold their
  number until they are released. New calls take the lowest available number.

DEPENDENCIES
  None
  
RETURN VALUE
  Returns tracked sequence number

SIDE EFFECTS
  None
  
===========================================================================*/
int dsatact_track_sequence_number
(
  sys_modem_as_id_e_type subs_id,
  cm_call_id_type        call_id,
  cm_call_event_e_type   call_event,
  cm_call_type_e_type    call_type
)
{
  dsatetsicall_call_state_da_info  *call_da_val = NULL;
  /* Sequence numbers internal to this function are 
     really 22.030 sequence numbers - 1 */
  int index, first_avail_seqnum, callid_seqnum;
  int seq_number = CALL_SEQNUM_INVALID;
  
  call_da_val = dsat_get_base_addr_per_subs(DSAT_CALL_DA_VALS, subs_id, TRUE);
  if (NULL == call_da_val)
  {
    return seq_number;
  }
  /* Search through sequence number indexed array... */
  for ( index = 0, first_avail_seqnum = callid_seqnum = CALL_SEQNUM_INVALID; 
        index < CM_CALL_ID_MAX; 
        index++ )
  {
    /* When first available sequence number is found... */
    if ( CALL_SEQNUM_INVALID == first_avail_seqnum && 
         CM_CALL_ID_INVALID ==  call_da_val->dsat_seqnum_callid[index].call_id )
    {
      first_avail_seqnum = index;
      seq_number = index + 1;
    }
    
    /* If call ID found... */
    if ( CALL_SEQNUM_INVALID == callid_seqnum &&
         call_id == call_da_val->dsat_seqnum_callid[index].call_id )
    {
      callid_seqnum = index;
      seq_number = index + 1;
    }
  }
  
  DS_AT_MSG5_HIGH("In track_sequence_number call_id %d call_evt %d call_type %d first_avail_seqnum %d callid_seqnum %d",
                   call_id, call_event, call_type, first_avail_seqnum, callid_seqnum);

  switch( call_event )
  {
    case CM_CALL_EVENT_ORIG:
    case CM_CALL_EVENT_SETUP_IND:
    case CM_CALL_EVENT_ACT_BEARER_IND:
      /* Should never be existing sequence number for incoming call ID,
         try to clean up */
      if ( CALL_SEQNUM_INVALID != callid_seqnum )
      {
        DS_ATCOP_ERROR_LOG_1("Event incoming & already sequence number for call ID =d",
                   call_id);
        call_da_val->dsat_seqnum_callid[callid_seqnum].call_id = CM_CALL_ID_INVALID;
      }
      if ( CALL_SEQNUM_INVALID != first_avail_seqnum )
      {
        call_da_val->dsat_seqnum_callid[first_avail_seqnum].call_id = call_id;
        call_da_val->dsat_seqnum_callid[first_avail_seqnum].call_type = call_type;
        call_da_val->dsat_seqnum_callid[first_avail_seqnum].is_conf_participant = FALSE;
        call_da_val->last_seq_num = first_avail_seqnum;
      }
      break;
    case CM_CALL_EVENT_CONNECT:
    case CM_CALL_EVENT_INCOM:
    case CM_CALL_EVENT_RAB_REESTAB_IND:
    case CM_CALL_EVENT_CONFERENCE_INFO:
      /* May find existing sequence number for connecting call ID if previous 
         incoming call, else assign first available */
      if (( CALL_SEQNUM_INVALID == callid_seqnum ) && 
         ( CALL_SEQNUM_INVALID != first_avail_seqnum ))
      {
        call_da_val->dsat_seqnum_callid[first_avail_seqnum].call_id = call_id;
        call_da_val->dsat_seqnum_callid[first_avail_seqnum].call_type = call_type;
        call_da_val->last_seq_num = first_avail_seqnum;
        /* Update seqnum and call id mapping for CM_CALL_EVENT_CONFERENCE_INFO */
        if(call_event == CM_CALL_EVENT_CONFERENCE_INFO)
        {
          call_da_val->dsat_seqnum_callid[first_avail_seqnum].is_conf_participant = TRUE;
        }
        else
        {
          call_da_val->dsat_seqnum_callid[first_avail_seqnum].is_conf_participant = FALSE;
        }
      }

      if(CALL_SEQNUM_INVALID != callid_seqnum)
      {
        /* If there is any participants info in disconnected status, callid_seqnum will be valid one.
         So clearing sequence info for the participant. */
        if(call_event == CM_CALL_EVENT_CONFERENCE_INFO )
        {
          call_da_val->dsat_seqnum_callid[callid_seqnum].call_id = CM_CALL_ID_INVALID;
          call_da_val->dsat_seqnum_callid[callid_seqnum].call_type = CM_CALL_TYPE_NONE;
          call_da_val->dsat_seqnum_callid[callid_seqnum].is_conf_participant = FALSE;        
        }
        else
        {
          /* Update call type. It is possible if MT Video call is answered as voice. */
          call_da_val->dsat_seqnum_callid[callid_seqnum].call_type = call_type;
        }
      }
      break;
    case CM_CALL_EVENT_END:
    case CM_CALL_EVENT_PDN_CONN_REJ_IND:
    case CM_CALL_EVENT_PDN_CONN_FAIL_IND:
    case CM_CALL_EVENT_RES_ALLOC_REJ_IND:
    case CM_CALL_EVENT_RES_ALLOC_FAIL_IND:
      /* Should find existing sequence number for ending call ID */
      if ( CALL_SEQNUM_INVALID != callid_seqnum )
      {
        call_da_val->dsat_seqnum_callid[callid_seqnum].call_id = CM_CALL_ID_INVALID;
        call_da_val->dsat_seqnum_callid[callid_seqnum].call_type = CM_CALL_TYPE_NONE;
        call_da_val->dsat_seqnum_callid[callid_seqnum].is_conf_participant = FALSE;
        /* Saving sequence number for last call ended; will be used for +CMCCSI URC */
        call_da_val->last_seq_num = callid_seqnum;

        /* Clearing sequence number for conference participants if any */
        /* Dont clear the call tracking information of MPTY participant if handover was happened recently.
           Clear these info during message router indication received from CM for SRVCCed Calls */
        if(call_da_val->conf_linked_call_id == call_id &&
           call_da_val->etsicall_num_participant_in_conf > 0 &&
           call_da_val->handover_complete == FALSE)
        {
          for(index = 0; index < CM_CALL_ID_MAX; index++)
          {
            if(call_da_val->dsat_seqnum_callid[index].is_conf_participant == TRUE)
            {
              call_da_val->dsat_seqnum_callid[index].call_id = CM_CALL_ID_INVALID;
              call_da_val->dsat_seqnum_callid[index].call_type = CM_CALL_TYPE_NONE;
              call_da_val->dsat_seqnum_callid[index].is_conf_participant = FALSE;
            }
          }
        }
      }
      break;
    default:
      DS_ATCOP_ERROR_LOG_1("Unanticipated event =d",call_event);
      break;
  }
  return seq_number;
}/* dsatact_track_sequence_number */
