#ifndef AS_ADDRESSING_HPP
#define AS_ADDRESSING_HPP

#include <string>

enum addr_mode {
  AM_IMMEDIATE   = 0x0,
  AM_ACCUMULATOR = 0x1,
  AM_IMPLIED     = 0x2,
  AM_RELATIVE    = 0x3,
  AM_ABSOLUTE    = 0x4,
  AM_ABSOLUTE_X  = 0x5,
  AM_ABSOLUTE_Y  = 0x6,
  AM_ZEROPAGE    = 0x7,
  AM_ZEROPAGE_X  = 0x8,
  AM_ZEROPAGE_Y  = 0x9,
  AM_INDIRECT    = 0xA,
  AM_INDIRECT_X  = 0xB,
  AM_INDIRECT_Y  = 0xC,
  AM_NONE        = 0xD
};

std::string get_addr_name(addr_mode);

#endif
