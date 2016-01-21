#include <list>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include "graph.h"
#include <chrono>


typedef std::chrono::high_resolution_clock Clock;


using namespace std;


int main(int argc, char *argv[]){
	ofstream output("result.txt");
	//output.flags(ofstream::right);
	//output.width(30);
	int num_graphs,num_pairs;

	output<<"TEST FOR SPARSE GRAPH"<<endl;
	output<<"________________________________________________________"<<endl;
	

	for(num_graphs=0;num_graphs<5;num_graphs++){
		vector<int> mask[5000];
		Graph g;
		int edgenum;
		g1_mask(mask);
		edgenum=graphGenerator(mask,g);

		connection(g,edgenum);

		for(num_pairs=0;num_pairs<5;num_pairs++){
			int srcID,dstID;
			Graph g1,g2,g3;
			int cap1,cap2,cap3;

			g1=g;
			g2=g;
			g3=g;
			


			srcID=rand()%5000;
			do{
				dstID=rand()%5000;
			}while(dstID==srcID);

			output<<"Graph Num:"<<num_graphs+1<<   "Pair Num:"<<num_pairs+1<<   "srcID:"<<srcID<<   "dstID:"<<dstID<<endl;
			output<<"algorithm   "<<"Capacity   "<<"time(microseconds)   "<<endl;

			auto begin1=Clock::now();
			cap1=dijkstra_ARRAY(srcID,dstID,g1);
			auto end1=Clock::now();
			output<<"dij_list    "<<cap1<<"     "<<chrono::duration_cast<std::chrono::microseconds>(end1-begin1).count()<<endl;

			auto begin2=Clock::now();
			cap2=dijkstra_HEAP(srcID,dstID,g2);
			auto end2=Clock::now();
			output<<"dij_heap    "<<cap2<<"     "<<chrono::duration_cast<std::chrono::microseconds>(end2-begin2).count()<<endl;


			auto begin3=Clock::now();
			cap3=kruskal(srcID,dstID,g3);
			auto end3=Clock::now();
			output<<"kruskal     "<<cap3<<"     "<<chrono::duration_cast<std::chrono::microseconds>(end3-begin3).count()<<endl;

		
			
		}
		output<<endl;

	}

	output<<endl<<endl;


	output<<"TEST FOR DENSE GRAPH"<<endl;
	output<<"________________________________________________________"<<endl;
	

	for(num_graphs=0;num_graphs<5;num_graphs++){
		vector<int> mask[5000];
		Graph g;
		int edgenum;
		g2_mask(mask);
		edgenum=graphGenerator(mask,g);

		connection(g,edgenum);

		for(num_pairs=0;num_pairs<5;num_pairs++){
			int srcID,dstID;
			Graph g1,g2,g3;
			int cap1,cap2,cap3;

			g1=g;
			g2=g;
			g3=g;
			


			srcID=rand()%5000;
			do{
				dstID=rand()%5000;
			}while(dstID==srcID);

			output<<"Graph Num:"<<num_graphs+1<<   "Pair Num:"<<num_pairs+1<<   "srcID:"<<srcID<<   "dstID:"<<dstID<<endl;
			output<<"algorithm   "<<"Capacity   "<<"time(microseconds)   "<<endl;

			auto begin1=Clock::now();
			cap1=dijkstra_ARRAY(srcID,dstID,g1);
			auto end1=Clock::now();
			output<<"dij_list    "<<cap1<<"     "<<chrono::duration_cast<std::chrono::microseconds>(end1-begin1).count()<<endl;

			auto begin2=Clock::now();
			cap2=dijkstra_HEAP(srcID,dstID,g2);
			auto end2=Clock::now();
			output<<"dij_heap    "<<cap2<<"     "<<chrono::duration_cast<std::chrono::microseconds>(end2-begin2).count()<<endl;


			auto begin3=Clock::now();
			cap3=kruskal(srcID,dstID,g3);
			auto end3=Clock::now();
			output<<"kruskal     "<<cap3<<"     "<<chrono::duration_cast<std::chrono::microseconds>(end3-begin3).count()<<endl;

		
			
		}
        output<<endl;

	}
	return 0;
}
