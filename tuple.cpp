#include "tuple.h"

CTypeFactory::types_map CTypeFactory::m_types;

CTuple::CTuple(const std::list<std::string>& types) {
	for (auto type : types) {
		auto new_val = CTypeFactory::create(type);
		if (new_val == nullptr) {
			std::cerr << "This type is not supported. Supported types: " << std::endl
				  << CTypeFactory::get_supported() << std::endl;
		}
		else {
			m_types.push_back(new_val);
		}
	}
}

void* CTuple::operator[](int index) {
	if (index >= 0 && index < m_types.size()) {
		return m_types[index]->value();
	}
	return NULL;
}

std::string CTuple::type(int index) const {
	if (index >= 0 && index < m_types.size()) {
		return m_types[index]->get_type();
	}
	return "No such element";
}
