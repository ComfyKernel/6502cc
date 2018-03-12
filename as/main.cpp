#include <iostream>
#include <iomanip>
#include <fstream>

#include <cstring>
#include <string>

#include <vector>
#include <tuple>

#include <exception>

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

const std::string __addr_name_invalid="[Invalid Name]";

std::string get_addr_name(addr_mode mode) {
  for(const auto& i : __addr_name_table) {
    if(i.second == mode) {
      return i.first;
    }
  }

  return __addr_name_invalid;
}

typedef std::tuple<std::string, addr_mode, unsigned int> _op_pair;

_op_pair _opcodes[]={
  _op_pair("lda", AM_IMMEDIATE , 0xA9),
  _op_pair("lda", AM_ZEROPAGE  , 0xA5),
  _op_pair("lda", AM_ZEROPAGE_X, 0xB5),
  _op_pair("lda", AM_ABSOLUTE  , 0xAD),
  _op_pair("lda", AM_ABSOLUTE_X, 0xBD),
  _op_pair("lda", AM_ABSOLUTE_Y, 0xB9),
  _op_pair("lda", AM_INDIRECT_X, 0xA1),
  _op_pair("lda", AM_INDIRECT_Y, 0xB1)
};

typedef std::tuple<unsigned int, addr_mode, unsigned int, std::string> opcode;

void segment_text(std::ifstream& data, std::vector<std::string>& out);
bool process(std::vector<opcode>& out, std::vector<std::string>& data);

int main(int argc, char *argv[]) {
  std::cout<<"Using AS-6502 : v"<<__V_MAJOR__<<"."<<__V_MINOR__<<"\n";
  
  if(argc < 2) {
    std::cout<<"\e[31mError!\e[0m : No input file!\n";
    return 1;
  }

  bool o_set = false;

  std::string o_file;
  std::string i_file;
  
  for(int i=1; i<argc; ++i) {
    if(strcmp(argv[i], "-o") == 0) {
      if(i + 1 >= argc) {
	std::cout<<"\e[31mError!\e[0m : No output file specified! (-o)\n";
	return 2;
      } else {
	o_file = argv[i + 1];

	o_set = true;
	i++;
      }
    } else {
      i_file = argv[i];

      if(!o_set) {
	o_set = true;

	o_file = i_file.substr(0, i_file.find_last_of(".")) + ".o";
      }
    }
  }

  std::cout<<"Assembling file "<<i_file<<" to "<<o_file<<"\n";

  std::ifstream f_i_file(i_file);
  std::ofstream f_o_file(o_file, std::ios::binary);

  if(!f_i_file.is_open()) {
    std::cout<<"\e[31mError!\e[0m Failed opening file '"<<i_file<<"'\n";
    return 3;
  }

  if(!f_o_file.is_open()) {
    std::cout<<"\e[31mError!\e[0m Cannot write to file '"<<o_file<<"'\n";
    return 4;
  }

  std::vector<std::string> segmented;
  segment_text(f_i_file, segmented);

  std::vector<opcode> opcodes;
  if(!process(opcodes, segmented)) {
    std::cout<<"Preprocessing failed!\n";
    return 5;
  }
  
  f_i_file.close();
  f_o_file.close();
  
  return 0;
}

void segment_text(std::ifstream& data, std::vector<std::string>& out) {
  std::string segment;
  while(data >> segment) {
    for(unsigned int i=0; i<segment.size(); ++i) {
      switch(segment[i]) {
      case ':':
	std::cout<<"[Segment] : "<<segment<<"\n";
	out.push_back(segment.substr(0, i+1));
	break;
      default:
	break;
      }
    }

    std::cout<<"[Segment] : "<<segment<<"\n";
    out.push_back(segment);
  }
}

bool get_number(const std::string& in, int& num, int& length, bool& isaddr) {
  isaddr = true;

  int base = 10;
  int len  = 0;

  std::string numstr = "";
  
  for(const auto& i : in) {
    switch(i) {
    case '#':
      isaddr = false;
      break;
    case '$':
      base = 16;
      break;
    case '%':
      base = 2;
      break;
    default:
      len++;
      numstr += i;
      break;
    }
  }

  length = len;

  try {
    num = std::stoi(numstr, nullptr, base);
  } catch(std::exception& e) {
    return false;
  }

  /*std::cout<<"[Num] '"<<num<<"', Base : '"<<base<<"', Is Address : '"
    <<std::boolalpha<<isaddr<<std::noboolalpha<<"'\n";*/

  return true;
}

