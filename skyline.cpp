#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "skyline.h"

using namespace std;

struct ident{
	int coordinate;//x coordinate
	int h;//height
	string p;//position,s or e
};

bool sortHeight(const ident & a, const  ident & b)
{

	if(a.coordinate == b.coordinate){

		if(a.p==b.p){

			if(a.p=="s")
				return(a.h > b.h);
			else
				return (a.h < b.h);
		}
		else
			return (a.p == "s");
	}
	else{
		return (a.coordinate<b.coordinate);
	}

}

vector<ident> combinevectors(vector<ident> &vec1,vector<ident> &vec2,int total){//aim is to merge 2 vectors 
	vector<ident>temp=vec1;
	for (int i=0;i<total;i++)
		temp.push_back(vec2[i]);
	int t=(total*2)-1;
	std::sort(temp.begin(),temp.end(),sortHeight);//sorting of the buildings

	return temp;
}

int main(){
	ifstream input;
	vector<ident> x1;
	vector<ident> x2;
	PriorityQueue pq;

	input.open("input.txt");
	int numBuilding, xleft, xright, height,i=0;
	input >> numBuilding;

	while (input >> xleft >> height >> xright){
		ident temp1={xleft,height,"s"};//push starting
		ident temp2={xright,height,"e"};//push ending
		x1.push_back(temp1);
		x2.push_back(temp2);
		i++;
		if(i==numBuilding)//to avoid get data from empty txt line
			break;
	}

	vector<ident> mainvec=combinevectors(x1,x2,numBuilding);//mainvec is sorted according to x coordinate

	pq.push(0);//for the ending point for skyline view

	for(int i=0;i<mainvec.size();i++){

		if(mainvec[i].coordinate!=0 && i==0){
			cout<<"0 0"<<endl;
		}

		if(mainvec[i].p=="s"){//if the height is bigger than the one,observed in priority queue than it should be printed out
			int a=pq.GetMax();
			pq.push(mainvec[i].h);
			if(a<mainvec[i].h)
				cout<<mainvec[i].coordinate<< " "<<mainvec[i].h<<endl;
		}
		else {
			int b=pq.GetMax();//if x coordinate is representing an end contion then check for wheater max of priority queue is changed if so then print that coordinate
			pq.remove(mainvec[i].h);
			int c=pq.GetMax();
			if(b>c)
				cout<<mainvec[i].coordinate<< " "<<c<<endl;
		}
	}
	return 0;
}
