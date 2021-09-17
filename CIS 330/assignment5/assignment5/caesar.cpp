#include "cipher.hpp"
#include "caesar.hpp"
#include <iostream>
// Single-argument constructor
CaesarCipher::CaesarCipher() : Cipher(), shiftnum(){
	std::cout << "Please set the shiftnum:" << std::endl;
    std::cin >> shiftnum;

}


// Overloaded encrypt method
std::string
CaesarCipher::encrypt( std::string &inputText ) {
	std::string text = inputText;
	std::string::size_type len = text.length();
    int shift;
	for (int i = 1; i < len; ++i) {
        if(text[i]>='a'&&text[i]<='z' || text[i] == ' '){
            shift = shiftnum % 27; 
            int index = text[i]-'a';
            int max = 26-index;
            if(text[i] == ' '){
                if(shift >= 1){
                    text[i] = 'a'+ (shift-1);
                }else{
                    text[i] += shift;
                }
            }else{
                if (shift > max){
                    text[i] = 'a' + (shift - max - 1);
                }else{
                    if(shift == max){
                        text[i] = ' ';
                    }else{
                        text[i] += shift;      
                    }
                } 
            }
        }

        if(text[i]>='A'&&text[i]<='Z'){
            shift = shiftnum % 26;
                int index = text[i]-'A';
                int max = 25-index;
                if (shiftnum > max) {
                    text[i] = 'A' + (shiftnum - max - 1);
                } else {
                    text[i] += shiftnum;
                }           
        }    
	}
	return text;
}

std::string
CaesarCipher::decrypt( std::string &inputText) {
	std::string text = inputText;
    std::string::size_type len = text.length();
    int shift;
    for (int i = 1; i < len; ++i) {
        if(text[i]>='a'&&text[i]<='z' || text[i] == ' '){
            shift = shiftnum % 27; 
            int index = text[i]-'a';
            int max = index;
            if(text[i] == ' '){
                if(shift >= 1){
                    text[i] = 'z'- (shift-1);
                }else{
                    text[i] -= shift;
                }
            }else{
                if (shift > max){
                    if(shift-max == 1){
                        text[i] = ' ';
                    }else{
                        text[i] = 'z' - (shift - max - 1);
                    }
                }else{
                    if(shift == max){
                        text[i] = 'a';
                    }else{
                        text[i] -= shift;      
                    }
                } 
            }
        }

        if(text[i]>='A'&&text[i]<='Z'){
            shift = shiftnum % 26;
                int index = text[i]-'A';
                int max = index;
                if (shiftnum > max) {
                    text[i] = 'Z' - (shiftnum - max - 1);
                } else {
                    text[i] -= shiftnum;
                }           
        }    
    }
    return text;
}