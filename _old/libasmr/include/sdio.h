#ifndef ASMR_SDIO_H
#define ASMR_SDIO_H

#include <cstdint>

// see https://yannik520.github.io/sdio.html

namespace asmr {
    namespace sdio {

        //:::: Card Commands
        //::::::::::::::::::

        struct CommandFrame {
            unsigned int start         : 1; // = 0
            unsigned int transmission  : 1; // = 1
            unsigned int command_index : 6;
            uint32_t     argument;
            unsigned int crc7          : 7;
            unsigned int end           : 1; // = 1
        };

        //:::: General Commands
        enum class CMD {
            GO_IDLE_STATE        = 0,         // Class 0 (basic)
            ALL_SEND_CID         = 2,         //      :
            SEND_RELATIVE_ADDR   = 3,         //      :
            SET_DSR              = 4,         //      :
            TOGGLE_CARD_SELECT   = 7,         //      :
            SEND_IF_COND         = 8,         //      :
            SEND_CSD             = 9,         //      :
            SEND_CID             = 10,        //      :
            STOP_TRANSMISSION    = 12,        //      :
            SEND_STATUS          = 13,        //      :
            GO_INACTIVE_STATE    = 15,        //      :
            SET_BLOCKLEN         = 16,        // Class 2 (Block-Oriented Read)
            READ_SINGLE_BLOCK    = 17,        //      :
            READ_MULTIPLE_BLOCK  = 18,        //      :
            WRITE_BLOCK          = 24,        // Class 4 (Block-Oriented Write)
            WRITE_MULTIPLE_BLOCK = 25,        //      :
            PROGRAM_CSD          = 27,        //      :
            APP_CMD              = 55,
        };

        //:::: Application-specific Commands
        // note: must be preceded by a APP_CMD (CMD55)
        enum class ACMD {
            SD_STATUS            = 13,
            SD_APP_OP_COND       = 41,
        };



        // TODO commands
        //

        //:::: Card Modes & States
        //::::::::::::::::::::::::

        enum class OperationMode {
            Inactive,
            CardIdentification,
            DataTransfer,
        };

        enum class CardState {
            Inactive,                // Inactive Mode
            Idle,                    // Identification Mode
            Ready,                   //        :
            Identification,          //        :
            Standby,                 // Data Transfer Mode
            Transfer,                //        :
            SendingData,             //        :
            ReceivingData,           //        :
            Programming,             //        :
            Disconnect,              //        :
        };

        enum class Speed {
            Init,
            Tx,
        };

        //:::: Card Responses
        //:::::::::::::::::::

        namespace Response {
            // Normal Response [48 bits]
            struct R1 {
                unsigned int start         : 1; // = 0
                unsigned int transmission  : 1; // = 0
                unsigned int command_index : 6;
                uint32_t     card_status;
                unsigned int crc7          : 7;
                unsigned int end           : 1; // = 1
            };

            // Card Identification/Specific Data (CID/CSD) [136 bits]
            struct R2 {
                unsigned int start         : 1; // = 0
                unsigned int transmission  : 1; // = 0
                unsigned int reserved      : 6; // = '0b111111'
                uint32_t     card_data[4];
                unsigned int crc7          : 7;
                unsigned int end           : 1; // = 1
            };

            // Operation Condition Register (OCR) [48 bits]
            struct R3 {
                unsigned int start         : 1; // = 0
                unsigned int transmission  : 1; // = 0
                unsigned int reserved1     : 6; // = '0b111111'
                uint32_t     op_cond;
                unsigned int reserved2     : 7; // = '0b1111111'
                unsigned int end           : 1; // = 1
            };

            // Published Relative Card Address (RCA) [48 bits]
            struct R6 {
                unsigned int start         : 1; // = 0
                unsigned int transmission  : 1; // = 0
                unsigned int command_index : 6; // = '0b000011'
                uint16_t     card_address;
                uint16_t     card_status;
                unsigned int crc7          : 7;
                unsigned int end           : 1; // = 1
            };

            // Card Interface Condition [48 bits]
            struct R7 {
                unsigned int start         : 1; // = 0
                unsigned int transmission  : 1; // = 0
                unsigned int command_index : 6; // = '0b001000'
                uint16_t     reserved1;
                unsigned int reserved2     : 4;
                unsigned int accepted_volts: 4;
                uint8_t      echo_back;
                unsigned int crc7          : 7;
                unsigned int end           : 1; // = 1
            };
        }

    }
}

#endif
