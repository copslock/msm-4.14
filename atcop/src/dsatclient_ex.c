/*===========================================================================

                        D A T A   S E R V I C E S

                A T   C O M M A N D   P R O C E S S O R

    C L I E N T   I N T E R F A C E   I M P L E M E N T A T I O N  F I L E


DESCRIPTION
  This file contains the definitions of data structures, defines and
  enumerated constants, and function implementations required for the
  data services AT command processor client asynchronous interface.

  Copyright (c) 2005 - 2015,2017,2019 by Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary.
===========================================================================*/


/*===========================================================================

                      EDIT HISTORY FOR FILE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //commercial/MPSS.HI.1.0.c8/Main/modem_proc/datamodem_r/interface/atcop/src/dsatclient_ex.c#5 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/04/17   ss      Added support for remote AT commands based on EFS.
06/27/14   tk      Initial revision (created file for Dynamic ATCoP).

===========================================================================*/
#include "datamodem_variation.h"
#include "customer.h"

#include <stringl/stringl.h>


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "comdef.h"
#include "amssassert.h"
#include "queue.h"

#include "intconv.h"
#include "dsatclienti.h"
#include "dsati.h"
#include "dsatdl.h"
#include "ps_utils.h"
#include "rcevt.h"
#include "rcecb.h"

/*===========================================================================

                    REGIONAL DEFINITIONS AND DECLARATIONS

===========================================================================*/
  extern boolean dsat_init_completed;
  extern dsat_fwd_at_pending_type dsatcmdp_processing_fwd_cmd;


/*===========================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

  This section contains local definitions for constants, macros, types,
  variables and other items needed by this module.

===========================================================================*/
  #define DSAT_MAX_CLIENT (1)

  #define FWD_AT_CMD_LIST_PATH "/ds/atcop/strings/allowed_list_efs.txt"

  /* The table that holds the data for the commands that are fowarded
  */
  qmi_at_fwd_list_q_type qmi_at_fwd_list;

  /* Current allowed list that can be forwarded to external client 
  */
  LOCAL byte allowed_list[][MAX_CMD_SIZE]={"+CLVL","+CKPD","+CMUT","+CTSA",
                                           "+CBKLT","+CFUN","+CDIS","+CRSL","+CMAR",
                                           "+CSO","+CSS","+CBC","$QCPWRDN",""};

  /* Allowed list that can be forwarded to external client based on entries in EFS*/
  dsat_allowed_list_efs_type allowed_list_efs_info;

  /* This holds the valid forwarded client_id's that has been regsitered
  */
  int32 dsat_fwd_at_clients[DSAT_MAX_CLIENT]={0};

/*-------------------------- Local Functions -------------------------------*/
/*===========================================================================

FUNCTION CLIENT_VALIDATE_FWD_AT_CMDS

DESCRIPTION
  This function verifies the AT commands requested for forwarding from 
  the client's command queue buffer.

DEPENDENCIES
  None
  
RETURN VALUE
  TRUE on successful operation, FALSE otherwise.
  
SIDE EFFECTS
  None
  
===========================================================================*/
LOCAL boolean client_validate_fwd_at_cmds 
(
  int32                               client_id,      /*  registered client_id  */
  uint8                               num_valid_cmds,/* number of valid commands*/
  const dsat_cmd_list_type            at_cmd_list[]  /* list of AT commands     */
);
/*===========================================================================

FUNCTION CLIENT_UPDATE_FWD_AT_CMDS

DESCRIPTION
  This function updates the internal tables with the forward AT 
  command registration from the client's 
  command queue buffer.

DEPENDENCIES
  None
  
RETURN VALUE
  TRUE on successful operation, FALSE otherwise.
  
SIDE EFFECTS
  None
  
===========================================================================*/
LOCAL boolean client_update_fwd_at_cmds 
(
  int32                              client_id,     /*  registered client_id  */
  uint8                              num_valid_cmds,/*number of valid commands*/
  const dsat_cmd_list_type           at_cmd_list[], /*list of AT commands     */
  dsatclient_ext_at_cmd_exec_cb      ext_at_cmd_exec_cb,/* execution call back*/
  dsatclient_ext_at_cmd_abort_cb     ext_at_abort_cb,  /* Abort call back     */
  void                              *user_info_ptr     /*       Client data   */
);

/*===========================================================================

FUNCTION CLIENT_VALIDATE_FWD_CLIENT_ID

DESCRIPTION
  This function checks for valid client id.

DEPENDENCIES
  None
  
RETURN VALUE
  TRUE   -- When client-id given is a valid client id
  FALSE  -- client id is INVALID
  
SIDE EFFECTS
  None
  
===========================================================================*/
LOCAL boolean client_validate_fwd_client_id 
(
  int32                              client_id  /* Client id */
);

/*===========================================================================

FUNCTION CLIENT_COMPARE_FWD_AT_CMDS

DESCRIPTION
  This function finds the AT command name in the forwarding AT
  commands list queue.

DEPENDENCIES
  None
  
RETURN VALUE
  TRUE on successful operation
  FALSE otherwise.
  
SIDE EFFECTS
  None
  
===========================================================================*/

static int client_compare_fwd_at_cmd
(
  void *cmd_ptr,
  void *cmd_name 
);

/*==========================================================================

FUNCTION DSATCLIENT_REGISTER_FWD_CLIENT

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
boolean dsatclient_register_fwd_client 
(
  dsatclient_cmd_status_cb_type   status_cb,      /*Status callback*/
  void                           *user_info_ptr   /* Client data   */
)
{
  ds_cmd_type            *cmd_buf  = NULL;
  dsat_fwd_at_cmd_s_type *forward_at_cmd = NULL;
  
  if(FALSE == dsat_is_atcop_allowed())
  {
    DS_ATCOP_ERROR_LOG_0(" ATcop is not initialized");
     return FALSE;
  }

  if((status_cb == NULL)||(dsat_init_completed == FALSE))
  {
    DS_ATCOP_ERROR_LOG_1("Registration failure.Init Status =d ",dsat_init_completed);
    return FALSE;
  }

  /*-----------------------------------------------------------
     Post the command to DS task and return success to client
  ------------------------------------------------------------*/
  cmd_buf  = dsat_get_cmd_buf(sizeof(dsat_fwd_at_cmd_s_type), FALSE);
  forward_at_cmd = cmd_buf->cmd_payload_ptr;

  cmd_buf->hdr.cmd_id = DS_CMD_ATCOP_FWD_CLIENT_REG;
  forward_at_cmd->status_cb = status_cb;
  forward_at_cmd->user_info_ptr = user_info_ptr;
  ds_put_cmd(cmd_buf);

  return TRUE;
}/* dsatclient_register_fwd_client */

/*===========================================================================

FUNCTION DSATCLIENT_DEREGISTER_FWD_CLIENT

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
boolean dsatclient_deregister_fwd_client 
(
  int32           client_id /* Registered client id */
)
{
  ds_cmd_type            *cmd_buf  = NULL;
  dsat_fwd_at_cmd_s_type *forward_at_cmd = NULL;

  if((client_id == 0)||(dsat_init_completed == FALSE))
  {
    DS_ATCOP_ERROR_LOG_1("De-Registration failure.Init Status =d ",
                                      dsat_init_completed);
    return FALSE;
  }

  /*-----------------------------------------------------------
     Post the command to DS task and return success to client
  ------------------------------------------------------------*/
  cmd_buf = dsat_get_cmd_buf(sizeof(dsat_fwd_at_cmd_s_type), FALSE);
  forward_at_cmd = cmd_buf->cmd_payload_ptr;

  cmd_buf->hdr.cmd_id = DS_CMD_ATCOP_FWD_CLIENT_DEREG;
  forward_at_cmd->client_id = client_id;
  ds_put_cmd(cmd_buf);

  return TRUE;
}/* dsatclient_deregister_fwd_client */

