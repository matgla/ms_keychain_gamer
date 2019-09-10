#include <iostream>
#include <thread>
#include <string>


#include <simavr/avr_ioport.h>
#include <simavr/sim_avr.h>
#include <simavr/sim_elf.h>

int main()
{
    elf_firmware_t elf;
    const char* filename = "ms_keychain_gamer.elf";

    elf_read_firmware(filename, &elf);
    int frequency = 8000000;
    std::string mmcu = "attiny85";
    std::cout << "Loading firmware: " << filename << std::endl
        << "frequency: " << frequency << std::endl
        << "mcu: " << mmcu << std::endl;

    elf.frequency = frequency;
    avr_t* avr = avr_make_mcu_by_name(mmcu.c_str());
    if (!avr)
    {
        std::cout << "AVR not known: " << mmcu;
    }
    avr_init(avr);
    avr_load_firmware(avr, &elf);
    avr_irq_register_notify(
        avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ('B'), 3),
        [](struct avr_irq_t * irq, uint32_t value, void * param) { std::cerr << "LED state changed!" << std::endl; },
        NULL);

    while (true)
    {
        avr_run(avr);
    }
}