#ifndef CAESAR_HPP_
#define CAESAR_HPP_

#include "cipher.hpp"

class CaesarCipher : public Cipher {
public:
    CaesarCipher(); // constructor

	// Default destructor 
    
	virtual std::string encrypt( std::string &text );
	virtual std::string decrypt( std::string &text );
private:
	int shiftnum;
};

#endif