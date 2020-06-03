/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                D A T A   S E R V I C E S

                A T   C O M M A N D   
                
                P R O C E S S I N G

GENERAL DESCRIPTION
   This module executes the AT commands. It mainly executes the ASKEY common commands.

EXTERNALIZED FUNCTIONS

EXTERNALIZED FUNCTIONS INTERNAL TO DSAT UNIT
  dsat_askey_lab_test_cfg_cmd

INITIALIZATION AND SEQUENCING REQUIREMENTS

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/


/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/30/18   philip  Created file. ASKEY_PROPRIETARY_ATCMD

===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "datamodem_variation.h"
#include "comdef.h"
#include "customer.h"

#include <stringl/stringl.h>


#if defined(T_WINNT)
#error code not present
#endif /* WINNT */

#include "dsati.h"
#include "dsatcmif.h"

#include "dsataskeytab.h"
#include <unistd.h>

#include<cmapi.h>

#include "dsataskeydata.h"
#include "nv_items.h"
#include "dcc_task_svc.h"

#include "dsatparm.h"


//#include "qmi_nas_utils.h"

#ifndef DWORD_HI
  #define DWORD_HI(x) ((unsigned int)((x>>8)&0xFFFF))
#endif

#ifndef DWORD_LO
  #define DWORD_LO(x) ((unsigned int)(x&0xFFFF))
#endif

//+philip, 2018/07/30, allow multiple times programming for OTP NV items
#ifdef ASKEY_LAB_TEST_OTP
extern unsigned long askey_lab_test_cfg;


/*===========================================================================

FUNCTION DSATASKEY_EXEC_LAB_TEST_CFG_CMD

DESCRIPTION


DEPENDENCIES
  None

RETURN VALUE


SIDE EFFECTS
  None

===========================================================================*/
/* ARGSUSED */
dsat_result_enum_type dsataskey_exec_lab_test_cfg_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
)
{
  dsat_result_enum_type     result = DSAT_OK;

  DS_AT_MSG1_MED("lab test = 0x%08XL", askey_lab_test_cfg);

  /* AT WRITE COMMAND SYNTAX */
  if(tok_ptr->op == (NA|EQ|AR))
  {
    if(tok_ptr->args_found == 1)
    {
      askey_lab_test_cfg = atol((const char *) tok_ptr->arg[0]);
    }
    else
    {
      return DSAT_ERROR;
    }
  }
  /* AT TEST COMMAND SYNTAX */
  else if (tok_ptr->op == (NA|EQ|QU))
  {
    /* Do nothing */
  }
  /* AT READ COMMAND SYNTAX */
  else if (tok_ptr->op == (NA|QU))
  {
    /* get the current value */
    res_buff_ptr->used = (word)snprintf( (char *)res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "@ASKEY_LAB_TEST_CFG: 0x%04X%04X",
                                           DWORD_HI(askey_lab_test_cfg),
                                           DWORD_LO(askey_lab_test_cfg) );
  }
  else
  {
    return DSAT_ERROR;
  }

  return result;
} /* dsataskey_exec_lab_test_cfg_cmd */
#endif /* ASKEY_LAB_TEST_OTP */


#ifdef ASKEY_PCI_LOCK
 /* Askey, 2020/02/20,PGTEL-1963 - Celllock - modified AT command from pci_lock efs to cell_restrict_params efs  { */
