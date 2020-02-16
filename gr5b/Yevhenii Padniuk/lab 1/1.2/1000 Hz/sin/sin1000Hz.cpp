#include<iostream>
#include <fstream>
#include <cmath>
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraph.h"

void sin1000Hz()
{
	std::ifstream Points("1.txt");

	double* x = new double[2482]; 
	double* y1 = new double[2482]; 
	int n1 = 2482;
	for (int i = 0; i < 2482; i++)
	{
		Points >> x[i] >> y1[i];
	}

	TCanvas *c1 = new TCanvas("c1", "", 50,20,400,400);

	TGraph * gr1 = new  TGraph ( n1 , x , y1 );
	gr1 -> GetYaxis () -> SetTitle ( "A = 1 V" );
	gr1 -> GetXaxis () -> SetTitle ( "#tau = 5 ms #nu = 1000 Hz" );
	gr1 -> SetLineColor(kPink+7);
	gr1 -> Draw ( "AC " );
}