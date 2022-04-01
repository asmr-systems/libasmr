/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "../disks.h"           /* Disk manager for physical drive mapping */


DSTATUS convert_status(asmr::Disk::Status status) {
    switch ((uint8_t)status) {
    case (uint8_t)asmr::Disk::Status::NotReady:
        return STA_NOINIT;
    case (uint8_t)asmr::Disk::Status::NoDisk:
        return STA_NODISK;
    case (uint8_t)asmr::Disk::Status::ReadOnly:
        return STA_PROTECT;
    }

    return 0x00;
}

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
    auto disk = asmr::Disks::get(pdrv);
    return convert_status(disk->status());
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
    auto disk = asmr::Disks::get(pdrv);
    return convert_status(disk->init());
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
    auto disk = asmr::Disks::get(pdrv);
    return static_cast<DRESULT>(disk->read(buff, sector, count));
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
    auto disk = asmr::Disks::get(pdrv);
    return static_cast<DRESULT>(disk->write(buff, sector, count));
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
    // ????
    // auto disk = asmr::Disks::get(pdrv);
    // return disk->ioctl(); ?????

    return RES_PARERR;
}
