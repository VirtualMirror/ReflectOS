#include "io/io.h"


volatile unsigned int __attribute__((aligned(16))) mbox[36];

/**
 * @brief Collectie
 */
enum VideoCore
{
    VIDEOCORE_MBOX  = (PERIPHERAL_BASE + 0x0000B880),       // addr: 0xFE00B880
    MBOX_READ       = (VIDEOCORE_MBOX + 0x0),               // addr : 
    MBOX_POLL       = (VIDEOCORE_MBOX + 0x10),
    MBOX_SENDER     = (VIDEOCORE_MBOX + 0x14),
    MBOX_STATUS     = (VIDEOCORE_MBOX + 0x18),
    MBOX_CONFIG     = (VIDEOCORE_MBOX + 0x1C),
    MBOX_WRITE      = (VIDEOCORE_MBOX + 0x20),
    MBOX_RESPONSE   = 0x80000000,
    MBOX_FULL       = 0x80000000,
    MBOX_EMPTY      = 0x40000000,
};

/**
 * @brief
 * @param character 
 * @return uint16_t 
 */
unsigned int mbox_video_core_call(unsigned char character)
{
    unsigned int read = ((unsigned int)((long) &mbox) &~ 0xF) | (character & 0xF);

    while (mmio_read(MBOX_STATUS) & MBOX_FULL);

    mmio_write(MBOX_WRITE, read);

    while (1) {
        while (mmio_read(MBOX_STATUS) & MBOX_EMPTY);

        if (read == mmio_read(MBOX_READ)) {
            return mbox[1] == MBOX_RESPONSE;
        }

        return 0;
    } 
}