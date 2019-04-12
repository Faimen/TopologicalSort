

#include "pch.h"
#include <iostream>
#include <vector>
#include <stack>

class Topological_Sorting
{

private:
	struct sNode
	{
		bool bVisited = false;
		bool bCircle = false;
		std::vector<sNode*> vecChildren;
		std::vector<sNode*> vecParent;
		int number;
	};

	sNode *nodeGraf = nullptr;
	
public:
	std::vector<sNode*> vecOutputGraf;

	Topological_Sorting()
	{
		//ВОТ ИЗ-ЗА ЭТОГО У МЕНЯ НЕ РАБОТАЛО!!!!!
		int matrixAdjacency[4][4] = { 0 };/*{(0 , 0 , 0 , 1),
											 (0 , 0 , 0 , 0),
											 (0 , 1 , 0	, 0),
											 (0 , 1 , 1 , 0) };*/
		matrixAdjacency[0][3] = 1;
		matrixAdjacency[2][1] = 1;
		matrixAdjacency[3][1] = 1;
		matrixAdjacency[3][2] = 1;
		nodeGraf = new sNode[4];
		
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				if (matrixAdjacency[i][j] == 1)
				{
					nodeGraf[i].vecChildren.push_back(&nodeGraf[j]);
					nodeGraf[j].vecParent.push_back(&nodeGraf[i]);
				}
			}
			nodeGraf[i].number = i + 1;
		}


	}
	~Topological_Sorting()
	{ 

	}

	bool DepthСrawl(sNode* Current, int i)
	{
		//ПОИСК В ГЛУБИНУ
		Current->bVisited = true;
		for (size_t j = i; j < 4; j++)
		{
			if (nodeGraf[j].bVisited != true)
				//ПРоверка на радотилей
				if (nodeGraf[i].vecParent.empty())
				DepthСrawl(&nodeGraf[j], j);
		}
		vecOutputGraf.push_back(Current);
		return true;
	}

	bool TopologicalSort()
	{
		//Вывод связей в графе
		for (size_t i = 0; i < 4; i++)
		{
			std::cout << nodeGraf[i].number << " --> ";
			for (auto Child : nodeGraf[i].vecChildren)
				std::cout << Child->number << " --> ";
			std::cout << "\n";
		}

		for (size_t i = 0; i < 4; i++)
		{
			if (nodeGraf[i].bVisited != true)
			{
				if (nodeGraf[i].vecParent.empty())
				DepthСrawl(&nodeGraf[i], i);
			}
		}
		//НАДО СТЕК ПЕРЕВЕРНУТЬ!
		std::reverse(vecOutputGraf.begin(), vecOutputGraf.end());
		return true;
	}
};



int main()
{
    std::cout << "Hello World!\n"; 

	Topological_Sorting test;
	for (auto graf : test.vecOutputGraf)
		std::cout << graf->number << "\t";
	std::cout << "\n";
	test.TopologicalSort();
	for (auto graf : test.vecOutputGraf)
		std::cout << graf->number<< "\t";
	
	
}
