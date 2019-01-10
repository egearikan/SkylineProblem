#ifndef skyline_hpp
#define skyline_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

/////////////////////////Public Operations
////////////////////////-size=get the current size
////////////////////////-getMax=get the root which is max in priority queue object
////////////////////////-isEmpty()=check for the size 
////////////////////////-push=insert the key to priority queue object
////////////////////////-remove=delete the element from priority queue object 
class PriorityQueue {
public:
	int size(){return A.size();}

	int GetMax(){return A[0];}//return the root

	bool isEmpty(){
		if(size()==0)
			return true;
		else 
			return false;
	}

	void push(int value){
		A.push_back(value);//push the new item to back of vector 
		int index = size() - 1;
		percolateUp(index);//then send it to check if the heap proporty violated or not for that value
	}

	void remove(int value){

		for(int i=0;i<size();i++){
			if(A[i]==value){
				int temp=A[size()-1];
				A[size()-1]=A[i];
				A[i]=temp;
				A.pop_back();
				percolateDown(0);
				break;
			}
		}
	}
private:

	vector<int> A;//main vector to store the heights in pq
	int PARENT(int i) {return (i - 1) / 2;}// get parent
	int RIGHT(int i) { return (2 * i + 2);}//get right child
	int LEFT(int i) {return (2 * i + 1);}// get left child	

	void percolateDown(int i){

		int left = LEFT(i);//get right and left child to check wheter the if property violated or not
		int right = RIGHT(i);

		int largest = i;
		//largest is the current node
		// compare ith index's value with left and right 
		if (left < size() && A[left] > A[i])
			largest = left;
		// compare ith index's value with left and right 
		if (right < size() && A[right] > A[largest])
			largest = right;

		// swap i with largest if the left or right child is bigger than parent
		if (largest != i) {
			swap(A[i], A[largest]);
			percolateDown(largest);//check again for heap property 
		}
	}

	void percolateUp(int i){
		//if the current node and parent violates heap structure
		if (i && A[PARENT(i)] < A[i]){
			swap(A[i], A[PARENT(i)]);//swap heap property violators
			percolateUp(PARENT(i));//heapify the parent node
		}
	}
};
#endif 
