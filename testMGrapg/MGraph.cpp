#include "MGraph.h"
#include <iostream>
#include "queue"
#include <time.h>
#include <algorithm>
using namespace std;
MGraph::MGraph(int capacity)
{
	m_iCapacity = capacity;
	m_iNodeCount = 0;
	m_pNodeArray = new Node[m_iCapacity];
	m_pMatrix = new int[m_iCapacity*m_iCapacity];   //�ڽӾ���
	//��ʼ������
	for (int i = 0; i < m_iCapacity*m_iCapacity; i++)
	{
		m_pMatrix[i] = 65535;
	}
}

MGraph::~MGraph()
{
	delete [] m_pNodeArray;         //���ͷŽڵ�����Ӧ���ڴ�
	delete [] m_pMatrix;            //���ͷ��ڽӾ�������Ӧ���ڴ�
}

bool MGraph::addNode(Node * pNode)
{
	if (pNode == nullptr)
	{
		return false;
	}
	m_pNodeArray[m_iNodeCount] = pNode->m_cData;
	m_iNodeCount++;
	return true;
}

void MGraph::resetNode()
{
	for (int i=0;i<m_iNodeCount;i++)
	{
		m_pNodeArray[i].m_bIsVisited = false;  
	}
}

bool MGraph::setValueToMatrixForDirectedGraph(int row, int col, int val)
{
	return false;
}
//���������ڽӾ�����row�У�col�е�Ԫ������ֵ,Ĭ����1
bool MGraph::setValueToMatrixForUndirectedGraph(int row, int col, int val)
{	
	//������
	if (row < 0 || row >= m_iCapacity)
	{
		return false;
	}
	if (col < 0 || col >= m_iCapacity)
	{
		return false;
	}
	m_pMatrix[row*m_iCapacity + col] = val;
	m_pMatrix[col*m_iCapacity + row] = val;//�������ڽӾ���
	Edge pedge(row,col,val);
	edgevec.push_back(pedge);   //�����߼�����
	return true;
}

void MGraph::printMartrix()
{
	for (int i = 0; i < m_iCapacity; i++)
	{
		for (int k = 0; k < m_iCapacity; k++)
		{
			cout << m_pMatrix[i*m_iCapacity + k] << " ";
		}
		cout << endl;                        //ÿ��ӡm_iCapacity��Ԫ�ػ�һ��
	}
}

void MGraph::depthFirstTraverse(int nodeIndex)
{
	int value = 0;
	cout << m_pNodeArray[nodeIndex].m_cData << " ";//��ӡ�ڵ�����
	m_pNodeArray[nodeIndex].m_bIsVisited = true;
	for (int i = 0;i<m_iCapacity;i++)     //i=0����ͨ���ԣ�����ͬʱ��������ͼ��i = nodeindex �����Ż�������ͼ
	{
		getValueFromMatrix(nodeIndex, i, value);  //�ڽӾ����еľ���ֵ����value
		if (value != 0)  //��ʾnodeIndex��������Ľڵ�������Ϊi�Ľڵ�����ֻ�� 01 �� 1  ��Ȩ���ӵ�ͼ
		{
			if (m_pNodeArray[i].m_bIsVisited)
			{
				continue;  //������ʹ���
			}
			else
			{
				depthFirstTraverse(i);   //�ݹ����������
			}
		}
		else
		{
			continue;   //
		}
	}
}

