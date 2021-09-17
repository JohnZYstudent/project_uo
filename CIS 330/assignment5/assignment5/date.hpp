#ifndef DATE_HPP_
#define DATE_HPP_
#include <iostream>
#include <string>
#include "cipher.hpp"

class DateCipher : public Cipher {
public:
    DateCipher(); // constructor

	// Default destructor 
    
	virtual std::string encrypt( std::string &text );
	virtual std::string decrypt( std::string &text );
private:
	std::string date;
};

#endif /* ROT13CIPHER_HPP_ */