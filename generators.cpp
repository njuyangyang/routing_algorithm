#include <list>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "graph.h"

using namespace std;

//to determine whether there is a same num in vector<int>
bool check(vector<int> checklist,int num){
	bool result=true;
	for(auto & i:checklist){
		if(i==num){
			result=false;
		}
	}
	return result;
}

//generate a mask for the graph G1 with fixed degree 6
void g1_mask(vector<int> (&generateTemp)[5000]){

	srand (time(NULL));
	int i,candidate,edgeNum;
	bool result;
	int counter=0;
	do{
		edgeNum=0;
		for(i=0;i<5000;i++){
			generateTemp[i].clear();
		}
		for(i=0; i<4999; i++){
			while(generateTemp[i].size()<6 && edgeNum<(15000)){
				candidate=rand()%(4999-i)+i+1;
				result=check(generateTemp[i],candidate);
				counter=0;
				while(generateTemp[candidate].size()==6 || !result){
					candidate=rand()%(4999-i)+i+1;
					counter++;
					result=check(generateTemp[i],candidate);
					if(counter>200) goto label1;
				}
				generateTemp[i].push_back(candidate);
				generateTemp[candidate].push_back(i);
				edgeNum++;
			}
			/*
			cout<<i<<":  ";
			for(auto & temp :generateTemp[i]){
				cout<<temp<<";";
			}
			cout<<endl;
			*/
		}label1: cout<<"retry generate G_1 mask"<<edgeNum<<endl;
	}while(edgeNum!=15000);
	cout<<"mask successfully generated a G_1"<<endl;
/*

	label1:
	for(i=0;i<5000;i++){
		cout<<i<<":  ";
		for(auto & temp :generateTemp[i]){
			cout<<temp<<";";
		}
		cout<<endl;
	}
	cout<<"have found  "<<edgeNum<<endl;

	for(i=0;i<5000;i++){
		if(generateTemp[i].size()<6){
			cout<<i<<":  "<<generateTemp[i].size()<<endl;
		}
	}*/
}




int g2_mask(vector<int> (&generateTemp)[5000]){
	int counter=0;
	int i,j;
	int decision;
	bool result;
	srand (time(NULL));

	for(i=0;i<5000;i++){
			generateTemp[i].clear();
		}
	for(i=0;i<5000;i++){
		for(j=i+1;j<5000;j++){
			decision=rand()%100;
			if(decision<20){
				generateTemp[i].push_back(j);
				generateTemp[j].push_back(i);
				counter++;	
			}
		}
	}
	cout<<"mask successfully generated a G_2"<<endl;
	return counter;
}




int graphGenerator(vector<int> (&mask)[5000],Graph &graph){
	int i,edgeID;
	srand(time(NULL));

	for(i=0;i<5000;i++){
		Node nodeTemp(i);
		graph.addNode(nodeTemp);
	}
	edgeID=0;

	for(i=0;i<5000;i++){
		vector<int> & maskRecord=mask[i];	
		for(auto & maskPoint:maskRecord){
			if(maskPoint>i){
				int weightTemp=rand()%100000+10;
				Edge edgeTemp1(edgeID++,i,maskPoint,weightTemp);
				Edge edgeTemp2(edgeID++,maskPoint,i,weightTemp);
				graph.addEdgeByID(i,edgeTemp1);
				graph.addEdgeByID(maskPoint,edgeTemp2);
			}
		}
	}
	cout<<"Graph generated successfully"<<endl;
	return edgeID;
}

void connection(Graph& graph,int edgeID){
    int i;
    edgeID+=100;
	for(i=0;i<4999;i++){
		Node nodeTemp=graph.findNodeByID(i);
		if (!(nodeTemp.checkNextEdge(i+1))){
			Edge edgeTemp1(edgeID++,i,i+1,5);
			Edge edgeTemp2(edgeID++,i+1,i,5);
			graph.addEdgeByID(i,edgeTemp1);
			graph.addEdgeByID(i+1,edgeTemp2);
		}
	}
	if(i==4999){
		Node nodeTemp=graph.findNodeByID(i);
		if(!(nodeTemp.checkNextEdge(0))){
			Edge edgeTemp1(edgeID++,i,0,5);
			Edge edgeTemp2(edgeID++,0,i,5);
			graph.addEdgeByID(i,edgeTemp1);
			graph.addEdgeByID(0,edgeTemp2);
		}
	}

	cout<<"connectivity confirmed"<<endl;
}
































