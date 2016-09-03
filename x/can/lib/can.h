/*
 * x/lib/can.h
 *
 * Definitions for CAN network layer (socket addr / CAN frame / CAN filter)
 *
 * @author Halis Duraki <duraki.halis@nsoft.ba>
 * /usr/include/duraki
 */

#ifndef _UAPI_CAN_H
#define _UAPI_CAN_H

#include <sys/types.h>
#include <sys/socket.h>
#include "types.h"

/* controller area network (CAN) kernel definitions */

/* special address description flags for the CAN_ID */
#define CAN_EFF_FLAG 0x80000000U /* EFF/SFF is set */
#define CAN_RTR_FLAG 0x40000000U /* remote transmission request */
#define CAN_ERR_FLAG 0x20000000U /* error message frame */

/* valid bits in CAN ID for frame formats */
#define CAN_SFF_MASK 0x000007FFU /* standard frame format (SFF) */
#define CAN_EFF_MASK 0x1FFFFFFFU /* extended frame format (EFF) */
#define CAN_ERR_MASK 0x1FFFFFFFU /* omit EFF, RTR, ERR flags */

/**
 * Controller Area Network Identifier structure
 *
 * bit 0-28 / CAN identifier (11/29 bit)
 * bit 29	/ error message frame flag (0 = data frame, 1 = error message)
 * bit 30	/ remote transmission request flag (1 = rtr frame)
 * bit 31	/ frame format flag (0 = standard 11-bit, 1 = extended 29-bit)
 */
typedef __u32 canid_t;

#define CAN_SFF_ID_BITS		11
#define CAN_EFF_ID_BITS		29

/**
 * Controller Area Network Error Message Frame Mask structure
 *
 * bit 0-28		/ error class mask
 * bit 29-31	/ set to zero
 */
typedef __u32 can_err_mask_t;

/* CAN payload length and DLC definitions according to ISO 11898-1 */
// http://www.iso.org/iso/catalogue_detail.htm?csnumber=63648
#define CAN_MAX_DLC		8
#define CAN_MAX_DLEN	8

/* CAN FD payload length and DLC definitions according to ISO 11898-7 */
#define CANFD_MAX_DLC	15
#define CANFD_MAX_DLEN	64

/**
 * struct can_frame - basic CAN frame structure
 *
 * @can_id:		CAN ID of the frame and CAN_*_FLAG flags, see canid_t definition
 * @can_dlc:	frame payload length in byte (0 .. 8) aka data length code 
 * 				N.B. the DLC field from ISO 11898-1 Chapter 8.4.2.3 has a 1:1 
 * 				mapping of the 'data length code' to the real payload length
 * @__pad:		padding
 * @__res0:		reserved / padding
 * @__res1:		reserved / padding
 * @data:		CAN frame payload (up to 8 byte)
 */
struct can_frame {
	canid_t can_id;		/* 32 bit CAN_ID + EFF/RTR/ERR flags */
	__u8	can_dlc;	/* frame payload length in byte (0 .. CAN_MAX_DLEN) */
	__u8	__pad;		/* padding */
	__u8	__res0;		/* reserved / padding */
	__u8	__res1;		/* reserved / padding */
	__u8	data[CAN_MAX_DLEN] __attribute__((aligned(8)));
};

/**
 * defined bits for canfd_frame.flags
 *
 * The use of struct canfd_frame implies the EDL / Extended Data Length bit 
 * to be set in a CAN frame bitstream on the wire. The EDL bit switch turns 
 * the CAN controllers bitstream processor into the CAN FD mode which creates
 * two new options within the CAN FD frame specification:
 *
 * Bit Rate Switch (bitrate)
 * Error State Indicator (error state)
 */
#define CANFD_BRS 0x01; /* bit rate switch */
#define CANFD_ESI 0x02; /* error state */

/**
 * struct canfd_frame - CAN flexible data rate frame structure
 * @can_id: CAN ID of the frame and CAN_*_FLAG flags, see canid_t definition
 * @len:    frame payload length in byte (0 .. CANFD_MAX_DLEN)
 * @flags:  additional flags for CAN FD
 * @__res0: reserved / padding
 * @__res1: reserved / padding
 * @data:   CAN FD frame payload (up to CANFD_MAX_DLEN byte)
 */
struct canfd_frame {
	canid_t can_id; /* 32 bit CAN_ID + EFF/RTR/ERR flags */
	__u8	len;	/* frame payload length in byte */
	__u8	flags;	/* additional flags for CAN FD */
	__u8	__res0;	/* reserved / padding */
	__u8	__res1; /* reserved / padding */
	__u8	data[CANFD_MAX_DLEN] __attribute__((aligned(8)));
};

#define CAN_MTU			(sizeof(struct can_frame))
#define CANFD_MTU		(sizeof(struct canfd_frame))

/* protocols of protocol family PF_CAN */
#define CAN_RAW			1 /* RAW sockets */
#define CAN_BCM			2 /* Broadcast Manager */
#define CAN_TP16		3 /* VAG Transport Protocol v1.6 */
#define CAN_TP20		4 /* CAG Transport Protocol v2.0 */
#define CAN_MCNET		5 /* Bosch MCNet */
#define CAN_ISOTP		6 /* ISO 15765-2 Transport Protocol */

#define SOL_CAN_BASE	100

/**
 * struct sockaddr_can - the sockaddr structure for CAN sockets
 * @can_family:	address family number AF_CAN
 * @can_ifindex: CAN network interface index
 * @can_addr: protocol specific address information
 */
struct sockaddr_can {
	/* required from types.h */
	__uint8_t can_family;
	int		can_ifindex;
	union {
		/* transport protocol class address information */
		struct { canid_t rx_id, tx_id; } tp;
	} can_addr;
};

/**
 * struct can_filter - CAN ID based filter in can_register()
 * @can_id: relevant bits of CAN ID which are not masked out.
 * @can_err_mask_t: CAN mask
 */
struct can_filter {
	canid_t can_id;
	canid_t can_mask;
};

#define CAN_INV_FILTER 0x20000000U /* to be set in can_filter.can_id */

#endif /* !_UAPI_CAN_H */