dsat_result_enum_type dsataskey_exec_pcilock_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
)
{
  dsat_result_enum_type     result = DSAT_OK;
  const char cell_lock_params_name[] = "/nv/item_files/modem/lte/rrc/efs/cell_restrict_opt_params";
  uint32 dl_earfcn = 0;
  uint16 pci = 0;
  int cell_lock_len = 36;
  byte cell_lock_param[cell_lock_len];
  
  DS_AT_MSG0_LOW("@ASKEY_PCILOCK");
  
  /* AT WRITE COMMAND SYNTAX */
  if(tok_ptr->op == (NA|EQ|AR))
  {
	DS_AT_MSG1_LOW("@ASKEY_PCILOCK, arg num = %d", tok_ptr->args_found);
	
    if(tok_ptr->args_found == 2)
    {
	  // Disable PCI lock, delete pci_lock EFS
	  if((strcmp((const char *)tok_ptr->arg[0], (const char *)"null") == 0 || strcmp((const char *)tok_ptr->arg[0], (const char *)"NULL") == 0 || strcmp((const char *)tok_ptr->arg[0], (const char *)"Null") == 0 )||
         (strcmp((const char *)tok_ptr->arg[1], (const char *)"null") == 0 || strcmp((const char *)tok_ptr->arg[1], (const char *)"NULL") == 0 || strcmp((const char *)tok_ptr->arg[1], (const char *)"Null") == 0 ))
      {
	    int err =0;
	    struct fs_stat stat = {0};
	    err = efs_stat (cell_lock_params_name, &stat);
	    DS_AT_MSG2_HIGH("efs_stat() return %d, efs_errno=%d", err, efs_errno);
	  
	    if( err==0 )	// pci_lock exists
	    {
		  DS_AT_MSG0_HIGH("@ASKEY_TEST, pci_lock exist, delete it!");
		  err = efs_unlink(cell_lock_params_name);
	      DS_AT_MSG2_HIGH("efs_unlink() return %d, efs_errno=%d", err, efs_errno);
	    }
		return result;
      }

	  // Set PCI lock
	  dl_earfcn = (uint32) atoi((const char *) tok_ptr->arg[0]);
           pci = (uint16) atoi((const char *) tok_ptr->arg[1]);
	  DS_AT_MSG2_LOW("@ASKEY_PCILOCK, earfcn = %d, pci = %d", dl_earfcn, pci);
	//Enable Default Cell_lock_params
	  cell_lock_param[0] = 0; //mobility _with_cell_lock (1 byes)
	  cell_lock_param[1] = 0;//Reserved bytes (7 bytes)
	  cell_lock_param[2] = 0;
	  cell_lock_param[3] = 0;
	  cell_lock_param[4] = 0;
	  cell_lock_param[5] = 0;
	  cell_lock_param[6] = 0;
	  cell_lock_param[7] = 0;
	  cell_lock_param[8] = 0x05;//short cell barring timer (4 bytes)
	  cell_lock_param[9] = 0;
	  cell_lock_param[10] =  0;
	  cell_lock_param[11] =  0;
	  cell_lock_param[12] =  0x1e; //reduce barring timer (4 bytes)
	  cell_lock_param[13] =  0;
	  cell_lock_param[14] =  0;
	  cell_lock_param[15] =  0;
	  cell_lock_param[16] =  0x5a;//backoff barring timers (4 bytes)
	  cell_lock_param[17] =  0;
	  cell_lock_param[18] =  0;
	  cell_lock_param[19] =  0;
	  cell_lock_param[20] =  dl_earfcn & 0x000000FF;//DL_earfcn (4 bytes)
	  cell_lock_param[21] =  (dl_earfcn >> 8) & 0x000000FF;
	  cell_lock_param[22] =  (dl_earfcn >> 16) & 0x000000FF;
	  cell_lock_param[23] =  (dl_earfcn >> 24) & 0x000000FF;
	  cell_lock_param[24] =  pci & 0x00FF;//PCI ID (2 bytes)
	  cell_lock_param[25] =  (pci>>8) & 0x00FF;
	  cell_lock_param[26] =  0;//Reserved (2 bytes)
	  cell_lock_param[27] =  0;
	  cell_lock_param[28] = 0; // lock earfcn1(4 bytes)
	  cell_lock_param[29] = 0;
	  cell_lock_param[30] = 0;
	  cell_lock_param[31] = 0;
	  cell_lock_param[32] = 0; // lock earfcn2( 4byters)
	  cell_lock_param[33] = 0;
	  cell_lock_param[34] = 0;
	  cell_lock_param[35] = 0;
	  
	  if(efs_put(cell_lock_params_name, (void*)&cell_lock_param, cell_lock_len, O_RDWR|O_CREAT|O_TRUNC|O_AUTODIR, 0777) == 0)
      {
        DS_AT_MSG0_HIGH("@ASKEY_PCILOCK, set pci lock success");
        result = DSAT_OK;       
      }
      else
      {
        DS_AT_MSG1_ERROR("Problem writing cell_lock_param to NV : %s",cell_lock_param);
        return DSAT_ERROR;
      }
	  
    }
    else
    {
	  DS_AT_MSG0_MED("@ASKEY_PCILOCK, arg error!!");
      return DSAT_ERROR;
    }
	
  }
  /* AT TEST COMMAND SYNTAX */
  else if (tok_ptr->op == (NA|EQ|QU))
  {
    /* Do nothing */
	res_buff_ptr->used = (word)snprintf( (char *)res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "@ASKEY_PCILOCK=<earfcn>,<pci>");
	
  }
  /* AT READ COMMAND SYNTAX */
  else if (tok_ptr->op == (NA|QU))
  {
	
	boolean pl_flag = FALSE;

	DS_AT_MSG0_HIGH("@ASKEY_PCILOCK, Read PCI lock");
	
	if (efs_get(cell_lock_params_name, (byte*)&cell_lock_param, cell_lock_len) > 0)
    {
      if(cell_lock_len <= 0)
      {
        DS_AT_MSG1_ERROR("pci_lock_file no data : %d",cell_lock_len);
        efs_deltree(cell_lock_params_name);
        res_buff_ptr->used += (word)snprintf( (char *)&res_buff_ptr->data_ptr[res_buff_ptr->used],
                               res_buff_ptr->size - res_buff_ptr->used, "disable");
        result = DSAT_OK;
      }
      else
      {
        pl_flag = TRUE;
      }
    }
    else
    {      
      DS_AT_MSG1_ERROR("No pci_lock_file exist : %d",cell_lock_len);
      res_buff_ptr->used += (word)snprintf( (char *)&res_buff_ptr->data_ptr[res_buff_ptr->used],
                               res_buff_ptr->size - res_buff_ptr->used, "disable");
      result = DSAT_OK;
    }

    if (pl_flag)
    {
      dl_earfcn = (cell_lock_param[23] << 24) + (cell_lock_param[22] << 16) + (cell_lock_param[21] << 8) + cell_lock_param[20];
      pci = (cell_lock_param[25] << 8) + (cell_lock_param[24]);

	  DS_AT_MSG2_HIGH("pci_lock from EFS. EARFCN: %d, PCI: %d", dl_earfcn, pci);
	  
	  res_buff_ptr->used = (word)snprintf( (char *)res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "pci_lock from EFS. EARFCN: %lu, PCI: %d", dl_earfcn, pci);
    }
  }
  else
  {
    return DSAT_ERROR;
  }

  return result;
}
 /* Askey, 2020/02/20,PGTEL-1963 - Celllock - modified AT command from pci_lock efs to cell_restrict_params efs  } */
#endif /* end #ifdef ASKEY_PCI_LOCK */