/*===========================================================================

FUNCTION DSATCLIENT_REGISTER_FWD_AT_CMD

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
boolean dsatclient_register_fwd_at_cmd 
(
  int32                            client_id,      /*  registered client_id   */
  uint8                            num_valid_cmds, /* number of valid commands*/
  dsat_cmd_list_type               at_cmd_list[],  /* list of AT commands     */
  dsatclient_cmd_status_cb_type    status_cb,      /*status call back         */
  dsatclient_ext_at_cmd_exec_cb    ext_at_cmd_exec_cb, /* execution call back */
  dsatclient_ext_at_cmd_abort_cb   ext_at_abort_cb,  /* Abort call back       */
  void                            *user_info_ptr     /* user data  pointer    */
)
{
  uint8 valid_index = 0;
  uint8 i = 0;
  ds_cmd_type            *cmd_buf  = NULL;
  dsat_fwd_at_cmd_s_type *forward_at_cmd = NULL;

  /* Data Validation */
  if((status_cb == NULL)||(ext_at_cmd_exec_cb == NULL)||
     (dsat_init_completed == FALSE)||(at_cmd_list == NULL)||
     ( num_valid_cmds == 0 ) || ( num_valid_cmds > MAX_CMD_LIST))
  {
   DS_ATCOP_ERROR_LOG_0("Invalid data provided for ATCoP registration");
    return FALSE;
  }

  /* Abortability check */
  while(valid_index < num_valid_cmds)
  {
    if(at_cmd_list[valid_index].is_abortable == TRUE)
    {
      if( ext_at_abort_cb == NULL)
      {
       DS_ATCOP_ERROR_LOG_0("Invalid input data");
        return FALSE;
      }
    }

    if((at_cmd_list[valid_index].cmd_buff_len > MAX_CMD_SIZE)||
       (at_cmd_list[valid_index].cmd_buff_len == 0))
    {
     DS_ATCOP_ERROR_LOG_0("Invalid command data");
      return FALSE;
    }
    valid_index++;
  }/* while(valid_index < num_valid_cmds) */

  /*-----------------------------------------------------------
     Post the command to DS task and return success to client
  ------------------------------------------------------------*/
  cmd_buf  = dsat_get_cmd_buf(sizeof(dsat_fwd_at_cmd_s_type), FALSE);
  forward_at_cmd = cmd_buf->cmd_payload_ptr;

  cmd_buf->hdr.cmd_id = DS_CMD_ATCOP_FWD_AT_CMD_REG;

  for ( i = 0; i < num_valid_cmds; ++i)
  {
    forward_at_cmd->at_cmd_list[i].cmd_buff_len = 
                                    at_cmd_list[i].cmd_buff_len;
    (void) dsatutil_memscpy((void*)&forward_at_cmd->at_cmd_list[i].cmd_buff[0],
             MAX_CMD_SIZE,
            (void*)&at_cmd_list[i].cmd_buff[0],
            forward_at_cmd->at_cmd_list[i].cmd_buff_len);      
    forward_at_cmd->at_cmd_list[i].is_abortable = 
                                    at_cmd_list[i].is_abortable;
  }
  forward_at_cmd->client_id = client_id;
  forward_at_cmd->num_valid_cmds = num_valid_cmds;
  forward_at_cmd->status_cb = status_cb;
  forward_at_cmd->ext_at_cmd_exec_cb = ext_at_cmd_exec_cb;
  forward_at_cmd->ext_at_abort_cb = ext_at_abort_cb;
  forward_at_cmd->user_info_ptr = user_info_ptr;
  DS_AT_MSG1_MED("Num of valid commands received - %d",num_valid_cmds);
  ds_put_cmd(cmd_buf);

  return TRUE;
}/* dsatclient_register_fwd_at_cmd */

/*===========================================================================
FUNCTION DSATCLIENT_DEREGISTER_FWD_AT_CMD

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
boolean dsatclient_deregister_fwd_at_cmd 
(
  int32              client_id,      /*  registered client_id   */
  uint8              num_valid_cmds, /* number of valid commands*/
  dsat_cmd_list_type            at_cmd_list[],  /* list of AT commands     */
  dsatclient_cmd_status_cb_type status_cb,      /*status call back         */
  void                          *user_info_ptr  /* user data  pointer      */
)
{
  uint8 valid_index = 0;
  uint8 i = 0;
  ds_cmd_type * cmd_buf = NULL;
  dsat_fwd_at_cmd_s_type *fwd_at_cmd_ptr;

  /* Data Validation */
  if((dsat_init_completed == FALSE)||(at_cmd_list == NULL)||
     ( num_valid_cmds == 0 ) || ( num_valid_cmds > MAX_CMD_LIST))
  {
   DS_ATCOP_ERROR_LOG_0("Invalid data provided for ATCoP deregistration");
    return FALSE;
  }

  /* Abortability check */
  while(valid_index < num_valid_cmds)
  {
    if((at_cmd_list[valid_index].cmd_buff_len > MAX_CMD_SIZE)||
       (at_cmd_list[valid_index].cmd_buff_len == 0))
    {
     DS_ATCOP_ERROR_LOG_0("Invalid command data");
      return FALSE;
    }
    valid_index++;
  }/* while(valid_index < num_valid_cmds) */

  /*-----------------------------------------------------------
     Post the command to DS task and return success to client
  ------------------------------------------------------------*/
  cmd_buf = dsat_get_cmd_buf(sizeof(dsat_fwd_at_cmd_s_type), FALSE);
  fwd_at_cmd_ptr = cmd_buf->cmd_payload_ptr;

  cmd_buf->hdr.cmd_id = DS_CMD_ATCOP_FWD_AT_CMD_DEREG;
  for ( i = 0; i < num_valid_cmds; ++i)
  {
    fwd_at_cmd_ptr->at_cmd_list[i].cmd_buff_len = 
                                  at_cmd_list[i].cmd_buff_len;
    (void) dsatutil_memscpy((void*)&fwd_at_cmd_ptr->at_cmd_list[i].cmd_buff[0],
             MAX_CMD_SIZE,
            (void*)&at_cmd_list[i].cmd_buff[0],
            fwd_at_cmd_ptr->at_cmd_list[i].cmd_buff_len);
    fwd_at_cmd_ptr->at_cmd_list[i].cmd_buff[fwd_at_cmd_ptr->at_cmd_list[i].cmd_buff_len] = '\0';
    DS_AT_MSG_SPRINTF_3_ERROR("deregister cmd name = %s, %s, %d",
         (void*)&at_cmd_list[i].cmd_buff[0],
         (void*)&fwd_at_cmd_ptr->at_cmd_list[i].cmd_buff[0],
         fwd_at_cmd_ptr->at_cmd_list[i].cmd_buff_len);

  }
  fwd_at_cmd_ptr->client_id = client_id;
  fwd_at_cmd_ptr->num_valid_cmds = num_valid_cmds;
  fwd_at_cmd_ptr->status_cb = status_cb;
  fwd_at_cmd_ptr->user_info_ptr = user_info_ptr;
  DS_AT_MSG1_MED("Num of valid commands received - %d",num_valid_cmds);
  ds_put_cmd(cmd_buf);
  return TRUE;
}/* dsatclient_deregister_fwd_at_cmd */

