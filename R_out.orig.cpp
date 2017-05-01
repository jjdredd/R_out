#include "Riostream.h"
#include <vector>
#include <string>
#include <TString.h>
#include <TSystem.h>
#include <TInterpreter.h>
#include <TFile.h>
#include <TF1.h>
#include <TF2.h>
#include <TNtuple.h>
#include <TH1.h>
#include <TH2.h>


struct vec  {
	float x,y,z,t;
};

void R_out() {
	//  Read data from an ascii file and create a root file with an histogram and an ntuple.
	//   see a variant of this macro in basic2.C
	//Author: Rene Brun
      

	// read file $ROOTSYS/tutorials/tree/basic.dat
	// this file has 3 columns of float data
	TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
	dir.ReplaceAll("R_out.C","");
	dir.ReplaceAll("/./","/");
	ifstream in;
	in.open(Form("%sbasic.dat",dir.Data()));
	std::vector<vec> values;

	Float_t x,y,z,tout,anl;
	Int_t nphoto = 0, neven=0;
	TFile *f = new TFile("basic.root","RECREATE");
	TH1F *h1 = new TH1F("h1","x distribution",100,-1,1);
	TH1F *h2 = new TH1F("h2","Nphot distrb  ",100,0,2000);
	TH2F *h3 = new TH2F("h3","x VS y        ",100,-0.8,0.8,100,-2.2,-0.8);
	TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","x:y:z");

	while ( in.good() ) {
		std::string s;
		struct vec v;
		std::getline (in, s);
		if (s.empty()) {
			continue;
		}
		sscanf (s.c_str(), "%f %f %f %f",&v.x, &v.y, &v.z, &v.t);
		sscanf (s.c_str(), "%f %f %f %f",&x, &y, &z, &tout);
		values.push_back(v);


		// in >> x >> y >> z >> tout ;                      
		// if (!in.good()) break;
		////  if (nphot  < 5) printf("x=%8f, y=%8f, z=%8f\n",x,y,z);
		if(x != 9000 ) {
			///// if (nphoto < 5) printf("x=%8f, y=%8f, z=%8f\n",x,y,z);
			h1->Fill(x);
			ntuple->Fill(x,y,z);
			h3->Fill(x,y);
			nphoto = nphoto + 1;
		}  else  
			{                            
				neven = neven + 1;
				anl = static_cast<float> (nphoto);
			if(neven>1){	printf("Nphot =%8f\n",nphoto);
				h2->Fill(anl);}
				nphoto = 0;
			}
	}
	anl = static_cast<float> (nphoto);
	h2->Fill(anl);
	printf(" found %d points\n",nphoto);
	printf(" found %d Neven\n",neven);

	in.close();

	f->Write();
}
