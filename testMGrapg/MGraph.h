#ifndef MGRAPH_H_
#define MGRAPH_H_

//����vector��ģ�壬����ĺ���breadthFirstTraverseImpl(vector<int> preVec)���õ�

#include <vector>
#include "Node.h"
#include "Edge.h"

using namespace std;
class MGraph
{
public:
	MGraph(int capacity);           //���캯��������ͼ
	~MGraph();                      //��������������ͼ
	bool addNode(Node *pNode);    //���ӽڵ�
	void resetNode();             //���ýڵ�ķ���״̬Ϊδ����
								  //������ͼ���ڽӾ����Ԫ������ֵ
	bool setValueToMatrixForDirectedGraph(int row, int col, int val = 1);
	//������ͼ���ڽӾ����Ԫ������ֵ
	bool setValueToMatrixForUndirectedGraph(int row, int col, int val = 1);

	void printMartrix();          //��ӡ�ڽӾ���

	void depthFirstTraverse(int nodeIndex);              //������ȱ���
	void breadthFirstTraverse(int nodeIndex);            //������ȱ���
	void miniSpanTree_prim(int nodeIndex);
	void miniSpanTree_Kruskal();
	void shortPath_Dijkstra(int being_node);

private:
	bool getValueFromMatrix(int row, int col, int &val);   //��ȡ�ڽӾ�����Ԫ�ص�ֵ
														   //������ȱ����Ĺ��ߺ����������洢ĳһ���Ԫ��
	void breadthFirstTraverseImpl(vector<int> preVec);

	int getMinEdge(vector<Edge> cedgevec);

	bool isInSet(vector<int> nodeSet, int target);

	void mergeNodeSet(vector<int> &nodeSetA, vector<int> nodeSetB);
private:
	int m_iCapacity;               //ͼ�Ľڵ������                                
	int m_iNodeCount;              //ͼ��ǰ�Ľڵ������
	Node *m_pNodeArray;            //ָ��ͼ���׽ڵ��ָ��
	int *m_pMatrix;                //ָ���ڽӾ�����Ԫ�ص�ָ��
	vector <Edge> edgevec;		   //�߼�����
	vector<Edge> m_pEdge;				   //��С�������ߵ�ָ��
};

#endif