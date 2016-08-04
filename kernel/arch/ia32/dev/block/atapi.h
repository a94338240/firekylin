/*  This file is part of The Firekylin Operating System.
 *
 *  Copyright 2016 Liuxiaofeng
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef _ATAPI_H
#define _ATAPI_H

#define HD_DATA		0x1f0	/* _CTL when writing */
#define HD_ERROR	0x1f1	/* see err-bits */
#define HD_PRECOMP   HD_ERROR	/* same address, read=error, write=precomp */
#define HD_NSECTOR	0x1f2	/* nr of sectors to read/write */
#define HD_SECTOR	0x1f3	/* starting sector */
#define HD_LCYL		0x1f4	/* starting cylinder */
#define HD_HCYL		0x1f5	/* high byte of starting cyl */
#define HD_CURRENT	0x1f6	/* 101dhhhh , d=drive, hhhh=head */
#define HD_STATUS	0x1f7	/* see status-bits */
#define HD_COMMAND  HD_STATUS	/* same address, read=status, write=cmd */

#define ATA_BUS1	0x1f0
#define ATA_BUS2	0x170
#define ATA_BUS3	0x1e8
#define ATA_BUS4	0x168

#define ATA_CTL1	0x3f6
#define ATA_CTL2	0x376
#define ATA_CTL3	0x3e6
#define ATA_CTL4	0x366

#define ATA_DATA(b)	((b)+0)
#define ATA_ERROR(b)	((b)+1)	/* read  */
#define ATA_PRECOMP(b)	((b)+1) /* write */
#define ATA_NSCTIOR(b)	((b)+2)
#define ATA_SECTOR(b)	((b)+3)
#define ATA_LCYL(b)	((b)+4)
#define ATA_HCYL(b)	((b)+5)
#define ATA_HEAD(b)	((b)+6)
#define ATA_STATUS(b)	((b)+7)	/* read  */
#define ATA_COMMAND(b)	((b)+7) /* write */

#define HD_CMD		0x3f6

/* Bits of HD_ERROR */
#define HD_ERR_MARK	0x01
#define HD_ERR_TRK0	0x02
#define HD_ERR_ABRT	0x04
#define HD_ERR_ID	0x10
#define HD_ERR_ECC	0x40
#define	HD_ERR_BBD	0x80

/* Bits of HD_STATUS */
#define HD_STAT_ERR	0x01
#define HD_STAT_IDX	0x02
#define HD_STAT_ECC	0x04
#define HD_STAT_DRQ	0x08
#define HD_STAT_SEEK	0x10
#define HD_STAT_WRERR	0x20
#define HD_STAT_DRDY	0x40
#define HD_STAT_BUSY	0x80

/* Values for HD_COMMAND */
#define WIN_RESTORE	0x10
#define WIN_READ	0x20
#define WIN_WRITE	0x30
#define WIN_VERIFY	0x40
#define WIN_FORMAT	0x50
#define WIN_INIT	0x60
#define WIN_SEEK 	0x70
#define WIN_DIAGNOSE	0x90
#define WIN_SPECIFY	0x91
#define WIN_IDENTIFY	0xEC

#endif
