#include "TMath.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TF1.h"
#include "stdio.h"
#include "TText.h"
#include "Riostream.h"
#include "/home/volodymyr/Documents/MyLibs/root/ExtendedRoot.C"
#include <string>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>

using namespace std;

Data ampDelta(20);
Data phaseDelta(20);
int N=0;

double findfreqofsignal(TGraph* gr){ // This code was written by V. Svintozelskyi. Take it into account, please.
    double* x = gr->GetX();
    double* y = gr->GetY();
    int n = gr->GetN();
    int i =0;

    double max = TMath::MaxElement(gr->GetN(),gr->GetY());
    double min = TMath::MinElement(gr->GetN(),gr->GetY());
    double median = (max+min)/2.0;

    double rise = (median -y[0])/abs((median -y[0]));
    int counter = 0;
    while((y[counter]-median)*rise < 0)counter++;
    double level = y[counter];
    int firstcont = counter;
    // double delta = abs(level - y[counter-1]);

    rise = -rise;
    while(abs(y[counter]-level) < (max-min)/5.0)counter++;
    while((y[counter]-level)*rise < 0)counter++;
    
    double period = 2.0*(x[counter]-x[firstcont]);
    return 2*TMath::Pi()/period;
}

double sinf(double* x, double* pars){
    return pars[0] * sin(pars[1] * x[0] + pars[2]) + pars[3];
}

Data loadDataa(TString filename){
    // cout << "Loading file " << filename << ".."<<endl;
    ifstream datafile(filename);
    if(!datafile.is_open()){
        cout << "\t\t!!  File "<<filename<<" hasn`t been opened!"<<endl;
        return Data(0);
    }
    Int_t N = 0;
    string line;
    while(!datafile.eof()){
        getline(datafile,line);
        if(line[0]=='#')
            continue;
        if (line.empty())
            continue;
        N++;
    }
    cout<<"\t\t.. "<<"detected "<<N<<" lines"<<endl;
    Data data(N);
    datafile.clear();
    datafile.seekg(0,ios_base::beg);
    Int_t i = 0;
    while (!datafile.eof()) {
        getline(datafile, line);
        if (line.empty())
            continue;
        if(line[0]=='#')
            continue;
        replace(line, ".\t", ".0\t");
        replace(line, "00.", "0.");
        Double_t x,y,xerr,yerr;
        char name[15];
        //sscanf(line.c_str(),"%*f\t%*f\t%f\t%f\t%f\t%f",&t,&d,&err,&err2);
        // cout<<line<<endl;
        // char a[15] , b[15] ,c[15] ;
        // sscanf(line.c_str(),"%s,%s,%s,%lf,%lf",a,b,c,&x,&y);
        // cout<<a<<"  "<<b<<"  "<<c<<endl;
        // cout<<x<<"--"<<y<<endl;
        int p1 = line.find(',',line.find(',',line.find(',')+1)+1);
        int p2 = line.find(',',p1+1);
        int p3 = line.find(',',p2+1);

        data.x[i]= stof(line.substr(p1+1,p2));
        data.y[i]=stof(line.substr(p2+1,p3));
        data.yerror[i]=0;
        data.xerror[i]=0;
        string nam(name);
        data.info[i]=nam;
        i++;
    }
    datafile.close();
    Data dat(N);
    for(int i =0;i<N;i++){
        dat.x[i]=data.x[i];
        dat.y[i]=data.y[i];
        dat.xerror[i]=data.xerror[i];
        dat.yerror[i]=data.yerror[i];
    }
    return dat;
}

double func(double* x, double* pars){
    double E = 108*(1-0.09*x[0]);
    // double E = 108;
    double r = x[0]*pars[0]*log((E-72.4)/(E-95.2));
    // cout<<r<<endl;
    return r*1000;
}

double func2(double* x, double* pars){
    double y = x[0];
    double a = x[1];
    double b = x[2];
    return (y-b)/a;
}


bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

TCanvas* drawgraph(Data data,string name){
    TCanvas* canv = new TCanvas();
    TGraphErrors* gr1 = TGraphErr(data);
    gr1->SetTitle(Form("%s;CH1;CH2",name.c_str()));
    gr1->Draw("AP");
    gr1->SetMarkerStyle(20);
    // save(canv);
    return canv;
}

