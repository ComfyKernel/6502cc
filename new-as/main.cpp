#include <iostream>
#include <utility>

#include "segmenter.hpp"

std::ostream& perror() {
  std::cout<<"\e[31;1mError!\e[0m ";
  return std::cout;
}

std::string in_file,
	    out_file;

bool out_set = false;



void _af_name(int& argi, int argc, char *argv[]) {
  out_file = argv[argi + 1];
  out_set  = true;
  argi++;
};

void _af_obj(int& argi, int argc, char *argv[]) {
  out_file = in_file.substr(0, in_file.find_last_of('.') - 1);
  out_set  = true;
};

typedef void(*_arg_func)(int&,int,char**);
typedef std::pair<std::string,_arg_func> _arg_pair;

std::vector<_arg_pair> _arg_funcs;

int main(int argc, char *argv[]) {
  std::cout<<"Running 6502-AS v."
	   <<__P_VER_MAJOR<<"."
	   <<__P_VER_MINOR<<"\n";

  if(argc <= 1) {
    perror()<<"No arguments provided!\n";
    return 1;
  }

  _arg_funcs.push_back(_arg_pair("-o", _af_name));
  _arg_funcs.push_back(_arg_pair("-c", _af_obj));

  for(int i=0; i<argc; ++i) {
    bool matched=false;
    
    for(int f=0; f<_arg_funcs.size(); ++f) {
      if(_arg_funcs[f].first == argv[i]) {
	_arg_funcs[f].second(i, argc, argv);
	matched=true;
      }
    }

    if(!matched) {
      in_file = argv[i];
    }
  }

  std::ifstream file(in_file);

  if(!file.is_open()) {
    perror()<<"Could not open file '"<<in_file<<"'\n";
    return 2;
  }
  
  return 0;
}