/*===========================================================================

FUNCTION DSATCLIENT_REGISTER_FWD_CLIENT_HANDLER

DESCRIPTION
  This function process the forward AT command registration from the client's 
  command queue buffer.

DEPENDENCIES
  None
  
RETURN VALUE
  DSAT_ASYNC_EVENT
  
SIDE EFFECTS
  None
  
===========================================================================*/
dsat_result_enum_type dsatclient_register_fwd_client_handler 
(
  ds_cmd_type         * cmd_ptr              /* DS Command pointer         */
)
{
  uint8 client =0;
  uint32 client_id = 0;
  boolean generate_client_id = FALSE;
  dsat_fwd_at_cmd_s_type *forward_at_cmd = dsat_get_cmd_payload_ptr(cmd_ptr);

  while(client < DSAT_MAX_CLIENT)
  {
    if(dsat_fwd_at_clients[client] == DSAT_INVALID_CLIENT_ID )
    {
      generate_client_id = TRUE;
      break;
    }
    client++;
  }/* while(client < DSAT_MAX_CLIENT) */

  if(generate_client_id == TRUE)
  {
    ps_utils_generate_rand_num( &client_id, sizeof(uint32) );

    /* client_validate_fwd_client_id returns false if
       client id is valid and not assigned already */

    if( (client_id == 0) || (FALSE != client_validate_fwd_client_id(client_id)) )
    {
      DS_ATCOP_ERROR_FATAL("Invalid client id");
    }
    DS_AT_MSG1_HIGH("New client id %d", client_id);
    dsat_fwd_at_clients[client] = client_id;
  }
    /* Update client of registration status */
  forward_at_cmd->status_cb(generate_client_id,
                     client_id,
                     forward_at_cmd->user_info_ptr);

  return DSAT_ASYNC_EVENT;
}/* dsatclient_register_fwd_client_handler */

/*===========================================================================

FUNCTION DSATCLIENT_DEREGISTER_FWD_CLIENT_HANDLER

DESCRIPTION
  This function process the forward AT command de-registration from the client's 
  command queue buffer.

DEPENDENCIES
  None
  
RETURN VALUE
  DSAT_ASYNC_EVENT  -- if no client command processing is pending 
  DSAT_ERROR        -- if command response is still pending for this
                       client.

SIDE EFFECTS
  None
  
===========================================================================*/
dsat_result_enum_type dsatclient_deregister_fwd_client_handler 
(
  ds_cmd_type         * cmd_ptr              /* DS Command pointer         */
)
{
  dsat_result_enum_type  result_code = DSAT_ASYNC_EVENT;
  dsat_fwd_at_cmd_s_type *forward_at_cmd = dsat_get_cmd_payload_ptr(cmd_ptr);
  int32                  client_id = 0;
  dsat_fwd_at_cmd_table_type *fwd_at_cmd_p = NULL;
  dsat_fwd_at_cmd_table_type *temp_fwd_at_cmd_p = NULL;

  client_id = forward_at_cmd->client_id;

  if (DSAT_DL_VALIDATE_SYMBOL_ADDR(dsatdl_vtable.dsatclient_deregister_fwd_cmd_fp))
  {
    result_code = dsatdl_vtable.dsatclient_deregister_fwd_cmd_fp(client_id);
  }

  

  /* Clear the registered commands associated with this client */
  fwd_at_cmd_p = (dsat_fwd_at_cmd_table_type*)q_check(&qmi_at_fwd_list.at_fwd_cmd_q);
  while(fwd_at_cmd_p != NULL)
  {
    if(0 == dsatutil_strcmp_ig_sp_case((const byte *)fwd_at_cmd_p->cmd_name,
                                       (const byte *)"+CFUN"))
    {
      (void)rcecb_unregister_name("SYSM:FWD:SHUTDOWN", (void *)dsat_reset_cmd);
    }
    
    else if ( 0 == dsatutil_strcmp_ig_sp_case((const byte *)fwd_at_cmd_p->cmd_name,
                                          (void *)"$QCPWRDN" ) )
    {
      (void)rcecb_unregister_name("SYSM:FWD:POWEROFF", (void *)dsat_shutdown_cmd);
    }
    temp_fwd_at_cmd_p = fwd_at_cmd_p;
    fwd_at_cmd_p = q_next(&qmi_at_fwd_list.at_fwd_cmd_q,
                           &(fwd_at_cmd_p->link));
    if(temp_fwd_at_cmd_p->client_id == client_id)
    {
      if(TRUE == q_delete_ext( &qmi_at_fwd_list.at_fwd_cmd_q, 
                                             &temp_fwd_at_cmd_p->link))
    {
        DS_AT_MSG_SPRINTF_2_HIGH("at fwd command name %s successfully deleted from queue for client id %d",
                                             temp_fwd_at_cmd_p->cmd_name, client_id);
        qmi_at_fwd_list.at_fwd_cmd_cnt--;
        dsatutil_free_memory(temp_fwd_at_cmd_p);
      }
      else
      {
        DS_AT_MSG1_HIGH("at fwd command 0x%p could not be deleted from queue",
                                             temp_fwd_at_cmd_p);
      }
    }
  }
  
  return result_code;
}/* dsatclient_deregister_fwd_client_handler */ 

/*===========================================================================

FUNCTION DSATCLIENT_REGISTER_FWD_AT_CMD_HANDLER

DESCRIPTION
  This function process the forward AT command registration from the client's 
  command queue buffer.

DEPENDENCIES
  None
  
RETURN VALUE
  DSAT_ASYNC_EVENT
  
SIDE EFFECTS
  None
  
===========================================================================*/
dsat_result_enum_type dsatclient_register_fwd_at_cmd_handler 
(
  ds_cmd_type         * cmd_ptr              /* DS Command pointer         */
)
{
  boolean result                   = DSAT_FAILURE;
  dsat_fwd_at_cmd_s_type *forward_at_cmd = dsat_get_cmd_payload_ptr(cmd_ptr);
  dsat_fwd_at_cmd_table_type *fwd_at_cmd_p = NULL;

  if( FALSE == client_validate_fwd_client_id(
                      forward_at_cmd->client_id))
  {
   DS_ATCOP_ERROR_LOG_0("Invalid client id");
  }
  else
  {
    /* Check whether the commands are valid */
    result = client_validate_fwd_at_cmds( 
             forward_at_cmd->client_id,
             forward_at_cmd->num_valid_cmds,
             (const dsat_cmd_list_type *)forward_at_cmd->at_cmd_list
             );

    DS_AT_MSG1_HIGH("Validation done result = %d", (int)result);

    /* If validation is success update the client table and send status call
       back function with DSAT_SUCCESS..
       If validation fails send status call back with DSAT_FAILURE.
    */
    if(result == DSAT_SUCCESS)
    {
        /* Update the forwarded AT commands table*/
      result = client_update_fwd_at_cmds(
         forward_at_cmd->client_id,
         forward_at_cmd->num_valid_cmds,
         (const dsat_cmd_list_type *)forward_at_cmd->at_cmd_list,
         forward_at_cmd->ext_at_cmd_exec_cb,
         forward_at_cmd->ext_at_abort_cb,
         forward_at_cmd->user_info_ptr
         );
    }
  }

  /* Update client of registration status */
  DS_AT_MSG1_MED("Result = %d",(int)result);
  forward_at_cmd->status_cb(result,
       forward_at_cmd->client_id,
       forward_at_cmd->user_info_ptr);

  fwd_at_cmd_p = (dsat_fwd_at_cmd_table_type*)q_check(&qmi_at_fwd_list.at_fwd_cmd_q);
  while(fwd_at_cmd_p != NULL)
    {  

    if(0 == dsatutil_strcmp_ig_sp_case((const byte *)fwd_at_cmd_p->cmd_name,
                                   (const byte *)"+CFUN"))
      {
        (void)rcecb_register_name("SYSM:FWD:SHUTDOWN", (void *)dsat_reset_cmd);
      }
    else if ( 0 == dsatutil_strcmp_ig_sp_case((const byte *)fwd_at_cmd_p->cmd_name,
                                          (void *)"$QCPWRDN" ) )
      {
        (void)rcecb_register_name("SYSM:FWD:POWEROFF", (void *)dsat_shutdown_cmd);
      }
    fwd_at_cmd_p = q_next(&qmi_at_fwd_list.at_fwd_cmd_q,
                          &(fwd_at_cmd_p->link));
    }  
  return DSAT_ASYNC_EVENT;

}/* dsatclient_register_fwd_at_cmd_handler  */

