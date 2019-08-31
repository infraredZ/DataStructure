#ifndef MGRAPH_H_
#define MGRAPH_H_

//包含vector类模板，后面的函数breadthFirstTraverseImpl(vector<int> preVec)会用到

#include <vector>
#include "Node.h"
#include "Edge.h"

using namespace std;
class MGraph
{
public:
	MGraph(int capacity);           //构造函数，创建图
	~MGraph();                      //析构函数，销毁图
	bool addNode(Node *pNode);    //增加节点
	void resetNode();             //重置节点的访问状态为未访问
								  //给有向图的邻接矩阵的元素设置值
	bool setValueToMatrixForDirectedGraph(int row, int col, int val = 1);
	//给无向图的邻接矩阵的元素设置值
	bool setValueToMatrixForUndirectedGraph(int row, int col, int val = 1);

	void printMartrix();          //打印邻接矩阵

	void depthFirstTraverse(int nodeIndex);              //深度优先遍历
	void breadthFirstTraverse(int nodeIndex);            //广度优先遍历
	void miniSpanTree_prim(int nodeIndex);
	void miniSpanTree_Kruskal();
	void shortPath_Dijkstra(int being_node);

private:
	bool getValueFromMatrix(int row, int col, int &val);   //获取邻接矩阵中元素的值
														   //广度优先遍历的工具函数，用来存储某一层的元素
	void breadthFirstTraverseImpl(vector<int> preVec);

	int getMinEdge(vector<Edge> cedgevec);

	bool isInSet(vector<int> nodeSet, int target);

	void mergeNodeSet(vector<int> &nodeSetA, vector<int> nodeSetB);
private:
	int m_iCapacity;               //图的节点的容量                                
	int m_iNodeCount;              //图当前的节点的数量
	Node *m_pNodeArray;            //指向图中首节点的指针
	int *m_pMatrix;                //指向邻接矩阵首元素的指针
	vector <Edge> edgevec;		   //边集数组
	vector<Edge> m_pEdge;				   //最小生成树边的指针
};

#endif