#ifdef ASKEY_AT_TEST
// Testing AT command
dsat_result_enum_type dsataskey_exec_test_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
)
{
  dsat_result_enum_type     result = DSAT_OK;
#if 0 	// jelly. sdx55 data structure has been modified, need to re-write.
  uint32 toLTE = 0;
  sys_modem_as_id_e_type subs_id = dsat_get_current_subs_id(FALSE);
  
  
  DS_AT_MSG0_LOW("@ASKEY_TEST");
  
  /* AT WRITE COMMAND SYNTAX */
  if(tok_ptr->op == (NA|EQ|AR)) 
  {
	DS_AT_MSG1_HIGH("@ASKEY_TEST, arg num = %d", tok_ptr->args_found);
	
    if(tok_ptr->args_found == 0)
    {
	  DS_AT_MSG0_HIGH("@ASKEY_TEST, arg error!! 1 = change mode, 2 = delete pci_lock");
      return DSAT_ERROR;
	}
	
	int cmd = atoi((const char *) tok_ptr->arg[0]);
	if( cmd == 0 && tok_ptr->args_found == 2)	// mode pref change
	{
	  DS_AT_MSG0_HIGH("@ASKEY_TEST, Change mode pref. 0: auto. 1: LTE");
	  
	  cm_cmd_user_pref_update_type pref_info = {0};
	  if( FALSE == cm_user_pref_init( &pref_info ) )
	  {
		DS_AT_MSG0_MED("@ASKEY_TEST, cm_user_pref_init() error");
	  }
	  
	  pref_info.asubs_id =  subs_id;
	  //pref_info.client_id = dsatcm_client_id;		// use default client .....
	  pref_info.client_id = CM_CLIENT_ID_ANONYMOUS;
	  pref_info.pref_term = CM_PREF_TERM_PERMANENT;
	  
	  toLTE = (uint32) atoi((const char *) tok_ptr->arg[1]);
	  if(toLTE == 0) 	// auto
	  {
		DS_AT_MSG0_HIGH("@ASKEY_TEST, set pref to AUTO");
		pref_info.mode_pref = CM_MODE_PREF_AUTOMATIC;
	  }
	  else	//LTE only
	  {
		DS_AT_MSG0_HIGH("@ASKEY_TEST, set pref to LTE");
		pref_info.mode_pref = CM_MODE_PREF_LTE_ONLY;
	  }
	  
	  //if(FALSE == cm_user_pref_update_req(&pref_info, dsatcmif_ph_cmd_cb_func, NULL))
	  if(FALSE == cm_user_pref_update_req(&pref_info, NULL, NULL))
	  {
		//SET_PENDING(DSAT_ASKEY_ACT_SET_PERFERRED_BAND_IDX ,0, DSAT_PENDING_FALSE)
		DS_AT_MSG0_HIGH("@ASKEY_TEST, cm_user_pref_update_req() fail");
		result = DSAT_ERROR;
	  }
      else
	  {
		DS_AT_MSG0_HIGH("@ASKEY_TEST, cm_user_pref_update_req() success!!");
		result = DSAT_OK;
      }
	  
    }
	else if (cmd == 1)	// delete pci_lock
	{
	  DS_AT_MSG0_HIGH("@ASKEY_TEST, Going to delete efs file /nv/item_files/modem/lte/rrc/csp/pci_lock");
	  int err =0;
	  struct fs_stat stat = {0};
	  err = efs_stat ("/nv/item_files/modem/lte/rrc/csp/pci_lock", &stat);
	  DS_AT_MSG2_HIGH("efs_stat() return %d, efs_errno=%d", err, efs_errno);
	  
	  if( err==0 )	// pci_lock exists
	  {
		DS_AT_MSG0_HIGH("@ASKEY_TEST, pci_lock exist, delete it!");
		err = efs_unlink("/nv/item_files/modem/lte/rrc/csp/pci_lock");
	    DS_AT_MSG2_HIGH("efs_unlink() return %d, efs_errno=%d", err, efs_errno);
	  }
	}
	else if (cmd == 2 && tok_ptr->args_found==2)	// change modem operation mode
	{
	  DS_AT_MSG0_HIGH("@ASKEY_TEST, Modem change mode");
	  int op_mode = (int) atoi((const char *) tok_ptr->arg[1]);
	  
	  if(op_mode==0 )	// LPM
	  {
		int exe_result = dsatcmif_change_operating_mode(6);
		DS_AT_MSG1_HIGH("to LPM, result = %d", exe_result);
	  }
	  else				// Online mode 
	  {
	    int exe_result = dsatcmif_change_operating_mode(5);
		DS_AT_MSG1_HIGH("to Online, result = %d", exe_result);
	  }
	}
	else if (cmd == 3)	// check pci_lock whether exist or not.
	{
	  DS_AT_MSG0_HIGH("@ASKEY_TEST, Checking efs file /nv/item_files/modem/lte/rrc/csp/pci_lock");
	  int err =0;
	  struct fs_stat stat = {0};
	  err = efs_stat ("/nv/item_files/modem/lte/rrc/csp/pci_lock", &stat);
	  DS_AT_MSG2_HIGH("efs_stat() return %d, efs_errno=%d", err, efs_errno);
	  
	  if( err==0 )	// pci_lock exists
	  {
		DS_AT_MSG0_HIGH("@ASKEY_TEST, pci_lock exist!");
		res_buff_ptr->used = (word)snprintf( (char *)res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "pci_lock exists!!");
	  } else	// pci_lock not exists
	  {
		DS_AT_MSG0_HIGH("@ASKEY_TEST, pci_lock NOT exist!");
		res_buff_ptr->used = (word)snprintf( (char *)res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "pci_lock NOT exists!!");
	  }
	}
	else if (cmd == 4)	// Get PLMN info
	{
	  DS_AT_MSG0_HIGH("@ASKEY_TEST, GNWS");
	  
	}
	else if (cmd == 5)	// Put nv item
	{
	  DS_AT_MSG0_HIGH("@ASKEY_TEST, put nv item #409");

	  nv_item_type nv_data;
	  nv_stat_enum_type nv_status = 0;
	  memset((void*)&nv_data, 0, sizeof(nv_data));

	  byte value = (byte) atoi((const char *) tok_ptr->arg[1]);
	  DS_AT_MSG1_HIGH("set value = %d", value);

	  if(value!=100) {
		  nv_data.tty = value;
		  
		  nv_status = (nv_stat_enum_type) dcc_put_nv_item( NV_TTY_I, (nv_item_type *) &nv_data );

		  if ( nv_status != NV_DONE_S )
		  	DS_AT_MSG0_HIGH("nv#409, write fail");
		  else
		  	DS_AT_MSG0_HIGH("nv#409, write success!");
	  }
	  DS_AT_MSG0_HIGH("Done");

	  /*
	  res_buff_ptr->used = (word)snprintf( (char *)res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "net assign apn: %s", 
                                           net_assign_apn);
                                          */
	}
	else if(cmd==6)
	{
	  DS_AT_MSG0_HIGH("@ASKEY_TEST, get_sig_info()");
	  
	  int tech = (int) atoi((const char *) tok_ptr->arg[1]);
	  int sub_id = (int) atoi((const char *) tok_ptr->arg[2]);
	  cmapi_signal_info_s_type askey_signal_info;
	  //sys_modem_as_id_e_type askey_as_id = SYS_MODEM_AS_ID_1;
	  cmapi_err_e_type askey_cmapi_result = CMAPI_SUCCESS;

	  memset(&askey_signal_info, 0x0, sizeof(askey_signal_info));
	  askey_cmapi_result = cmapi_get_signal_info_ext(tech, 	// 4: LTE, 3: WCDMA
												   &askey_signal_info, (sys_modem_as_id_e_type)sub_id);

	  if(askey_cmapi_result == CMAPI_SUCCESS)
	  {
	    res_buff_ptr->used = (word)snprintf( (char *)res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "@signal info: LTE CQI[0]=%d, LTE CQI[1]=%d, LTE SINR is %d dB.", 
                                            askey_signal_info.wb_cqi_per_codeword[0],
                                            askey_signal_info.wb_cqi_per_codeword[1],
                                            askey_signal_info.log_sinr10xdb.value);

		DS_AT_MSG1_HIGH("<<jelly>> Technology = %d",askey_signal_info.sys_mode);
        DS_AT_MSG2_HIGH("<<jelly>> LTE CQI[0]=%d, CQI[1]=%d",askey_signal_info.wb_cqi_per_codeword[0],askey_signal_info.wb_cqi_per_codeword[1]);
	    DS_AT_MSG1_HIGH("<<jelly>> LTE SINR =%d dB",askey_signal_info.log_sinr10xdb.value);
		DS_AT_MSG2_HIGH("<<jelly>> WCDMA avg_cqi=%d, sample=%d",askey_signal_info.cqi_info.avg_cqi, askey_signal_info.cqi_info.avg_cqi_num_samples);
	  } else {
	    DS_AT_MSG1_HIGH("<<jelly>> Return error cause %d", askey_cmapi_result);
	  }
	}
    else
    {
	  DS_AT_MSG0_HIGH("@ASKEY_TEST, arg error!! 0: change Pref mode, 1: delete pci_lock, 2: change modem op_mode");
      return DSAT_ERROR;
    }
	
  }
  /* AT TEST COMMAND SYNTAX */
  else if (tok_ptr->op == (NA|EQ|QU))
  {
    /* Do nothing */
	/*
	res_buff_ptr->used = (word)snprintf( (char *)res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "@ASKEY_PCILOCK=<earfcn>,<pci>");
	*/
  }
  /* AT READ COMMAND SYNTAX */
  else if (tok_ptr->op == (NA|QU))
  {  
	/*
	DS_AT_MSG2_LOW("@ASKEY_PCILOCK, [FAKE] earfcn = %d, freq = %d", 200, 100);
	res_buff_ptr->used = (word)snprintf( (char *)res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "@ASKEY_PCILOCK: 0x%d%d",
                                           100,
                                           200 );									  
	*/									
  }
  else
  {
    return DSAT_ERROR;
  }
#endif 
  return result;
}
#endif /* ASKEY_AT_TEST */

