#include "cipher.hpp"
#include "date.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <iterator>
// Single-argument constructor
DateCipher::DateCipher() : Cipher(),date(){
    std::string datetext;
    std::cout << "Enter the date DD/MM/YY:" << std::endl;
    std::cin >> datetext;
    for(int i=0;i<datetext.length();i++){
        if(datetext[i] != '/'){
            date += datetext[i];
        }
    }
}


// Overloaded encrypt method
std::string
DateCipher::encrypt( std::string &inputText ) {
    std::string text = inputText;
    std::string::size_type len = text.length();
    std::string datecode[len];
    int index = 0; 
    for(int i = 0;i <= len;i++){
        if(text[i] == ' '){
            datecode[i] = ' ';
        }else if(text[i]>='a'&&text[i]<='z' || text[i]>='A'&&text[i]<='Z'){
            if(index%6 == 0){
                datecode[i] = date[0];
                index += 1;                
            }else{
                datecode[i] = date[index%6];
                index += 1;
            }
        }
    }

	for (int i = 0; i != len; ++i) {
        if(text[i]>='a'&&text[i]<='z'){
            int shift= atoi(datecode[i].c_str());
            int index = text[i] - 'a';
            int max = 25 - index;
            //std::cout << text[i] <<":"<< shift<< ":" << index<<":" << max << std::endl;
            if(shift > max){
                text[i] = 'a' + shift - max - 1;
            }else{
                text[i] += shift;
            }
        }
        if(text[i]>='A'&&text[i]<='Z'){
            int shift= atoi(datecode[i].c_str());
            int index = text[i] - 'A';
            int max = 25 - index;
            //std::cout << text[i] <<":"<< shift<< ":" << index<<":" << max << std::endl;
            if(shift > max){
                text[i] = 'A' + shift - max - 1;
            }else{
                text[i] += shift;
            }
        }
	}
	return text;
}

std::string
DateCipher::decrypt( std::string &inputText ) {
    std::string text = inputText;
    std::string::size_type len = text.length();
    std::string datecode[len];
    int index = 0; 
    for(int i = 0;i <= len;i++){
        if(text[i] == ' '){
            datecode[i] = ' ';
        }else if(text[i]>='a'&&text[i]<='z' || text[i]>='A'&&text[i]<='Z'){
            if(index%6 == 0){
                datecode[i] = date[0];
                index += 1;                
            }else{
                datecode[i] = date[index%6];
                index += 1;
            }
        }
    }

    for (int i = 0; i != len; ++i) {
        if(text[i]>='a'&&text[i]<='z'){
            int shift= atoi(datecode[i].c_str());
            int index = text[i] - 'a';
            int max = index;
            //std::cout << text[i] <<":"<< shift<< ":" << index<<":" << max << std::endl;
            if(shift > max){
                text[i] = 'z' - (shift - max - 1);
            }else{
                text[i] -= shift;
            }
        }
        if(text[i]>='A'&&text[i]<='Z'){
            int shift= atoi(datecode[i].c_str());
            int index = text[i] - 'A';
            int max = index;
            //std::cout << text[i] <<":"<< shift<< ":" << index<<":" << max << std::endl;
            if(shift > max){
                text[i] = 'Z' + shift - max - 1;
            }else{
                text[i] -= shift;
            }
        }
    }
    return text;
}