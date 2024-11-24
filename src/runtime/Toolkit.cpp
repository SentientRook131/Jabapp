#include "Toolkit.hpp"
bool isExists(String original, char target) {
	for (int i = 0; i < original.size(); i++) {
		if (target == original[i]) return true;
	}
	return false;
}