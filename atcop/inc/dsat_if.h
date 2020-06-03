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


Copyright (c) 2019 by Qualcomm Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "datamodem_variation.h"
#include "comdef.h"
#include "customer.h"
#include "dsmsgrrecv.h"
#include "ds707.h"
#include "dsat_v.h"
#include "ds3gsiolib.h"
#if defined(FEATURE_DATA_GCSD) || defined(FEATURE_DATA_WCDMA_CS)
#include "dsucsdappif.h"
#endif /* defined(FEATURE_DATA_GCSD) || defined(FEATURE_DATA_WCDMA_CS) */
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

/*-------------------------------------------------------------------------
    Protypes for local functions:
-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
            Function Definitions:
-------------------------------------------------------------------------*/
/*===========================================================================

FUNCTION DSAT_DEREGISTER_HANDLERS_IF

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
void dsat_deregister_handlers_if ( void );

/*==============================================================================

FUNCTION dsat_get_es_export_val_if

DESCRIPTION This function returns the dsat_es_export_val global variable .	

PARAMETERS index of array

DEPENDENCIES None

RETURN VALUE global variable

SIDE EFFECTS None
===========================================================================*/
dsat_num_item_type dsat_get_es_export_val_if(int index);

/*===========================================================================

FUNCTION dsat_report_rate_on_connect_if

DESCRIPTION
  This function is called by other modules to write the value to the current 
  rate variable dsat_report_rate_val. If dsat_x_val, set by the ATX command,
  is greater than 0 this rate will be reported with the next CONNECT result
  and during the call with any CONNECT result due to re-entry of online data
  mode. The dsat_report_rate_val variable will be reset to 0
  on the next call to dsat_sio_is_free(). 

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  Modifies the value of the dsat_report_rate_val.
===========================================================================*/
void dsat_report_rate_on_connect_if
(
  dsat_connect_rate_s_type connect_rate   /* Rate to report with next CONNECT */
);

/*===========================================================================

FUNCTION dsat_register_handlers_if

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
dsat_result_enum_type dsat_register_handlers_if
(
  dsat_incom_answer_cb_type  call_answer_cb, /* Answer call back */
  dsat_call_hangup_cb_type   call_hangup_cb  /* Hangup call back */
);

/*===========================================================================

FUNCTION  dsat_send_cr_result_if

DESCRIPTION
  Sends intermediate service reporting result code to TE or PS protocol
  stack based on response routing provided by response router.

  Should be called from mode specific protocol stack at time during
  connection negotiation that speed and quality of service is determined 
  and before compression and connect result code are sent.
 
DEPENDENCIES
  None
  
RETURN VALUE
  None
  
SIDE EFFECTS
  None
===========================================================================*/
void dsat_send_cr_result_if
(
  dsat_cr_service_e_type service
);

/*===========================================================================

FUNCTION  dsat_send_dr_result_ex_if

DESCRIPTION
  Sends intermediate data compression reporting result code to TE or
  PS protocol stack based on response routing provided by response
  router.

  Should be called from mode specific protocol stack when compression
  negotiation completed and before connect result code sent.
 
DEPENDENCIES
  None
  
RETURN VALUE
  None
  
SIDE EFFECTS
  None
===========================================================================*/
void dsat_send_dr_result_ex_if
(
  dsat_dr_mode_e_type      compression,          /*  Compression mode            */
  ds3g_siolib_port_e_type  port /*Port Id*/
);

/*===========================================================================

FUNCTION  DSAT_SEND_CR_RESULT_EX_IF

DESCRIPTION
  Sends intermediate service reporting result code to TE or PS protocol
  stack based on response routing provided by response router.

  Should be called from mode specific protocol stack at time during
  connection negotiation that speed and quality of service is determined 
  and before compression and connect result code are sent.
 
DEPENDENCIES
  None
  
RETURN VALUE
  None
  
SIDE EFFECTS
  None
===========================================================================*/
void dsat_send_cr_result_ex_if
(
  dsat_cr_service_e_type service,
  ds3g_siolib_port_e_type port 
);

/*===========================================================================

FUNCTION  dsat_send_result_code_if

DESCRIPTION
  Sends ITU-T V.25 ter basic code or mode specific extended result code
  to TE or PS protocol stack based on response routing provided if ATQ
  is 0. Also, modifies ATCOP internal state variables.

  If AT+CRC is 0, only the basic result codes are returned.
  The extended RING codes are translated to the basic code.
  Basic result codes are returned if ATQ is 0.

  Extended cellular result codes are returned if AT+CRC is 1.

DEPENDENCIES
  None
  
RETURN VALUE
  None
  
SIDE EFFECTS
  May modify ATCOP internal state variables and SIO preprocessor mode.
===========================================================================*/
void dsat_send_result_code_if
(
  dsat_result_enum_type result_code         /* Command result code */
);

