#ifndef AS_6502_SEGMENTER_HPP
#define AS_6502_SEGMENTER_HPP

#include <vector>
#include <string>
#include <fstream>

void segment(std::vector<std::string>& out,
	     std::ifstream& file);

#endif
