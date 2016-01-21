#include <vector>
#include "graph.h"
#include <iostream>

using namespace std;

vector<Edge> heapSort(vector<Edge>& input){
	//cout<<"using heapSort for edges in Kruskal"<<endl;
	EdgeHeap heap;
	vector<Edge> output;
	for(auto & i: input){
		heap.Insert(i);
	}

	while(heap.Size()>0){
		output.push_back(heap.ExtractMin());
	}

	return output;
}