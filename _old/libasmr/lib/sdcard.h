#ifndef ASMR_LIB_SDCARD_H
#define ASMR_LIB_SDCARD_H

#include <memory>

#include "hal/sdhc.h"
#include "disks.h"


namespace asmr {

    class SDCard : public Disk {
    public:
        struct Config {};

        SDCard(std::shared_ptr<hal::SDHostCtlr> sdhc, Config c);

        virtual Disk::Status init() override;
        virtual Disk::Status status() override;
        virtual Disk::Status read(uint8_t* buffer, uint64_t sector, unsigned int n) override;
        virtual Disk::Status write(const uint8_t* buffer, uint64_t sector, unsigned int n) override;

    private:
        std::shared_ptr<hal::SDHostCtlr> sdhc;
    };

}

#endif