#ifdef ASKEY_PREF_NET
dsat_result_enum_type dsataskey_exec_prefnet_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
)
{
  dsat_result_enum_type     result = DSAT_OK;

#if 0 	// jelly. sdx55 data structure has been modified, need to re-write this function.
  cm_cmd_user_pref_update_type sys_pref = {0};
  cm_mode_pref_e_type mode_pref = CM_MODE_PREF_LTE_ONLY;
  sys_modem_as_id_e_type subs_id = dsat_get_current_subs_id(FALSE);
  
  DS_AT_MSG0_HIGH("@ASKEY_PREFNET");
  
  /* AT WRITE COMMAND SYNTAX */
  if(tok_ptr->op == (NA|EQ|AR))
  {
    if(tok_ptr->args_found<1)
    {
    	DS_AT_MSG0_HIGH("argument error!");
		return DSAT_OK;
    }
	/*
	uint16 to_mode = atoi((const char *) tok_ptr->arg[0]);		//bit 3 (8): WCDMA only, bit 4 (16): LTE 

      if ( ! TARGET_SUPPORTS_CDMA  ) to_mode &= (mode_pref_mask_type_v01) ~QMI_NAS_RAT_MODE_PREF_CDMA2000_1X_V01;
      if ( ! TARGET_SUPPORTS_HDR   ) to_mode &= (mode_pref_mask_type_v01) ~QMI_NAS_RAT_MODE_PREF_CDMA2000_HRPD_V01;
      if ( ! TARGET_SUPPORTS_GSM   ) to_mode &= (mode_pref_mask_type_v01) ~QMI_NAS_RAT_MODE_PREF_GSM_V01;
      if ( ! TARGET_SUPPORTS_WCDMA ) to_mode &= (mode_pref_mask_type_v01) ~QMI_NAS_RAT_MODE_PREF_UMTS_V01;
      if ( ! TARGET_SUPPORTS_LTE   ) to_mode &= (mode_pref_mask_type_v01) ~QMI_NAS_RAT_MODE_PREF_LTE_V01;
      if ( ! TARGET_SUPPORTS_TDS   ) to_mode &= (mode_pref_mask_type_v01) ~QMI_NAS_RAT_MODE_PREF_TDSCDMA_V01;

      if ( to_mode == 0x0000 )
      {
        errval = QMI_ERR_OP_DEVICE_UNSUPPORTED_V01;
        return DSAT_ERROR;
      }
	
	mode_pref = qmi_nas_map_mode_pref_qmi_to_cm( to_mode );
	DS_AT_MSG1_HIGH("<<jelly>> mode_pref = %d\n", mode_pref);
	if (mode_pref == CM_MODE_PREF_NONE)
    {
	  DS_AT_MSG0_HIGH("Mode not support!");
	  return DSAT_ERROR;
    }

    
    */
    
	if ( !cm_user_pref_init( &sys_pref ) )
    {
      DS_AT_MSG0_HIGH("pref init fail");
      return DSAT_ERROR;
    }
    
    
	// LTE only: 38, WCDMA only: 14
    mode_pref = (cm_mode_pref_e_type) atoi((const char *) tok_ptr->arg[0]);
	//net_pref = (cm_network_sel_mode_pref_e_type) atoi((const char *) tok_ptr->arg[1]);

	//DS_AT_MSG2_HIGH("mode_pref=%d, net_pref=%d", mode_pref, net_pref);

	sys_pref.mode_pref = mode_pref;
	sys_pref.asubs_id =  subs_id;
    sys_pref.client_id = dsatcm_client_id;
    sys_pref.pref_term = CM_PREF_TERM_PERMANENT;
	sys_pref.voice_domain_pref = SYS_VOICE_DOMAIN_PREF_NO_CHANGE;

	SET_PENDING(DSAT_ASKEY_ACT_PREFNET_IDX ,0, DSAT_PENDING_TRUE)
    if(FALSE == cm_user_pref_update_req(&sys_pref, dsatcmif_ph_cmd_cb_func, NULL))
    {
       SET_PENDING(DSAT_ASKEY_ACT_PREFNET_IDX ,0, DSAT_PENDING_FALSE)
       result = DSAT_ERROR;
    }
    else
    {
      result = DSAT_ASYNC_CMD;
    }
	
  }
  /* AT TEST COMMAND SYNTAX */
  else if (tok_ptr->op == (NA|EQ|QU))
  {
    /* Do nothing */
	res_buff_ptr->used = (word)snprintf( (char *)res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "@ASKEY_PREFNET");
	
  }
  /* AT READ COMMAND SYNTAX */
  else if (tok_ptr->op == (NA|QU))
  {
	res_buff_ptr->used = (word)snprintf( (char *)res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "@ASKEY_PREFNET");

  }
  else
  {
    return DSAT_ERROR;
  }
#endif 

  return result;
	
}
#endif /* ASKEY_PREF_NET */

