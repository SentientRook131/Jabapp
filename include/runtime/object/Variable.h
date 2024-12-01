#pragma once
#include <../include/runtime/usings.h>
class Variable {
	private:
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