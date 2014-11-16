#ifndef NODE_H
#define NODE_H

class Node
{
	//friend class DancingLinks;
	//friend class Matrix;

public:
	enum Directions {Up = 0, Down = 1, Left = 2, Right = 3, Top = 4};

	Node(int val);
	~Node(void);
	// Insert node 'p' at 'dir' direction
	Node *connect(const Directions dir, Node *p);
	// Find the 'count'th nodes at 'dir' direction
	Node *next(const Directions dir, const int count);
	Node *disconnect(void);
	Node *coverColumn(void);
	Node *reconnect(void);
	Node *unCoverColumn(void);
	Node *coverRow(void);
	Node *unCoverRow(void);
	int value(void) const {return v;}
	Node *to(const Directions dir) const {return d[dir];}

private:
	int v;
	Node *d[5];
};

#endif // NODE_H