void graph(){
    cout<<"Loading.."<<endl;
    // Data data1 = loadData("data");
    DIR *dir;
    DIR *folder;
    struct dirent *ent;
    struct dirent *file;
    if ((dir = opendir ("./")) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
        printf ("%s\n", ent->d_name);
        if(ent->d_type != DT_DIR)
                    continue;
        if((folder = opendir (Form("./%s",ent->d_name))) != NULL){
            std::vector<Data> dataset;
            int* matrix = new int[2];
            while ((file = readdir (folder)) != NULL) {
                if(file->d_type != DT_REG)
                    continue;
                // cout<<"container "<<ent->d_name<<"  file "<<file->d_name<<endl;
                if(hasEnding(file->d_name,".CSV" )){
                    cout<<"loading:P "<<Form("%s/%s",ent->d_name,file->d_name)<<endl;
                    Data data = loadDataa(Form("%s/%s",ent->d_name,file->d_name));
                    dataset.push_back(data);
                    if(dataset.size()==1){
                        if (hasEnding(file->d_name,"CH1.CSV" ))
                            matrix = new int[2]{0,1};
                        else
                            matrix = new int[2]{1,0};
                    }
                    // printData(data);                
                    // drawgraph(data, (file->d_name));
                    // exit(0);
                }
            }
            if (dataset.size()==2){        
                // double* ch1data = new double[dataset[0].n];
                // double* ch2 = new double[dataset[0].n];
                TGraph* graphCh1=new TGraph(0,new double[0]{},new double[0]{});
                TGraph* graphCh2=new TGraph(0,new double[0]{},new double[0]{});
                for(int i = 0;i<dataset[0].n;i++){
                    graphCh1->Set(i+1);
                    graphCh2->Set(i+1);
                    graphCh1->SetPoint(i,dataset[matrix[0]].x[i],dataset[matrix[0]].y[i]);
                    graphCh2->SetPoint(i,dataset[matrix[1]].x[i],dataset[matrix[1]].y[i]);
                }
                TCanvas* canv = new TCanvas();
                canv->SetName(ent->d_name);
                canv->SetTitle(ent->d_name);
                canv->Divide(2,1);
                canv->cd(1);
                graphCh1->Draw("AP");
                graphCh1->SetTitle("CH1");

                TF1* fff = new TF1("f1", sinf, -10,10,4);
                double freq = findfreqofsignal(graphCh1);
                fff->FixParameter(1,freq);
                fff->SetParameter(2,0);
                fff->FixParameter(0,(TMath::MaxElement(graphCh1->GetN(),graphCh1->GetY())-TMath::MinElement(graphCh1->GetN(),graphCh1->GetY()))/2);
                fff->FixParameter(3,(TMath::MaxElement(graphCh1->GetN(),graphCh1->GetY())+TMath::MinElement(graphCh1->GetN(),graphCh1->GetY()))/2);
                cout<<fff->GetParameter(0)<<"   "<<fff->GetParameter(1)<<"   "<<fff->GetParameter(2)<<"   "<<fff->GetParameter(3)<<endl;
                graphCh1->Fit(fff);
                fff->ReleaseParameter(0);
                fff->ReleaseParameter(1);
                fff->ReleaseParameter(3);
                graphCh1->Fit(fff);
                graphCh1->SetTitle(Form("CH1;t [s];%fSin(%ft+%f)+%f",fff->GetParameter(0),fff->GetParameter(1),fff->GetParameter(2),fff->GetParameter(3)));
                canv->cd(2);
                graphCh2->Draw("AP");
                graphCh2->SetTitle("CH2");
                TF1* ff2 = new TF1("f2", sinf, -10,10,4);
                ff2->FixParameter(1,freq);
                ff2->SetParameter(2,0);
                ff2->FixParameter(0,(TMath::MaxElement(graphCh2->GetN(),graphCh2->GetY())-TMath::MinElement(graphCh2->GetN(),graphCh2->GetY()))/2);
                ff2->FixParameter(3,(TMath::MaxElement(graphCh2->GetN(),graphCh2->GetY())+TMath::MinElement(graphCh2->GetN(),graphCh2->GetY()))/2);
                graphCh2->Fit(ff2);
                ff2->ReleaseParameter(0);
                ff2->ReleaseParameter(1);
                ff2->ReleaseParameter(3);
                graphCh2->Fit(ff2);
                graphCh2->SetTitle(Form("CH2;t [s];%fSin(%ft+%f)+%f",ff2->GetParameter(0),ff2->GetParameter(1),ff2->GetParameter(2),ff2->GetParameter(3)));
                setFitStyleCanvas(canv->GetPad(1));
                setFitStyleCanvas(canv->GetPad(2));
                
                double deltaPhase = std::fmod((ff2->GetParameter(2)-fff->GetParameter(2)),2*TMath::Pi());
                double deltaAmp = ff2->GetParameter(0)/fff->GetParameter(0);
                double frequency= fff->GetParameter(1)/(2* TMath::Pi());

                ampDelta.x[N] = frequency;
                ampDelta.y[N] = deltaAmp;
                phaseDelta.x[N] = frequency;
                phaseDelta.y[N] = deltaPhase;
                N++;

                graphCh1->GetYaxis()->SetTitleOffset(0.95);
                graphCh2->GetYaxis()->SetTitleOffset(0.95);
                save(canv);
            }
            closedir (folder);
            // exit(0);
        }else {
          perror ("");
          return EXIT_FAILURE;
        }
      }
      closedir (dir);
    } else {
      perror ("");
      return EXIT_FAILURE;
    }
    cout<<"loading ended"<<endl;
    TCanvas* final = new TCanvas();
    final->Divide(2,1);
    TGraph* ampgraph = new TGraph(N, ampDelta.x,ampDelta.y);
    ampgraph->SetTitle(";#omega [Hz];K(#omega)");
    ampgraph->Draw("AP");

    // double rc1=5.38e-3; // 0.0246543
    // double rc2=5.38e-3;
    // TF1* theoryK = new TF1("K", [](double* x, double* pars){return ;},-2,1.5e3,2);
    // theoryK->SetParameter(0,rc1);
    // theoryK->SetParameter(1,rc2);
    // // theoryK->Draw("same");
    // ampgraph->Fit(theoryK);
    final->SetLogx();
    setFitStyleCanvas(final);
    save(final,"FINAL_K");
    TCanvas* final2 = new TCanvas();
    TGraph* phgraph = new TGraph(N, phaseDelta.x,phaseDelta.y);
    phgraph->SetTitle(";#omega [Hz];#phi(#omega)");
    phgraph->Draw("AP");

    // TF1* theoryPh = new TF1("Ph", [](double* x, double* pars){return -TMath::ATan((x[0]*pars[1]))+TMath::ATan(1/(x[0]*pars[0]));},-2,1.5e3,2);
    // theoryPh->SetParameter(0,rc1);
    // theoryPh->SetParameter(1,rc2);
    // // theoryPh->Draw("same");
    // phgraph->Fit(theoryPh);
    final2->SetLogx();
    setFitStyleCanvas(final2);
    save(final2,"FINAL_Phi");
}


