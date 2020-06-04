/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                        D A T A   S E R V I C E S
                A T   C O M M A N D   P R O C E S S O R

      M U L T I M O D E   T A R G E T   C O M M A N D   T A B L E S

GENERAL DESCRIPTION
  This module contains the top level command tables for the multimode
  target.  It also contains any target specific command tables required
  to support target specific support of AT modem commands.

EXTERNALIZED FUNCTIONS
  None
    
INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

  Copyright (c) 2005 - 2017,2019 by Qualcomm Technologies, Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/


/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $PVCSPath$
  $Header: //commercial/MPSS.HI.1.0.c8/Main/modem_proc/datamodem_r/interface/atcop/src/dsatmmtgt.c#1 $


when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/16/19   ya      Remove IMS dependency on ATCOP
12/15/17   skc     Added enhancement on supplementary service for IP Call.
10/30/17   rk      Removed DS Flag FEATURE_DSAT_EXT_CLIENT_SUPPORT.
08/01/17   skc     Made changes to handle CHLD and CLCC for SRVCCed MPTY Call.
07/21/17   ss      Added support for eMBMS AT commands
10/08/16   skc     Added enhancement on CHLD and CLCC for VoLTE MPTY Call.
01/30/15   tk      Feature wrapped $QCVOIPM command with FEATURE_IMS.
11/18/14   tk      ATCoP changes for dynamic memory optimizations.
06/27/14   tk/sc   Added support for Dynamic ATCoP.
12/30/13   sc      Fixed static code bugs.
07/02/13   pg      Migrated to MMGSDI API to find PLMN info in SE13 table
08/22/12   sk      Mainlining Nikel Changes.
07/31/12   sk      C-EONS Feature Support.
02/17/11   ua      Added support for $QCRMCALL.
02/17/12   sk      Migrating Data related AT commands interface to unified MH.
01/19/12   sk      Feature cleanup.
10/20/11   nc      Added support for CUAD/CEAP/CERP commands.
04/20/11   ad      Fixed NIKEL featurization issue. 
04/20/11   bs      NIKEL Phase I support.
03/16/11   bs      Restructured command tables to be mode independant.
07/08/10   ad      Added support for $ECALL command.
06/04/10   bs      MMGSDI SESSION Migration.
05/10/10   kk      Added support for $QCVOLT, $QCHWREV, $QCBOOTVER, $QCTEMP, 
                   $QCAGC, $QCALLUP.
01/06/10   bs      Added +CGACT command support for LTE.
11/16/09   ca      Added support for MMGSDI Auth commands.
12/15/09   nc      Featurisation changes for LTE.
04/20/09   bs/sa   Added support for Modem Bridge Architecture.
09/09/09   ua      Added support for EONS (spec 22.101).
12/29/08   nc      Added support for +VTS Command
11/28/08   cs      Off-Target build Compiler and Lint warning fixes.
10/23/08   bs      Added support for 1X AT Phonebook commands.
07/21/08   bs      Added support for CDMA NAARefresh.
07/16/08   ua      Added support for external client support.
06/30/08   bs      Fixing Featurization issues.
06/13/08   ua      Correcting reading of data from RUIM/NV items
                   for OMH 2.
02/18/08   sa      Added modification for Passport Feature support.
09/07/07   sa      Corrected feature wrapping for dsat707_hdr_table
                   and updated vendor tables.
08/30/07   sa      Updated for CDMA and GSM(WCDMA) enabled targets.
04/28/05   snb     Initial version, after dsatmsm6300tgt.c

===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "datamodem_variation.h"
#include "comdef.h"
#include "customer.h"


#include "dsati.h"
#include "dsatclienti.h"
#include "dsatctab.h"
#ifdef FEATURE_DATA_IS707
#include "dsat707extctab.h"
#include "dsat707vend.h"
#ifdef FEATURE_HDR
#include "dsat707hdrctab.h"
#endif
#ifdef FEATURE_DS_MOBILE_IP
#include "dsat707mipctab.h"
#endif
#include "dsat707vendctab.h"
#endif /* FEATURE_DATA_IS707 */
#ifdef FEATURE_DSAT_ETSI_MODE
#include "dsatetsictab.h"
#include "dsatetsicmif.h"
#include "dsatetsime.h"
#include "dsatetsicall.h"
#endif /* FEATURE_DSAT_ETSI_MODE */
#if defined(FEATURE_ETSI_SMS) || defined(FEATURE_CDMA_SMS)
#include "dsatsms.h"
#endif /* defined(FEATURE_ETSI_SMS) || defined(FEATURE_CDMA_SMS) */


