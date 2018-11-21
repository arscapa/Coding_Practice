/*
Write the following program: Create a struct that holds a student’s first name and grade (on a scale of 0-100). Ask the user how many students they want to enter. Dynamically allocate an array to hold all of the students. Then prompt the user for each name and grade. Once the user has entered all the names and grade pairs, sort the list by grade (highest first). Then print all the names and grades in sorted order.

For the following input:

Joe
82
Terry
73
Ralph
4
Alex
94
Mark
88
The output should look like this:

Alex got a grade of 94
Mark got a grade of 88
Joe got a grade of 82
Terry got a grade of 73
Ralph got a grade of 4

*/

#include <iostream>
#include <cstring>

struct Student
{
	std::string name;
	int grade;
};

void printData(struct Student *s, int length)
	{
		int a;
		for(a=0; a<length; a++)
		{
			std::cout << "Name of student " << a+1 << " = " << s->name << std::endl;
			std::cout << "Grade of student " << a+1 << " = " <<  s->grade << std::endl;
		};
	}


int main()
{	
	std::cout << "How many students would you like to enter? " << std::endl;
	int numStudents;
	std::cin >> numStudents;
	
	Student *students = new Student[numStudents];
	
	int i;
	for(i=0; i<numStudents; i++)
	{
		std::cout << "Enter name of student " << i+1 << std::endl;
		std::cin >> students[i].name;
		std::cout << "Enter grade of student " << i+1 << std::endl;
		std::cin >> students[i].grade;
	};
	
	printData(students,numStudents);
	
		
	delete[] students;
	
	return 0;
	
}



