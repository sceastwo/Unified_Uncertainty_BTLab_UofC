

#include <cstdlib>
#include <iostream>

#include "variables.h"
#include "simple_expression.h"
#include "causal_network.h"

//#define __TESTING_VARIABLES__
#define __TESTING_TOKEN_READ__

void testing()
{
#ifdef __TESTING_VARIABLES__
	variable_list::add_variable("A", 4);
	variable_list::add_variable("B", 2);
	variable_list::add_variable("C", 3);
	std::cout << variable_list::has_variable("A") << ' ' 
			  << variable_list::has_variable("B") << ' ' 
			  << variable_list::has_variable("C") << ' ' 
			  << variable_list::has_variable("D") << '\n';
	std::cout << variable_list::get_domain_size("A") << ' '
			  << variable_list::get_domain_size("B") << ' '
			  << variable_list::get_domain_size("C") << '\n';
	variable_list::remove_variable("B");
	std::cout << variable_list::has_variable("B") << '\n';
	variable_list::reset_list();
	for (uint16 i = 1; i <= 100; i++)
	{
		variable_list::add_variable("X" + to_string(i), 2 + (i % 4));
	}
	for (uint16 i = 1; i <= 100; i++)
	{
		std::cout << variable_list::has_variable("X" + to_string(i)) << ' ' 
				  << variable_list::has_variable("Y" + to_string(i)) << ' '
				  << variable_list::get_domain_size("X" + to_string(i)) << '\n';
	}

#endif

#ifdef __TESTING_TOKEN_READ__
	{
		ifstream input("read_token_test.txt");
		string curr_token = "";
		do
		{
			curr_token = read_token(input);
			std::cout << "\n********\n";
			std::cout << curr_token;
			std::cout << "\n********";
		} while (curr_token != "");
	}
#endif

}

int main()
{
	variable_list::initialize_list();

	//std::cout << sizeof(short) << ' ' << sizeof(long) << '\n';
	//std::cout << sizeof(uint16) << ' ' << sizeof(uint32) << '\n';

	testing();

	/*simple_expression** exp_list = new simple_expression*[10];
	exp_list[0]->num_of_vars = 4;
	std::cout << exp_list[0]->num_of_vars << '\n';
	exp_list[1] = new null_expression();*/


	system("PAUSE");
	return EXIT_SUCCESS;
}

