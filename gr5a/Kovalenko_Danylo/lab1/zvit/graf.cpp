#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
int main()
{
string x, x1, x2;
int k;
ifstream fin("fur_sig.CSV");
ofstream fout("fur_sig.dat");
while (!fin.eof()) 
	{
		getline(fin,x); 
		if (!fin.eof() && x[2]==',' && x[3]!=' ') 
			{
				k=x.size(); 
				size_t s=x.find(' ');
				x1=x.substr(3,s-2);
				x2=x.substr(s+1, k-2);
				fout << setw(20) << x1 << setw(14) << x2 << endl;
			} 
	}
return 0;
}
