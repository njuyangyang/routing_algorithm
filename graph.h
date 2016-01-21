#ifndef GRAPH_H_
#define GRAPH_H_


#include <vector>
#include <list>
#include <iostream>
#include <cstdlib>
#include <iterator>

using namespace std;

//enum for the status of a node
enum Status {
	UNSEEN,
	FRINGER,
	INTREE
};

enum Color {
	BLACK,
	GREY,
	WHITE,
};


//An object of this class represents an edge in the graph.
class Edge{
private:
	int edgeID=-1;
	int orgNodeID=-1;//the originating vertex
	int dstNodeID=-1;//the destination vertex
	int weight=0;//cost of the edge
public:
	Edge()=default;

	Edge(int id,int incost):edgeID(id),weight(incost){ }

	Edge(int id,int first, int second, int inCost):

	edgeID(id),orgNodeID(first),dstNodeID(second),weight(inCost) { }

	int getEdgeID(){
		return edgeID;
	}

	int getDstNodeID(){
		return dstNodeID;
	}

	int getOrgNodeID(){
		return orgNodeID;
	}

	int getWeight(){
		return weight;
	}

	void setEdgeID(int id){
		edgeID=id;
	}

	void setDstNodeID(int id){
		dstNodeID=id;
	}

	void setOrgNodeID(int id){
		orgNodeID=id;
	}

	void setWeight(int wet){
		weight=wet;
	}

	void edgeDisplay(){
		cout<<"edgeID:   "<<edgeID<<"src: "<<orgNodeID<<";    dst: "<<dstNodeID<<";    weight: "<<weight<<endl;
	}
};

//An object of this class holds a vertex of the graph
class Node{
private:
	int nodeID=-1;
	list<Edge> edgeList;//list of outgoing edges for this vertex
	//attributes for Dijkstra
	int dad=-1;
	int capacity=0;
	int capacity2=0;
	Status status=UNSEEN;
	//attributes for kruskal
	int father=-1;
	int rank=0;
	Color color=WHITE;
	
public:
	Node()=default;

	Node(int id):nodeID(id){ }
	Node(int id,int cap):nodeID(id),capacity(cap){ }

	//do not del the adj nodes here...they will be deleted by graph destructor

	Color getColor(){
		return color;
	}

	void setColor(Color tg){
		color=tg;
	}

	int getID(){
		return nodeID;
	}

	list<Edge> getEdgeList(){
		return edgeList;
	}

	Status getStatus(){
		return status;
	}

	int getDad(){
		return dad;
	}

	int getCapacity(){
		return capacity;
	}

	int getCapacity2(){
		return capacity2;
	}
	int getFather(){
		return father;
	}

	int getRank(){
		return rank;
	}

	void setStatus(Status stat){
		status=stat;
	}

	void setDad(int dadID){
		dad=dadID;
	}

	void setCapacity(int cap){
		capacity=cap;
	}

	void setCapacity2(int cap){
		capacity2=cap;
	}

	void setFather(int id){
		father=id;
	}

	void setRank(int ran){
		rank=ran;
	}

	

	void addEdge(Edge edge){
		edgeList.push_front(edge);
	}

	//displays all adjacent verticies of this vertex
	void nodeDisplay(){
		cout<<"Node "<<nodeID<<endl;
		cout<<"dad "<<dad<<endl;
		cout<<"capacity   "<<capacity<<endl;
		cout<<"status  "<<status<<endl;
		cout<<"father  "<<father<<endl;
		cout<<"rank  "<<rank<<endl;

		for(auto &i: edgeList){
			cout<<"     ";
			i.edgeDisplay();
		}
	}

	list<Edge>::size_type getDegree(){
		return edgeList.size();
	}	

	bool checkNextEdge(int dstID){
		bool result=false;
		for(auto & edge:edgeList){
			if(dstID==edge.getDstNodeID()){
				result=true;
				break;
			}
		}

		return result;
	}
};

//An object of class graph holds a directed graph
class Graph{
private:
	vector<Node> nodeList;//list of verticies

public:
	Graph()=default;


	void graphDisplay(){
		for(auto &i: nodeList){
			i.nodeDisplay();
			cout<<endl;
		}
	}

	void addNode(Node nNode){
		nodeList.push_back(nNode);
	}

	Node& findNodeByID(int identity){
		return nodeList[identity];
	}