void MGraph::breadthFirstTraverse(int nodeIndex)
{
//�ݹ�ķ�����
// 	cout << m_pNodeArray[nodeIndex].m_cData << " ";
// 	m_pNodeArray[nodeIndex].m_bIsVisited = true;
// 	vector<int> curVec;
// 	curVec.push_back(nodeIndex);
// 	breadthFirstTraverseImpl(curVec);

//�ǵݹ�ķ���
	int i, j; //iΪ�ڽӱ��row  j :col
	int value;
	queue <int> Q;

	/* ��0 - m_iCapacity��ÿһ�㶼��ʼһ�顣
	*	����֤�˲���ͨ��ͼҲ���Է����ꡣ
	*/
	//for (i=0;i<m_iCapacity;i++)    
	
//	{
		if (!m_pNodeArray[nodeIndex].m_bIsVisited)
		{
			m_pNodeArray[nodeIndex].m_bIsVisited = true;
			cout << m_pNodeArray[nodeIndex].m_cData << " ";
			Q.push(nodeIndex);
			while (!Q.empty())
			{
				i=Q.front();  //���ʶ��еĵ�һ��Ԫ��
				Q.pop();
				for (j=0;j<m_iCapacity;j++)    //j = 0 Ҳ��Ϊ������ͼ�ı�����
				{
					getValueFromMatrix(i, j, value);   //value ����Ȩֵ��
					if (value &&!m_pNodeArray[j].m_bIsVisited)
					{
						m_pNodeArray[j].m_bIsVisited = true;
						cout << m_pNodeArray[j].m_cData << " ";
						Q.push(j);
					}
				}
			}
		}
	//}


}
/*********************************
* �ʺϱ߶࣬����ͼ��
*
*********************************/
void MGraph::miniSpanTree_prim(int nodeIndex)
{
	/*****************************/
	clock_t start, finish;
	double duration;
	/***************************/
	int i, j, k,n, m,sum=0;
	int value;
	int min;
	vector<int> adjvex;
	vector<int> lowcost;
// 	vector<int> tempcost; //��ʱ����һ�¸���Ȩֵ
// 	vector<int> tempvex; //��ʱ����һ�¸���������±�
	adjvex.push_back(nodeIndex);
	m_pNodeArray[nodeIndex].m_bIsVisited = true;
	n = m_iCapacity - 1;  //ֻ��Ҫ8����
	start = clock();

	while (n--)
	{
		min = 65535;
		for (i = 0; i < adjvex.size(); ++i)    //ѭ���Ѿ����������е��������������
		{
			
			m = adjvex.at(i);
			
			for (j = 0; j < m_iCapacity; j++)   //����ѡ���˳��һ����ABC...
			{	
				getValueFromMatrix(m, j, value);
				if (value < min&& !m_pNodeArray[j].m_bIsVisited && value != 0)
				{
// 					tempcost.push_back(value);
// 					tempvex.push_back(j);//�����±� 
					min = value;
					k = j;
				}
			}
		}
		i = 0;
// 		auto minvalue = min_element(begin(tempcost), end(tempcost));    //�ҳ���С�� ����϶�����һֱ����һ����Сֵ����
// 		k = tempvex.at(distance(begin(tempcost), minvalue));
		m_pNodeArray[k].m_bIsVisited = true;   //��������Ѿ������˵Ķ��㡣
		lowcost.push_back(min);  //�����lowcost��
		adjvex.push_back(k);  //������Сֵ���±ꣻ
/*		cout<< *minvalue << " ";*/
		cout << min << " ";
// 		tempvex.clear();  //���
// 		tempcost.clear();
	}
	cout << endl;
	for (auto c : lowcost)
	{
		sum = sum + c;
	}
	cout << "Prim�㷨������ͻ��ѣ�" << sum << endl;
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "��ʱ��" << duration;
}

