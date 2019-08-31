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
	m_pMatrix = new int[m_iCapacity*m_iCapacity];   //邻接矩阵
	//初始化矩阵
	for (int i = 0; i < m_iCapacity*m_iCapacity; i++)
	{
		m_pMatrix[i] = 65535;
	}
}

MGraph::~MGraph()
{
	delete [] m_pNodeArray;         //先释放节点所对应的内存
	delete [] m_pMatrix;            //再释放邻接矩阵所对应的内存
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
//给无向表的邻接矩阵中row行，col列的元素设置值,默认是1
bool MGraph::setValueToMatrixForUndirectedGraph(int row, int col, int val)
{	
	//输入检测
	if (row < 0 || row >= m_iCapacity)
	{
		return false;
	}
	if (col < 0 || col >= m_iCapacity)
	{
		return false;
	}
	m_pMatrix[row*m_iCapacity + col] = val;
	m_pMatrix[col*m_iCapacity + row] = val;//创建的邻接矩阵
	Edge pedge(row,col,val);
	edgevec.push_back(pedge);   //创建边集数组
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
		cout << endl;                        //每打印m_iCapacity个元素换一行
	}
}

void MGraph::depthFirstTraverse(int nodeIndex)
{
	int value = 0;
	cout << m_pNodeArray[nodeIndex].m_cData << " ";//打印节点数据
	m_pNodeArray[nodeIndex].m_bIsVisited = true;
	for (int i = 0;i<m_iCapacity;i++)     //i=0具有通用性，可以同时适用有向图。i = nodeindex 算是优化了无向图
	{
		getValueFromMatrix(nodeIndex, i, value);  //邻接矩阵中的距离值传入value
		if (value != 0)  //表示nodeIndex这个索引的节点与索引为i的节点相连只有 01 与 1  无权连接的图
		{
			if (m_pNodeArray[i].m_bIsVisited)
			{
				continue;  //代表访问过了
			}
			else
			{
				depthFirstTraverse(i);   //递归继续向下找
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
//递归的方法，
// 	cout << m_pNodeArray[nodeIndex].m_cData << " ";
// 	m_pNodeArray[nodeIndex].m_bIsVisited = true;
// 	vector<int> curVec;
// 	curVec.push_back(nodeIndex);
// 	breadthFirstTraverseImpl(curVec);

//非递归的方法
	int i, j; //i为邻接表的row  j :col
	int value;
	queue <int> Q;

	/* 从0 - m_iCapacity的每一点都开始一遍。
	*	即保证了不连通的图也可以访问完。
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
				i=Q.front();  //访问队列的第一个元素
				Q.pop();
				for (j=0;j<m_iCapacity;j++)    //j = 0 也是为了有向图的遍历。
				{
					getValueFromMatrix(i, j, value);   //value 就是权值，
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
* 适合边多，稠密图。
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
// 	vector<int> tempcost; //临时保存一下各个权值
// 	vector<int> tempvex; //临时保存一下各个顶点的下标
	adjvex.push_back(nodeIndex);
	m_pNodeArray[nodeIndex].m_bIsVisited = true;
	n = m_iCapacity - 1;  //只需要8条边
	start = clock();

	while (n--)
	{
		min = 65535;
		for (i = 0; i < adjvex.size(); ++i)    //循环已经包含的所有点与其他店的连接
		{
			
			m = adjvex.at(i);
			
			for (j = 0; j < m_iCapacity; j++)   //这里选择的顺序不一定是ABC...
			{	
				getValueFromMatrix(m, j, value);
				if (value < min&& !m_pNodeArray[j].m_bIsVisited && value != 0)
				{
// 					tempcost.push_back(value);
// 					tempvex.push_back(j);//保存下标 
					min = value;
					k = j;
				}
			}
		}
		i = 0;
// 		auto minvalue = min_element(begin(tempcost), end(tempcost));    //找出最小的 这里肯定不如一直保留一个最小值划算
// 		k = tempvex.at(distance(begin(tempcost), minvalue));
		m_pNodeArray[k].m_bIsVisited = true;   //代表的是已经包含了的顶点。
		lowcost.push_back(min);  //保存进lowcost中
		adjvex.push_back(k);  //保存最小值的下标；
/*		cout<< *minvalue << " ";*/
		cout << min << " ";
// 		tempvex.clear();  //清除
// 		tempcost.clear();
	}
	cout << endl;
	for (auto c : lowcost)
	{
		sum = sum + c;
	}
	cout << "Prim算法——最低花费：" << sum << endl;
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "用时：" << duration;
}

void MGraph::miniSpanTree_Kruskal()
{
	int edgecount = 0;
	int sum= 0;
	vector <vector<int>> nodeSets;     //二维容器  。一维为一个单独的连通域，二维为每一个连通域中所有的顶点标号

	while (edgecount < m_iCapacity - 1) //8条边就结束算法
	{
		int minEdgeIndex = getMinEdge(edgevec);
		edgevec.at(minEdgeIndex).m_bSelected = true;// 这个值被访问了。
		int nodeAIndex = edgevec.at(minEdgeIndex).m_begin;
		int nodeBIndex = edgevec.at(minEdgeIndex).m_end;
		bool nodeAIsSet = false;
		bool nodeBIsSet = false;
		int nodeAInsetLabel = -1;
		int nodeBInsetLabel = -1;
		for (int i = 0; i<nodeSets.size();i++)
		{
			nodeAIsSet = isInSet(nodeSets[i], nodeAIndex);   //头节点在节点(已经选中)的集合里
			if (nodeAIsSet)
			{
				nodeAInsetLabel = i;   //判断头节点在哪个连通域中
			}
		}
		for (int i = 0; i < nodeSets.size(); i++)
		{
			nodeBIsSet = isInSet(nodeSets[i], nodeBIndex);   //尾节点
			if (nodeBIsSet)
			{
				nodeBInsetLabel = i;  //判断尾节点在哪个连通域中
			}
		}
		//这条边的节点都不在任何一个连通域中
		if (nodeAInsetLabel == -1 && nodeBInsetLabel == -1)  
		{
			vector <int> vec;
			vec.push_back(nodeAIndex);
			vec.push_back(nodeBIndex);
			nodeSets.push_back(vec);//单独多一个连通域，
		}
		// 尾节点在一个连通域中，头节点不在。因为这条边连起来了，所以就在一个连通域中了
		else if (nodeAInsetLabel == -1 && nodeBInsetLabel != -1)  
		{
			nodeSets[nodeBInsetLabel].push_back(nodeAIndex);
		}
		// 尾节点在一个连通域中，头节点不在。因为这条边连起来了，所以就在一个连通域中了
		else if (nodeAInsetLabel != -1 && nodeBInsetLabel == -1)
		{
			nodeSets[nodeAInsetLabel].push_back(nodeBIndex);
		}
		//两个节点分别在不同的连通域，因为这条边，变成了一个连通域
		else if (nodeAInsetLabel != -1 && nodeBInsetLabel != -1 && nodeAInsetLabel != nodeBInsetLabel)
		{
			//把尾节点所在的连通域合并到头节点所在的连通域中
			mergeNodeSet(nodeSets[nodeAInsetLabel], nodeSets[nodeBInsetLabel]);
			
			for (int k = nodeBInsetLabel;k<nodeSets.size()-1;k++)
			{
				nodeSets[k] = nodeSets[k + 1]; //k 是尾节点。把第k+1个连通域的值赋值给K个连通域
			}
			//想缩减连通域的范围，这里连通域较少，所以没执行
		}
		//头尾节点都在一个连通域中。所以这个点被抛弃。
		else if (nodeAInsetLabel!=-1&&nodeBInsetLabel!=-1 && nodeAInsetLabel == nodeBInsetLabel)
		{
			continue;  //不能将这个节点加入到nodeSets
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
	cout << "Kruskal算法——最低花费：" << sum << endl;

}

void MGraph::shortPath_Dijkstra(int being_node)
{
	//1.由起始节点开始向外扩散，找到最小的点，然后从最小的向下深挖
	int finalvalue[9];
	int flag[9];//找到标志的记录
	int value = 0;
	int w=0 ; //下标记录
	int min = 0;
	
	for (int i = 0;i<m_iCapacity;i++)
	{
		getValueFromMatrix(being_node, i, value);
		finalvalue[i] = value; //初始化数组  //已连接的的就权值了
		flag[i] = 0;
	}
	finalvalue[being_node] = 0;//起始点就不用找了
	flag[being_node] = 1; //自己就不再查找了
	for (int i =1;i<m_iCapacity;i++)
	{
		min = 65535;
		for (int j = 0;j<m_iCapacity;j++)
		{
			if (flag[j]==0 && finalvalue[j]<min)
			{
				min = finalvalue[j];//找到这个数组中的最小值
				w = j;
			}
		}
		flag[w] = 1; //找到了最小的值
		for (int k = 0;k<m_iCapacity;k++)   //修正的方法就是，从个点找下去找完所有连接就算成功
		{
			getValueFromMatrix(w, k, value);
			if (flag[k]==0 && finalvalue[k]>min+value)
			{
				finalvalue[k] =  min + value;
			}
		}
	}
	cout << "距离:" << endl;
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
					curVec.push_back(i);				//记录当前节点相连的节点
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
		breadthFirstTraverseImpl(curVec);    //当前节点遍历完成后，递归上诉记录的节点
	}
}



int MGraph::getMinEdge(vector<Edge> cedgevec)
{
	int edgeIndex = 0;
	int minWeight = cedgevec.at(0).m_weight;   //最小值初始化为第一个值
	int i ;
	for (i =0;i<cedgevec.size();i++)
	{
		if (cedgevec[i].m_bSelected) //如果这个最小值已经用过一次，就跳过它。
		{
			continue;
		}
		else
		{
			if (minWeight >= cedgevec[i].m_weight)  //上面的循环主要是获得这个minWeight
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

void MGraph::mergeNodeSet(vector<int>& nodeSetA, vector<int> nodeSetB)  //前面是引用
{
	for (int i = 0; i < (int)nodeSetB.size(); i++)
	{
		nodeSetA.push_back(nodeSetB[i]);
	}
}


