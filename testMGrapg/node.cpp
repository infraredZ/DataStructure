#include "Node.h"

Node::Node(char data)
{
	m_cData = data;
	m_bIsVisited = false;    //默认为该节点没有被访问过
}