void MGraph::miniSpanTree_Kruskal()
{
	int edgecount = 0;
	int sum= 0;
	vector <vector<int>> nodeSets;     //��ά����  ��һάΪһ����������ͨ�򣬶�άΪÿһ����ͨ�������еĶ�����

	while (edgecount < m_iCapacity - 1) //8���߾ͽ����㷨
	{
		int minEdgeIndex = getMinEdge(edgevec);
		edgevec.at(minEdgeIndex).m_bSelected = true;// ���ֵ�������ˡ�
		int nodeAIndex = edgevec.at(minEdgeIndex).m_begin;
		int nodeBIndex = edgevec.at(minEdgeIndex).m_end;
		bool nodeAIsSet = false;
		bool nodeBIsSet = false;
		int nodeAInsetLabel = -1;
		int nodeBInsetLabel = -1;
		for (int i = 0; i<nodeSets.size();i++)
		{
			nodeAIsSet = isInSet(nodeSets[i], nodeAIndex);   //ͷ�ڵ��ڽڵ�(�Ѿ�ѡ��)�ļ�����
			if (nodeAIsSet)
			{
				nodeAInsetLabel = i;   //�ж�ͷ�ڵ����ĸ���ͨ����
			}
		}
		for (int i = 0; i < nodeSets.size(); i++)
		{
			nodeBIsSet = isInSet(nodeSets[i], nodeBIndex);   //β�ڵ�
			if (nodeBIsSet)
			{
				nodeBInsetLabel = i;  //�ж�β�ڵ����ĸ���ͨ����
			}
		}
		//�����ߵĽڵ㶼�����κ�һ����ͨ����
		if (nodeAInsetLabel == -1 && nodeBInsetLabel == -1)  
		{
			vector <int> vec;
			vec.push_back(nodeAIndex);
			vec.push_back(nodeBIndex);
			nodeSets.push_back(vec);//������һ����ͨ��
		}
		// β�ڵ���һ����ͨ���У�ͷ�ڵ㲻�ڡ���Ϊ�������������ˣ����Ծ���һ����ͨ������
		else if (nodeAInsetLabel == -1 && nodeBInsetLabel != -1)  
		{
			nodeSets[nodeBInsetLabel].push_back(nodeAIndex);
		}
		// β�ڵ���һ����ͨ���У�ͷ�ڵ㲻�ڡ���Ϊ�������������ˣ����Ծ���һ����ͨ������
		else if (nodeAInsetLabel != -1 && nodeBInsetLabel == -1)
		{
			nodeSets[nodeAInsetLabel].push_back(nodeBIndex);
		}
		//�����ڵ�ֱ��ڲ�ͬ����ͨ����Ϊ�����ߣ������һ����ͨ��
		else if (nodeAInsetLabel != -1 && nodeBInsetLabel != -1 && nodeAInsetLabel != nodeBInsetLabel)
		{
			//��β�ڵ����ڵ���ͨ��ϲ���ͷ�ڵ����ڵ���ͨ����
			mergeNodeSet(nodeSets[nodeAInsetLabel], nodeSets[nodeBInsetLabel]);
			
			for (int k = nodeBInsetLabel;k<nodeSets.size()-1;k++)
			{
				nodeSets[k] = nodeSets[k + 1]; //k ��β�ڵ㡣�ѵ�k+1����ͨ���ֵ��ֵ��K����ͨ��
			}
			//��������ͨ��ķ�Χ��������ͨ����٣�����ûִ��
		}
		//ͷβ�ڵ㶼��һ����ͨ���С���������㱻������
		else if (nodeAInsetLabel!=-1&&nodeBInsetLabel!=-1 && nodeAInsetLabel == nodeBInsetLabel)
		{
			continue;  //���ܽ�����ڵ���뵽nodeSets
		}
		m_pEdge.push_back(edgevec[minEdgeIndex]);
		edgecount++;
		cout << edgevec[minEdgeIndex].m_begin << "--" << edgevec[minEdgeIndex].m_end << "   ";
		cout << edgevec[minEdgeIndex].m_weight << endl;
	}
	for (auto c:m_pEdge)
	{
		sum = sum + c.m_weight;
	}
	cout << "Kruskal�㷨������ͻ��ѣ�" << sum << endl;

}