	void addEdgeByID(int identity,Edge edge){
		nodeList[identity].addEdge(edge);
	}

	vector<Node>::size_type getSize(){
		return nodeList.size();
	}
};






class BinaryHeap
{
    private:
        vector <int> heap;
        int local[5000];
        Graph* graphPtr;
        int left(int parent);
        int right(int parent);
        int parent(int child);
        int brother(int neighbor);
        void heapify(int index);
        
        

    public:
        BinaryHeap(Graph* gr):graphPtr(gr){
        	for(auto& i: local){
        		i=-1;
        	}
        }
        void Insert(int nodeID);
        Node& ExtractMax();
        void DisplayHeap();
        void Refresh(int nodeID);
        int Size();

};

inline
void BinaryHeap::Refresh(int nodeID){
	int location=local[nodeID];
	heapify(location);
}
inline
int BinaryHeap::Size(){
    return heap.size();
}
 

inline
void BinaryHeap::Insert(int nodeID){
    heap.push_back(nodeID);
    local[nodeID]=heap.size()-1;
    heapify(heap.size() -1);
}

inline
Node& BinaryHeap::ExtractMax(){	
	int max=heap[0];
	local[heap[0]]=-1;
	heap[0] = heap.at(heap.size() - 1);
	local[heap[0]]=0;
    heap.pop_back();
    if(heap.size()>1){
    	heapify(0);
    }
    return graphPtr->findNodeByID(max);
}
 

inline
void BinaryHeap::DisplayHeap(){
    cout<<"Heap -->  ";
    for(auto & i: heap)
    {
        graphPtr->findNodeByID(i).nodeDisplay();
    }
    cout<<endl;
}
 
/*
 * Return Left Child
 */
inline
int BinaryHeap::left(int parent){
    int l = 2 * parent + 1;
    if (l < heap.size())
        return l;
    else
        return -1;
}
 
/*
 * Return Right Child
 */
inline

int BinaryHeap::right(int parent){
    int r = 2 * parent + 2;
    if (r < heap.size())
        return r;
    else
        return -1;
}
 
/*
 * Return Parent
 */
inline
int BinaryHeap::parent(int child)
{
    int p = (child - 1)/2;
    if (child == 0)
        return -1;
    else
        return p;
}

inline
int BinaryHeap::brother(int neighbor){
	if(neighbor%2==0){
		return neighbor-1;
	}
	else
		return neighbor+1;
}
 
/*
 * Heapify- Maintain Heap Structure bottom up
 */
inline
void BinaryHeap::heapify(int in){
	int parents=parent(in);
	int leftchild=left(in);
	int rightchild=right(in);

	if(parents>=0 && graphPtr->findNodeByID(heap[parents]).getCapacity()<graphPtr->findNodeByID(heap[in]).getCapacity()){
		int swaper=heap[parents];
		heap[parents]=heap[in];
		heap[in]=swaper;
		local[heap[in]]=in;
		local[heap[parents]]=parents;

		heapify(parents);
	}
	else{ 
		if(leftchild >= 0){
			if(rightchild>=0  && graphPtr->findNodeByID(heap[leftchild]).getCapacity()<graphPtr->findNodeByID(heap[rightchild]).getCapacity()){
				leftchild=rightchild;     
			}
			if(graphPtr->findNodeByID(heap[leftchild]).getCapacity()>graphPtr->findNodeByID(heap[in]).getCapacity()){
				int swaper=heap[leftchild];
				heap[leftchild]=heap[in];
				heap[in]=swaper;
				local[heap[in]]=in;
				local[heap[leftchild]]=leftchild;

				heapify(leftchild);
			}
		}
	}
}

class SpecialList{
private:
	int slist[5000];
	Graph* graphPtr;
	int size=0;

public:
    SpecialList(Graph* gr):graphPtr(gr){
    	for(auto &i :slist){
    		i=-1;
    	}
    }
    void Insert(int nodeID);
    Node& ExtractMax();
    void DisplayList();
    int Size();
    void Refresh(int nodeID);
};

inline
void SpecialList::Refresh(int nodeID){
	slist[nodeID]=graphPtr->findNodeByID(nodeID).getCapacity();
}

inline
void SpecialList::Insert(int nodeID){
	slist[nodeID]=graphPtr->findNodeByID(nodeID).getCapacity();
	size++;
}

