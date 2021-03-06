// EPOS LM3S811 (ARM Cortex-M3) UART Mediator Declarations

#ifndef __sifive_e_uart_h
#define __sifive_e_uart_h

#include <machine/uart.h>
#include <machine/riscv/engine/ns16550a.h>
#include <system/memory_map.h>

__BEGIN_SYS

class UART_Engine: public UART_Common
{
private:
    static const unsigned int UNITS = Traits<UART>::UNITS;

public:
    UART_Engine(unsigned int unit, unsigned int baud_rate, unsigned int data_bits, unsigned int parity, unsigned int stop_bits): _unit(unit), _ns16550a(new(reinterpret_cast<void *>(Memory_Map::UART_BASE)) NS16550A) {
        assert(unit < UNITS);
        _unit = unit;
        _ns16550a = new(reinterpret_cast<void *>(Memory_Map::UART_BASE)) NS16550A;
        config(baud_rate, data_bits, parity, stop_bits);
    }

    void config(unsigned int baud_rate, unsigned int data_bits, unsigned int parity, unsigned int stop_bits) {
        _ns16550a->config(baud_rate, data_bits, parity, stop_bits);
    }

    void config(unsigned int * baud_rate, unsigned int * data_bits, unsigned int * parity, unsigned int * stop_bits) {
        _ns16550a->config(baud_rate, data_bits, parity, stop_bits);
    }

    char rxd() { return _ns16550a->rxd(); }
    void txd(char c) { return _ns16550a->txd(c); }

    bool rxd_ok() { return _ns16550a->rxd_ok(); }
    bool txd_ok() { return _ns16550a->txd_ok(); }

    void int_enable(bool receive = true, bool transmit = true, bool line = true, bool modem = true) {
        _ns16550a->int_enable(receive, transmit, line, modem);
    }
    void int_disable(bool receive = true, bool transmit = true, bool line = true, bool modem = true) {
        _ns16550a->int_disable(receive, transmit, line, modem);
    }

    void reset() { _ns16550a->reset(); }
    void loopback(bool flag) { _ns16550a->loopback(flag); }

    void power(const Power_Mode & mode) {}

    static void init() {}

private:
    unsigned int _unit;
    NS16550A * _ns16550a;
};

__END_SYS

#endif
