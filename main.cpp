#include "tuple.h"

int main(int argc, char** argv) {
	CTypeFactory::register_type<int>("int");
	CTypeFactory::register_type<double>("double");

	CTuple tuple(std::list<std::string>{ "int", "double" });
	std::cout << tuple.type(0) << " : " << *(reinterpret_cast<int*>(tuple[0])) << std::endl;

	auto second_val = reinterpret_cast<double*>(tuple[1]);
	*second_val = 0.1;
	std::cout << tuple.type(1) << " : " << *(reinterpret_cast<double*>(tuple[1])) << std::endl;

	return 0;
};
