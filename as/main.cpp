#include <iostream>
#include <fstream>

#include <cstring>
#include <string>

#include <vector>

std::vector<std::string> process_text(std::ifstream& data);

int main(int argc, char *argv[]) {
  std::cout<<"Using AS-6502 : v"<<__V_MAJOR__<<"."<<__V_MINOR__<<"\n";
  
  if(argc < 2) {
    std::cout<<"\e[31mError!\e[0m : No input file!\n";
    return 1;
  }

  bool o_set = false;

  std::string o_file;
  std::string i_file;
  
  for(unsigned int i=1; i<argc; ++i) {
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
  
  std::vector<std::string> processed = process_text(f_i_file);
  
  f_i_file.close();
  f_o_file.close();
  
  return 0;
}

std::vector<std::string> process_text(std::ifstream& data) {
  std::vector<std::string> _out;

  std::string segment;
  while(data >> segment) {
    std::cout<<"[Segment] : "<<segment<<"\n";
    _out.push_back(segment);
  }
  
  return _out;
}