#ifdef FEATURE_CDMA_SMS
#include "dsat707smsctab.h"
#endif /* FEATURE_ETSI_SMS */

#ifdef FEATURE_DATA_GCSD_FAX
#include "dsatgsmfax.h"
#endif  /* FEATURE_DATA_GCSD_FAX */

#include "dsatvoice.h"
#include "dsatcmif.h"
#include "dsatme.h"
#include "dsatvend.h"
#include "dsatact.h"
/*===========================================================================

                    REGIONAL DEFINITIONS AND DECLARATIONS

===========================================================================*/



/*===========================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

  This section contains local definitions for constants, macros, types,
  variables and other items needed by this module.

===========================================================================*/

/*---------------------------------------------------------------------------
                           Defaults and limits
---------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------
						   ASKEY Command Tables 
--------------------------------------------------------------------------*/

#ifdef ASKEY_PROPRIETARY_ATCMD

extern const dsati_cmd_ex_type dsat_askey_basic_at_table_ex[ ];

/*--------------------------------------------------------------------------
                       Askey Proprietary Command Tables 
--------------------------------------------------------------------------*/
LOCAL dsati_at_cmd_table_ex_entry_type askey_table_entries_ex[ ] =
{
  { dsat_askey_basic_at_table_ex},
};

#endif /* ASKEY_PROPRIETARY_ATCMD */

// philip, 20190313, Add askey extended and vendor types of AT cmd table
#if defined(ASKEY_PROPRIETARY_ATCMD) || defined(ASKEY_EXT_VENDOR_ATCMD)
extern const dsati_cmd_ex_type dsat_askey_ext_table_ex[ ];
extern const dsati_cmd_ex_type dsat_askey_vendor_table_ex[ ];
#endif /* ASKEY_PROPRIETARY_ATCMD || ASKEY_EXT_VENDOR_ATCMD */

/*--------------------------------------------------------------------------
                       Common Command Tables 
--------------------------------------------------------------------------*/

LOCAL dsati_at_cmd_table_ex_entry_type basic_table_entries_ex[ ] =
{
  { dsat_basic_table_ex },
  { dsat_basic_action_table_ex }
};

LOCAL dsati_at_cmd_table_ex_entry_type sreg_table_entries_ex[ ] =
{
  {dsat_sreg_table_ex }
};

/*--------------------------------------------------------------------------
                       Target Specific Command Tables 
--------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
                      Top Level Command Tables - GSM
---------------------------------------------------------------------------*/

LOCAL dsati_at_cmd_table_ex_entry_type extended_table_entries_ex[ ] =
{
  {dsat_ext_table_ex},

#ifdef FEATURE_DSAT_ETSI_MODE
  {dsatetsi_ext_table_ex} ,  
  {dsatetsi_ext_action_table_ex} ,
#endif /* FEATURE_DSAT_ETSI_MODE */

#ifdef FEATURE_DATA_IS707
  {dsat707_ext_para_table_ex} ,
  {dsat707_ext_action_table_ex} ,
#endif /* FEATURE_DATA_IS707 */

// philip, 20190313, Add askey extended and vendor types of AT cmd table
#if defined(ASKEY_PROPRIETARY_ATCMD) || defined(ASKEY_EXT_VENDOR_ATCMD)
  {dsat_askey_ext_table_ex}
#endif /* ASKEY_PROPRIETARY_ATCMD || ASKEY_EXT_VENDOR_ATCMD */
};

LOCAL dsati_at_cmd_table_ex_entry_type vendor_table_entries_ex[ ] =
{
  {dsat_vendor_table_ex},
#ifdef FEATURE_DATA_IS707
  {dsat707_vend_para_table_ex},
  {dsat707_vend_action_table_ex},
  {dsat707_hdr_table_ex},
#ifdef FEATURE_DS_MOBILE_IP
  {dsat707_mip_table_ex},
#endif /* FEATURE_DS_MOBILE_IP */
#ifdef FEATURE_CDMA_SMS
  {dsat707_sms_table_ex},
#endif /* FEATURE_CDMA_SMS */
#endif /* FEATURE_DATA_IS707 */

// philip, 20190313, Add askey extended and vendor types of AT cmd table
#if defined(ASKEY_PROPRIETARY_ATCMD) || defined(ASKEY_EXT_VENDOR_ATCMD)
  {dsat_askey_vendor_table_ex}
#endif /* ASKEY_PROPRIETARY_ATCMD || ASKEY_EXT_VENDOR_ATCMD */
};
/*---------------------------------------------------------------------------
                      Top Level Command Tables - 1X
---------------------------------------------------------------------------*/

