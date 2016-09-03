#ifndef _UAPI_CAN_RAW_H
#define _UAPI_CAN_RAW_H

#include <sys/types.h>
#include "lib/can.h"

#define SOL_CAN_RAW (SOL_CAN_BASE + CAN_RAW)

enum {
	CAN_RAW_FILTER = 1,
	CAN_RAW_ERR_FILTER,
	CAN_RAW_LOOPBACK,
	CAN_RAW_RECV_OWN_MSGS,
	CAN_RAW_FD_FRAMES,
	CAN_RAW_JOIN_FILTERS
};

#endif /* !_UAPI_CAN_RAW_H */