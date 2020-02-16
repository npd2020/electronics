#include<iostream>
#include <fstream>
#include <cmath>
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraph.h"

void Fourier700Hz()
{
	std::ifstream Points("1.txt");

	double* x = new double[1006]; 
	double* y1 = new double[1006]; 
	int n1 = 1006;
	for (int i = 0; i < 1006; i++)
	{
		Points >> x[i] >> y1[i];
	}

	TCanvas *c1 = new TCanvas("c1", "", 50,20,600,400);

	TGraph * gr1 = new  TGraph ( n1 , x , y1 );
	gr1 -> GetYaxis () -> SetTitle ( " 10 dB" );
	gr1 -> GetXaxis () -> SetTitle ( "#nu = 12.5 kHz" );
	gr1 -> SetLineColor(kGreen+4);
	gr1 -> Draw ( "AC " );
}