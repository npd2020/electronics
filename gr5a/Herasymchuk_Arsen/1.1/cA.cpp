#include<iostream>
#include <fstream>
#include <cmath>
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraph.h"

void cA()
{
	std::ifstream Points("Conductor.txt");

	double* x = new double[14]; //Frequency(kHz)
	double* y1 = new double[14]; //Capacity(microFarad)
	double* y2 = new double[14]; //
	double* y3 = new double[14]; //Impedance(Om)
	double* y4 = new double[14];
	int n1 = 14;
	for (int i = 0; i < 14; i++)
	{
		Points >> x[i] >> y1[i] >> y2[i] >> y3[i] >> y4[i];
	}

	TCanvas *c1 = new TCanvas("c1", "", 50,20,400,400);

	TGraph * gr1 = new  TGraph ( n1 , x , y1 );
	gr1 -> GetYaxis () -> SetTitle ( "1/R (S)" );
	gr1 -> GetXaxis () -> SetTitle ( "#nu (kHz)" );
	gr1 -> SetLineColor(kAzure+2);
	gr1 -> Draw ( "AC *" );
	c1 -> SaveAs("Cond_R.pdf");

    TCanvas *c2 = new TCanvas("c2", "", 470,20,500,400);

    TGraph * gr2 = new  TGraph ( n1 , x , y2 );
	gr2 -> GetYaxis () -> SetTitle ( "1/X (S)" );
	gr2 -> GetXaxis () -> SetTitle ( "#nu (kHz)" );
	gr2 -> SetLineColor(kAzure+2);
	gr2 -> Draw ( "AC *" );
	c2 -> SaveAs("Cond_X.pdf");

    TCanvas *c3 = new TCanvas("c3", "", 980,20,400,400);

    TGraph * gr3 = new  TGraph ( n1 , x , y3 );
	gr3 -> GetYaxis () -> SetTitle ( "Z (kOm)" );
	gr3 -> GetXaxis () -> SetTitle ( "#nu (kHz)" );
	gr3 -> SetLineColor(kAzure+2);
	gr3 -> Draw ( "AC *" );
	c3 -> SaveAs("Cond_Z.pdf");

	TCanvas *c4 = new TCanvas("c4", "", 980,20,400,400);

    TGraph * gr4 = new  TGraph ( n1 , x , y4 );
	gr4 -> GetYaxis () -> SetTitle ( "#phi (deg)" );
	gr4 -> GetXaxis () -> SetTitle ( "#nu (kHz)" );
	gr4 -> SetLineColor(kAzure+2);
	gr4 -> Draw ( "AC *" );
	c4 -> SaveAs("Cond_phi.pdf");
}
