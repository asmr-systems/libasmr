#include "sdcard.h"


//:::: Public
//:::::::::::

asmr::SDCard::SDCard(std::shared_ptr<asmr::hal::SDHostCtlr> sdhc, Config c)
    : sdhc(sdhc)
{

}

asmr::Disk::Status asmr::SDCard::init() {
    auto ok = hal::SDHostCtlr::Status::Ok;
    hal::SDHostCtlr::Status status;

    // (0) SDHC initialize
    status = sdhc->init();
    if (status != ok) return Disk::Status::RWError;

    // (2) SDHC initialize cards
    status = sdhc->initialize_cards();

    // (3) SDHC set clock speed to transfer
    status = sdhc->set_clock_speed(sdio::Speed::Tx);

    // (4) SDHC read CSD/CID
    status = sdhc->get_card_info();

    // (5) SDHC select card
    status = sdhc->select_card();

    // (6) SDHC enable wide bus mode
    status = sdhc->enable_wide_bus();

    return Disk::Status::Ok;
}

asmr::Disk::Status asmr::SDCard::status() {
    // (1) SDHC get state
    return Disk::Status::Ok;
}

asmr::Disk::Status asmr::SDCard::read(uint8_t* buffer, uint64_t sector, unsigned int n) {
    return Disk::Status::Ok;
}

asmr::Disk::Status asmr::SDCard::write(const uint8_t* buffer, uint64_t sector, unsigned int n) {
    return Disk::Status::Ok;
}


//:::: Private
//::::::::::::
