/*******************************************************************************
 * Copyright (c) 2020, Rockwell Automation, Inc.
 * All rights reserved.
 *
 ******************************************************************************/

#ifndef OPENER_CIPFILE_H_
#define OPENER_CIPFILE_H_

#include <stdio.h>

#include "ciptypes.h"

static const CipUint kCipFileObjectClassCode = 0x37U;

static const CipUint kCipFileObjectInitiateUploadServiceCode = 0x4BU;
static const CipUint kCipFileObjectUploadTransferServiceCode = 0x4FU;

typedef struct cip_file_object_file_revision {
  CipUsint major_revision;
  CipUsint minor_revision;
} CipFileObjectFileRevision;

/** @brief Valid values for CIP File Object State
 *
 */
typedef enum cip_file_object_state_values {
  kCipFileStateNonExistent = 0,
  kCipFileStateFileEmpty,
  kCipFileStateFileLoaded,
  kCipFileStateTransferUploadedInitiated,
  kCipFileStateTransferDownloadInitiated,
  kCipFileStateTransferUploadInProgress,
  kCipFileStateTransferDownloadInProgress,
  kCipFileStateStoring
} CipFileStateValue;

typedef enum cip_file_object_invokation_method_values {
  kCipFileInvocationMethodNoAction = 0,
  kCipFileInvocationMethodResetToIdentityObject,
  kCipFileInvocationMethodPowerCycleOnDevice,
  kCipFileInvocationMethodStartServiceRequestRequired,
  kCipFileInvocationMethodApplicationObjectInternalRequestRequired,
  kCipFileInvocationMethodNotApplicable = 255
} CipFileObjectInvokationMethodValues;

typedef enum cip_file_object_file_access_rule {
  kCipFileObjectFileAccessRuleReadWrite = 0,
  kCipFileObjectFileAccessRuleReadOnly,
} CipFileObjectFileAccessRule;

typedef enum cip_file_object_file_encoding_format {
  kCipFileObjectFileEncodinfFormatBinary = 0,
  kCipFileObjectFileEncodinfFormatCompressedFile = 1,
  kCipFileObjectFileEncodinfFormatUnkown = 255
} CipFileObjectFileEncodingFormat;

typedef enum cip_file_transfer_packet_type {
  kCipFileTransferPacketTypeFirstTransferPacket = 0,
  kCipFileTransferPacketTypeMiddleTransferPacket = 1,
  kCipFileTransferPacketTypeLastTransferPacket = 2,
  kCipFileTransferPacketTypeAbortTransfer = 3,
  kCipFileTransferPacketTypeFirstAndLastPacket = 4
} CipFileTransferPacketType;

typedef struct cip_file_object_values {
  CipUsint state; /**< Valid values are the ones in @ref CipFileStateValue*/
  CipStringI instance_name;
  CipUint file_format_version;
  CipStringI file_name;
  CipFileObjectFileRevision file_revision;
  CipUdint file_size;
  CipUint file_checksum;
  CipUsint invocation_method;
  CipByte file_save_parameters;
  CipUsint file_access_rule;
  CipUsint file_encoding_format;
  /* Non CIP values */
  FILE *file_handle; /* TODO: Make platform independent */
  size_t last_send_size;
  CipUsint negotiated_transfer_size;
  CipUsint transfer_number;
} CipFileObjectValues;

EipStatus CipFileInit(void);

#endif /* OPENER_CIPFILE_H_ */