/*===========================================================================

FUNCTION DSATCLIENT_DEREGISTER_FWD_AT_CMD_HANDLER

DESCRIPTION
  This function process the forward AT command deregistration from the
  client's command queue buffer.

DEPENDENCIES
  None

RETURN VALUE
  DSAT_ASYNC_EVENT

SIDE EFFECTS
  None

===========================================================================*/
dsat_result_enum_type dsatclient_deregister_fwd_at_cmd_handler
(
  ds_cmd_type *        cmd_ptr              /* DS Command pointer */
)
{
  dsat_result_enum_type   result = DSAT_ASYNC_EVENT;
  dsat_fwd_at_cmd_s_type *fwd_at_cmd_ptr = dsat_get_cmd_payload_ptr(cmd_ptr);
  uint8                   index1 = 0;
  uint8                   index2 = 0;
  dsat_fwd_at_cmd_table_type *fwd_at_cmd_queue_p = NULL;
  boolean match_found = FALSE;

   if( FALSE == client_validate_fwd_client_id(fwd_at_cmd_ptr->client_id) ||
       fwd_at_cmd_ptr->num_valid_cmds > MAX_CMD_LIST )
   {
    DS_ATCOP_ERROR_LOG_0("Invalid client id");
   }
   else
   {
    if (DSAT_DL_VALIDATE_SYMBOL_ADDR(dsatdl_vtable.dsatclient_deregister_fwd_cmd_fp))
    {
      /* Check if processing is pending for a command in this list */
      for (index1 = 0; index1 < fwd_at_cmd_ptr->num_valid_cmds; index1++)
      {
        if (0 == dsatutil_strcmp_ig_sp_case(
                   (const byte *)fwd_at_cmd_ptr->at_cmd_list[index1].cmd_buff,
                   (const byte *)dsatcmdp_processing_fwd_cmd.cmd_name))
        {
          result = dsatdl_vtable.dsatclient_deregister_fwd_cmd_fp(fwd_at_cmd_ptr->client_id);
          break;
        }
      }
    }

    /* Validate the command list */
    for(index1 = 0; index1 < fwd_at_cmd_ptr->num_valid_cmds; index1++)
    {
      /* command length validation */
      if( fwd_at_cmd_ptr->at_cmd_list[index1].cmd_buff_len > (MAX_CMD_SIZE-1))
      {
        DS_AT_MSG1_ERROR("Invalid command len %d",fwd_at_cmd_ptr->at_cmd_list[index1].cmd_buff_len);
        
        match_found = FALSE;
        goto bail;
      }

      /* check all the commands in the input deregister list are in forwarding list */
      match_found = FALSE;
      if ( NULL != q_linear_search( &qmi_at_fwd_list.at_fwd_cmd_q,
                     client_compare_fwd_at_cmd,
                     (void *)&fwd_at_cmd_ptr->at_cmd_list[index1].cmd_buff))
      {
          match_found = TRUE;
      }

      /* Even a single entry in the input deregister list is not register , drop the request */
      if(match_found == FALSE)
      {
        DS_AT_MSG_SPRINTF_1_ERROR("Un-registered at fwd command %s received",
                               fwd_at_cmd_ptr->at_cmd_list[index1].cmd_buff);
        goto bail;
      }

      /* Check if entry is duplicated in the input deregister list */
      for(index2 = 0; index2 < index1; index2++)
      {
        if(0 == dsatutil_strcmp_ig_sp_case(
                                 (const byte *)fwd_at_cmd_ptr->at_cmd_list[index2].cmd_buff,
                                 (const byte *)fwd_at_cmd_ptr->at_cmd_list[index1].cmd_buff))
        {
          DS_AT_MSG_SPRINTF_1_ERROR("Duplicate entry found in deregister list cmd name = %s",
          (const byte *)fwd_at_cmd_ptr->at_cmd_list[index1].cmd_buff);
          match_found = FALSE;
          goto bail;
        }        
      }
    }
    
    /*No check for index1 ? and dont need to stop the processing command?*/
    
    /* Deregister each command in the list if it was registered for this client */
    for (index1 = 0; index1 < fwd_at_cmd_ptr->num_valid_cmds; index1++)
    {
      /* Check if the command is present in the registered commands table */
      fwd_at_cmd_queue_p = (dsat_fwd_at_cmd_table_type*)q_check(&qmi_at_fwd_list.at_fwd_cmd_q);
      while(fwd_at_cmd_queue_p != NULL)
      {
        /* Check if the command was registered for this client */
        if ((fwd_at_cmd_ptr->client_id == fwd_at_cmd_queue_p->client_id) &&
            (0 == dsatutil_strcmp_ig_sp_case(
                    (const byte *)fwd_at_cmd_ptr->at_cmd_list[index1].cmd_buff,
                    (const byte *)fwd_at_cmd_queue_p->cmd_name)))
        {
          DS_AT_MSG_SPRINTF_2_HIGH("deregister at fwd cmd name = %s, cliend id %d ",
                                    (const byte *)fwd_at_cmd_ptr->at_cmd_list[index1].cmd_buff,
                                    (const byte *)fwd_at_cmd_ptr->client_id);
#ifdef FEATURE_MODEM_RCINIT_PHASE2
          if (0 == dsatutil_strcmp_ig_sp_case(
                     (const byte *) fwd_at_cmd_queue_p->cmd_name,
                     (const byte *) "+CFUN"))
          {
            (void)rcecb_unregister_name("SYSM:FWD:SHUTDOWN", (void *)dsat_reset_cmd);
          }
          else if (0 == dsatutil_strcmp_ig_sp_case(
                          (const byte *)fwd_at_cmd_queue_p->cmd_name,
                          (const byte *) "$QCPWRDN"))
          {
            (void)rcecb_unregister_name("SYSM:FWD:POWEROFF", (void *)dsat_shutdown_cmd);
          }
#endif
           if (TRUE == q_delete_ext( &qmi_at_fwd_list.at_fwd_cmd_q,
                                    &fwd_at_cmd_queue_p->link ) )
          {
            qmi_at_fwd_list.at_fwd_cmd_cnt--;
            dsatutil_free_memory(fwd_at_cmd_queue_p);
          }
          else
          {
            DS_AT_MSG1_ERROR("deregister at fwd command node 0x%p could not be deleted from queue",
                              fwd_at_cmd_queue_p);
          }
          break;
        }
        fwd_at_cmd_queue_p = q_next(&qmi_at_fwd_list.at_fwd_cmd_q,
                           &(fwd_at_cmd_queue_p->link));
      }
    }
  }

bail:
  if(fwd_at_cmd_ptr->status_cb && fwd_at_cmd_ptr->user_info_ptr)
  { 
    fwd_at_cmd_ptr->status_cb(match_found,
		fwd_at_cmd_ptr->client_id,
		fwd_at_cmd_ptr->user_info_ptr);
  }
  
  return result;
} /* dsatclient_deregister_fwd_at_cmd_handler */

