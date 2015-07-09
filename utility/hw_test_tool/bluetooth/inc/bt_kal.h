/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/or its licensors, any
 * reproduction, modification, use or disclosure of MediaTek Software, and
 * information contained herein, in whole or in part, shall be strictly
 * prohibited.
 * 
 * MediaTek Inc. (C) 2010. All rights reserved.
 * 
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
 * ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
 * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE
 * RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE
 * MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
 * CHARGE PAID BY RECEIVER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek
 * Software") have been modified by MediaTek Inc. All revisions are subject to
 * any receiver's applicable license agreements with MediaTek Inc.
 */

#ifndef _BT_KAL_H
#define _BT_KAL_H

#include "custom/CFG_BT_File.h"
#include "os_dep.h"

#define CUSTOM_BT_CFG_FILE          "/data/BT.cfg"
#define INTERNAL_BT_CFG_FILE        "/data/bluetooth/BT.cfg"

typedef DWORD BtStatus;

/* BtStatus */
#define BT_STATUS_SUCCESS             0
#define BT_STATUS_FAILED              1
#define BT_STATUS_PENDING             2
#define BT_STATUS_BUSY                3
#define BT_STATUS_NO_RESOURCES        4
#define BT_STATUS_NOT_FOUND           5
#define BT_STATUS_DEVICE_NOT_FOUND    6
#define BT_STATUS_CONNECTION_FAILED   7
#define BT_STATUS_TIMEOUT             8
#define BT_STATUS_NO_CONNECTION       9
#define BT_STATUS_INVALID_PARM        10
#define BT_STATUS_IN_PROGRESS         11
#define BT_STATUS_RESTRICTED          12
#define BT_STATUS_INVALID_TYPE        13
#define BT_STATUS_HCI_INIT_ERR        14
#define BT_STATUS_NOT_SUPPORTED       15
#define BT_STATUS_IN_USE              16
#define BT_STATUS_SDP_CONT_STATE      17
#define BT_STATUS_CANCELLED           18
#define BT_STATUS_NOSERVICES          19
#define BT_STATUS_SCO_REJECT          20
#define BT_STATUS_CHIP_REASON         21
#define BT_STATUS_BLOCK_LIST          22
#define BT_STATUS_SCATTERNET_REJECT   23


typedef BtStatus (*tHciCmdFunc) ( void );
typedef struct {
	tHciCmdFunc command_func;
} sHciScriptElement_t;

typedef union {
	struct btradio_conf_data fields;
	unsigned char raw[sizeof(struct btradio_conf_data)];
} BTConfData_t;

typedef struct {
	BTConfData_t bt_conf;
	sHciScriptElement_t* cur_script;
} sBTInitVar_t;


#define HCI_CMD_PARM_LEN         248
#define MAX_EVENT_SIZE	         256

typedef USHORT HciCommandType;
typedef UCHAR  HciEventType;

typedef struct _HciCommand {
	UCHAR parms[HCI_CMD_PARM_LEN];
} HciCommand;

typedef struct _HciEvent {
	HciEventType event;    /* The type of HCI event received  */
	UCHAR len;             /* Length of the event parameters */
	UCHAR *parms;          /* Event-specific parameters */
} HciEvent;


typedef int (*SETUP_UART_PARAM)(unsigned long hComPort, int iBaudrate, int iFlowControl);


/****************************************************
 * F U N C T I O N  D E C L A R A T I O N S
*****************************************************/

BOOL BT_SetBaudRate(
	HANDLE  hComPort,
	DWORD   dwBaud, 
	DWORD   dwHostBaud,
	DWORD   dwFlowControl
);

BOOL BT_WakeMagic(
	HANDLE  hComPort,
	BOOL    fgWaitResponse
);

BOOL BT_DownPatch(
	HANDLE  hComPort,
	PBYTE   pbPatch,
	DWORD   dwPatchLen
);

BOOL BT_SendHciCommand(
	HANDLE  hComPort,
	HciCommandType wOpCode, 
	DWORD   len, 
	HciCommand* hciCommand 
);

BOOL BT_ReadExpectedEvent(
	HANDLE  hComPort,
	PUCHAR  pEventPacket,
	DWORD   dwMaxBufSz,
	UCHAR   ucExpectedEventCode,
	PDWORD  pdwPacketLen,
	BOOLEAN fCheckCompleteOpCode,
	USHORT  usExpectedOpCode,
	BOOLEAN fCheckCommandStatus,
	UCHAR   ucExpectedStatus
);

int bt_send_data(int fd, unsigned char *buf, unsigned long len);

int bt_receive_data(int fd, unsigned char *buf, unsigned long len);

#endif
