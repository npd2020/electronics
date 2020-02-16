#include <fstream>
#include <cmath>
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraph.h"

void Res()
{
	std::ifstream Points("ResPoints.txt");

	double* x = new double[20]; //Frequency(kHz)
	double* y1 = new double[20]; //Capacity(pikoFarad)
	double* y2 = new double[20]; //Industance(miliGenry)
	double* y3 = new double[20]; //Impedance(Om)
	int n1 = 10;
	for (int i = 0; i < 20; i++)
	{
		Points >> x[i] >> y1[i] >> y2[i] >> y3[i];
	}

	TCanvas *c1 = new TCanvas("c1", "", 50,20,400,400);

	TGraph * gr1 = new  TGraph ( n1 , x , y1 );
	gr1 -> GetYaxis () -> SetTitle ( "C (pF)" );
	gr1 -> GetXaxis () -> SetTitle ( "#nu (kHz)" );
	gr1 -> SetLineColor(kAzure+2);
	gr1 -> Draw ( "AC *" );
	c1 -> SaveAs("Res_Capacity.pdf");

    TCanvas *c2 = new TCanvas("c2", "", 470,20,500,400);

    TGraph * gr2 = new  TGraph ( n1 , x , y2 );
	gr2 -> GetYaxis () -> SetTitle ( "L (mG)" );
	gr2 -> GetXaxis () -> SetTitle ( "#nu (kHz)" );
	gr2 -> SetLineColor(kAzure+2);
	gr2 -> Draw ( "AC *" );
	c2 -> SaveAs("Res_Inductance.pdf");

    TCanvas *c3 = new TCanvas("c3", "", 980,20,400,400);

    TGraph * gr3 = new  TGraph ( n1 , x , y3 );
	gr3 -> GetYaxis () -> SetTitle ( "Z (Om)" );
	gr3 -> GetXaxis () -> SetTitle ( "#nu (kHz)" );
	gr3 -> SetLineColor(kAzure+2);
	gr3 -> Draw ( "AC *" );
	c3 -> SaveAs("Res_Impedance.pdf");
}