dsat_result_enum_type dsataskey_exec_makecall_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
)
{
    DS_AT_MSG0_HIGH("@ASKEY_MAKE_CALL");
    res_buff_ptr->used = (word)snprintf( (char *)res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "@ASKEY_MAKE_CALL");
	return DSAT_OK;
}


dsat_result_enum_type dsataskey_exec_fwd_test_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
)
{
    DS_AT_MSG0_HIGH("@ASKEY_FWD_TEST");
    res_buff_ptr->used = (word)snprintf( (char *)res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "@ASKEY_FWD_TEST");
	return DSAT_OK;
}

#if 0 
dsat_result_enum_type dsataskey_exec_roaming_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
)
{
  dsat_result_enum_type     result = DSAT_OK;
  cm_cmd_user_pref_update_type sys_pref = {0};
  cm_mode_pref_e_type mode_pref = CM_MODE_PREF_LTE_ONLY;
  sys_modem_as_id_e_type subs_id = dsat_get_current_subs_id(FALSE);
  
  DS_AT_MSG0_HIGH("@ASKEY_ROAMING");
  
  /* AT WRITE COMMAND SYNTAX */
  if(tok_ptr->op == (NA|EQ|AR))
  {
    if(tok_ptr->args_found<1)
    {
    	DS_AT_MSG0_HIGH("argument error!");
		return DSAT_OK;
    }
	/*
	uint16 to_mode = atoi((const char *) tok_ptr->arg[0]);		//bit 3 (8): WCDMA only, bit 4 (16): LTE 

      if ( ! TARGET_SUPPORTS_CDMA  ) to_mode &= (mode_pref_mask_type_v01) ~QMI_NAS_RAT_MODE_PREF_CDMA2000_1X_V01;
      if ( ! TARGET_SUPPORTS_HDR   ) to_mode &= (mode_pref_mask_type_v01) ~QMI_NAS_RAT_MODE_PREF_CDMA2000_HRPD_V01;
      if ( ! TARGET_SUPPORTS_GSM   ) to_mode &= (mode_pref_mask_type_v01) ~QMI_NAS_RAT_MODE_PREF_GSM_V01;
      if ( ! TARGET_SUPPORTS_WCDMA ) to_mode &= (mode_pref_mask_type_v01) ~QMI_NAS_RAT_MODE_PREF_UMTS_V01;
      if ( ! TARGET_SUPPORTS_LTE   ) to_mode &= (mode_pref_mask_type_v01) ~QMI_NAS_RAT_MODE_PREF_LTE_V01;
      if ( ! TARGET_SUPPORTS_TDS   ) to_mode &= (mode_pref_mask_type_v01) ~QMI_NAS_RAT_MODE_PREF_TDSCDMA_V01;

      if ( to_mode == 0x0000 )
      {
        errval = QMI_ERR_OP_DEVICE_UNSUPPORTED_V01;
        return DSAT_ERROR;
      }
	
	mode_pref = qmi_nas_map_mode_pref_qmi_to_cm( to_mode );
	DS_AT_MSG1_HIGH("<<jelly>> mode_pref = %d\n", mode_pref);
	if (mode_pref == CM_MODE_PREF_NONE)
    {
	  DS_AT_MSG0_HIGH("Mode not support!");
	  return DSAT_ERROR;
    }

    
    */
    
	if ( !cm_user_pref_init( &sys_pref ) )
    {
      DS_AT_MSG0_HIGH("pref init fail");
      return DSAT_ERROR;
    }
    
    
	// LTE only: 38, WCDMA only: 14
    mode_pref = (cm_mode_pref_e_type) atoi((const char *) tok_ptr->arg[0]);
	//net_pref = (cm_network_sel_mode_pref_e_type) atoi((const char *) tok_ptr->arg[1]);

	//DS_AT_MSG2_HIGH("mode_pref=%d, net_pref=%d", mode_pref, net_pref);

	sys_pref.mode_pref = mode_pref;
	sys_pref.asubs_id =  subs_id;
    sys_pref.client_id = dsatcm_client_id;
    sys_pref.pref_term = CM_PREF_TERM_PERMANENT;
	sys_pref.voice_domain_pref = SYS_VOICE_DOMAIN_PREF_NO_CHANGE;

	SET_PENDING(DSAT_ASKEY_ACT_PREFNET_IDX ,0, DSAT_PENDING_TRUE)
    if(FALSE == cm_user_pref_update_req(&sys_pref, dsatcmif_ph_cmd_cb_func, NULL))
    {
       SET_PENDING(DSAT_ASKEY_ACT_PREFNET_IDX ,0, DSAT_PENDING_FALSE)
       result = DSAT_ERROR;
    }
    else
    {
      result = DSAT_ASYNC_CMD;
    }
	
  }
  /* AT TEST COMMAND SYNTAX */
  else if (tok_ptr->op == (NA|EQ|QU))
  {
    /* Do nothing */
	res_buff_ptr->used = (word)snprintf( (char *)res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "@ASKEY_ROAMING");
	
  }
  /* AT READ COMMAND SYNTAX */
  else if (tok_ptr->op == (NA|QU))
  {
	res_buff_ptr->used = (word)snprintf( (char *)res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "@ASKEY_ROAMING");

  }
  else
  {
    return DSAT_ERROR;
  }

  return result;
	
}

