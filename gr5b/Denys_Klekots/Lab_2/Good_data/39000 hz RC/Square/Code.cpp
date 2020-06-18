#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

void showVector(vector<string> v, char* name ){
	ofstream GoodPoints(name);
	int m = v.size();
	for (int i=0;i<m;i++){
		GoodPoints<<v[i]<<endl;
	}
	GoodPoints<<"end";

	cout<<"OK"<<endl;
}

void foo(char* input, char* output){

ifstream points(input);

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
	showVector(V, output);



}

int main()
{
    char* input="F0001CH1.txt";
    char* output="CH1.txt";
	foo(input, output);

	input="F0001CH2.txt";
	output="CH2.txt";
	foo(input, output);

	return 0;
}
