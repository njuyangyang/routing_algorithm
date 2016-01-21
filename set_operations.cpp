#include <vector>
#include "graph.h"
#include <iostream>

using namespace std;

void makeSet(Node& node){
	node.setFather(-2);
	node.setRank(0);
	//cout<<"made set "<<node.getID()<<endl;
}


//using path compression
Node& findSet(Node& node,Graph& graph){
	vector<int> path;
	Node nodeTemp;
	nodeTemp=node;
	int fatherID=nodeTemp.getFather();
	int id=nodeTemp.getID();

	while(fatherID>-1){
		path.push_back(id);
		nodeTemp=graph.findNodeByID(fatherID);
		fatherID=nodeTemp.getFather();
		id=nodeTemp.getID();	
	}

	//rootRank=nodeTemp.getID();

	for(auto & i: path){
		graph.findNodeByID(i).setFather(id);
	}

	return graph.findNodeByID(id);
}

//union by rank

Node& unionSet(Node& node1,Node& node2,Graph& graph){
	Node& root1=findSet(node1,graph);
	Node& root2=findSet(node2,graph);
	int rank1=root1.getRank();
	int rank2=root2.getRank();
	int id1=root1.getID();
	int id2=root2.getID();
	if(id1==id2){
		return root1;
	}

	if(rank1!=rank2){
		if(rank1>rank2){
			root2.setFather(id1);
			//cout<<"add "<<id2<<"  to  "<<id1<<endl;
			return root1;
		}
		else{
			root1.setFather(id2);
			//cout<<"add "<<id1<<"  to  "<<id2<<endl;
			return root2;
		}
	}
	else{
		root2.setFather(id1);
		root1.setRank(rank1+1);
		//cout<<"add "<<id2<<"  to  "<<id1<<endl;
		return root1;
	}
}

























