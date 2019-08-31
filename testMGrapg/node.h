#ifndef NODE_H_
#define NODE_H_

class Node
{
public:
	Node(char data = 0); //节点的构造函数
	char m_cData;         //节点的数据域
	bool m_bIsVisited;   //标记该节点是否被访问过
};

#endif