/*===========================================================================
FUNCTION CLIENT_FWD_CMD_REQUEST_HANDLER

DESCRIPTION
  This function is the handler function for forward command request. 

DEPENDENCIES
  None
  
RETURN VALUE
  DSAT_ERROR : if there was any problem .
  DSAT_OK : if it is a success.

SIDE EFFECTS
  None
  
======================================================================*/

LOCAL dsat_result_enum_type client_fwd_cmd_request_handler
(
  ds_at_fwd_cmd_request_s_type *fwd_cmd_req, /* Reset command request pointer */
  tokens_struct_type           *token_ptr    /* Token pointer */
)
{
  boolean             result     = FALSE;
  dsat_cmd_state_type curr_state;
  dsat_fwd_at_cmd_table_type *fwd_at_cmd_p = NULL;

  memset(&curr_state, 0x00, sizeof(dsat_cmd_state_type));

  fwd_at_cmd_p = (dsat_fwd_at_cmd_table_type*)q_check(&qmi_at_fwd_list.at_fwd_cmd_q);
  while(fwd_at_cmd_p != NULL)
  {
    if ( 0 ==  dsatutil_strcmp_ig_sp_case( (const byte *)token_ptr->name, 
                           (const byte *)&fwd_at_cmd_p->cmd_name[0]) )
    {
      DS_AT_MSG_SPRINTF_1_HIGH("Found match for QMI RESET client processing cmd=%s ",
                               token_ptr->name);

      dsatclient_state_info_update(&curr_state);

    /* Do not over write any of the dsatcmdp_processing_fwd_cmd
           as it could corrupt the earlier valid data as both AT command and QMI DMS could 
           co-exist. The Port of .DS3G_SIOLIB_PORT_MAX is used as a unique value to identify 
           its belong to QMI DMS request. */

      if ( fwd_at_cmd_p->ext_at_cmd_exec_cb == NULL )
      {
        DS_ATCOP_ERROR_FATAL("Exec_callback function pointer is NULL");
      }
      /* DS3G_SIOLIB_PORT_MAX ==> This is used to to uniquely identify if this is for QMI DMS
          */
      if ( DSAT_SUCCESS == fwd_at_cmd_p->ext_at_cmd_exec_cb( 
                                       dsatcmdp_at_state,
                                       (const tokens_struct_type *)token_ptr,
                                       curr_state,
                                       (uint32)(int)(DS3G_SIOLIB_PORT_MAX),
                                      fwd_at_cmd_p->user_info_ptr))
      {
        result = TRUE;
       
      } /* Command forwarding is SUCCESS */
      else
      {
        result = FALSE;
      }
      break;
    }/* End of If .. */

    fwd_at_cmd_p = q_next(&qmi_at_fwd_list.at_fwd_cmd_q,
                          &(fwd_at_cmd_p->link));
  } /* end of for loop */

  if ((NULL != fwd_cmd_req) && (NULL != fwd_cmd_req->status_func_cb))
  {
    fwd_cmd_req->status_func_cb(result, fwd_cmd_req->user_info_ptr);
  }

  return DSAT_ASYNC_EVENT;
}/* client_fwd_cmd_request_handler */

/*===========================================================================
FUNCTION DSATCLIENT_RESET_CMD_REQUEST_HANDLER

DESCRIPTION
  This function is the handler function for reset request. 

DEPENDENCIES
  None
  
RETURN VALUE
  DSAT_ERROR : if there was any problem .
  DSAT_OK : if it is a success.

SIDE EFFECTS
  None
  
======================================================================*/

dsat_result_enum_type dsatclient_reset_cmd_request_handler
(
  ds_cmd_type         * cmd_ptr              /* DS Command pointer         */
)
{
  ds_at_fwd_cmd_request_s_type *fwd_req_cmd = dsat_get_cmd_payload_ptr(cmd_ptr);
  tokens_struct_type token;

  /* Populate the token pointer info related to AT+CFUN=1,1 */
  token.name       = (byte *) "+CFUN";
  token.args_found = 2;
  token.arg[0]     = (byte *) "1";
  token.arg[1]     = (byte *) "1";
  token.op         = (unsigned int)(NA|EQ|AR);

  return client_fwd_cmd_request_handler(fwd_req_cmd, &token);
} /* dsatclient_reset_cmd_request_handler */

/*===========================================================================
FUNCTION DSATCLIENT_SHUTDOWN_CMD_REQUEST_HANDLER

DESCRIPTION
  This function is the handler function for shutdown request. 

DEPENDENCIES
  None
  
RETURN VALUE
  DSAT_ERROR : if there was any problem .
  DSAT_OK : if it is a success.

SIDE EFFECTS
  None
  
======================================================================*/

dsat_result_enum_type  dsatclient_shutdown_cmd_request_handler
(
  ds_cmd_type         * cmd_ptr              /* DS Command pointer         */
)
{
  ds_at_fwd_cmd_request_s_type *fwd_req_cmd = dsat_get_cmd_payload_ptr(cmd_ptr);
  tokens_struct_type token;

  /* Populate the token pointer info related to AT$QCPWRDN */
  token.name       = (byte *) "$QCPWRDN";
  token.args_found = 0;
  token.op         = (unsigned int)(NA);

  return client_fwd_cmd_request_handler(fwd_req_cmd, &token);
} /* dsatclient_shutdown_cmd_request_handler */

