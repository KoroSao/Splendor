#include "type.h"

namespace Splendor{
    std::initializer_list<Type> Types = {Type::nobles, Type::cite, Type::un, Type::deux, Type::trois};


    std::string toString(Type c) {
		switch (c) {
		case Type::nobles: return "Noble";
		case Type::cite: return "Cite";
		case Type::un: return "I";
		case Type::deux: return "II";
		case Type::trois: return "III";

		default: throw SplendorException("Type inconnue");
		}
	}

}