#endif



// philip, 20180810, [Generic][TMO] Set preferred band
#ifdef ASKEY_SET_PREFERRED_BAND

/*===========================================================================

FUNCTION cm_print_lte_band_mask

DESCRIPTION
Print the LTE band mask.

DEPENDENCIES
None

RETURN VALUE
None

SIDE EFFECTS
none

===========================================================================*/
void dsat_print_lte_band_mask(
  sys_lte_band_mask_e_type lte_band_pref
)
{
#if (LTE_BAND_NUM == 256)
  DS_AT_MSG4_MED("LTE bands 193_256: 0x%08x %08x, 129_192: 0x%08x %08x",
               QWORD_HIGH(lte_band_pref.bits_193_256),
               QWORD_LOW(lte_band_pref.bits_193_256),
               QWORD_HIGH(lte_band_pref.bits_129_192),
               QWORD_LOW(lte_band_pref.bits_129_192));
  DS_AT_MSG4_MED("LTE bands  65_128: 0x%08x %08x,  1_64:   0x%08x %08x",
               QWORD_HIGH(lte_band_pref.bits_65_128),
               QWORD_LOW(lte_band_pref.bits_65_128),
               QWORD_HIGH(lte_band_pref.bits_1_64),
               QWORD_LOW(lte_band_pref.bits_1_64));
#else
  DS_AT_MSG2_MED("LTE bands    1_64: 0x%08x %08x", QWORD_HIGH(lte_band_pref),
               QWORD_LOW(lte_band_pref));
#endif
}

void cmph_get_mode_band_capability(

  sys_sys_mode_mask_e_type     *mode_capability,
  /* Mode capability supported by the current target */

  sys_band_mask_e_type         *band_capability,
  /* Band capability supported by the current target */

  sys_lte_band_mask_e_type     *lte_band_capability,
  /* LTE band capability supported by the current target */

  sys_band_mask_e_type         *tds_band_capability
  /* TD-SCDMA band capability supported by the current target */

);


#if 0	// jelly, 1209,2019 - data structure change, need to rewrite.
void cmph_get_comm_mode_band_capab_with_pm(

  sd_ss_mode_pref_e_type         *comm_mode,
  /* Mode capability supported by the current target */

  sd_ss_band_pref_e_type         *comm_band,
  /* Band capability supported by the current target */

  sys_lte_band_mask_e_type       *comm_lte_band,
  /* LTE band capability supported by the current target */

  sd_ss_band_pref_e_type         *comm_tds_band,
  /* TD-SCDMA band capability supported by the current target */

  sys_modem_as_id_e_type       as_id
  /* ASID for which the capabilties are required */

);
#endif 