/*===========================================================================

FUNCTION CLIENT_VALIDATE_FWD_AT_CMDS

DESCRIPTION
  This function verifies the AT commands requested for forwarding from the client's 
  command queue buffer.

DEPENDENCIES
  None
  
RETURN VALUE
  TRUE on successful operation
  FALSE otherwise.
  
SIDE EFFECTS
  None
  
===========================================================================*/
LOCAL boolean client_validate_fwd_at_cmds 
(
  int32                                     client_id,  /* Registered client */
  uint8                                     num_valid_cmds, /*no of commands*/
  const dsat_cmd_list_type                  at_cmd_list[] /* AT command list */
)
{
  uint8 cmd_loop = 0;
  uint8 i =0;
  boolean valid_cmd = FALSE;
  uint8 allowed_list_len = ARR_SIZE(allowed_list);
  byte temp_fwd_at_cmd_name[MAX_CMD_SIZE]={0};
  uint8 allowed_list_efs_len=0;
  dsat_cmd_category_enum_type token_cat = BASIC_AT_CMD;
  dsati_at_cmd_table_entry_type *array_ptr = NULL;  /* Ptr to array of cmd tables */
  
  /* Check if the number of valid commands is less than MAX_CMD_LIST */
  if( num_valid_cmds > MAX_CMD_LIST )
  {
    DS_ATCOP_ERROR_LOG_1("Num_valid_cmds(=d) is greater than allowed length per request",
      num_valid_cmds);
    return FALSE;
  }

  for(cmd_loop = 0; cmd_loop < num_valid_cmds; cmd_loop++)
  {
    /* command length validation */
    if( at_cmd_list[cmd_loop].cmd_buff_len > (MAX_CMD_SIZE-1))
    {
      DS_ATCOP_ERROR_LOG_1("Invalid command len =d",at_cmd_list[cmd_loop].cmd_buff_len);
      return FALSE;
    }

    /* cmd name string formation */
    (void) dsatutil_memscpy((void*)&temp_fwd_at_cmd_name[0],MAX_CMD_SIZE,
              (void*)at_cmd_list[cmd_loop].cmd_buff, 
                     MIN(MAX_CMD_SIZE,at_cmd_list[cmd_loop].cmd_buff_len));

    temp_fwd_at_cmd_name[at_cmd_list[cmd_loop].cmd_buff_len]='\0';

    /* Process the entry for validity against allowed list */
    for( i=0,valid_cmd = FALSE;i<( allowed_list_len-1);i++)
    {
      if(0 == dsatutil_strcmp_ig_sp_case((const byte *)temp_fwd_at_cmd_name,
                                         (const byte *)allowed_list[i]))
      {
        valid_cmd = TRUE;
        break;
      }
    }

    /* Process the entry for validity against the allowed list baseed on EFS */
    if(allowed_list_efs_info.is_available == TRUE && valid_cmd == FALSE)
    {
      allowed_list_efs_len = allowed_list_efs_info.num_at_cmds;
      for( i=0 ; i < allowed_list_efs_len ; i++ )
      {
        if(0 == dsatutil_strcmp_ig_sp_case((const byte *)temp_fwd_at_cmd_name,
                                           (const byte *)*(allowed_list_efs_info.cmd_list_efs + i)))
        {
          valid_cmd = TRUE;
          break;
        }
      }
    }
    
    /* if command not found in allowed list then check if the command
     * is part of AT command tables (ex, vendor). If found in AT
     * command table then validate attribute NOT_FORWARDABLE.
     * If attribute is set then command is not allowed to register.
     * Note: All basic and sreg commands are not allowed to register.
     */
    if(valid_cmd == FALSE)
    {
      int no_match = 1;
      int j, k;
      const dsati_cmd_type *table_ptr;
      token_cat = BASIC_AT_CMD;
      while( token_cat < NUM_AT_CMD_CATEGORIES)
      {
         no_match = 1;
         array_ptr = at_cmd_table[token_cat];
        if ( array_ptr != NULL )
        {
        /* Search each command table entry pointed to by array entry. */
          for ( j = 0, k = 0; array_ptr[j].table_ptr != NULL && no_match; j++ )
          {
            /* Search each command table entry for command match. */
            for ( k = 0; k < *(array_ptr[j].table_size) && no_match; k++ )
            {
              no_match =
                dsatutil_strcmp_ig_sp_case( temp_fwd_at_cmd_name,
                                          (const byte *)array_ptr[j].table_ptr[k].name );
            }
          }
        }

        if(!no_match)
        {
          table_ptr = &(array_ptr[j-1].table_ptr[k-1]);
          if (token_cat == BASIC_AT_CMD || token_cat == SREG_AT_CMD|| 
              table_ptr->attrib & NOT_FORWARDABLE)
          {
     DS_ATCOP_ERROR_LOG_0("AT spec command is not allowed to register for forwarding");
      return FALSE;
    }
          break;
        }
        token_cat++;
      }
    }

    /* Check if entry is already present in table */
    if ( NULL != q_linear_search( &qmi_at_fwd_list.at_fwd_cmd_q,
                                  client_compare_fwd_at_cmd,
                                  (void *)&temp_fwd_at_cmd_name ) )
      {
        DS_AT_MSG_SPRINTF_1_ERROR("Command %s is already registered",temp_fwd_at_cmd_name);
        return FALSE;
      }
      

    /* Check if entry is duplicated in the fwd at cmd sent list */
    for(i=0; i<cmd_loop; i++)
    {
      if(!dsatutil_strcmp_ig_sp_case(
                                 (const byte *)at_cmd_list[i].cmd_buff,
                                 (const byte *)temp_fwd_at_cmd_name))
      {
       DS_ATCOP_ERROR_LOG_0("Duplicated entry provided in registration");
        return FALSE;
      }
    }
  } /* for(cmd_loop = 0 ... */
  
  return TRUE;
}/* client_validate_fwd_at_cmds */

/*===========================================================================

FUNCTION CLIENT_UPDATE_FWD_AT_CMDS

DESCRIPTION
  This function updates the internal tables with the forward AT command 
  registration from the client's command queue buffer.

DEPENDENCIES
  None
  
RETURN VALUE
  TRUE on successful operation
  FALSE otherwise.
  
SIDE EFFECTS
  None
  
===========================================================================*/
LOCAL boolean client_update_fwd_at_cmds 
(
  int32                              client_id,         /* Registered client */
  uint8                               num_valid_cmds,   /*no of commands     */
  const dsat_cmd_list_type            at_cmd_list[],    /*AT command list    */
  dsatclient_ext_at_cmd_exec_cb  ext_at_cmd_exec_cb,    /*Execution handler  */
  dsatclient_ext_at_cmd_abort_cb     ext_at_abort_cb,   /*Abort handler      */
  void                           *user_info_ptr         /*client info        */
)
{
  dsat_fwd_at_cmd_table_type *dsat_fwd_at_cmd_p;
  uint8 i =0;

  for( i=0; i<num_valid_cmds; i++ )
  {
    dsat_fwd_at_cmd_p = dsat_alloc_memory(sizeof(dsat_fwd_at_cmd_table_type), FALSE);
    memset(dsat_fwd_at_cmd_p, 0, sizeof(dsat_fwd_at_cmd_table_type));

    dsat_fwd_at_cmd_p->client_id = client_id;
    (void) dsatutil_memscpy((void*)dsat_fwd_at_cmd_p->cmd_name,
            MAX_CMD_SIZE,(void*)at_cmd_list[i].cmd_buff,
            MIN(MAX_CMD_SIZE,at_cmd_list[i].cmd_buff_len));
    dsat_fwd_at_cmd_p->cmd_name[at_cmd_list[i].cmd_buff_len]='\0';
    dsat_fwd_at_cmd_p->is_abortable = at_cmd_list[i].is_abortable;
    dsat_fwd_at_cmd_p->ext_at_cmd_exec_cb = ext_at_cmd_exec_cb;
    dsat_fwd_at_cmd_p->ext_at_abort_cb = ext_at_abort_cb;
    dsat_fwd_at_cmd_p->user_info_ptr = user_info_ptr;

    (void) q_link ( dsat_fwd_at_cmd_p, &dsat_fwd_at_cmd_p->link );
    q_put( &(qmi_at_fwd_list.at_fwd_cmd_q), &(dsat_fwd_at_cmd_p->link) );
    qmi_at_fwd_list.at_fwd_cmd_cnt++;
    
	DS_AT_MSG_SPRINTF_1_HIGH("AT forward command %s successfully registered",
				 dsat_fwd_at_cmd_p->cmd_name);
  }

  return TRUE;
}/* client_update_fwd_at_cmds */

/*===========================================================================

FUNCTION CLIENT_VALIDATE_FWD_CLIENT_ID

DESCRIPTION
  This function checks for valid client id.

DEPENDENCIES
  None
  
RETURN VALUE
  TRUE   -- When client-id given is a valid client id
  FALSE  -- client id is INVALID
  
SIDE EFFECTS
  None
  
===========================================================================*/
LOCAL boolean client_validate_fwd_client_id 
(
  int32                              client_id  /* client_id for validation */
)
{
  int i =0;

  /* Pre condition check */
  if(client_id == 0)
  {
    DS_ATCOP_ERROR_LOG_1("Invalid client id (=d)", client_id);
    return FALSE;
  }
  
  while(i < DSAT_MAX_CLIENT)
  {
    if(dsat_fwd_at_clients[i] == client_id)
    {
      DS_AT_MSG1_MED("ID already existing at index %d",i);
      return TRUE;
    }
    ++i;
  }
  
  DS_ATCOP_ERROR_LOG_1("Client id (%d) not found", client_id);
  return FALSE;
} /* client_validate_fwd_client_id */


