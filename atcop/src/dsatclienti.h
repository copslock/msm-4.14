#ifndef DSATCLIENTI_H
#define DSATCLIENTI_H
/*===========================================================================

                        D A T A   S E R V I C E S

                A T   C O M M A N D   P R O C E S S O R

   C L I E N T   I N T E R F A C E   I N T E R N A L  H E A D E R   F I L E


DESCRIPTION
  This file contains the definitions of data structures, defines and
  enumerated constants, and function prototypes required for the
  data services AT command processor client asynchronous interface.

  Copyright (c) 2005 - 2020 by Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary.
===========================================================================*/


/*===========================================================================

                      EDIT HISTORY FOR FILE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //commercial/MPSS.HI.1.0.c8/Main/modem_proc/datamodem_r/interface/atcop/src/dsatclienti.h#2 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
10/30/17   rk      Removed DS Flag FEATURE_DSAT_EXT_CLIENT_SUPPORT.
11/18/14   tk      ATCoP changes for dynamic memory optimizations.
01/19/12   sk      Feature cleanup.
06/23/09   vg	   Fixed lint errors.
03/04/09   sa      AU level CMI modifications.
07/16/08   ua      Added support for external client support.
04/23/07   pp      Lint Medium fixes.
04/15/05   ar      Relocate DSAT_CLIENT_ID_MAX macro
02/07/05   ar      Adjust prototype for dsat_client_invoke_acc_callback.
01/26/05   ar      Add accessory manager interface elements.
01/24/05   ibm     Initial version.

===========================================================================*/


#include "datamodem_variation.h"
#include "dsatclient.h"
#include "dsat_v.h"
#include "dstask_v.h"

/*===========================================================================

                      PUBLIC DATA DECLARATIONS

===========================================================================*/

typedef struct
{
  boolean reg;                        /* True, if registred */
  char *at_cmd_ptr; /* Received AT command buffer */
  uint16 cmd_len;                     /* Length of the command string */ 
  dsat_client_cmd_rsp_cb_func cb_func;/* Clients response call back fn */
  void    *client_data;                 /* Clients data */
  boolean pending_flag;                 /* True, if another client/port is being processed.*/
  /* Below URC registration info is persistent*/
  boolean                     urc_reg;              /* True, if client registred for URCs */
  dsat_client_cmd_rsp_cb_func urc_resp_cb_func;     /* Client's response call back fn */
  void                       *urc_client_data;      /* Client data */
  dsat_fwd_resp_enum_type     prev_response_type;   /* Last sent resp_type*/
}dsat_client_info_s_type;

typedef struct
{
  char                         at_cmd_buff[MAX_LINE_SIZE];
  uint16                       cmd_len;
  int8                         client_id;
  dsat_client_cmd_rsp_cb_func  cb_func;
  void                        *client_data;
}ds_at_send_at_cmd_s_type;

/* Macro to validate client type; TRUE is error */
#define VALIDATE_CLIENT_TYPE(client_type )\
        ( client_type <= DSAT_CLIENT_TYPE_INVALID ) ||\
         ( client_type >= DSAT_EXT_CLIENT_ID_MAX ) 

/* Macro to validate client ID; TRUE is error */
#define VALIDATE_CLIENT_ID(clientid )\
      ( clientid >= DSAT_EXT_CLIENT_ID_MAX)||\
      ( clientid <= DSAT_EXT_CLIENT_ID_INVALID)

/*===========================================================================

FUNCTION DSATCLIENT_SEND_AT_CMD_HANDLER

DESCRIPTION
  This function is the handler to process the client's AT command with in DS
  task context. 

DEPENDENCIES
  Currently, only +CSIM, +CRSM, +CLCK commands are supported. 

RETURN VALUE
  DSAT_OK : If commands are successfully posted to ATCOP in DS task. 

SIDE EFFECTS
  None

===========================================================================*/
dsat_result_enum_type  dsatclient_send_at_cmd_handler 
(
  ds_cmd_type         * cmd_ptr              /* DS Command pointer         */
);

/*===========================================================================

FUNCTION DSATCLIENT_SEND_AT_CMD_I

DESCRIPTION
  This function allows external clients to send in AT commands. This function
  will be executed from clients context. 

  Internally, this client is mapped to DS3G_SIOLIB_CLIENT_VSP_PORT and 
  corresponding signal is raised to process the AT command.

DEPENDENCIES
  Currently, only +CSIM, +CRSM, +CLCK, AT commands are supported. 

RETURN VALUE
  TRUE: If commands are successfully posted to ATCOP in DS task. 
  FALSE: On any error and no further processing is done.

SIDE EFFECTS
  None

===========================================================================*/
/*ARGSUSED*/
boolean dsatclient_send_at_cmd_i
(
  dsat_ext_client_id_type      client_id,  /* Registered client id */
  dsat_data_s_type             at_cmd,     /* AT command buffer and length  */
  dsat_client_cmd_rsp_cb_func  cb_func,    /* Response callback function */
  void                        *client_data /* Client's data */
);

/*===========================================================================

FUNCTION DSATCLIENT_REGISTER_CLIENT_I

DESCRIPTION
  This function allows a client to register with ATCOP for sending in AT 
  commands. The client ID will be a non-negative integer, if the call is 
  successful, and a negative value otherwise. Re-registrations are not allowed
  before releasing the earlier registration.

DEPENDENCIES
  None

RETURN VALUE
  TRUE on successful operation, FALSE otherwise.
  Client identifier is DSAT_EXT_CLIENT_ID_INVALID on error, non-negative
  integer on success.

SIDE EFFECTS
  None

===========================================================================*/
boolean dsatclient_register_client_i
( 
  dsat_client_e_type      client_type,   /* Known client type */
  dsat_ext_client_id_type *client_id_ptr /* Assign client ID upon success */
);

#endif /* DSATCLIENTI_H  */

