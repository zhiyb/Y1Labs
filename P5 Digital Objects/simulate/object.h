#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

class object
{
public:
	object(object *parent = 0);
	virtual ~object(void);
	void addChild(object *obj) {children.push_back(obj);}
	virtual void update(void) {updateChildren();}

protected:
	virtual void updateChildren(void);

private:
	std::vector<object *> children;
};

#endif // OBJECT_H
