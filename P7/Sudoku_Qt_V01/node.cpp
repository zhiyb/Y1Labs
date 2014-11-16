#include "node.h"

Node::Node(int row)
{
	for (int i = 0; i < 4; i++)
		d[i] = this;
	r = row;
}

Node *Node::connect(const Directions dir, Node *p)
{
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
	if (r == -1) {
		d[Left]->d[Right] = d[Right];
		d[Right]->d[Left] = d[Left];
	} else {
		d[Up]->d[Down] = d[Down];
		d[Down]->d[Up] = d[Up];
	}
	return this;
}

Node *Node::coverColumn(void)
{
	Node *row = this;
	while (row->r != -1)
		row = row->d[Up];
	row->disconnect();			// Disconnect column node
	for (row = row->d[Down]; row->r != -1; row = row->d[Down])
		for (Node *col = row->d[Right]; col != row; col = col->d[Right])
			col->disconnect();	// Disconnect nodes in the row
	return this;
}

Node *Node::reconnect(void)
{
	if (r == -1) {
		d[Left]->d[Right] = this;
		d[Right]->d[Left] = this;
	} else {
		d[Up]->d[Down] = this;
		d[Down]->d[Up] = this;
	}
	return this;
}

Node *Node::unCoverColumn(void)
{
	Node *row = this;
	while (row->r != -1)
		row = row->d[Up];
	row->reconnect();			// Reconnect column node
	for (row = row->d[Up]; row->r != -1; row = row->d[Up])
		for (Node *col = row->d[Left]; col != row; col = col->d[Left])
			col->reconnect();	// Reconnect nodes in the row
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
	Node *col = this;
	do {
		col->unCoverColumn();
		col = col->d[Left];
	} while (col != this);
	return this;
}
