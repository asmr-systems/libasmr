#ifndef ASMR_LIB_FS_H
#define ASMR_LIB_FS_H

#include "disks.h"

#include "fatfs/ff.h"


namespace asmr {

    class FileSystem {
    public:
        enum class Status {
            Ok               = 0,
            DiskError        = 1,
            NotReady         = 2,
            NoSuchFile       = 3,
            NoSuchPath       = 4,
            AccessDenied     = 5,
            InvalidDisk      = 6,
            TooManyOpenFiles = 7,
        };

        FileSystem(Disk::Id i);
        Status init();

        // implement methods from FATfs ff.h
        // Status mount();
        Status open(const char* path);
        Status list(const char* dir);

    private:
        FATFS fs;
    };

}

#endif