inline
Node& SpecialList::ExtractMax(){
	int max=0;
	int i,index;
		//cout<<"we can get here!"<<endl;
	for(i=0;i<5000;i++){
			//cout<<"we can get here:  "<<i<<endl;
		if(slist[i]>max){
			max=slist[i];
			index=i;
			//cout<<index<<endl;
		}
	}
	Node& rmax=graphPtr->findNodeByID(index);
	slist[index]=-1;
	size--;
	return rmax;
}

inline
void SpecialList::DisplayList(){
	int i;
	cout<<"List -->  ";
    for(i=0;i<4999;i++){
    	if(slist[i]>-1){
        	graphPtr->findNodeByID(i).nodeDisplay();
    	}
    }
    cout<<endl;
}

inline 
int SpecialList::Size(){
	return size;
}



class EdgeHeap
{
    private:
        vector <Edge> heap;
        int left(int parent);
        int right(int parent);
        int parent(int child);
        int brother(int neighbor);
        void heapify(int index);

    public:
        EdgeHeap()
        {}
        void Insert(Edge edge);
        Edge ExtractMin();
        void DisplayHeap();
        int Size();
};
/*
 * Return Heap Size
 */
inline
int EdgeHeap::Size(){
    return heap.size();
}
 

inline
void EdgeHeap::Insert(Edge element){
    heap.push_back(element);
    heapify(heap.size() -1);
}

inline
Edge EdgeHeap::ExtractMin(){	
	Edge max=heap[0];
	heap[0] = heap.at(heap.size() - 1);
    heap.pop_back();
    if(heap.size()>1){
    	heapify(0);
    }
    return max;
}
 

inline
void EdgeHeap::DisplayHeap(){
    vector <Edge>::iterator pos = heap.begin();
    cout<<"Heap -->  ";
    while (pos != heap.end())
    {
        pos->edgeDisplay();
        cout<<endl;
        pos++;
    }
    cout<<endl;
}
 
/*
 * Return Left Child
 */
inline
int EdgeHeap::left(int parent){
    int l = 2 * parent + 1;
    if (l < heap.size())
        return l;
    else
        return -1;
}
 
/*
 * Return Right Child
 */
inline

int EdgeHeap::right(int parent){
    int r = 2 * parent + 2;
    if (r < heap.size())
        return r;
    else
        return -1;
}
 
/*
 * Return Parent
 */
inline
int EdgeHeap::parent(int child)
{
    int p = (child - 1)/2;
    if (child == 0)
        return -1;
    else
        return p;
}

inline
int EdgeHeap::brother(int neighbor){
	if(neighbor%2==0){
		return neighbor-1;
	}
	else
		return neighbor+1;
}
 
/*
 * Heapify- Maintain Heap Structure bottom up
 */
inline
void EdgeHeap::heapify(int in){
	int parents=parent(in);
	int leftchild=left(in);
	int rightchild=right(in);

	if(parents>=0 && heap[parents].getWeight()>heap[in].getWeight()){
		Edge swaper=heap[parents];
		heap[parents]=heap[in];
		heap[in]=swaper;
		heapify(parents);
	}
	else{ 
		if(leftchild >= 0){
			if(rightchild>=0  && heap[leftchild].getWeight()>heap[rightchild].getWeight()){
				leftchild=rightchild;     
			}
			if(heap[leftchild].getWeight()<heap[in].getWeight()){
				Edge swaper=heap[leftchild];
				heap[leftchild]=heap[in];
				heap[in]=swaper;
				heapify(leftchild);
			}
		}
	}
}








void g1_mask(vector<int> (&generaterTemp)[5000]);
int g2_mask(vector<int> (&generateTemp)[5000]);
int graphGenerator(vector<int> (&mask)[5000],Graph &graph);
void connection(Graph& graph,int edgeID);
bool check(vector<int> checklist,int num);
Node& unionSet(Node& node1,Node& node2,Graph& graph);
Node& findSet(Node& node,Graph& graph);
void makeSet(Node& node);
vector<Edge> heapSort(vector<Edge>& input);
int dijkstra_ARRAY(int srcID, int dstID, Graph& graph);
int dijkstra_HEAP(int srcID, int dstID, Graph& graph);
int kruskal(int src,int dst,Graph & graph);
void dfs(int src,int dst,Graph& tree,int &capp);



#endif