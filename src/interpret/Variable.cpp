#include <runtime/object/Variable.h>
#include <runtime/usings.h>

Variable::Variable(const String &name, const String &type, const Object &value) {
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
void Variable::setValue(const Object &value) { this->value = value; }