/*===========================================================================
FUNCTION DSATASKEY_EXEC_PREFBAND_CMD

DESCRIPTION
  This function takes the result from the command line parser
  and executes it. It executes at@askey_prefband command.
  This command provides the ability to set/get the device band preferences. 

Command:
  AT@ASKEY_PREFBAND = <mode_term>, <pref_gw_band>, <pref_lte_band>


<mode_term> mode terms, values as follows:
  PERM: Permanent mode change.
  TEMP: Until a power cycle.

<pref_gw_band> UMTS band, values as follows:
1|2|4|5|8

<pref_lte_band> LTE band, values as follows:
2|4|5|7|12|66|71

DEPENDENCIES
  
RETURN VALUE
  returns an enum that describes the result of the command execution.
  possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_OK/DSAT_ASYNC_CMD : if success.
    
SIDE EFFECTS
  None
  
===========================================================================*/
/* ARGSUSED */
dsat_result_enum_type dsataskey_exec_prefband_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
)
{
#if 0
  dsat_result_enum_type result = DSAT_OK;
  cm_pref_chg_req_s_type user_pref;
  char *p_band_str;
  cm_band_pref_e_type lv_gw_band_pref;
  sys_lte_band_mask_e_type lv_lte_band_pref;
  dsat_error_info_s_type  err_info;
  sys_modem_as_id_e_type subs_id = dsat_get_current_subs_id(FALSE);
  
  err_info.errval = DSAT_ERR_NO_ERROR;
  err_info.arg_num = 0;

  if ( (NA|EQ|AR) == tok_ptr->op )
  {
    /* Verify the input parameter range  */
    if ( ( tok_ptr->args_found != 3 ) || ( !VALID_TOKEN(0) ) )
    {
      err_info.errval = DSAT_ERR_INVALID_NUM_OF_ARGS;
      goto send_error;
    }

    /* Initialize user_pref to defaults */
    memset(&user_pref, 0x0, sizeof(user_pref));
    if ( !cm_pref_change_req_init( &user_pref ) )
    {
      err_info.errval = DSAT_ERR_PARAMETER_OUT_OF_RANGE;
      goto send_error;
    }

    /* Convert GW band string to band mask */
	p_band_str = strtok((char *) tok_ptr->arg[1], "|");
	lv_gw_band_pref = SYS_BAND_MASK_EMPTY;

	while ( p_band_str != NULL )
	{
	  switch ( atol((const char *)p_band_str) )
	  {
	  case 1:
	  	lv_gw_band_pref |= CM_BAND_PREF_WCDMA_I_IMT_2000;
	  	break;
	  case 2:
	  	lv_gw_band_pref |= CM_BAND_PREF_WCDMA_II_PCS_1900;
	  	break;
	  case 4:
	  	lv_gw_band_pref |= CM_BAND_PREF_WCDMA_IV_1700;
	  	break;
	  case 5:
	  	lv_gw_band_pref |= CM_BAND_PREF_WCDMA_V_850;
	  	break;
	  case 8:
	  	lv_gw_band_pref |= CM_BAND_PREF_WCDMA_VIII_900;
	  	break;
	  default:
	  	DS_AT_MSG1_ERROR("Invalid band %s", p_band_str);
		err_info.errval = DSAT_ERR_PARAMETER_OUT_OF_RANGE;
        goto send_error;
	  }

	  p_band_str = strtok(NULL, "|");
	}


	DS_AT_MSG0_HIGH("<<jelly>> set user_pref.mode_band.bands.band");
	
    user_pref.mode_band.bands.band = lv_gw_band_pref;
    DS_AT_MSG2_HIGH("GW bands = 0x%08x %08x.",
                              QWORD_HIGH(lv_gw_band_pref),
                              QWORD_LOW(lv_gw_band_pref));

    /* Convert LTE band string to band mask */
	p_band_str = strtok((char *) tok_ptr->arg[2], "|");
	SYS_LTE_BAND_MASK_CLR_ALL_BANDS( &lv_lte_band_pref );
	while ( p_band_str != NULL )
	{
	  if (!SYS_LTE_BAND_MASK_ADD_BAND(&lv_lte_band_pref, (size_t) atol((const char *)p_band_str)-1))
	  {
	  	DS_AT_MSG1_ERROR("Invalid band %s", p_band_str);
		err_info.errval = DSAT_ERR_PARAMETER_OUT_OF_RANGE;
        goto send_error;
	  }
	  p_band_str = strtok(NULL, "|");
	}

	DS_AT_MSG0_HIGH("<<jelly>> set user_pref.mode_band.bands.lte_band");


	
    user_pref.mode_band.bands.lte_band = lv_lte_band_pref;
	dsat_print_lte_band_mask( lv_lte_band_pref );
	
    user_pref.asubs_id =  subs_id;
    user_pref.client_id = dsatcm_client_id;
    user_pref.pref_term = strcmp( "PERM", (const char*) tok_ptr->arg[0]) ? 
		CM_PREF_TERM_PWR_CYCLE : CM_PREF_TERM_PERMANENT;
    user_pref.network_sel_mode_pref = CM_NETWORK_SEL_MODE_PREF_NO_CHANGE;
    DS_AT_MSG1_HIGH("pref_term = %d.", user_pref.pref_term);

    SET_PENDING(DSAT_ASKEY_ACT_SET_PERFERRED_BAND_IDX ,0, DSAT_PENDING_TRUE)

	user_pref.cmd_cb_func = dsatcmif_ph_cmd_cb_func;
    user_pref.data_block_ptr = NULL;
    
    if(FALSE == cm_ph_cmd_pref_change_req(&user_pref))
    {
       DS_AT_MSG0_ERROR("cm_ph_cmd_pref_change_req() return false!!");
       SET_PENDING(DSAT_ASKEY_ACT_SET_PERFERRED_BAND_IDX ,0, DSAT_PENDING_FALSE)
       result = DSAT_ERROR;
    }
    else
    {
      DS_AT_MSG0_HIGH("cm_ph_cmd_pref_change_req() return true");
      result = DSAT_ASYNC_CMD;
    }
  }
  else if ( (NA|EQ|QU) == tok_ptr->op )
  {
    sys_sys_mode_mask_e_type mode_capability;
    sys_band_mask_e_type band_capability = SD_SS_BAND_PREF_NONE;
    sys_lte_band_mask_e_type lte_band_capability = SYS_LTE_BAND_MASK_CONST_NONE;
	sys_band_mask_e_type tds_band_capability;
	
    /* get mode and band capabilities of PM policy via state machine.  */
    cmph_get_mode_band_capability( &mode_capability,
                                   &band_capability,
                                   &lte_band_capability,
                                   &tds_band_capability );

    DS_AT_MSG2_MED("bands    1_64: 0x%08x %08x", QWORD_HIGH(band_capability),
               QWORD_LOW(band_capability));
    dsat_print_lte_band_mask(lte_band_capability);

    res_buff_ptr->used = (word)snprintf((char *)res_buff_ptr->data_ptr,
                                        res_buff_ptr->size,
                                        "Band Capability: gw=0x%08lx %08lx, lte 65_128=0x%08lx %08lx, 1_64=0x%08lx %08lx",
                                        QWORD_HIGH(band_capability),
                                        QWORD_LOW(band_capability),
                                        QWORD_HIGH(lte_band_capability.bits_65_128),
                                        QWORD_LOW(lte_band_capability.bits_65_128),
                                        QWORD_HIGH(lte_band_capability.bits_1_64),
                                        QWORD_LOW(lte_band_capability.bits_1_64));
    result = DSAT_OK;
  }
  else if ( (NA|QU) == tok_ptr->op )
  {
    sys_modem_as_id_e_type		asubs_id = SYS_MODEM_AS_ID_1;
    sd_ss_mode_pref_e_type		comm_mode = SD_SS_MODE_PREF_NONE;
    sd_ss_band_pref_e_type		comm_band = SD_SS_BAND_PREF_NONE;
    sd_ss_band_pref_e_type		comm_tds_band = SD_SS_BAND_PREF_NONE;
    sys_lte_band_mask_e_type		comm_lte_band = SYS_LTE_BAND_MASK_CONST_NONE;
    /* Get ( capability & preference ) */
    cmph_get_comm_mode_band_capab_with_pm(&comm_mode,
									  &comm_band,
									  &comm_lte_band,
									  &comm_tds_band,
									  asubs_id);
    res_buff_ptr->used = (word)snprintf((char *)res_buff_ptr->data_ptr,
									  res_buff_ptr->size,
									  "@ASKEY_PREFBAND:gw=0x%08lx %08lx, lte 65_128=0x%08lx %08lx, 1_64=0x%08lx %08lx",
									  QWORD_HIGH(comm_band),
									  QWORD_LOW(comm_band),
									  QWORD_HIGH(comm_lte_band.bits_65_128),
									  QWORD_LOW(comm_lte_band.bits_65_128),
									  QWORD_HIGH(comm_lte_band.bits_1_64),
									  QWORD_LOW(comm_lte_band.bits_1_64));
    result = DSAT_OK;
  }
  else
  {
    result = DSAT_ERROR;
  }

  return result;

send_error:
  if( err_info.errval == DSAT_ERR_INVALID_NUM_OF_ARGS )
  {
    DS_AT_MSG1_ERROR("Error:%d",err_info.errval);
  }
  else
  {
    DS_AT_MSG2_ERROR("Error:%d, arg_num:%d",err_info.errval,err_info.arg_num);
  }
#endif 
  return DSAT_ERROR;

}/*  dsatvend_exec_prefmode_cmd */