/*===========================================================================

FUNCTION CLIENT_COMPARE_FWD_AT_CMDS

DESCRIPTION
  This function finds the AT command name in the forwarding AT
  commands list queue.

DEPENDENCIES
  None
  
RETURN VALUE
  TRUE on successful operation
  FALSE otherwise.
  
SIDE EFFECTS
  None
  
===========================================================================*/

static int client_compare_fwd_at_cmd
(
  void *cmd_ptr,
  void *cmd_name 
)
{
  dsat_fwd_at_cmd_table_type *dsat_fwd_at_cmd = (dsat_fwd_at_cmd_table_type *)cmd_ptr;

  if(!dsatutil_strcmp_ig_sp_case(
                              (const byte *)dsat_fwd_at_cmd->cmd_name,
                              (const byte *)cmd_name))
  {
    return TRUE;
  }

  return FALSE;

}

/*===========================================================================

FUNCTION DSATCLIENT_STATE_INFO_UPDATE

DESCRIPTION
  This function is called to update the state info values 
  that are exchanged between ATCOP and remote forwarded client.
  
DEPENDENCIES
  None 

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void dsatclient_state_info_update
(
  dsat_cmd_state_type * curr_state_ptr  /* State Info to update */
)
{

  memset((void*)curr_state_ptr, 0x0, 
          sizeof(dsat_cmd_state_type));

  curr_state_ptr->dsat_v_val = (dsat_num_item_type)dsatutil_get_val(
                                       DSAT_BASIC_V_IDX,0,0,NUM_TYPE);
  curr_state_ptr->dsat_q_val = (dsat_num_item_type)dsatutil_get_val(
                                       DSAT_BASIC_Q_IDX,0,0,NUM_TYPE);
  curr_state_ptr->dsat_s3_val = (dsat_num_item_type)dsatutil_get_val(
                                       DSAT_SREG_S3_IDX,0,0,NUM_TYPE);
  curr_state_ptr->dsat_s4_val = (dsat_num_item_type)dsatutil_get_val(
                                       DSAT_SREG_S4_IDX,0,0,NUM_TYPE);
 curr_state_ptr->dsat_max_arg_size = DSAT_MAX_ARG;
#ifdef FEATURE_DSAT_ETSI_MODE
  curr_state_ptr->dsat_clir_val = (dsat_num_item_type)dsatutil_get_val(
                                   DSATETSI_EXT_ACT_CLIR_ETSI_IDX,0,0,NUM_TYPE);
  curr_state_ptr->dsat_colp_val = (dsat_num_item_type)dsatutil_get_val(
                                   DSATETSI_EXT_ACT_COLP_ETSI_IDX,0,0,NUM_TYPE);
  curr_state_ptr->dsat_cmee_val = (dsat_num_item_type)dsatutil_get_val(
                                               DSAT_EXT_CMEE_IDX,0,0,NUM_TYPE);

  curr_state_ptr->dsat_cscs_val = (dsat_num_item_type)dsatutil_get_val(
                                               DSATETSI_EXT_CSCS_IDX,0,0,NUM_TYPE);

  (void) dsatutil_memscpy((void*)&curr_state_ptr->dsat_ccug_val[0],
          (3* (sizeof(dsat_num_item_type))),
          (void*)dsatutil_get_val(DSATETSI_EXT_ACT_CCUG_ETSI_IDX,0,0,STR_TYPE),
         (3* (sizeof(dsat_num_item_type))));

 (void) dsatutil_memscpy((void*)&curr_state_ptr->dsat_cmec_val[0],
         (3* (sizeof(dsat_num_item_type))),
         (void*)dsatutil_get_val(DSATETSI_EXT_ACT_CMEC_ETSI_IDX,0,0,STR_TYPE),
         (3* (sizeof(dsat_num_item_type))));
 /* CMEC 4th Param will be sent as an optional TLV from QMI so add it in a
    separate variable */
  curr_state_ptr->dsat_cmec_val_4 = (dsat_num_item_type)dsatutil_get_val(
                                   DSATETSI_EXT_ACT_CMEC_ETSI_IDX,0,3,NUM_TYPE);
#endif /* #ifdef FEATURE_DSAT_ETSI_MODE */

} /* dsatclient_state_info_update */

/*===========================================================================

FUNCTION DSATCLIENT_EXT_SEND_RESPONSE_EX

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
void
dsatclient_ext_send_response_ex
(
  boolean                                    cmd_status,   /* CMD status      */
  int32                                      client_id,    /* Client id       */
  dsat_client_result_enum_type               result_code,  /* result code     */
  dsat_fwd_resp_enum_type                    resp_type,    /* resp_type       */
  dsm_item_type                             *resp_buff_ptr,/* response buffer */
  uint32                                     atcop_info    /* Atcop Info      */
)
{
  DSAT_DL_LOCK();

  if (DSAT_DL_VALIDATE_SYMBOL_ADDR(dsatdl_vtable.dsatclient_ext_send_response_fp))
  {
    dsatdl_vtable.dsatclient_ext_send_response_fp(cmd_status, client_id, result_code,
                                                  resp_type, resp_buff_ptr, atcop_info);
  }
  else
  {
    dsm_free_packet(&resp_buff_ptr);
  }

  DSAT_DL_UNLOCK();

  return;
}/* dsatclient_ext_send_response_ex */

/*===========================================================================
FUNCTION DSATCLIENT_EXT_SEND_URC

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
dsatclient_ext_send_urc
(
  uint8                                    cmd_status,   /* CMD status      */
  int32                                      client_id,    /* Client id       */
  dsm_item_type                             *resp_buff_ptr/* response buffer */
)
{
  DSAT_DL_LOCK();

  if (DSAT_DL_VALIDATE_SYMBOL_ADDR(dsatdl_vtable.dsatclient_ext_send_urc_fp))
  {
    dsatdl_vtable.dsatclient_ext_send_urc_fp(cmd_status, client_id, resp_buff_ptr);
  }
  else
  {
    dsm_free_packet(&resp_buff_ptr);
  }

  DSAT_DL_UNLOCK();

  return;
}/* dsatclient_ext_send_urc */

/*===========================================================================

FUNCTION CLIENT_FWD_CMD_REQUEST

DESCRIPTION
  This function is used for forward command request.

DEPENDENCIES 
  AT forward demon up and running.

RETURN VALUE
  1 : Input prameter validation successful
  0 : Otherwise
  
SIDE EFFECTS
  None
  
===========================================================================*/
LOCAL boolean client_fwd_cmd_request
(
  ds_cmd_enum_type            cmd_id,         /* Command ID */
  dsat_cmd_status_cb_fn_type  status_func_cb, /* Status callback */
  void                       *user_info_ptr   /* Client data       */
)
{
  ds_cmd_type                  *cmd_ptr     = NULL;
  ds_at_fwd_cmd_request_s_type *fwd_req_cmd = NULL;

  if (FALSE == dsat_is_atcop_allowed())
  {
   DS_ATCOP_ERROR_LOG_0(" ATcop is not initialized");
    return FALSE;
  }

  /*-----------------------------------------------------------
     Post the command to DS task and return success to client
  ------------------------------------------------------------*/
  cmd_ptr = dsat_get_cmd_buf(sizeof(ds_at_fwd_cmd_request_s_type), FALSE);
  fwd_req_cmd = cmd_ptr->cmd_payload_ptr;

  cmd_ptr->hdr.cmd_id         = cmd_id;
  fwd_req_cmd->status_func_cb = status_func_cb;
  fwd_req_cmd->user_info_ptr  = user_info_ptr;

  ds_put_cmd(cmd_ptr);

  return TRUE;
} /* client_fwd_cmd_request */

