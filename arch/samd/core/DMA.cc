#include "DMA.h"


// DMA descriptor list entry points.
__attribute__((__aligned__(16))) static DmacDescriptor
    _descriptor[VARIANT_DMAC_CH_NUM],
    _writeback[VARIANT_DMAC_CH_NUM];

// pointer to DMA channel objects
static DMAChannel* _dmaChan[VARIANT_DMAC_CH_NUM] = {0}; // NULL

DMAChannel::DMAChannel() {
    // TODO initialize
}
