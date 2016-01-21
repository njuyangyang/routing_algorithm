#include <list>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "graph.h"

using namespace std;


int dijkstra_ARRAY(int srcID, int dstID, Graph& graph){
	Node& src=graph.findNodeByID(srcID);
	Node& dst=graph.findNodeByID(dstID);
	list<Edge> edgelist;
	SpecialList fringerlist(&graph);
	int i;

	for(i=0;i<5000;i++){
		Node& temp=graph.findNodeByID(i);
		temp.setStatus(UNSEEN);
	}

	src.setStatus(INTREE);

	edgelist=src.getEdgeList();



	for(auto & edgeTemp:edgelist){
		int dstTemp=edgeTemp.getDstNodeID();
		Node& nodeTemp=graph.findNodeByID(dstTemp);
		nodeTemp.setStatus(FRINGER);
		nodeTemp.setCapacity(edgeTemp.getWeight());
		nodeTemp.setDad(srcID);
		fringerlist.Insert(dstTemp);
	}

	//fringerlist.DisplayList();



	while(dst.getStatus()!=INTREE){
		/*
		list<Node>::iterator begin,end,it,max_it;
		begin=fringerlist.begin();
		end=fringerlist.end();
		int max_value=begin->getCapacity();
		max_it=begin;

		for(it=begin;it!=end;it++){
			if(it->getCapacity()>max_value){
				max_it=it;
				max_value=it->getCapacity();
			}
		}

		int srcTemp=max_it->getID();
		fringerlist.erase(max_it);
		*/
		Node& nodeTemp=fringerlist.ExtractMax();
		//nodeTemp.nodeDisplay();

		int srcTemp=nodeTemp.getID();
	
		nodeTemp.setStatus(INTREE);
		

		edgelist=nodeTemp.getEdgeList();
		for(auto & edgeTemp :edgelist){
			int dstTemp=edgeTemp.getDstNodeID();
			Node& nodeTemp1=graph.findNodeByID(dstTemp);
			if(nodeTemp1.getStatus()==UNSEEN){
				nodeTemp1.setStatus(FRINGER);
				nodeTemp1.setDad(srcTemp);
				nodeTemp1.setCapacity(min(edgeTemp.getWeight(),nodeTemp.getCapacity()));
				fringerlist.Insert(dstTemp);
			}
			else{
				if(nodeTemp1.getStatus()==FRINGER && nodeTemp1.getCapacity()<min(edgeTemp.getWeight(),nodeTemp.getCapacity())){
					nodeTemp1.setDad(srcTemp);
					nodeTemp1.setCapacity(min(edgeTemp.getWeight(),nodeTemp.getCapacity()));
					fringerlist.Refresh(dstTemp);
				}
			}
		}
	}

	return dst.getCapacity();
}



int dijkstra_HEAP(int srcID, int dstID, Graph& graph){
	Node& src=graph.findNodeByID(srcID);
	Node& dst=graph.findNodeByID(dstID);
	list<Edge> edgelist;
	BinaryHeap fringerlist(&graph);
	int i;

	for(i=0;i<5000;i++){
		Node& temp=graph.findNodeByID(i);
		temp.setStatus(UNSEEN);
	}

	src.setStatus(INTREE);

	edgelist=src.getEdgeList();

	for(auto & edgeTemp:edgelist){
		int dstTemp=edgeTemp.getDstNodeID();
		Node& nodeTemp=graph.findNodeByID(dstTemp);
		nodeTemp.setStatus(FRINGER);
		nodeTemp.setCapacity(edgeTemp.getWeight());
		nodeTemp.setDad(srcID);
		fringerlist.Insert(dstTemp);
	}

	while(dst.getStatus()!=INTREE){
		/*
		list<Node>::iterator begin,end,it,max_it;
		begin=fringerlist.begin();
		end=fringerlist.end();
		int max_value=begin->getCapacity();
		max_it=begin;

		for(it=begin;it!=end;it++){
			if(it->getCapacity()>max_value){
				max_it=it;
				max_value=it->getCapacity();
			}
		}

		int srcTemp=max_it->getID();
		fringerlist.erase(max_it);
		*/
		Node& nodeTemp=fringerlist.ExtractMax();
		int srcTemp=nodeTemp.getID();
		nodeTemp.setStatus(INTREE);

		edgelist=nodeTemp.getEdgeList();
		for(auto & edgeTemp :edgelist){
			int dstTemp=edgeTemp.getDstNodeID();
			Node& nodeTemp1=graph.findNodeByID(dstTemp);
			if(nodeTemp1.getStatus()==UNSEEN){
				nodeTemp1.setStatus(FRINGER);
				nodeTemp1.setDad(srcTemp);
				nodeTemp1.setCapacity(min(edgeTemp.getWeight(),nodeTemp.getCapacity()));
				fringerlist.Insert(dstTemp);
			}
			else{
				if(nodeTemp1.getStatus()==FRINGER && nodeTemp1.getCapacity()<min(edgeTemp.getWeight(),nodeTemp.getCapacity())){
					nodeTemp1.setDad(srcTemp);
					nodeTemp1.setCapacity(min(edgeTemp.getWeight(),nodeTemp.getCapacity()));
					fringerlist.Refresh(dstTemp);
				}
			}
		}
	}

	return dst.getCapacity();
}

