#include <iostream>
#include <iomanip>
#include <fstream>

#include <cstring>
#include <string>

#include <vector>
#include <tuple>

#include <exception>

#include "addressing.hpp"
#include "opcodes.hpp"

bool verbose_logging = false;

typedef std::tuple<unsigned int, addr_mode, unsigned int, std::string> opcode;

void segment_text(std::ifstream& data, std::vector<std::string>& out);
bool process(std::vector<opcode>& out, std::vector<std::string>& data);
bool compile(std::ofstream& out, std::vector<opcode>& opcodes);

int main(int argc, char *argv[]) {
  std::cout<<"Using AS-6502 : v"<<__V_MAJOR__<<"."<<__V_MINOR__<<"\n";
  
  if(argc < 2) {
    std::cout<<"\e[31mError!\e[0m : No input file!\n";
    return 1;
  }

  bool o_set = false,
       c_set = false;

  std::string o_file, o_ext;
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
    } else if(strcmp(argv[i], "-v") == 0 ||
	      strcmp(argv[i], "--verbose") == 0) {
      verbose_logging = true;
      
    } else if(strcmp(argv[i], "-c") == 0) {
      c_set = true;
      o_ext = ".o";
    } else {
      i_file = argv[i];
    }
  }

  if(!c_set) {
    o_ext = ".bin";
  }

  if(!o_set) {
    o_file = i_file.substr(0, i_file.find_last_of(".")) + o_ext;
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

  if(!compile(f_o_file, opcodes)) {
    std::cout<<"Compilation failed!\n";
    return 6;
  }
  
  f_i_file.close();
  f_o_file.close();

  std::cout<<"\e[32mSuccess!\e[0m\n";
  
  return 0;
}

void segment_text(std::ifstream& data, std::vector<std::string>& out) {
  std::string segment;
  while(data >> segment) {
    for(unsigned int i=0; i<segment.size(); ++i) {
      switch(segment[i]) {
      case ':':
	if(verbose_logging) {
	  std::cout<<"[Segment] : "<<segment<<"\n";
	}
	out.push_back(segment.substr(0, i+1));
	break;
      default:
	break;
      }
    }

    if(verbose_logging) {
      std::cout<<"[Segment] : "<<segment<<"\n";
    }
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

  if(verbose_logging) {
    std::cout<<"[Num] '"<<num<<"', Base : '"<<base<<"', Is Address : '"
	     <<std::boolalpha<<isaddr<<std::noboolalpha<<"'\n";
  }

  return true;
}

bool process(std::vector<opcode>& out, std::vector<std::string>& data) {
  for(unsigned int i=0; i<data.size(); ++i) {
    bool opcode_found = false;
    
    for(const auto& o : _opcodes) {
      if(std::get<0>(o) == data[i]) {
	// std::cout<<"[Opcode] : "<<std::get<0>(o)<<"\n";
	opcode_found = true;
	
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

	if(verbose_logging) {
	  std::cout<<"[OP] : '"<<std::get<0>(o)<<" (0x"<<std::hex<<std::get<2>(o)<<std::dec
		   <<")' [OPER] : '"<<num<<"' [OPER2] : '"<<str<<"' [MODE] '"
		   <<get_addr_name(mode)<<"'\n";
	}

	out.push_back(opcode(std::get<2>(o), mode, num, str));
	
	++i;
	break;
      }
    }

    if(!opcode_found) {
      std::cout<<"\e[31mError!\e[0m Unknown opcode encountered! '"<<data[i]<<"'\n";
      return false;
    }
  }

  return true;
}

bool compile(std::ofstream& out, std::vector<opcode>& opcodes) {
  int8_t val;
  
  for(const auto& i : opcodes) {
    val = std::get<0>(i) & 0xFF;
    out.write((char*)&val, sizeof(int8_t));

    switch(std::get<1>(i)) {
    case AM_ABSOLUTE:
    case AM_ABSOLUTE_X:
    case AM_ABSOLUTE_Y:
    case AM_INDIRECT:
      val = std::get<2>(i) & 0xFF;
      out.write((char*)&val, sizeof(int8_t));
      val = (std::get<2>(i) & 0xFF00) >> 8;
      out.write((char*)&val, sizeof(int8_t));
      break;
    default:
      val = std::get<2>(i) & 0xFF;
      out.write((char*)&val, sizeof(int8_t));
    }
  }

  return true;
}
