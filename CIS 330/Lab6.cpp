#include <iostream>
#include <string>
#include "Lab6.hpp"
class Student{
	 void setfirstName(string first){
	 	Student.firstName = first;
	 }

	 void setlastName(string last){
	 	Student.lastName = last;
	 }

	 bool setAge(int age){
	 	if(age >= 0){
	 		Student.age = age;
	 		return true;
	 	}else{
	 		return false;
	 	}
	 }

	 string getfirstName(){
	 	return Student.firstName;
	 }

	 string getlastName(){
	 	return Student.lastName;
	 }

	 int getAge(){
	 	return Student.age;
	 }
}