/*===========================================================================

FUNCTION  dsat_send_result_code_ex_if

DESCRIPTION
  Sends ITU-T V.25 ter basic code or mode specific extended result code
  to TE or PS protocol stack based on response routing provided if ATQ
  is 0. Also, modifies ATCOP internal state variables.

  If AT+CRC is 0, only the basic result codes are returned.
  The extended RING codes are translated to the basic code.
  Basic result codes are returned if ATQ is 0.

  Extended cellular result codes are returned if AT+CRC is 1.

DEPENDENCIES
  None
  
RETURN VALUE
  None
  
SIDE EFFECTS
  May modify ATCOP internal state variables and SIO preprocessor mode.
===========================================================================*/
void dsat_send_result_code_ex_if
(
  dsat_result_enum_type   result_code,         /* Command result code */
  ds3g_siolib_port_e_type port                 /*Port Id*/
  
);

/*===========================================================================

FUNCTION dsat_change_rlp_params_if

DESCRIPTION
  This function updates the paramater sets which control the
  circuit-switched non-transparent RLP.  It is used by the UCSD API to
  modify the +CRLP and +DS command paramaters.

DEPENDENCIES
  None

RETURN VALUE
  returns an enum that describes the result of validation.
  possible values:
    DSAT_ERROR : if there was any problem
    DSAT_OK : if it is a success.

SIDE EFFECTS
  None
  
===========================================================================*/
dsat_result_enum_type dsat_change_rlp_params_if
(
  const ds_ucsd_nt_info_type  *rlp_params_ptr      /* RLP parameter values */
);

/*===========================================================================

FUNCTION dsat_get_rlp_params_if

DESCRIPTION
  This function populates the passed structure of parameters which
  control the circuit-switched non-transparent RLP.  It is used by the
  UCSD API to query the +CRLP and +DS command paramaters.

DEPENDENCIES
  None

RETURN VALUE
  returns an enum that describes the result of validation.
  possible values:
    DSAT_OK : if it is a success.

SIDE EFFECTS
  None
  
===========================================================================*/
dsat_result_enum_type dsat_get_rlp_params_if
(
  ds_ucsd_rlp_sets_type  *rlp_params_ptr           /* RLP parameter values */
);

/*===========================================================================

FUNCTION dsat_init_service_mode_if

DESCRIPTION
  Initializes the AT command processor to new operating mode. AT
  command processing functions are selected from table based on
  new operating mode. This setting is for a particular subscription.

DEPENDENCIES
  Must be called each time operating service mode changes.

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/

void dsat_init_service_mode_if
(
  sys_modem_as_id_e_type subs_id,       /* Subscription id */
  sys_sys_mode_e_type    service_mode1, /* Service mode - GSM, WCDMA, CDMA ... */
  sys_sys_mode_e_type    service_mode2  /* Service mode - GSM, WCDMA, CDMA ... */
);

/*==============================================================================

FUNCTION dsat_mmgsdi_event_cb_if

DESCRIPTION
  This function handles the MMGSDI client event response callback.  


DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None
===========================================================================*/
void dsat_mmgsdi_event_cb_if
(
  const mmgsdi_event_data_type *event
);

/*===========================================================================

FUNCTION  dsat_mmgsdi_client_init_if

DESCRIPTION
  This function updates the session id's to ATCoP.

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void dsat_mmgsdi_client_init_if
(
  mmgsdi_session_open_info_type *session_info_ptr,
  mmgsdi_client_id_type          client_id
);

/*===========================================================================
FUNCTION  dsat_cm_ph_subs_pref_handler_if

DESCRIPTION
  This function is the event handler invoked by CM for informing subscription
  specific info to ATCoP.
DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void dsat_cm_ph_subs_pref_handler_if
(
  void         *ds_cmd_ptr             /* DS Command pointer         */
);

/*===========================================================================

FUNCTION dsatetsipkt_embms_indication_handler_if

  This function handles all the embms indications coming from RRC
  Based on the indication type , different ATCOP embms handlers are
  called which do further processing.

DEPENDENCIES
  None
  
RETURN VALUE
  None

SIDE EFFECTS
  None
  
===========================================================================*/

void dsatetsipkt_embms_indication_handler_if
(
  void            *ind,
  msgr_umid_type   ind_type
);

/*===========================================================================
FUNCTION  dsat_set_current_1x_subs_id_if

DESCRIPTION
  This function used to set the current 1x subs id

DEPENDENCIES
  None

RETURNS
  None

SIDE EFFECTS
  None

===========================================================================*/
void dsat_set_current_1x_subs_id_if
(
  sys_modem_as_id_e_type subs_id
);

