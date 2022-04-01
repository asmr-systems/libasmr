#include "stm32f4xx.h"

#include "i2s.h"


using namespace asmr;


void fill_buffers(uint32_t* buffers[2], uint32_t length) {
    for (int i = 0; i < length; i+=2) {
        double v = (sin(TwoPi*static_cast<double>(i*12)/2048));
        buffers[0][i] = static_cast<int32_t>(2147483647 * v); // 32767 is max positive 16bit signed int
        double v2 = (sin(TwoPi*static_cast<double>(i*8)/2048));
        buffers[0][i+1] = static_cast<int32_t>(2147483647 * v2);

        buffers[1][i] = static_cast<int32_t>(i < 1024 ? 2147483647 : 0); // 32767 is max positive 16bit signed int
        buffers[1][i+1] = static_cast<int32_t>(i < 1024 ? 2147483647 : 0);

        // swap
        buffers[0][i] = static_cast<uint32_t>(buffers[0][i]) << 16 | static_cast<uint32_t>(buffers[0][i]) >> 16;
        buffers[0][i+1] = static_cast<uint32_t>(buffers[0][i+1]) << 16 | static_cast<uint32_t>(buffers[0][i+1]) >> 16;

        buffers[1][i] = static_cast<uint32_t>(buffers[1][i]) << 16 | static_cast<uint32_t>(buffers[1][i]) >> 16;
        buffers[1][i+1] = static_cast<uint32_t>(buffers[1][i+1]) << 16 | static_cast<uint32_t>(buffers[1][i+1]) >> 16;
    }

}

//:::: Public
//:::::::::::

hal::I2S::Status stm32f405::I2S::init(hal::I2S::Config c) {
    config = c;

    //:::: Assign Custom Interrupt Handler
    // see https://os.mbed.com/forum/mbed/topic/1439/?page=1#comment-7081
    hal::set_interrupt((int)DMA1_Stream4_IRQn, (uint32_t)&irq);

    //:::: initialize output buffers
    if (config.output_enabled) {
        output_buffers[0] = new uint32_t[config.buffer_size];
        output_buffers[1] = new uint32_t[config.buffer_size];

        // DEBUGGING
        fill_buffers(output_buffers, config.buffer_size);
    }

    //:::: initialize input buffers
    if (config.input_enabled) {
        input_buffers[0] = new uint32_t[config.buffer_size];
        input_buffers[1] = new uint32_t[config.buffer_size];
    }

    //:::: initialize output audio
    audio_output.buffer   = output_buffers[0];
    audio_output.channels = config.channels;
    audio_output.depth    = config.bit_depth;
    audio_output.length   = config.buffer_size;

    //:::: initialize input audio
    audio_input.buffer   = input_buffers[0];
    audio_input.channels = config.channels;
    audio_input.depth    = config.bit_depth;
    audio_input.length   = config.buffer_size;

    init();

    return hal::I2S::Status::Ok;
}

bool stm32f405::I2S::input_ready() {
    // TODO implement me
    return false;
};

bool stm32f405::I2S::output_ready() {
    // TODO implement me
    return false;
};

Audio& stm32f405::I2S::get_audio_input() {
    return audio_input;
};

Audio& stm32f405::I2S::get_audio_output() {
    return audio_output;
};

//:::: Protected
//::::::::::::::

void stm32f405::I2S::irq() {
    if (DMA1->HISR & DMA_HISR_TCIF4) {
        auto singleton = Instance();
        // set current write buffer.
        if (DMA1_Stream4->CR & DMA_SxCR_CT) {
            singleton->audio_output.buffer = singleton->output_buffers[0];
        } else {
            singleton->audio_output.buffer = singleton->output_buffers[1];
        }

        // transfer complete.
        DMA1->HIFCR |= DMA_HIFCR_CTCIF4; // clear interrupt flag.
    }
}

//:::: Private
//::::::::::::

