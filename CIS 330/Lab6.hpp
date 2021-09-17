#include <iostream>
#include <string>
class Student{
	public:
		void setfirstName(string firstName);
		void setlastName(String lastName);
		bool setAge(int age);
		string getfirstName();
		string getlastName();
		int getAge();
			
	private:
		string firstName;
		string lastName;
		int age;
}