bool process(std::vector<opcode>& out, std::vector<std::string>& data) {
  for(unsigned int i=0; i<data.size(); ++i) {
    for(const auto& o : _opcodes) {
      if(std::get<0>(o) == data[i]) {
	// std::cout<<"[Opcode] : "<<std::get<0>(o)<<"\n";

	bool is_addr    = false;
	int  num        = 0;
	int  len        = 0;
	std::string str = "";

	if (!get_number(data[i + 1], num, len, is_addr)) {
	  std::cout<<"\e[31mError!\e[0m Expecting number after '"<<std::get<0>(o)
		   <<"', Instead got '"<<data[i + 1]<<"'\n";
	  return false;
	}

	std::vector<addr_mode> excluded_addrs;

	if(len <= 2) {
	  excluded_addrs.push_back(AM_ABSOLUTE);
	  excluded_addrs.push_back(AM_ABSOLUTE_X);
	  excluded_addrs.push_back(AM_ABSOLUTE_Y);
	} else if(len <= 4) {
	  excluded_addrs.push_back(AM_IMMEDIATE);
	  excluded_addrs.push_back(AM_ACCUMULATOR);
	  excluded_addrs.push_back(AM_ZEROPAGE);
	  excluded_addrs.push_back(AM_ZEROPAGE_X);
	  excluded_addrs.push_back(AM_ZEROPAGE_X);
	  excluded_addrs.push_back(AM_INDIRECT);
	  excluded_addrs.push_back(AM_INDIRECT_X);
	  excluded_addrs.push_back(AM_INDIRECT_Y);
	  excluded_addrs.push_back(AM_IMPLIED);
	} else {
	  std::cout<<"\e[31mError!\e[0m Invalid number length '"<<len<<"'\n";
	}

	if(is_addr) {
	  excluded_addrs.push_back(AM_IMMEDIATE);
	  excluded_addrs.push_back(AM_ACCUMULATOR);
	  excluded_addrs.push_back(AM_IMPLIED);
	} else {
	  excluded_addrs.push_back(AM_RELATIVE);
	  excluded_addrs.push_back(AM_ABSOLUTE);
	  excluded_addrs.push_back(AM_ABSOLUTE_X);
	  excluded_addrs.push_back(AM_ABSOLUTE_Y);
	  excluded_addrs.push_back(AM_ZEROPAGE);
	  excluded_addrs.push_back(AM_ZEROPAGE_X);
	  excluded_addrs.push_back(AM_ZEROPAGE_Y);
	  excluded_addrs.push_back(AM_INDIRECT);
	  excluded_addrs.push_back(AM_INDIRECT_X);
	  excluded_addrs.push_back(AM_INDIRECT_Y);
	}

	addr_mode mode = AM_NONE;

	for(const auto& eo : _opcodes) {
	  if(std::get<0>(eo) == std::get<0>(o)) {
	    bool is_mode = true;
	    
	    for(const auto& e : excluded_addrs) {
	      if(std::get<1>(eo) == e) {
		is_mode = false;
		break;
	      }
	    }

	    if(is_mode) {
	      // std::cout<<"[Mode] '"<<get_addr_name(std::get<1>(eo))<<"'\n";
	      mode = std::get<1>(eo);
	      break;
	    }
	  }
	}

	if(mode == AM_NONE) {
	  std::cout<<"\e[31mError!\e[0m Could not find valid addressing mode for '"
		   <<std::get<0>(o)<<" "<<data[i + 1]<<"'\n";
	  return false;
	}

	std::cout<<"[OP] : '"<<std::get<0>(o)<<"' [OPER] : '"<<num
		 <<"' [OPER2] : '"<<str<<"' [MODE] '"<<get_addr_name(mode)<<"'\n";

	out.push_back(opcode(std::get<2>(o), mode, num, str));
	
	++i;
	break;
      } else {
	std::cout<<"\e[31mError!\e[0m Unknown opcode encountered! '"<<data[i]<<"'\n";
	return false;
      }
    }
  }

  return true;
}