int kruskal(int src,int dst,Graph & graph){
	vector<Edge> unsorted,sorted;
	int i,capacity;
	Graph forest;
	//forest.graphDisplay();
	for(i=0;i<5000;i++){
		Node& nodeTemp=graph.findNodeByID(i);
		makeSet(nodeTemp);
		Node nodeTemp1(i);
		forest.addNode(nodeTemp1);
		list<Edge> edgeListTemp=nodeTemp.getEdgeList();
		for(auto & edgeTemp:edgeListTemp){
			if(edgeTemp.getDstNodeID()>edgeTemp.getOrgNodeID()){
				unsorted.push_back(edgeTemp);
			}			
		}
	}

	//forest.graphDisplay();

	sorted=heapSort(unsorted);
	//graph.findNodeByID(src).setTag(TARGET);
	//graph.findNodeByID(dst).setTag(TARGET);
	//for(auto &edd : sorted){
	//	edd.edgeDisplay();
	//}

	//cout<<sorted.size()<<endl;
	//cout<<unsorted.size()<<endl;



	while(!sorted.empty()){
		Edge edgeTemp=sorted[sorted.size()-1];
		sorted.pop_back();

		//edgeTemp.edgeDisplay();

		int srcID=edgeTemp.getOrgNodeID();
		int dstID=edgeTemp.getDstNodeID();
		int  weightTemp=edgeTemp.getWeight();
		int edgeIdTemp=edgeTemp.getEdgeID();
		Edge edgeTempRev(edgeIdTemp,dstID,srcID,weightTemp);

		Node& srcTemp=graph.findNodeByID(srcID);
		Node& dstTemp=graph.findNodeByID(dstID);

		Node& srcTempRoot=findSet(srcTemp,graph);
		Node& dstTempRoot=findSet(dstTemp,graph);

		if(srcTempRoot.getID()!=dstTempRoot.getID()){
			unionSet(srcTempRoot,dstTempRoot,graph);
			forest.addEdgeByID(srcID,edgeTemp);
			forest.addEdgeByID(dstID,edgeTempRev);
		}
	}


	
	dfs(src,dst,forest,capacity);

	return capacity;

}

void dfs(int src,int dst,Graph& tree,int &capp){
	Node& source=tree.findNodeByID(src);
	source.setColor(GREY);
	list<Edge> edgelist=source.getEdgeList();

	for(auto & edgeTemp:edgelist){
		int tarNum=edgeTemp.getDstNodeID();
		Node& target=tree.findNodeByID(tarNum);

		if(target.getColor()==WHITE){
			if(source.getCapacity2()==0){
				target.setCapacity2(edgeTemp.getWeight());
			}
			else{
				target.setCapacity2(min(edgeTemp.getWeight(),source.getCapacity2()));
			}

			if(target.getID()==dst){
				 capp=target.getCapacity2();
				 return;
			}
			else{
				dfs(tarNum, dst, tree,capp);
			}	
		}
	}

	source.setColor(BLACK);
}
















