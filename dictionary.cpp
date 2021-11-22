#include "dictionary.h"
#include <iostream>

int main()
{

	nwacc::map<int,std::string>student;

	//20 keys and names
	student.put(5, "cathy");
	student.put(7, "lisa");
	student.put(9, "baxter");
	student.put(8, "kevin");
	student.put(27, "megan");
	student.put(12, "sam");
	student.put(2, "edgar");
	student.put(3, "jessy");


	student.print();

	std::cout << std::endl;


	//const iterator 


	std::cout << "out putting with iteraor" << std::endl;
	auto itr = student.begin();

	std::cout << *itr << " " << -itr << std::endl;//use iterator to display all values
	for (auto index = 0; index < 8; index++)
	{

		++itr;
		std::cout << *itr << " " << -itr << std::endl;
	}

	std::cout << std::endl;

	

	if (student.contains_key(9) == true)
	{
		std::cout << "9 is included" << std::endl;
	}

	if (student.contains_key(2) == true)
	{
		std::cout << "2 is included" << std::endl;
	}

	if (student.contains_value("megan") == true)
	{
		std::cout << "megan is included" << std::endl;
	}

	if (student.contains_value("cathy") == true)
	{
		std::cout << "cathy is included" << std::endl;
	}

	std::cout << "remove key 2" << std::endl;

	student.remove_key(2);
	student.print();

	std::cout << std::endl;
	std::cout <<"remove value megan" << std::endl;

	student.remove_value("megan");
	student.print();

	std::cout << std::endl;

	std::cout << "using get key '7' method" << std::endl;

	std::cout << student.get_key(7) << std::endl;

	std::cout << std::endl;

	std::cout << "using [3] operator" << std::endl;

	auto value = student[3];

	std::cout << value << std::endl;




	
};
