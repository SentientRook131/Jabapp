#include <runtime/Toolkit.hpp>

bool isExists(const String &original, const char target) {
	for (const char i : original) {
		if (target == i) return true;
	}
	return false;
}