/*===========================================================================

FUNCTION dsatcmdp_init_config_if

DESCRIPTION
  This function initializes the complete set of AT command parameters
  to their default values.

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void dsatcmdp_init_config_if
(
  void
);

/*===========================================================================

FUNCTION dsatcmdp_get_current_mode_per_subs_if

DESCRIPTION
  Gets the current AT command mode per subscription, GSM or WCDMA or CDMA.

DEPENDENCIES
  None

RETURN VALUE
  Current service mode per subscription.

SIDE EFFECTS
  None

===========================================================================*/
dsati_mode_e_type dsatcmdp_get_current_mode_per_subs_if
(
  sys_modem_as_id_e_type subs_id
);

/*==========================================================================

FUNCTION dsatclient_register_fwd_client_if

DESCRIPTION
  This function registers the client for forwarding AT commands.
  The client ID will be a non-negative integer

DEPENDENCIES
  None
  
RETURN VALUE
  TRUE on successful operation,
  FALSE otherwise.
  
SIDE EFFECTS
  None
  
===========================================================================*/
boolean dsatclient_register_fwd_client_if
(
  dsatclient_cmd_status_cb_type   status_cb,      /*Status callback*/
  void                           *user_info_ptr   /* Client data   */
);

/*===========================================================================

FUNCTION dsatclient_ext_send_response_if

DESCRIPTION
  This function is called to post the Command response from an
  external client when the command processing is complete. No action
  will be taken if no command is pending in forwarded state.
  
DEPENDENCIES
  None 

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void dsatclient_ext_send_response_if
(
  boolean                                    cmd_status,   /* CMD status      */
  int32                                      client_id,    /* Client id       */
  dsat_client_result_enum_type               result_code,  /* result code     */
  dsat_fwd_resp_enum_type                    resp_type,    /* resp_type       */
  dsm_item_type                             *resp_buff_ptr,/* response buffer */
  uint32                                     atcop_info    /* Atcop Info      */
);

/*===========================================================================

FUNCTION dsatclient_register_fwd_at_cmd_if

DESCRIPTION
  This function allows client to register the list of commands with ATCOP 
  for forwarding.

DEPENDENCIES
  None

RETURN VALUE
  TRUE on successful operation
  FALSE otherwise.

SIDE EFFECTS
  None

===========================================================================*/
boolean dsatclient_register_fwd_at_cmd_if
(
  int32                            client_id,      /*  registered client_id   */
  uint8                            num_valid_cmds, /* number of valid commands*/
  dsat_cmd_list_type               at_cmd_list[],  /* list of AT commands     */
  dsatclient_cmd_status_cb_type    status_cb,      /*status call back         */
  dsatclient_ext_at_cmd_exec_cb    ext_at_cmd_exec_cb, /* execution call back */
  dsatclient_ext_at_cmd_abort_cb   ext_at_abort_cb,  /* Abort call back       */
  void                            *user_info_ptr     /* user data  pointer    */
);

/*===========================================================================
FUNCTION dsatclient_ext_send_urc_if

DESCRIPTION
  This function is called to post the URC from an
  external client when the command processing is complete. No action
  will be taken if no command is pending in forwarded state.
  
DEPENDENCIES
  None 

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void
dsatclient_ext_send_urc_if
(
  uint8                                    cmd_status,   /* CMD status      */
  int32                                      client_id,    /* Client id       */
  dsm_item_type                             *resp_buff_ptr/* response buffer */
);

/*===========================================================================
FUNCTION dsatclient_deregister_fwd_at_cmd_if

DESCRIPTION
  This function allows client to deregister the list of commands with ATCOP 
  for forwarding.

DEPENDENCIES
  None

RETURN VALUE
  TRUE on successful operation
  FALSE otherwise.

SIDE EFFECTS
  None

===========================================================================*/
boolean dsatclient_deregister_fwd_at_cmd_if
(
  int32                          client_id,      /*  registered client_id   */
  uint8                          num_valid_cmds, /* number of valid commands*/
  dsat_cmd_list_type             at_cmd_list[],  /* list of AT commands     */
  dsatclient_cmd_status_cb_type  status_cb,      /* status call back        */
  void                          *user_info_ptr   /* user data  pointer      */
);

/*===========================================================================

FUNCTION dsatclient_deregister_fwd_client_if

DESCRIPTION
  This function deregisters the client of AT command forwarding.

DEPENDENCIES
  None
  
RETURN VALUE
  TRUE   --  When Successfully posted to DS task
  FALSE  --  client id is INVALID and ATCoP initialization is not complete
  
SIDE EFFECTS
  None
  
===========================================================================*/
boolean dsatclient_deregister_fwd_client_if
(
  int32           client_id /* Registered client id */
);

#if (defined(FEATURE_DATA_IS707) && defined(FEATURE_DS_IS707A_CMUX))
ds707_rateset_type dsat_get_707_cmux_rev_table_if
(
  uint8  val
);

ds707_rateset_type dsat_get_707_cmux_fwd_table_if
(
  uint8  val
);
#endif /* FEATURE_DATA_IS707 && FEATURE_DS_IS707A_CMUX) */

void dsat_init_qmi_at_fwd_list_if();