/*===========================================================================
FUNCTION DSAT_RESET_CMD_FORWARDING

DESCRIPTION  
  Caller can call this API for phone reboot request.ATcop will check and honour this request.

PARAMETERS 

  status_func_cb  ATcop will intimate reboot status(success/failure) to caller  by calling this call back function.
  user_info_ptr    Contain user data.
  
DEPENDENCIES 
  AT forward demon up and running.

RETURN VALUE
  1 : Input prameter validation successful
  0 : Otherwise

SIDE EFFECTS  None
===========================================================================*/
boolean dsat_reset_cmd_forwarding
(
  dsat_cmd_status_cb_fn_type   status_func_cb,      /* Status callback */
  void                        *user_info_ptr        /* Client data       */
)
{
  return client_fwd_cmd_request(DS_CMD_ATCOP_RESET_REQ_CMD,
                                status_func_cb, user_info_ptr);
}/*dsat_reset_cmd_forwarding*/
/*===========================================================================
FUNCTION DSAT_SHUTDOWN_CMD_FORWARDING

DESCRIPTION  
  Caller can call this API for phone shutdown request.ATcop will check and honour this request.

PARAMETERS 

  status_func_cb  ATcop will intimate reboot status(success/failure) to caller by calling this call back function.
  user_info_ptr    Contain user data.
  
DEPENDENCIES 
  AT forward demon up and running.

RETURN VALUE
  1 : Input prameter validation successful
  0 : Otherwise

SIDE EFFECTS  None
===========================================================================*/
boolean dsat_shutdown_cmd_forwarding
(
  dsat_cmd_status_cb_fn_type   status_func_cb,      /* Status callback */
  void                        *user_info_ptr        /* Client data       */
)
{
  return client_fwd_cmd_request(DS_CMD_ATCOP_SHUTDOWN_REQ_CMD,
                                status_func_cb, user_info_ptr);
}

void dsat_reset_cmd (void)
{
  (void) client_fwd_cmd_request(DS_CMD_ATCOP_RESET_REQ_CMD, NULL, NULL);
}

void dsat_shutdown_cmd(void)
{
  (void) client_fwd_cmd_request(DS_CMD_ATCOP_SHUTDOWN_REQ_CMD, NULL, NULL);
}

/*===========================================================================
FUNCTION DSAT_PARSE_ALLOWED_LIST_EFS()

DESCRIPTION  
    Parse the contents of EFS File and store it in Allowed List of AT cmds 
    based on EFS.  

PARAMETERS 
  buffer - Contents read from the EFS File containg the list of AT cmds 
           in a fixed format
  
DEPENDENCIES 
  Should be called only when the EFS file is present 

RETURN VALUE
  TRUE : On Success

SIDE EFFECTS
  NONE
===========================================================================*/

boolean dsat_parse_allowed_list_efs(char * buffer)
{
  uint8 index,i;
  uint8 num_cmds = allowed_list_efs_info.num_at_cmds;
  char** cmd_list;
  char* c_ptr=buffer;
  char temp_buffer[MAX_CMD_SIZE]= {'\0'};

  /* Allocate memory to fill allowed list of at cmds based on EFS */
  cmd_list = dsat_alloc_memory( sizeof(char*) * num_cmds , FALSE );

  for (index=0 ; index < num_cmds ; index++)
  {
    /* Allocate Memory for storing each AT command names */
    *(cmd_list+index) = dsat_alloc_memory(sizeof(char) * MAX_CMD_SIZE , FALSE);
    
    if ( index == num_cmds - 1 )
    {
      for (i=0; *c_ptr != '\r' && i < MAX_CMD_SIZE-1 && *c_ptr != '\0'; i++)
      {
        temp_buffer[i]=*c_ptr;
        c_ptr++;
      }
      strlcpy(*(cmd_list+index),temp_buffer,sizeof(char)*MAX_CMD_SIZE);
      memset( temp_buffer,0,sizeof(temp_buffer) );
 
    }
    else
    {
      for ( i=0; *c_ptr != ',' && i < MAX_CMD_SIZE-1 ; i++)
      {
        temp_buffer[i]= *c_ptr;
        c_ptr++;
      }
      strlcpy(*(cmd_list+index),temp_buffer,sizeof(char)*MAX_CMD_SIZE);
      memset( temp_buffer,0,sizeof(temp_buffer) );
      c_ptr++;
    }
  }
  allowed_list_efs_info.cmd_list_efs = cmd_list;

  return TRUE;
}

/*===========================================================================
FUNCTION DSAT_INIT_ALLOWED_LIST_EFS()

DESCRIPTION  
  Initializes allowed list of AT commands based on EFS file present

PARAMETERS 
  NONE
  
DEPENDENCIES 
  Allowed list based on EFS will be initialized only when EFS file is present.

RETURN VALUE
  NONE

SIDE EFFECTS  None
===========================================================================*/

void dsat_init_allowed_list_efs ()
{
  int fd;
  struct fs_stat status;
  char *buffer,*c_ptr;
  uint8 count=1;
  uint32 num_bytes,index;

  if( (efs_stat(FWD_AT_CMD_LIST_PATH,&status) != -1) &&
     (status.st_size != 0) )
  {
    fd = efs_open( FWD_AT_CMD_LIST_PATH, O_RDONLY | O_TRUNC, S_IRUSR | S_IWUSR);
  
    if (fd < 0)
    {
      DS_ATCOP_ERROR_LOG_1("efs_open failed: error code - =d", efs_errno);
      allowed_list_efs_info.is_available = FALSE;
    }
    else
    {
      /* Read the contents of the file and store it in a local buffer */
      buffer = dsat_alloc_memory(status.st_size , FALSE);

      num_bytes = efs_read(fd, buffer, status.st_size);

      /* Close the EFS file opened earlier */
      efs_close(fd);

      /* Calculate the no. of commands present in the file separated by comma */

      for ( index=0,c_ptr=buffer;*c_ptr != '\r' && index < num_bytes ;index++)
      {
        if(*c_ptr == ',')
        {
          count++;
        }
        c_ptr++;
      }

      /* Update the info for the number of at commands in the EFS file */
      allowed_list_efs_info.num_at_cmds = count;

      /* Parse the buffer read and store the commands in a dynamic 2D array */
      if ( dsat_parse_allowed_list_efs(buffer) == TRUE)
      {
        allowed_list_efs_info.is_available = TRUE;
      }
      else 
      {
        allowed_list_efs_info.is_available = FALSE;
      }

     /* Buffer read from the file is used now , so free it . */
     dsatutil_free_memory(buffer);
    }
  }
  else
  {
    allowed_list_efs_info.is_available = FALSE;
  }
  
}

/*===========================================================================
FUNCTION DSAT_DEINIT_ALLOWED_LIST_EFS()

DESCRIPTION  
  Deinitializes the allowed list of AT Commands based on EFS.

PARAMETERS 
  NONE
  
DEPENDENCIES 
  Allowed list based on EFS initialized during boot up.

RETURN VALUE
  NONE

SIDE EFFECTS  None
===========================================================================*/

void dsat_deinit_allowed_list_efs()
{
  uint8 index;
  uint8 num_cmd;
  char** cmd_list;

  /* Deinit only when info is available from the EFS file */
  if ( allowed_list_efs_info.is_available == TRUE )
  {
    num_cmd=allowed_list_efs_info.num_at_cmds;
    cmd_list =allowed_list_efs_info.cmd_list_efs;

    for (index=0;index<num_cmd; index++)
    {
      dsatutil_free_memory(*(cmd_list+index));
    }
    dsatutil_free_memory(cmd_list);
  }
}
