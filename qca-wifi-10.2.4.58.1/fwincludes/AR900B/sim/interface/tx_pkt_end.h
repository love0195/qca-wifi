// Copyright (c) 2012 Qualcomm Atheros, Inc.  All rights reserved.
// $ATH_LICENSE_HW_HDR_C$
//
// DO NOT EDIT!  This file is automatically generated
//               These definitions are tied to a particular hardware layout


#ifndef _TX_PKT_END_H_
#define _TX_PKT_END_H_
#if !defined(__ASSEMBLER__)
#endif

// ################ START SUMMARY #################
//
//	Dword	Fields
//	0	status[3:0], user_mask[7:4], reserved[31:8]
//
// ################ END SUMMARY #################

#define NUM_OF_DWORDS_TX_PKT_END 1

struct tx_pkt_end {
    volatile uint32_t status                          :  4, //[3:0]
                      user_mask                       :  4, //[7:4]
                      reserved                        : 24; //[31:8]
};

/*

status
			
			Reason for early termination of TX packet by the PHY 
			
			<enum 1    error_tx_underrun> PHY ran out of transmit
			data due to transmit underrun
			
			<enum 2    error_tx_chain_mask_zero>
			
			<enum 3    error_tx_extra_sym_mismatch>
			
			<enum 4    error_tx_vht_length_not_multiple_of_3>
			
			<enum 5    error_tx_bw_is_gt_dyn_bw>
			
			<enum 6  error_tx_11b_rate_illegal>
			
			<enum 7  error_tx_legacy_rate_illegal>
			
			<enum 8  error_tx_ht_rate_illegal>
			
			<enum 9  error_tx_vht_rate_illegal>
			
			
			
			 <legal 1-9>

user_mask
			
			Indicates which users this message relates to. This
			field is only valid for error conditions that are
			user-specific.
			
			
			
			<legal 0-7>

reserved
			
			Reserved: Set to 0 and ignored on receive  <legal 0>
*/


/* Description		TX_PKT_END_0_STATUS
			
			Reason for early termination of TX packet by the PHY 
			
			<enum 1    error_tx_underrun> PHY ran out of transmit
			data due to transmit underrun
			
			<enum 2    error_tx_chain_mask_zero>
			
			<enum 3    error_tx_extra_sym_mismatch>
			
			<enum 4    error_tx_vht_length_not_multiple_of_3>
			
			<enum 5    error_tx_bw_is_gt_dyn_bw>
			
			<enum 6  error_tx_11b_rate_illegal>
			
			<enum 7  error_tx_legacy_rate_illegal>
			
			<enum 8  error_tx_ht_rate_illegal>
			
			<enum 9  error_tx_vht_rate_illegal>
			
			
			
			 <legal 1-9>
*/
#define TX_PKT_END_0_STATUS_OFFSET                                   0x00000000
#define TX_PKT_END_0_STATUS_LSB                                      0
#define TX_PKT_END_0_STATUS_MASK                                     0x0000000f

/* Description		TX_PKT_END_0_USER_MASK
			
			Indicates which users this message relates to. This
			field is only valid for error conditions that are
			user-specific.
			
			
			
			<legal 0-7>
*/
#define TX_PKT_END_0_USER_MASK_OFFSET                                0x00000000
#define TX_PKT_END_0_USER_MASK_LSB                                   4
#define TX_PKT_END_0_USER_MASK_MASK                                  0x000000f0

/* Description		TX_PKT_END_0_RESERVED
			
			Reserved: Set to 0 and ignored on receive  <legal 0>
*/
#define TX_PKT_END_0_RESERVED_OFFSET                                 0x00000000
#define TX_PKT_END_0_RESERVED_LSB                                    8
#define TX_PKT_END_0_RESERVED_MASK                                   0xffffff00


#endif // _TX_PKT_END_H_
