#include<iostream>
#include <fstream>
#include <cmath>
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraph.h"

void caA()
{
	std::ifstream Points("Inductor.txt");

	double* x = new double[36]; //Frequency(kHz)
	double* y1 = new double[36]; //Capacity(microFarad)
	double* y2 = new double[36]; //
	double* y3 = new double[36]; //Impedance(Om)
	//double* y4 = new double[14];
	int n1 = 36;
	for (int i = 0; i < 36; i++)
	{
		Points >> x[i] >> y1[i] >> y2[i] >> y3[i];// >> y4[i];
	}

	TCanvas *c1 = new TCanvas("c1", "", 50,20,400,400);

	TGraph * gr1 = new  TGraph ( n1 , x , y1 );
	gr1 -> GetYaxis () -> SetTitle ( "L (mH)");
	gr1 -> GetXaxis () -> SetTitle ( "#nu (kHz)" );
	gr1 -> SetLineColor(kAzure+2);
	gr1 -> Draw ( "AC *" );
	c1 -> SaveAs("Ind_L.pdf");
	
    TCanvas *c2 = new TCanvas("c2", "", 470,20,500,400);

    TGraph * gr2 = new  TGraph ( n1 , x , y2 );
	gr2 -> GetYaxis () -> SetTitle ( "Z (Om)" );
	gr2 -> GetXaxis () -> SetTitle ( "#nu (kHz)" );
	gr2 -> SetLineColor(kAzure+2);
	gr2 -> Draw ( "AC *" );
	c2 -> SaveAs("Ind_Z.pdf");
	
    TCanvas *c3 = new TCanvas("c3", "", 980,20,400,400);

    TGraph * gr3 = new  TGraph ( n1 , x , y3 );
	gr3 -> GetYaxis () -> SetTitle ( "#phi (deg)" );
	gr3 -> GetXaxis () -> SetTitle ( "#nu (kHz)" );
	gr3 -> SetLineColor(kAzure+2);
	gr3 -> Draw ( "AC *" );
	c3 -> SaveAs("Ind_phi.pdf");
	/*
	TCanvas *c4 = new TCanvas("c4", "", 980,20,400,400);

    TGraph * gr4 = new  TGraph ( n1 , x , y4 );
	gr4 -> GetYaxis () -> SetTitle ( "Phi (deg)" );
	gr4 -> GetXaxis () -> SetTitle ( "#nu (kHz)" );
	gr4 -> SetLineColor(kAzure+2);
	gr4 -> Draw ( "AC *" );
	c4 -> SaveAs("Cond_phi.pdf");*/
}