void MGraph::shortPath_Dijkstra(int being_node)
{
	//1.����ʼ�ڵ㿪ʼ������ɢ���ҵ���С�ĵ㣬Ȼ�����С����������
	int finalvalue[9];
	int flag[9];//�ҵ���־�ļ�¼
	int value = 0;
	int w=0 ; //�±��¼
	int min = 0;
	
	for (int i = 0;i<m_iCapacity;i++)
	{
		getValueFromMatrix(being_node, i, value);
		finalvalue[i] = value; //��ʼ������  //�����ӵĵľ�Ȩֵ��
		flag[i] = 0;
	}
	finalvalue[being_node] = 0;//��ʼ��Ͳ�������
	flag[being_node] = 1; //�Լ��Ͳ��ٲ�����
	for (int i =1;i<m_iCapacity;i++)
	{
		min = 65535;
		for (int j = 0;j<m_iCapacity;j++)
		{
			if (flag[j]==0 && finalvalue[j]<min)
			{
				min = finalvalue[j];//�ҵ���������е���Сֵ
				w = j;
			}
		}
		flag[w] = 1; //�ҵ�����С��ֵ
		for (int k = 0;k<m_iCapacity;k++)   //�����ķ������ǣ��Ӹ�������ȥ�����������Ӿ���ɹ�
		{
			getValueFromMatrix(w, k, value);
			if (flag[k]==0 && finalvalue[k]>min+value)
			{
				finalvalue[k] =  min + value;
			}
		}
	}
	cout << "����:" << endl;
	for (int i=0;i<m_iCapacity;i++)
	{
		cout << finalvalue[i] << " ";
	}

	
}




bool MGraph::getValueFromMatrix(int row, int col, int & val)
{
	if (row < 0 || row >= m_iCapacity)
	{
		return false;
	}
	if (col < 0 || col >= m_iCapacity)
	{
		return false;
	}
	val = m_pMatrix[row*m_iCapacity + col];
	return true;
}

void MGraph::breadthFirstTraverseImpl(vector<int> preVec)
{
	int value = 0;
	vector<int> curVec;
	for (int j =0;j<(int)preVec.size();j++)
	{
		for (int i =0;i<m_iCapacity;i++)
		{
			getValueFromMatrix(preVec[j], i, value);
			if (value != 0)
			{
				if (m_pNodeArray[i].m_bIsVisited)
				{
					continue;
				}
				else
				{
					cout << m_pNodeArray[i].m_cData << " ";
					m_pNodeArray[i].m_bIsVisited = true;
					curVec.push_back(i);				//��¼��ǰ�ڵ������Ľڵ�
				}
			}
		}
	}
	if (curVec.size() == 0)
	{
		return;
	}
	else
	{
		breadthFirstTraverseImpl(curVec);    //��ǰ�ڵ������ɺ󣬵ݹ����߼�¼�Ľڵ�
	}
}



int MGraph::getMinEdge(vector<Edge> cedgevec)
{
	int edgeIndex = 0;
	int minWeight = cedgevec.at(0).m_weight;   //��Сֵ��ʼ��Ϊ��һ��ֵ
	int i ;
	for (i =0;i<cedgevec.size();i++)
	{
		if (cedgevec[i].m_bSelected) //��������Сֵ�Ѿ��ù�һ�Σ�����������
		{
			continue;
		}
		else
		{
			if (minWeight >= cedgevec[i].m_weight)  //�����ѭ����Ҫ�ǻ�����minWeight
			{
				minWeight = cedgevec[i].m_weight;
				edgeIndex = i;
			}
		}
	}
	return edgeIndex;
}

bool MGraph::isInSet(vector<int> nodeSet, int target)
{
	for (int i =0;i<nodeSet.size();i++)
	{
		if (nodeSet[i] == target)
		{
			return true;
		}
	}
	return false;
}

void MGraph::mergeNodeSet(vector<int>& nodeSetA, vector<int> nodeSetB)  //ǰ��������
{
	for (int i = 0; i < (int)nodeSetB.size(); i++)
	{
		nodeSetA.push_back(nodeSetB[i]);
	}
}


