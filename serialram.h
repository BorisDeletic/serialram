#ifndef SERIALRAM_H
#define SERIALRAM_H

#include "config.h"

#if defined(SERIALRAM_USESPIFIFO) && (!defined(__arm__) || !defined(CORE_TEENSY))
#undef SERIALRAM_USESPIFIFO // only do SPIFIFO on teensy arm boards
#endif

class CSerialRam
{
    enum EInstruction
    {
        INSTR_READ = 0x03,
        INSTR_WRITE = 0x02,
        INSTR_RDMR = 0x05,
        INSTR_WRMR = 0x01
    };

    enum
    {
        SEQUENTIAL_MODE = 0x40,
#if defined(__MK20DX128__)
        SPIFIFO_SIZE = 4
#elif defined(__MK20DX256__)
        SPIFIFO_SIZE = 8
#endif
    };

    bool largeAddressing;
    uint8_t chipSelect;

    void initTransfer(EInstruction instruction);
    void endTransfer(void);
    inline uint8_t sendByteMore(uint8_t byte) __attribute__((always_inline));
    inline uint8_t sendByteNoMore(uint8_t byte) __attribute__((always_inline));
    void sendAddress(uint32_t address);

public:
    enum ESPISpeed { SPEED_FULL, SPEED_HALF, SPEED_QUARTER };

    void begin(bool la, uint8_t pin, ESPISpeed speed);
    void end(void) { }

    void read(char *buffer, uint32_t address, uint32_t size);
    void write(const char *buffer, uint32_t address, uint32_t size);
};

#endif // SERIALRAM_H