void stm32f405::I2S::init() {
    // Enable the SPI2/I2S & GPIOB peripheral clock
    RCC->APB1ENR |= (0x1<<14); // SPI2/I2S
    RCC->AHB1ENR |= (0x2<<0);  // GPIOB

    //:::: Configure PB9 IO as I2S WS
    //:::::::::::::::::::::::::::::::
    GPIOB->MODER   |=   2<<18;                       // pin PB9(bits 19:18) as Alternative Function (AF) (10)
    GPIOB->OTYPER  &= ~(1<<9);                       // bit 9=0 --> Output push pull
    GPIOB->OSPEEDR |=   1<<18;                       // Pin PB9 (bits 19:18) as Fast Speed (1:0)
    GPIOB->PUPDR   |=   1<<19;                       // Pin PB9 (bits 19:18) are 1:0 --> pulldown
    GPIOB->AFR[1]  |=   0x5 << GPIO_AFRH_AFSEL9_Pos; // AF5 is SPI1/SPI2 (see p.272 of datasheet)


    //:::: Congifure PB13 as I2S SCLK
    //:::::::::::::::::::::::::::::::
    GPIOB->MODER   |= (2<<26);                        // pin PB13(bits 27:26) as Alternative Function (AF) (10)
    GPIOB->OTYPER  &= ~(1<<13);                       // bit 13=0 --> Output push pull
    GPIOB->OSPEEDR |= (1<<26);                        // Pin PB13 (bits 27:26) as Fast Speed (1:0)
    GPIOB->PUPDR   |= 1<<27;                          // Pin PB9 (bits 27:26) are 1:0 --> pulldown
    GPIOB->AFR[1]  |= (0x5 << GPIO_AFRH_AFSEL13_Pos); // AF5 is SPI1/SPI2 (see p.272 of datasheet)


    //:::: Configure PB15 as I2S SD
    //:::::::::::::::::::::::::::::
    GPIOB->MODER   |= (2<<30);                        // pin PB15(bits 31:30) as Alternative Function (AF) (10)
    GPIOB->OTYPER  &= ~(1<<15);                       // bit 15=0 --> Output push pull
    GPIOB->OSPEEDR |= (1<<30);                        // Pin PB15 (bits 31:30) as Fast Speed (1:0)
    GPIOB->PUPDR   |= 1<<31;                          // Pin PB9 (bits 31:10) are 1:0 --> pulldown
    GPIOB->AFR[1]  |= (0x5 << GPIO_AFRH_AFSEL15_Pos); // AF5 is SPI1/SPI2 (see p.272 of datasheet)


    //:::: Configure I2S
    //::::::::::::::::::
    SPI2->I2SCFGR |= SPI_I2SCFGR_I2SCFG_1;  // Set I2S to Controller Tx Mode (0b10)
    SPI2->I2SCFGR &= ~SPI_I2SCFGR_I2SSTD;   // clear standard (defaults to Philips std))
    SPI2->I2SCFGR &= ~SPI_I2SCFGR_CKPOL;    // set clock polarity to 0
    SPI2->I2SCFGR &= ~SPI_I2SCFGR_DATLEN;   // zero out data length bits
    SPI2->I2SCFGR |= SPI_I2SCFGR_DATLEN_0;  // set to 24 bit data length
    SPI2->I2SCFGR |= SPI_I2SCFGR_CHLEN;     // set 32 bit per audio channel


    //:::: Configure I2S Clock Pre-Scaling
    //:::::::::::::::::::::::::::::::::::
    SPI2->I2SPR &= ~SPI_I2SPR_MCKOE;              // mclk Controller Clock Out Disabled
    SPI2->I2SPR &= ~SPI_I2SPR_I2SDIV;             // zero out I2S clock divider
    SPI2->I2SPR |= (19 << SPI_I2SPR_I2SDIV_Pos);  // set divider to 53 (0x34) i guess?
    //SPI2->I2SPR |= SPI_I2SPR_ODD;               // set odd to 1 (what is this?)


    //:::: Configure PLL & I2S PLL
    //::::::::::::::::::::::::::::
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_1;                      // set PLLM (division factor) to 2
    RCC->PLLI2SCFGR &= ~RCC_PLLI2SCFGR_PLLI2SN;              // clear VCO multiplication factor
    RCC->PLLI2SCFGR |= (450 << RCC_PLLI2SCFGR_PLLI2SN_Pos);  // set mult factor to 302 (dec)
    RCC->PLLI2SCFGR &= ~RCC_PLLI2SCFGR_PLLI2SR;              // clear I2S clocks division factor
    RCC->PLLI2SCFGR |= (4 << RCC_PLLI2SCFGR_PLLI2SR_Pos);    // set I2S clocks division to 2

    // init DMA
    init_dma();

    //:::: Enable PLL & I2S
    //:::::::::::::::::::::
    RCC->CR       |= RCC_CR_PLLI2SON;       // enable PLL I2S
    SPI2->CR2     |= SPI_CR2_TXDMAEN;       // enable I2S via DMA
    SPI2->I2SCFGR |= SPI_I2SCFGR_I2SMOD;    // set mode to I2S
    SPI2->I2SCFGR |= SPI_I2SCFGR_I2SE;      // enable I2S
}

