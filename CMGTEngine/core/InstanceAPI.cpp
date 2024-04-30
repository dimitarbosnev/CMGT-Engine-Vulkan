#pragma once
#include "InstanceAPI.hpp"

namespace cmgt {
	InstanceAPI::InstanceAPI() {}
	InstanceAPI::~InstanceAPI(){
		cout << "API destroyed\n";
	}
}