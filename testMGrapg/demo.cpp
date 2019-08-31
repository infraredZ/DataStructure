#include "iostream"
#include "MGraph.h"
using namespace std;
/*

邻接表
0 1 0 0 0 1 0 0 0
1 0 1 0 0 0 1 0 1
0 1 0 1 0 0 0 0 1
0 0 1 0 1 0 1 1 1
0 0 0 1 0 1 0 1 0
1 0 0 0 1 0 1 0 0
0 1 0 1 0 1 0 1 0
0 0 0 1 1 0 1 0 0
0 1 1 1 0 0 0 0 0
*/
int main()
{
	MGraph *pMap = new MGraph(9);
	Node *pNodeA = new Node('A');	//0
	Node *pNodeB = new Node('B');	//1
	Node *pNodeC = new Node('C');	//2
	Node *pNodeD = new Node('D');	//3
	Node *pNodeE = new Node('E');	//4
	Node *pNodeF = new Node('F');	//5
	Node *pNodeG = new Node('G');	//6
	Node *pNodeH = new Node('H');	//7
	Node *pNodeI = new Node('I');	//8
	pMap->addNode(pNodeA);
	pMap->addNode(pNodeB);
	pMap->addNode(pNodeC);
	pMap->addNode(pNodeD);
	pMap->addNode(pNodeE);
	pMap->addNode(pNodeF);
	pMap->addNode(pNodeG);
	pMap->addNode(pNodeH);
	pMap->addNode(pNodeI);

	pMap->setValueToMatrixForUndirectedGraph(0, 1,9);
	//pMap->setValueToMatrixForUndirectedGraph(0, 1, 0);  //断开 A-B
	pMap->setValueToMatrixForUndirectedGraph(0, 5,2);//连接A-F
	//pMap->setValueToMatrixForUndirectedGraph(0, 5, 0);//断开A-F//第3个参数写入0即为断开
	pMap->setValueToMatrixForUndirectedGraph(1, 2,7);
	pMap->setValueToMatrixForUndirectedGraph(1, 8,4);
	pMap->setValueToMatrixForUndirectedGraph(1, 6,10);
	pMap->setValueToMatrixForUndirectedGraph(2, 8,1);
	pMap->setValueToMatrixForUndirectedGraph(2, 3,32);
	pMap->setValueToMatrixForUndirectedGraph(3, 4,9);
	pMap->setValueToMatrixForUndirectedGraph(3, 6,4);
	pMap->setValueToMatrixForUndirectedGraph(3, 7,3);
	pMap->setValueToMatrixForUndirectedGraph(3, 8,4);
	pMap->setValueToMatrixForUndirectedGraph(4, 5,10);
	pMap->setValueToMatrixForUndirectedGraph(4, 7,9);
	pMap->setValueToMatrixForUndirectedGraph(5, 6,1);
	pMap->setValueToMatrixForUndirectedGraph(6, 7,12);
	pMap->printMartrix();
	cout << endl;
	pMap->depthFirstTraverse(0);
	cout << endl;
	pMap->resetNode();
	pMap->breadthFirstTraverse(7);
	pMap->resetNode();
	cout << endl;
	pMap->miniSpanTree_prim(0);
	cout << endl;
	pMap->resetNode();
	pMap->miniSpanTree_Kruskal();
	pMap->resetNode();
	pMap->shortPath_Dijkstra(1);


	system("pause");
	return 0;
}