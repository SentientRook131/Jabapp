#pragma once
#include <usings.h>
class Variable {
	String name;
	String type;
	Object value;
	public:
	Variable(const String &, const String &, const Object &);
	String getName();
	String getType();
	Object getValue();
	void setValue(const Object &);
};