// philip, 20190313, Add askey extended and vendor types of AT cmd table
#if defined(ASKEY_PROPRIETARY_ATCMD) || defined(ASKEY_EXT_VENDOR_ATCMD)

// + command start
dsat_result_enum_type dsataskey_exec_test_ext_cmd
(
  dsat_mode_enum_type mode, 			/*	AT command mode:			*/
  const dsati_cmd_type *parse_table,	/*	Ptr to cmd in parse table	*/
  const tokens_struct_type *tok_ptr,	/*	Command tokens from parser	*/
  dsm_item_type *res_buff_ptr			/*	Place to put response		*/
)
{
  dsat_result_enum_type result = DSAT_OK;

  return result;
}

// $ command start
dsat_result_enum_type dsataskey_exec_test_vendor_cmd
(
  dsat_mode_enum_type mode, 			/*	AT command mode:			*/
  const dsati_cmd_type *parse_table,	/*	Ptr to cmd in parse table	*/
  const tokens_struct_type *tok_ptr,	/*	Command tokens from parser	*/
  dsm_item_type *res_buff_ptr			/*	Place to put response		*/
)
{
  dsat_result_enum_type result = DSAT_OK;

  return result;
}

dsat_result_enum_type dsataskey_exec_disableca_vendor_cmd
(
  dsat_mode_enum_type mode, 			/*	AT command mode:			*/
  const dsati_cmd_type *parse_table,	/*	Ptr to cmd in parse table	*/
  const tokens_struct_type *tok_ptr,	/*	Command tokens from parser	*/
  dsm_item_type *res_buff_ptr			/*	Place to put response		*/
)
{
  dsat_result_enum_type result = DSAT_OK;
  dsat_num_item_type    cmdType;
  char  uData, *nvName = "$disableca";
  char  *nvFileName="/nv/item_files/modem/lte/common/ca_disable";
  int   iv, nLen = strlen(nvName);

  DS_AT_MSG0_HIGH("start disable CA");

  //DS_AT_MSG0_ERROR("Disable CA function entered.");
  //result = dsatparm_exec_param_cmd(mode, parse_table, tok_ptr, res_buff_ptr);
  
  if (tok_ptr->op == (NA)) {
    /* read information */
    int efs_resp = 0;
	efs_resp = efs_get(nvFileName, (byte *)&uData, 1);
    if (efs_get(nvFileName, (byte *)&uData, 1) > 0) {
        /* value 1 is disabled */
        iv = (uData == 1);     // is it disabled?
        res_buff_ptr->used = (word)snprintf((char*)res_buff_ptr->data_ptr,
            res_buff_ptr->size, "CA %s", (iv?"Disabled":"Enabled") );
		
    } else {
        res_buff_ptr->used = (word)snprintf((char*)res_buff_ptr->data_ptr,
            res_buff_ptr->size, "CA Enabled" );
    }
    if( !(strncmp((const char *)parse_table->name, (const char *)nvName ,nLen))) {
      result = DSAT_NO_RESULT_CODE;
    }
  } else if (tok_ptr->op == (NA|EQ|AR)) {
    if(tok_ptr->arg[0] == '\0')
    {
      DS_AT_MSG0_ERROR("Must set parameter.");
      return DSAT_ERROR;
    }
    if( dsatutil_atoi( &cmdType, tok_ptr->arg[0], 10) != ATOI_OK )
    {
      DS_AT_MSG0_ERROR("Ascii to integer conversion failed");
      return DSAT_ERROR;
    }
    
    switch( cmdType ) {
    case 0:
      efs_deltree(nvFileName);
	  DS_AT_MSG0_HIGH("Disable CA =0, OK");
      return DSAT_OK;
    case 1:
        uData = 1;
        if(efs_put(nvFileName, (void*)&uData, 1, O_WRONLY|O_CREAT|O_TRUNC|O_AUTODIR, 0777) == 0)
        {
          //DS_AT_MSG0_ERROR(" ca_disable write ok.");
          DS_AT_MSG0_HIGH("Disable CA =1, OK");
          result = DSAT_OK;
        } else {
          DS_AT_MSG1_ERROR("Problem writing data to NV file:%s",nvFileName);
          return DSAT_ERROR;
        }
    }

    if( !(strncmp((const char *)parse_table->name, (const char *)nvName ,nLen))) {
      result = DSAT_NO_RESULT_CODE;
    }
  } else {
    result = DSAT_ERROR;
  }
  //DS_AT_MSG1_ERROR("Disable CA function exit: %d", result);
  return result;
}

	
#endif /* ASKEY_PROPRIETARY_ATCMD || ASKEY_EXT_VENDOR_ATCMD */

#endif /* ASKEY_SET_PREFERRED_BAND */
