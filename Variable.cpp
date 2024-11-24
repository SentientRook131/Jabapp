#include "Variable.h"

Variable::Variable(String name, String type, Object value) {
	this->name = name;
	this->type = type;
	this->value = value;
}
String Variable::getName() {
	return name;
}
String Variable::getType() {
	return type;
}
Object Variable::getValue() {
	return value;
}
void Variable::setValue(Object value) { this->value = value; }
