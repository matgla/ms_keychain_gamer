MEMORY
{
    FLASH (rx)   : ORIGIN = 0x08000000, LENGTH = 64K
    FS_FLASH(rx) : ORIGIN = 0x0800a000, LENGTH = 20K
    RAM (xrw)    : ORIGIN = 0x20000400, LENGTH = 19K
    KERNEL_RAM(rxw)  : ORIGIN = 0x20000000, LENGTH = 1K

}

_heap_size = 0x2500;
_stack_size = 0x1800;

INCLUDE ../../lib/msos/lib/hal/devices/arm/stm32/stm32f1/stm32f10x_common.ld
