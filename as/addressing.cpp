#include "addressing.hpp"

typedef std::pair<std::string, addr_mode> __addr_name;

__addr_name __addr_name_table[]={
  __addr_name("immediate"  , AM_IMMEDIATE),
  __addr_name("accumulator", AM_ACCUMULATOR),
  __addr_name("implied"    , AM_IMPLIED),
  __addr_name("relative"   , AM_RELATIVE),
  __addr_name("absolute"   , AM_ABSOLUTE),
  __addr_name("absolute x" , AM_ABSOLUTE_X),
  __addr_name("absolute y" , AM_ABSOLUTE_Y),
  __addr_name("zero page"  , AM_ZEROPAGE),
  __addr_name("zero page x", AM_ZEROPAGE_X),
  __addr_name("zero page y", AM_ZEROPAGE_Y),
  __addr_name("indirect"   , AM_INDIRECT),
  __addr_name("indirect x" , AM_INDIRECT_X),
  __addr_name("indirect y" , AM_INDIRECT_Y),
  __addr_name("none"       , AM_NONE)
};

const std::string __addr_name_invalid = "[Invalid Name]";

std::string get_addr_name(addr_mode mode) {
  for(const auto& i : __addr_name_table) {
    if(i.second == mode) {
      return i.first;
    }
  }

  return __addr_name_invalid;
}
