#include "sdhc.h"


//:::: Public
//:::::::::::

asmr::hal::SDHostCtlr::Status asmr::stm32f405::SDHostCtlr::init() {
    hal::SDHostCtlr::Status status;

    // Enable SDIO Peripheral Clock
    RCC->APB2ENR |= RCC_APB2ENR_SDIOEN;

    // Enable DMA2 Clock
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    // reset
    status = reset();

    // configure sdio peripheral
    status = set_clock_speed(sdio::Speed::Init);

    SDIO->CLKCR &= ~SDIO_CLKCR_NEGEDGE; // Clock Edge (rising)
    SDIO->CLKCR &= ~SDIO_CLKCR_BYPASS;  // Clock Bypass (disable)
    SDIO->CLKCR &= ~SDIO_CLKCR_PWRSAV;  // Clock Power Save (disable)
    SDIO->CLKCR &= ~SDIO_CLKCR_WIDBUS;  // Bus Width (initial 1 bit)
    SDIO->CLKCR &= ~SDIO_CLKCR_HWFC_EN; // Hardware Flow Control (disable)

    // configure gpio
    // TODO do something to refactor ho long this is....(alias types or something)
    clk_io = asmr::GPIO(config.clk_io.port, config.clk_io.pin,{asmr::hal::GPIO::Mode::AltFunc, asmr::hal::GPIO::Type::PushPull, asmr::hal::GPIO::Speed::High, asmr::hal::GPIO::ResistorPull::Down, 12});
    cmd_io = asmr::GPIO(config.cmd_io.port, config.cmd_io.pin,{asmr::hal::GPIO::Mode::AltFunc, asmr::hal::GPIO::Type::PushPull, asmr::hal::GPIO::Speed::High, asmr::hal::GPIO::ResistorPull::Down, 12});
    d0_io = asmr::GPIO(config.d0_io.port, config.d0_io.pin,{asmr::hal::GPIO::Mode::AltFunc, asmr::hal::GPIO::Type::PushPull, asmr::hal::GPIO::Speed::High, asmr::hal::GPIO::ResistorPull::Down, 12});
    d1_io = asmr::GPIO(config.d1_io.port, config.d1_io.pin,{asmr::hal::GPIO::Mode::AltFunc, asmr::hal::GPIO::Type::PushPull, asmr::hal::GPIO::Speed::High, asmr::hal::GPIO::ResistorPull::Down, 12});
    d2_io = asmr::GPIO(config.d2_io.port, config.d2_io.pin,{asmr::hal::GPIO::Mode::AltFunc, asmr::hal::GPIO::Type::PushPull, asmr::hal::GPIO::Speed::High, asmr::hal::GPIO::ResistorPull::Down, 12});
    d3_io = asmr::GPIO(config.d3_io.port, config.d3_io.pin,{asmr::hal::GPIO::Mode::AltFunc, asmr::hal::GPIO::Type::PushPull, asmr::hal::GPIO::Speed::High, asmr::hal::GPIO::ResistorPull::Down, 12});

    // turn on power
    status = power_on();

    // enable sdio clock;
    SDIO->CLKCR |= SDIO_CLKCR_CLKEN;

    // send GO_IDLE_STATE command
    // TODO return error from here?
    send_cmd(sdio::CMD::GO_IDLE_STATE, 0x0, Response::None);

    // TODO send SD_APP_OP_COND command
    send_cmd(sdio::ACMD::SD_APP_OP_COND, 0x0, Response::Short);

    // TODO other stuff??

    return hal::SDHostCtlr::Status::Ok;
}

asmr::hal::SDHostCtlr::Status asmr::stm32f405::SDHostCtlr::reset() {
    hal::SDHostCtlr::Status status;

    // disable SDIO clock
    SDIO->CLKCR &= ~SDIO_CLKCR_CLKEN;

    // power down
    status = power_off();

    // reset SDIO peripheral
    RCC->APB2RSTR |=  RCC_APB2RSTR_SDIORST; // enable
    RCC->APB2RSTR &= ~RCC_APB2RSTR_SDIORST; // disable

    // disable SDIO APB2 clock
    RCC->APB2ENR &= ~RCC_APB2ENR_SDIOEN;

    // reset GPIO pins
    // TODO store GPIO pins in class

    return hal::SDHostCtlr::Status::Ok;
}

