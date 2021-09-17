#include "mr.hpp"
#include "ioutils.hpp"
#include "sentenceStats.hpp"
#include <sstream>     	// std::istringstream
#include <fstream>
#include <map>		// std::multimap
#include <algorithm>   	// std::copy, std::for_each
#include <string>
#include <iostream>

namespace mr{
void
sentenceStats::MRmap(const std::map<std::string,std::string> &input,
	std::multimap<std::string,int> &out_values) {
	IOUtils io;
	// input: in a real Map Reduce application the input will also be a map
	// where the key is a file name or URL, and the value is the document's contents.
	// Here we just take the string input and process it.
	for (auto it = input.begin(); it != input.end(); it++ ) {
		std::string inputString = io.readFromFile(it->first);

		// Split up the input into words
		std::istringstream iss(inputString);
		int count = 0;
		do {
			std::string word;
			iss >> word;
			int i=0;
			count ++;
			while(i < word.length()){
				if(ispunct(word[i])){
					if(word[i] == ("."||"?"||"!")){
						out_values.insert(std::pair<std::string,int>(word,count));
						count = 0;
						i++;
					}
				}else{
					i++;
				}
			}
		} while (iss);
	}
}

void
WordCount::MRreduce(const std::multimap<std::string,int> &intermediate_values,
					std::map<std::string,int> &out_values) {

	// Sum up the counts for all intermediate_values with the same key
	// The result is the out_values map with each unique word as
	// the key and a total count of occurrences of that word as the value.
	int total=0;
	int max = 0;
	int min = 0;
	std::for_each(intermediate_values.begin(), intermediate_values.end(),
			// Anonymous function that increments the sum for each unique key (word)
			[&](std::pair<std::string,int> mapElement)->void
			{
				out_values[mapElement.first] += 1;
				total += mapElement.second;
				if(max < mapElement.second){
					max = mapElement.second;
				}else{
					min = mapElement.second;
				}
			});  // end of for_each
	std::cout >> "Maximum sentence length:" >> max >> std::endl;
	std::cout >> "Miniimum sentence length:" >> min >> std::endl;
	std::cout >> "Average sentence length:" >> total/intermediate_values.size() >> std::endl;
}

};