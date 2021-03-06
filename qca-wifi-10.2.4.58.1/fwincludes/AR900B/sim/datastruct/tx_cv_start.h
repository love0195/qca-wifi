// Copyright (c) 2012 Qualcomm Atheros, Inc.  All rights reserved.
// $ATH_LICENSE_HW_HDR_C$
//
// DO NOT EDIT!  This file is automatically generated
//               These definitions are tied to a particular hardware layout


#ifndef _TX_CV_START_H_
#define _TX_CV_START_H_
#if !defined(__ASSEMBLER__)
#endif

// ################ START SUMMARY #################
//
//	Dword	Fields
//	0	cv_required[0], cv_mem_fetch_required[1], reserved_0a[2], user_num[4:3], reserved_0b[7:5], cv_id[15:8], cv_size[29:16], reserved_0c[31:30]
//	1	cv_address[31:0]
//
// ################ END SUMMARY #################

#define NUM_OF_DWORDS_TX_CV_START 2

struct tx_cv_start {
    volatile uint32_t cv_required                     :  1, //[0]
                      cv_mem_fetch_required           :  1, //[1]
                      reserved_0a                     :  1, //[2]
                      user_num                        :  2, //[4:3]
                      reserved_0b                     :  3, //[7:5]
                      cv_id                           :  8, //[15:8]
                      cv_size                         : 14, //[29:16]
                      reserved_0c                     :  2; //[31:30]
    volatile uint32_t cv_address                      : 32; //[31:0]
};

/*

cv_required
			
			When set, usage of CV data is required, for either
			MU-MIMO transmission or SU beam forming.

cv_mem_fetch_required
			
			When set, the TX PCU shall fetch the cv data from
			memory. When NOT set, the CV data fetching is needed.

reserved_0a
			
			0

user_num
			
			Field only valid when cv_mem_fetch_required is set. 
			
			
			
			Indicates the position that this CV will be stored in
			the PHY.  0 corresponds to user 0 position, 1 corresponds to
			user 1 position, 2 corresponds to user 2 position.  <legal
			0-3>
			
			Field only valid when forced_phy_cv_Location is set.
			When 

reserved_0b
			
			0

cv_id
			
			A unique ID corresponding to the CV data. 
			
			
			
			(Added for tracking/debugging purposes only)

cv_size
			
			Field only valid when cv_mem_fetch_required is set. 
			
			
			
			Size of the CV in units of octets <legal all>

reserved_0c
			
			0

cv_address
			
			Field only valid when cv_mem_fetch_required is set. 
			
			
			
			The physical address of the CV data in memory.
*/


/* Description		TX_CV_START_0_CV_REQUIRED
			
			When set, usage of CV data is required, for either
			MU-MIMO transmission or SU beam forming.
*/
#define TX_CV_START_0_CV_REQUIRED_OFFSET                             0x00000000
#define TX_CV_START_0_CV_REQUIRED_LSB                                0
#define TX_CV_START_0_CV_REQUIRED_MASK                               0x00000001

/* Description		TX_CV_START_0_CV_MEM_FETCH_REQUIRED
			
			When set, the TX PCU shall fetch the cv data from
			memory. When NOT set, the CV data fetching is needed.
*/
#define TX_CV_START_0_CV_MEM_FETCH_REQUIRED_OFFSET                   0x00000000
#define TX_CV_START_0_CV_MEM_FETCH_REQUIRED_LSB                      1
#define TX_CV_START_0_CV_MEM_FETCH_REQUIRED_MASK                     0x00000002

/* Description		TX_CV_START_0_RESERVED_0A
			
			0
*/
#define TX_CV_START_0_RESERVED_0A_OFFSET                             0x00000000
#define TX_CV_START_0_RESERVED_0A_LSB                                2
#define TX_CV_START_0_RESERVED_0A_MASK                               0x00000004

/* Description		TX_CV_START_0_USER_NUM
			
			Field only valid when cv_mem_fetch_required is set. 
			
			
			
			Indicates the position that this CV will be stored in
			the PHY.  0 corresponds to user 0 position, 1 corresponds to
			user 1 position, 2 corresponds to user 2 position.  <legal
			0-3>
			
			Field only valid when forced_phy_cv_Location is set.
			When 
*/
#define TX_CV_START_0_USER_NUM_OFFSET                                0x00000000
#define TX_CV_START_0_USER_NUM_LSB                                   3
#define TX_CV_START_0_USER_NUM_MASK                                  0x00000018

/* Description		TX_CV_START_0_RESERVED_0B
			
			0
*/
#define TX_CV_START_0_RESERVED_0B_OFFSET                             0x00000000
#define TX_CV_START_0_RESERVED_0B_LSB                                5
#define TX_CV_START_0_RESERVED_0B_MASK                               0x000000e0

/* Description		TX_CV_START_0_CV_ID
			
			A unique ID corresponding to the CV data. 
			
			
			
			(Added for tracking/debugging purposes only)
*/
#define TX_CV_START_0_CV_ID_OFFSET                                   0x00000000
#define TX_CV_START_0_CV_ID_LSB                                      8
#define TX_CV_START_0_CV_ID_MASK                                     0x0000ff00

/* Description		TX_CV_START_0_CV_SIZE
			
			Field only valid when cv_mem_fetch_required is set. 
			
			
			
			Size of the CV in units of octets <legal all>
*/
#define TX_CV_START_0_CV_SIZE_OFFSET                                 0x00000000
#define TX_CV_START_0_CV_SIZE_LSB                                    16
#define TX_CV_START_0_CV_SIZE_MASK                                   0x3fff0000

/* Description		TX_CV_START_0_RESERVED_0C
			
			0
*/
#define TX_CV_START_0_RESERVED_0C_OFFSET                             0x00000000
#define TX_CV_START_0_RESERVED_0C_LSB                                30
#define TX_CV_START_0_RESERVED_0C_MASK                               0xc0000000

/* Description		TX_CV_START_1_CV_ADDRESS
			
			Field only valid when cv_mem_fetch_required is set. 
			
			
			
			The physical address of the CV data in memory.
*/
#define TX_CV_START_1_CV_ADDRESS_OFFSET                              0x00000004
#define TX_CV_START_1_CV_ADDRESS_LSB                                 0
#define TX_CV_START_1_CV_ADDRESS_MASK                                0xffffffff


#endif // _TX_CV_START_H_