const dsati_at_cmd_table_ex_type at_cmd_table_ex =
  { basic_table_entries_ex,
    sreg_table_entries_ex, 
    extended_table_entries_ex,
    vendor_table_entries_ex
	// philip, 2018/07/31
#ifdef ASKEY_PROPRIETARY_ATCMD
    ,askey_table_entries_ex
#endif /* ASKEY_PROPRIETARY_ATCMD */
  };
/*---------------------------------------------------------------------------
                      Asynchronous Event Handler Table
---------------------------------------------------------------------------*/

const dsati_async_event_table_entry_type async_event_table_entries[] =
{
  { DS_CMD_ATCOP_STATUS_CMD,       dsatme_cmd_status_handler_ex},
#ifdef FEATURE_DATA_GCSD_FAX
  { DS_CMD_ATCOP_FPS_T31_CMD_STATUS, dsatgsmfax_fps_t31_status_handler },
#endif  /* FEATURE_DATA_GCSD_FAX */

  { DS_CMD_ATCOP_CM_CALL_CMD,        dsatcmif_cm_call_cmd_handler_ex },
  { DS_CMD_ATCOP_CM_CALL_INFO_CMD,   dsatcmif_cm_call_event_handler_ex },
  { DS_CMD_ATCOP_CM_SS_CMD,          dsatcmif_cm_ss_cmd_handler },
  { DS_CMD_ATCOP_CM_PH_CMD,          dsatcmif_cm_ph_cmd_handler_ex },
  { DS_CMD_ATCOP_CM_PH_INFO_CMD,     dsatcmif_cm_ph_event_handler_ex },

  { DS_CMD_ATCOP_TIMER_EXPIRED_CMD,  dsatutil_dispatch_timer_handler },

#ifdef FEATURE_DSAT_ETSI_MODE
  { DS_CMD_ATCOP_CM_INBAND_CMD,       dsatcmif_cm_inband_cmd_handler },
  { DS_CMD_ATCOP_CM_INBAND_INFO_CMD,  dsatcmif_cm_inband_event_handler },
#endif /* FEATURE_DSAT_ETSI_MODE */

#ifdef FEATURE_MMGSDI
  { DS_CMD_ATCOP_MMGSDI_INFO_CMD,    dsatme_mmgsdi_event_handler },
  { DS_CMD_ATCOP_MMGSDI_SIM_INFO,    dsatme_mmgsdi_sim_event_handler_ex },
  { DS_CMD_ATCOP_COPS_AT_CMD,        dsatetsicall_cops_mmgsdi_handler},
  { DS_CMD_ATCOP_CPOL_AT_CMD,        dsatetsime_cpol_mmgsdi_handler},

#endif /* FEATURE_MMGSDI */

#ifdef FEATURE_DSAT_ETSI_MODE
  { DS_CMD_ATCOP_MMGSDI_APDU_RESP,     dsatetsime_mmgsdi_send_apdu_handler },
  { DS_CMD_ATCOP_MMGSDI_CRSM_RESP,     dsatetsime_mmgsdi_crsm_handler      },

#endif /* FEATURE_DSAT_ETSI_MODE */

#if defined(FEATURE_ETSI_PBM) || defined(FEATURE_DSAT_CDMA_PBM)
  { DS_CMD_ATCOP_PBM_CB_CMD,         dsatme_pbm_cb_cmd_handler },
#endif /* defined(FEATURE_ETSI_PBM) || defined(FEATURE_DSAT_CDMA_PBM) */
  { DS_CMD_ATCOP_TO_SIO_LOW_CMD,     dsati_to_sio_low_cmd_handler },
#ifdef FEATURE_DSAT_ETSI_MODE
  { DS_CMD_ATCOP_CM_SUPS_CMD,        dsatetsicmif_cm_sups_cmd_handler_ex },
  { DS_CMD_ATCOP_CM_SUPS_INFO_CMD,   dsatetsicmif_cm_sups_event_handler_ex },
#endif /* FEATURE_DSAT_ETSI_MODE */
#if defined(FEATURE_ETSI_SMS) || defined(FEATURE_CDMA_SMS)
  { DS_CMD_ATCOP_SMS_ERR_CMD,   dsatsms_err_handler },
  { DS_CMD_ATCOP_SMS_ABT_CMD,   dsatsms_abt_handler },
#endif /* defined(FEATURE_ETSI_SMS) || defined(FEATURE_CDMA_SMS) */



  { DS_CMD_ATCOP_SEND_AT_CMD,        dsatclient_send_at_cmd_handler },

  { DS_CMD_ATCOP_FWD_CLIENT_REG,    dsatclient_register_fwd_client_handler },
  { DS_CMD_ATCOP_FWD_CLIENT_DEREG,  dsatclient_deregister_fwd_client_handler },
  { DS_CMD_ATCOP_FWD_AT_CMD_REG,    dsatclient_register_fwd_at_cmd_handler },
  { DS_CMD_ATCOP_FWD_AT_CMD_DEREG,  dsatclient_deregister_fwd_at_cmd_handler },
  { DS_CMD_ATCOP_EXT_CMD_RESP,      dsatclient_ext_at_resp_handler },
  { DS_CMD_ATCOP_RESETD_REQ_CMD,    dsatclient_resetd_cmd_request_handler},
  { DS_CMD_ATCOP_SHUTDOWN_REQ_CMD,  dsatclient_shutdown_cmd_request_handler},
  { DS_CMD_ATCOP_EXT_CMD_URC,       dsatclient_ext_at_urc_handler},
#ifdef FEATURE_ECALL_APP 
  { DS_CMD_ATCOP_ECALL_CMD,         dsatvend_ecall_at_cmd_handler },
#endif /* FEATURE_ECALL_APP */

  { DS_CMD_ATCOP_PDP_CMD,       dsatetsipkt_at_cmd_handler },

#ifdef FEATURE_MMGSDI
    { DS_CMD_ATCOP_MMGSDI_INIT_INFO    ,  dsat_mmgsdi_init_handler },                                   
    { DS_CMD_ATCOP_MMGSDI_OPER_NAME_INFO, dsat_mmgsdi_get_operator_name_handler},
#endif /* FEATURE_MMGSDI */
    { DS_CMD_ATCOP_RMNET_EV_CMD, dsatvend_rmnet_ev_handler },
#ifdef FEATURE_DATA_PS_EAP
    { DS_CMD_ATCOP_EAP_SIM_AKA_TASK_SWITCH_CMD   , dsatetsime_eap_task_sw_handler },
    { DS_CMD_ATCOP_EAP_SIM_AKA_RESULT_IND_CMD , dsatetsime_eap_result_ind_handler },
    { DS_CMD_ATCOP_EAP_SIM_AKA_SUPP_RESULT_IND_CMD, dsatetsime_eap_supp_result_ind_handler },
    { DS_CMD_ATCOP_EAP_SIM_AKA_TRP_TX_CMD, dsatetsime_eap_trp_tx_handler },
#endif /* FEATURE_DATA_PS_EAP */

#ifdef FEATURE_DATA_MUX
    #error code not present
#endif /* FEATURE_DATA_MUX */

#ifdef FEATURE_DSAT_LTE 
#if defined(FEATURE_VOIP) && defined(FEATURE_IMS)
  { DS_CMD_ATCOP_VOIPM_AT_CMD,         dsatvend_voipm_config_handler },
#endif /* defined(FEATURE_VOIP) && defined(FEATURE_IMS) */
#endif /* FEATURE_DSAT_LTE */
  { DS_CMD_ATCOP_VOICE_CONF_PARTICIPANTS_IND_CMD,  dsatetsicmif_voice_conf_participant_handler},
  { DS_CMD_ATCOP_SRVCC_HO_COMPLETE_IND,            dsatetsicmif_srvcc_ho_comp_handler},
  { DS_CMD_ATCOP_IMS_SRV_STATUS_IND,               dsatvend_ims_srv_status_handler },
  { DS_CMD_ATCOP_EMBMS_AVAIL_TMGI_LIST    , dsatetsipkt_embms_avail_tmgi_list_handler},
  { DS_CMD_ATCOP_EMBMS_INTEREST_TMGI_LIST , dsatetsipkt_embms_interest_tmgi_handler},
  { DS_CMD_ATCOP_EMBMS_SAI_LIST_UPDATE    , dsatetsipkt_embms_sai_list_handler },
  { DS_CMD_ATCOP_EMBMS_ACTIVE_TMGI_LIST   , dsatetsipkt_embms_active_tmgi_list_handler },
  { DS_CMD_ATCOP_EMBMS_TMGI_DEACT_CNF     , dsatetsipkt_embms_deactivate_tmgi_cnf_handler },
  { DS_CMD_ATCOP_EMBMS_TMGI_ACT_CNF       , dsatetsipkt_embms_activate_tmgi_cnf_handler },

  /* need this here to appease the compiler when none of the
     above features is defined,
     DS_AT_ASYNC_EVENT_END should never be used for a real 
     event, ERR will be thrown if it is used */
  { DS_CMD_ATCOP_ASYNC_EVENT_END,    NULL }
};

const dsati_async_event_table_type async_event_table =
{
  async_event_table_entries, ARR_SIZE(async_event_table_entries)
};
