#pragma once
class Edge
{
public:
	Edge(int begin,int end,int weight);
	~Edge();
	int m_begin;
	int m_end;
	int m_weight;
	bool m_bSelected = false;
	
};