void stm32f405::I2S::init_dma() {
    // use SPI2TX which is on DMA1 Stream 4, Channel 0

    // enable DMA1 clock
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

    // (0) enable IRQ for DMA1 stream 4
    NVIC_EnableIRQ(DMA1_Stream4_IRQn);

    // (1) set peripheral port register
    DMA1_Stream4->PAR = reinterpret_cast<uint32_t>(&(SPI2->DR));

    // (2) set memory address
    DMA1_Stream4->M0AR = reinterpret_cast<uint32_t>(output_buffers[0]);
    DMA1_Stream4->M1AR = reinterpret_cast<uint32_t>(output_buffers[1]);

    // (3) configure number of data items to be transferred
    DMA1_Stream4->NDTR = config.buffer_size * 2; // MULTIPLY by 2 IF MSIZE = 32 and PSIZE = 16

    // (4) select channel
    //DMA1_Stream4->CR &= ~DMA_SxCR_CHSEL;  // channel 0 (0b00)

    // (5) configure transfer direction
    DMA1_Stream4->CR |= DMA_SxCR_DIR_0;  // memory to peripheral (0b01)

    // (6) configure circular buffer mode
    // DMA1_Stream4->CR |= DMA_SxCR_CIRC; // enable circular buffer
    DMA1_Stream4->CR |= DMA_SxCR_DBM;  // enable double buffer mode (circular buffer enabled)

    // (7) configure data width (memory and peripheral)
    DMA1_Stream4->CR &= ~DMA_SxCR_MSIZE;   // clear MSIZE
    DMA1_Stream4->CR &= ~DMA_SxCR_PSIZE;   // clear PSIZE
    DMA1_Stream4->CR |= DMA_SxCR_MSIZE_1;  // 32-bit (0b10)
    DMA1_Stream4->CR |= DMA_SxCR_PSIZE_0;  // 16-bit (0b01)

    // (7.25) set memory incrementing... DAMN.
    // SO, the manual says: "memory address pointer is incremented after each data transfer"
    // , but what they mean is that it is incremented after each load of source data to
    // dst data register. i thought it meant after each transfer_complete. I think
    // the word "transfer" is problematic here because they don't mean it in the
    // way they've been using it in the manual.
    DMA1_Stream4->CR |= DMA_SxCR_MINC;

    // (8) configure transfer complete interrupt
    DMA1_Stream4->CR |= DMA_SxCR_TCIE;  // enable "transfer complete" interrupt

    // (9) enable DMA Stream 4.
    DMA1_Stream4->CR |= DMA_SxCR_EN;
}
