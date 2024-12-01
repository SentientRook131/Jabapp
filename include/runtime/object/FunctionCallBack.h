#pragma once
#include <../include/runtime/usings.h>
class FunctionCallBack {
	public:
	FunctionCallBack();
	virtual Object execute(List<Object> arguments) = 0;
};