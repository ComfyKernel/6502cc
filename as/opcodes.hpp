#ifndef AS_OPCODES_HPP
#define AS_OPCODES_HPP

#include <tuple>
#include <string>

#include "addressing.hpp"

typedef std::tuple<std::string, addr_mode, unsigned int> _op_pair;

_op_pair _opcodes[]={
  _op_pair("adc", AM_IMMEDIATE  , 0x69),
  _op_pair("adc", AM_ZEROPAGE   , 0x65),
  _op_pair("adc", AM_ZEROPAGE_X , 0x75),
  _op_pair("adc", AM_ABSOLUTE   , 0x6D),
  _op_pair("adc", AM_ABSOLUTE_X , 0x7D),
  _op_pair("adc", AM_ABSOLUTE_Y , 0x79),
  _op_pair("adc", AM_INDIRECT_X , 0x61),
  _op_pair("adc", AM_INDIRECT_Y , 0x71),

  _op_pair("and", AM_IMMEDIATE  , 0x29),
  _op_pair("and", AM_ZEROPAGE   , 0x25),
  _op_pair("and", AM_ZEROPAGE_X , 0x35),
  _op_pair("and", AM_ABSOLUTE   , 0x2D),
  _op_pair("and", AM_ABSOLUTE_X , 0x3D),
  _op_pair("and", AM_ABSOLUTE_Y , 0x39),
  _op_pair("and", AM_INDIRECT_X , 0x21),
  _op_pair("and", AM_INDIRECT_Y , 0x31),

  _op_pair("asl", AM_ACCUMULATOR, 0x0A),
  _op_pair("asl", AM_ZEROPAGE   , 0x06),
  _op_pair("asl", AM_ZEROPAGE_X , 0x16),
  _op_pair("asl", AM_ABSOLUTE   , 0x0E),
  _op_pair("asl", AM_ABSOLUTE_X , 0x1E),

  _op_pair("bit", AM_ZEROPAGE   , 0x24),
  _op_pair("bit", AM_ABSOLUTE   , 0x2C),

  _op_pair("bpl", AM_RELATIVE   , 0x10),
  _op_pair("bmi", AM_RELATIVE   , 0x30),
  _op_pair("bvc", AM_RELATIVE   , 0x50),
  _op_pair("bvs", AM_RELATIVE   , 0x70),
  _op_pair("bcc", AM_RELATIVE   , 0x90),
  _op_pair("bcs", AM_RELATIVE   , 0xB0),
  _op_pair("bne", AM_RELATIVE   , 0xD0),
  _op_pair("beq", AM_RELATIVE   , 0xF0),

  _op_pair("brk", AM_IMPLIED    , 0x00),

  _op_pair("cmp", AM_IMMEDIATE  , 0xC9),
  _op_pair("cmp", AM_ZEROPAGE   , 0xC5),
  _op_pair("cmp", AM_ZEROPAGE_X , 0xD5),
  _op_pair("cmp", AM_ABSOLUTE   , 0xCD),
  _op_pair("cmp", AM_ABSOLUTE_X , 0xDD),
  _op_pair("cmp", AM_ABSOLUTE_Y , 0xD9),
  _op_pair("cmp", AM_INDIRECT_X , 0xC1),
  _op_pair("cmp", AM_INDIRECT_Y , 0xD1),

  _op_pair("cpx", AM_IMMEDIATE  , 0xE0),
  _op_pair("cpx", AM_ZEROPAGE   , 0xE4),
  _op_pair("cpx", AM_ABSOLUTE   , 0xEC),

  _op_pair("cpy", AM_IMMEDIATE  , 0xC0),
  _op_pair("cpy", AM_ZEROPAGE   , 0xC4),
  _op_pair("cpy", AM_ABSOLUTE   , 0xCC),

  _op_pair("dec", AM_ZEROPAGE   , 0xC6),
  _op_pair("dec", AM_ZEROPAGE_X , 0xD6),
  _op_pair("dec", AM_ABSOLUTE   , 0xCE),
  _op_pair("dec", AM_ABSOLUTE_X , 0xDE),

  _op_pair("eor", AM_IMMEDIATE  , 0x49),
  _op_pair("eor", AM_ZEROPAGE   , 0x45),
  _op_pair("eor", AM_ZEROPAGE_X , 0x55),
  _op_pair("eor", AM_ABSOLUTE   , 0x4D),
  _op_pair("eor", AM_ABSOLUTE_X , 0x5D),
  _op_pair("eor", AM_ABSOLUTE_Y , 0x59),
  _op_pair("eor", AM_INDIRECT_X , 0x41),
  _op_pair("eor", AM_INDIRECT_Y , 0x51),

  _op_pair("clc", AM_IMPLIED    , 0x18),
  _op_pair("sec", AM_IMPLIED    , 0x38),
  _op_pair("cli", AM_IMPLIED    , 0x58),
  _op_pair("sei", AM_IMPLIED    , 0x78),
  _op_pair("clv", AM_IMPLIED    , 0xB8),
  _op_pair("cld", AM_IMPLIED    , 0xD8),
  _op_pair("sed", AM_IMPLIED    , 0xF8),

  _op_pair("inc", AM_ZEROPAGE   , 0xE6),
  _op_pair("inc", AM_ZEROPAGE_X , 0xF6),
  _op_pair("inc", AM_ABSOLUTE   , 0xEE),
  _op_pair("inc", AM_ABSOLUTE_X , 0xFE),

  _op_pair("jmp", AM_ABSOLUTE   , 0x4C),
  _op_pair("jmp", AM_INDIRECT   , 0x6C),

  _op_pair("jsr", AM_ABSOLUTE   , 0x20),
  
  _op_pair("lda", AM_IMMEDIATE  , 0xA9),
  _op_pair("lda", AM_ZEROPAGE   , 0xA5),
  _op_pair("lda", AM_ZEROPAGE_X , 0xB5),
  _op_pair("lda", AM_ABSOLUTE   , 0xAD),
  _op_pair("lda", AM_ABSOLUTE_X , 0xBD),
  _op_pair("lda", AM_ABSOLUTE_Y , 0xB9),
  _op_pair("lda", AM_INDIRECT_X , 0xA1),
  _op_pair("lda", AM_INDIRECT_Y , 0xB1),
  
  _op_pair("ldx", AM_IMMEDIATE  , 0xA2),
  _op_pair("ldx", AM_ZEROPAGE   , 0xA6),
  _op_pair("ldx", AM_ZEROPAGE_Y , 0xB6),
  _op_pair("ldx", AM_ABSOLUTE   , 0xAE),
  _op_pair("ldx", AM_ABSOLUTE_Y , 0xBE),

  _op_pair("ldy", AM_IMMEDIATE  , 0xA0),
  _op_pair("ldy", AM_ZEROPAGE   , 0xA4),
  _op_pair("ldy", AM_ZEROPAGE_X , 0xB4),
  _op_pair("ldy", AM_ABSOLUTE   , 0xAC),
  _op_pair("ldy", AM_ABSOLUTE_X , 0xBC),

  _op_pair("lsr", AM_ACCUMULATOR, 0x4A),
  _op_pair("lsr", AM_ZEROPAGE   , 0x46),
  _op_pair("lsr", AM_ZEROPAGE_X , 0x56),
  _op_pair("lsr", AM_ABSOLUTE   , 0x4E),
  _op_pair("lsr", AM_ABSOLUTE_X , 0x5E),

  _op_pair("nop", AM_IMPLIED    , 0xEA),

  _op_pair("ora", AM_IMMEDIATE  , 0x09),
  _op_pair("ora", AM_ZEROPAGE   , 0x05),
  _op_pair("ora", AM_ZEROPAGE_X , 0x15),
  _op_pair("ora", AM_ABSOLUTE   , 0x0D),
  _op_pair("ora", AM_ABSOLUTE_X , 0x1D),
  _op_pair("ora", AM_ABSOLUTE_Y , 0x19),
  _op_pair("ora", AM_INDIRECT_X , 0x01),
  _op_pair("ora", AM_INDIRECT_Y , 0x11),

  _op_pair("tax", AM_IMPLIED    , 0xAA),
  _op_pair("txa", AM_IMPLIED    , 0x8A),
  _op_pair("dex", AM_IMPLIED    , 0xCA),
  _op_pair("inx", AM_IMPLIED    , 0xE8),
  _op_pair("tay", AM_IMPLIED    , 0xA8),
  _op_pair("tya", AM_IMPLIED    , 0x98),
  _op_pair("dey", AM_IMPLIED    , 0x88),
  _op_pair("iny", AM_IMPLIED    , 0xC8),

  _op_pair("rol", AM_ACCUMULATOR, 0x2A),
  _op_pair("rol", AM_ZEROPAGE   , 0x26),
  _op_pair("rol", AM_ZEROPAGE_X , 0x36),
  _op_pair("rol", AM_ABSOLUTE   , 0x2E),
  _op_pair("rol", AM_ABSOLUTE_X , 0x3E),

  _op_pair("ror", AM_ACCUMULATOR, 0x6A),
  _op_pair("ror", AM_ZEROPAGE   , 0x66),
  _op_pair("ror", AM_ZEROPAGE_X , 0x76),
  _op_pair("ror", AM_ABSOLUTE   , 0x6E),
  _op_pair("ror", AM_ABSOLUTE_X , 0x7E),

  _op_pair("rti", AM_IMPLIED    , 0x40),

  _op_pair("rts", AM_IMPLIED    , 0x60),

  _op_pair("sbc", AM_IMMEDIATE  , 0xE9),
  _op_pair("sbc", AM_ZEROPAGE   , 0xE5),
  _op_pair("sbc", AM_ZEROPAGE_X , 0xF5),
  _op_pair("sbc", AM_ABSOLUTE   , 0xED),
  _op_pair("sbc", AM_ABSOLUTE_X , 0xFD),
  _op_pair("sbc", AM_ABSOLUTE_Y , 0xF9),
  _op_pair("sbc", AM_INDIRECT_X , 0xE1),
  _op_pair("sbc", AM_INDIRECT_Y , 0xF1),
  
  _op_pair("sta", AM_ZEROPAGE   , 0x85),
  _op_pair("sta", AM_ZEROPAGE_X , 0x95),
  _op_pair("sta", AM_ABSOLUTE   , 0x8D),
  _op_pair("sta", AM_ABSOLUTE_X , 0x9D),
  _op_pair("sta", AM_ABSOLUTE_Y , 0x99),
  _op_pair("sta", AM_INDIRECT_X , 0x81),
  _op_pair("sta", AM_INDIRECT_Y , 0x91),

  _op_pair("txs", AM_IMPLIED    , 0x9A),
  _op_pair("tsx", AM_IMPLIED    , 0xBA),
  _op_pair("pha", AM_IMPLIED    , 0x48),
  _op_pair("pla", AM_IMPLIED    , 0x68),
  _op_pair("php", AM_IMPLIED    , 0x08),
  _op_pair("plp", AM_IMPLIED    , 0x28),
  
  _op_pair("stx", AM_ZEROPAGE   , 0x86),
  _op_pair("stx", AM_ZEROPAGE_Y , 0x96),
  _op_pair("stx", AM_ABSOLUTE   , 0x8E),

  _op_pair("sty", AM_ZEROPAGE   , 0x84),
  _op_pair("sty", AM_ZEROPAGE_X , 0x94),
  _op_pair("sty", AM_ABSOLUTE   , 0x8C),
};

#endif
