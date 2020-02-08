#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

void showVector(vector<string> v){
	ofstream GoodPoints("2.txt");
	int m = v.size();
	for (int i=0;i<m;i++){
		GoodPoints<<v[i]<<endl;
	}
	cout<<"OK";
}

int main()
{
	ifstream points("1.txt");

	vector<string> v;
	vector<string> V;

	string s="/0",a="";
	while (s!=""){
		getline(points,s);
		v.push_back(s);
	}
	int n = v.size();
	int m;
	for (int i=0;i<n;i++){
		m=v[i].size();
		for (int j=0;j<m;j++){
			if (v[i][j]!=',')
				a=a+v[i][j];
		}
		V.push_back(a);
		a="";
	}
	showVector(V);
	return 0;
}