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

int main () {

	ifstream in("basic.dat");

	float x,y,z,tout,anl;
	int nphoto = 0, neven=0;
	TH1F h1 = TH1F("h1","x distribution",100,-1,1);
	TH1F h2 = TH1F("h2","Nphot distrb  ",100,0,2000);
	TH2F h3 = TH2F("h3","x VS y        ",100,-0.8,0.8,100,-2.2,-0.8);
	TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","x:y:z");

	while ( in.good() ) {
		std::string s;
		std::getline (in, s);
		if (s.empty()) {
			continue;
		}
		sscanf (s.c_str(), "%f %f %f %f",&x, &y, &z, &tout);

		if(x != 9000 ) {
			h1.Fill(x);
			ntuple->Fill(x,y,z);
			h3.Fill(x,y);
			nphoto = nphoto + 1;
		}  else {                            
			neven = neven + 1;

			if( neven > 1 ) {
				std::cout << "Nphot = " << nphoto
					  << std::endl;
				h2.Fill(nphoto);
			}

			nphoto = 0;
		}
	}

	h2.Fill(nphoto);
	std::cout << "\tfound " << nphoto << " points" << std::endl;
	std::cout << "\tfound " << neven << " Neven" << std::endl;

	return 0;
}
