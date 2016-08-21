#include "object.h"
#include <iostream>

object::object(object *parent)
{
	children.clear();
	if (parent != 0)
		parent->addChild(this);
}

object::~object(void)
{
	//std::cerr << "object.deconstructor()" << std::endl;
	while (children.size() > 0) {
		delete children.back();
		children.pop_back();
	}
}

void object::updateChildren(void)
{
	for (std::vector<object *>::size_type i = 0; i < children.size(); i++) {
		children[i]->update();
		children[i]->updateChildren();
	}
}
