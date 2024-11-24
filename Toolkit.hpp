#pragma once
#include "usings.h"
bool isExists(String, char);
template<typename T, size_t size>
bool isExists(Array<T, size> original, T target) {
	for (int i = 0; i < original.size(); i++) {
		if (target == original[i]) return true;
	}
	return false;
}