#ifndef DSATASKEYDATA_H
#define DSATASKEYDATA_H

#include "../../../../../qmimsgs/nas/api/network_access_service_v01.h"
#include "../../../../../mmcp/api/public/sys.h"

typedef struct network_status_info_s {
	uint8 roaming;
	sys_mcc_type mcc;
	sys_mnc_type mnc;
	nas_radio_if_enum_v01 radio_if;
	//int32 registration_state;
	nas_registration_state_enum_v01 registration_state;
	uint8 spn_name[64];
	uint8 short_name[64];
	uint8 long_name[128];
} NetworkStatusInfo;

typedef struct cqi_info_s {
  uint8_t err_code;

  uint8_t sys_mode;

  int16_t log_sinr10xdb;

  uint8_t lte_cqi_per_codeword_valid;  
  uint8_t lte_cqi_per_codeword[2];

  uint8_t wcdma_avg_cqi_valid;  
  uint32_t wcdma_avg_cqi;
} CqiInfo;

NetworkStatusInfo askey_net_status;
CqiInfo askey_cqi_info;


// [jelly] remove it after cs4.1_master 
//byte net_assign_apn[100];


#endif 
