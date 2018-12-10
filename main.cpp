#include <iostream>
#include "darkvortex.h"

int main()
{
    std::string line(" abcd efgh  \n k \n ");
    std::string r = string_strip(line);
    std::cout << "-" << r << "-" << std::endl;
	std::cout << "finished...\n";
}
