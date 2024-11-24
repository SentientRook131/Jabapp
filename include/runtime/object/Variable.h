#pragma once
#include "usings.h"
class Variable {
	private:
	String name;
	String type;
	Object value;
	public:
	Variable(String, String, Object);
	String getName();
	String getType();
	Object getValue();
	void setValue(Object);
};