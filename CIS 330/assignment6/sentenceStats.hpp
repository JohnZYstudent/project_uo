#ifndef SENTENCESTATS_HPP_
#define SENTENCESTATS_HPP_

#include <fstream>
#include <string>
#include <map>
#include "mr.hpp"

namespace mr {

class sentenceStats : public MapReduce<std::string,int> {
public:
	virtual void MRmap(const std::map<std::string,std::string> &input,
			std::multimap<std::string,int> &out_values);
	virtual void MRreduce(const std::multimap<std::string,int> &intermediate_values,
			std::map<std::string,int> &out_values);
};

} 
#endif 