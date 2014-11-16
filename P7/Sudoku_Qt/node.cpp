#include "node.h"

Node::Node(int val)
{
	for (int i = 0; i < 5; i++)
		d[i] = this;
	v = val;
}

#define DELETED	(~(((int)-1) >> 1))
Node::~Node(void)
{
	if (d[Down]->v >= 0)
		delete d[Down];
	if (v < 0) {
		v = DELETED;
		if (d[Right]->v != DELETED)
			delete d[Right];
	}
}

Node *Node::connect(const Directions dir, Node *p)
{
	if (dir == Top) {
		d[Top] = p;
		p->v--;		// Count up
		return p;
	}
	int prev = (dir % 2) ? dir - 1 : dir + 1, next = dir;
	p->d[prev] = this;
	p->d[next] = this->d[next];
	p->d[prev]->d[next] = p;
	p->d[next]->d[prev] = p;
	return p;
}

Node *Node::next(const Directions dir, const int count)
{
	if (!count)
		return this;
	return d[dir]->next(dir, count - 1);
}

Node *Node::disconnect(void)
{
	if (v < 0) {
		if (d[Left]->d[Right] != this || d[Right]->d[Left] != this)
			return this;
		d[Left]->d[Right] = d[Right];
		d[Right]->d[Left] = d[Left];
	} else {
		if (d[Up]->d[Down] != this || d[Down]->d[Up] != this)
			return this;
		d[Up]->d[Down] = d[Down];
		d[Down]->d[Up] = d[Up];
	}
	d[Top]->v++;		// Count down
	return this;
}

Node *Node::coverColumn(void)
{
	Node *top = v < 0 ? this : d[Top];
	top->disconnect();			// Disconnect column node
	for (Node *row = top->d[Down]; row != top; row = row->d[Down])
		for (Node *col = row->d[Right]; col != row; col = col->d[Right])
			col->disconnect();	// Disconnect nodes in the row
	return this;
}

Node *Node::reconnect(void)
{
	if (v < 0) {
		if (d[Left]->d[Right] == this && d[Right]->d[Left] == this)
			return this;
		d[Left]->d[Right] = this;
		d[Right]->d[Left] = this;
	} else {
		if (d[Up]->d[Down] == this && d[Down]->d[Up] == this)
			return this;
		d[Up]->d[Down] = this;
		d[Down]->d[Up] = this;
	}
	d[Top]->v--;		// Count up
	return this;
}

Node *Node::unCoverColumn(void)
{
	Node *top = v < 0 ? this : d[Top];
	for (Node *row = top->d[Up]; row != top; row = row->d[Up])
		for (Node *col = row->d[Left]; col != row; col = col->d[Left])
			col->reconnect();	// Reconnect nodes in the row
	top->reconnect();			// Reconnect column node
	return this;
}

Node *Node::coverRow(void)
{
	Node *col = this;
	do {
		col->coverColumn();
		col = col->d[Right];
	} while (col != this);
	return this;
}

Node *Node::unCoverRow(void)
{
	Node *col = d[Left];
	do {
		col->unCoverColumn();
		col = col->d[Left];
	} while (col != d[Left]);
	return this;
}
