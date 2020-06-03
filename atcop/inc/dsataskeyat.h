#ifndef DSATASKEYAT_H
#define DSATASKEYAT_H
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                A S K EY P R O P R I E T A RY

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

// @ command start
dsat_result_enum_type dsataskey_exec_lab_test_cfg_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,      /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr  /*  Place to put response       */
);

// philip, 20180810, [Generic][TMO] Set preferred band
#ifdef ASKEY_SET_PREFERRED_BAND
dsat_result_enum_type dsataskey_exec_prefband_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
);
#endif /* ASKEY_SET_PREFERRED_BAND */

#ifdef ASKEY_PCI_LOCK
dsat_result_enum_type dsataskey_exec_pcilock_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
);
#endif

#ifdef ASKEY_AT_TEST
dsat_result_enum_type dsataskey_exec_test_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
);
#endif /* ASKEY_AT_TEST */

#ifdef ASKEY_PREF_NET
dsat_result_enum_type dsataskey_exec_prefnet_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
);
#endif /* ASKEY_PREF_NET */

dsat_result_enum_type dsataskey_exec_makecall_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
);


dsat_result_enum_type dsataskey_exec_fwd_test_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
);

// philip, 20190313, Add askey extended and vendor types of AT cmd table
#if defined(ASKEY_PROPRIETARY_ATCMD) || defined(ASKEY_EXT_VENDOR_ATCMD)


// + command start
dsat_result_enum_type dsataskey_exec_test_ext_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
);


// $ command start
dsat_result_enum_type dsataskey_exec_test_vendor_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *parse_table,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
);

dsat_result_enum_type dsataskey_exec_disableca_vendor_cmd
(
  dsat_mode_enum_type mode, 			/*	AT command mode:			*/
  const dsati_cmd_type *parse_table,	/*	Ptr to cmd in parse table	*/
  const tokens_struct_type *tok_ptr,	/*	Command tokens from parser	*/
  dsm_item_type *res_buff_ptr			/*	Place to put response		*/
);


#endif /* ASKEY_PROPRIETARY_ATCMD || ASKEY_EXT_VENDOR_ATCMD */


#endif /* DSATASKEYAT_H */

