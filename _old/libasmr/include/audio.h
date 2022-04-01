#ifndef ASMR_AUDIO_H
#define ASMR_AUDIO_H

#include <cstdint>


namespace asmr {

    struct Audio {
        uint32_t* buffer;
        uint16_t  channels = 2;
        uint16_t  depth    = 24;
        uint32_t  length   = 2048;
    };

}

#endif
