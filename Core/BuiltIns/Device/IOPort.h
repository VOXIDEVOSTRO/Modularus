#pragma once

#include <__KCONF.h>

static inline void outb(uint16_t Port, uint8_t Value)
{
    __asm__ volatile ("outb %0, %1" : : "a"(Value), "Nd"(Port));
}

static inline uint8_t inb(uint16_t Port)
{
    uint8_t Return;
    __asm__ volatile ("inb %1, %0" : "=a"(Return) : "Nd"(Port));
    return Return;
}

static inline void outw(uint16_t Port, uint16_t Value)
{
    __asm__ volatile ("outw %0, %1" : : "a"(Value), "Nd"(Port));
}

static inline uint16_t inw(uint16_t Port)
{
    uint16_t Return;
    __asm__ volatile ("inw %1, %0" : "=a"(Return) : "Nd"(Port));
    return Return;
}

static inline void outl(uint16_t Port, uint32_t Value)
{
    __asm__ volatile ("outl %0, %1" : : "a"(Value), "Nd"(Port));
}

static inline uint32_t inl(uint16_t Port)
{
    uint32_t Return;
    __asm__ volatile ("inl %1, %0" : "=a"(Return) : "Nd"(Port));
    return Return;
}