asmr::hal::SDHostCtlr::Status asmr::stm32f405::SDHostCtlr::power_on() {
    SDIO->POWER = 0x11;
    return hal::SDHostCtlr::Status::Ok;
}

asmr::hal::SDHostCtlr::Status asmr::stm32f405::SDHostCtlr::power_off() {
    SDIO->POWER = 0x00;
    return hal::SDHostCtlr::Status::Ok;
}

asmr::hal::SDHostCtlr::Status asmr::stm32f405::SDHostCtlr::initialize_cards() {
    return hal::SDHostCtlr::Status::Ok;
}

asmr::hal::SDHostCtlr::Status asmr::stm32f405::SDHostCtlr::set_clock_speed(asmr::sdio::Speed speed) {
    if (speed == sdio::Speed::Init) SDIO->CLKCR |= ClkDivInit;
    if (speed == sdio::Speed::Tx)   SDIO->CLKCR |= ClkDivTx;

    return hal::SDHostCtlr::Status::Ok;
}

asmr::hal::SDHostCtlr::Status asmr::stm32f405::SDHostCtlr::get_card_info() {
    return hal::SDHostCtlr::Status::Ok;
}

asmr::hal::SDHostCtlr::Status asmr::stm32f405::SDHostCtlr::select_card() {
    return hal::SDHostCtlr::Status::Ok;
}

asmr::hal::SDHostCtlr::Status asmr::stm32f405::SDHostCtlr::enable_wide_bus() {
    return hal::SDHostCtlr::Status::Ok;
}

asmr::hal::SDHostCtlr::Status asmr::stm32f405::SDHostCtlr::read_blocks() {
    return hal::SDHostCtlr::Status::Ok;
}

//:::: Protected
//::::::::::::::

asmr::stm32f405::SDHostCtlr::SDHostCtlr(hal::SDHostCtlr::Config config)
    : config(config)
{

}

void asmr::stm32f405::SDHostCtlr::irq() {
    auto singleton = Instance({});
}

//:::: Private
//::::::::::::

void asmr::stm32f405::SDHostCtlr::send_cmd(uint32_t cmd, uint32_t arg, uint32_t resp) {
    // set command argument register.
    SDIO->ARG = arg;

    // clear command register bits [0:10]
    // [5:0] CMDINDEX
    // [7:6] WAITRESP
    // [8]   WAITINT
    // [9]   WAITPEND
    // [10]  CPSMEN
    uint32_t tmp_cmd = SDIO->CMD & 0xFFFFF800;

    uint32_t enable_cpsm = SDIO_CMD_CPSMEN;  // by default enable CPSM
    uint32_t wait_int    = 0;//SDIO_CMD_WAITINT; // by default don't wait
    uint32_t wait_pend   = 0;//SDIO_CMD_WAITPEND; // by default don't wait

    // set command register.
    tmp_cmd |= cmd;            // command index [5:0]
    tmp_cmd |= resp<<6;        // expected response type [7:6]
    tmp_cmd |= wait_int;       // wait for interrupt [8] ??
    tmp_cmd |= wait_pend;      // wait for transfer complete [9] ??
    tmp_cmd |= enable_cpsm;    // enable CPSM [10]

    SDIO->CMD = tmp_cmd;
}

// void asmr::stm32f405::SDHostCtlr::send_cmd(sdio::CMD cmd, uint32_t arg, Response resp) {
//     send_cmd((uint32_t)cmd, arg, (uint32_t)resp);
// }

// void asmr::stm32f405::SDHostCtlr::send_cmd(sdio::ACMD cmd, uint32_t arg, Response resp) {
//     // send initial APP_CMD to indicate this is an application-specific command.
//     // TODO check for error
//     send_cmd(sdio::CMD::APP_CMD, 0x0, Response::Short);

//     // send application-specific command
//     // TODO check for error
//     send_cmd((uint32_t)cmd, arg, (uint32_t)resp);
// }
