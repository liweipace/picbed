#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TApplication.h>
#include "TRandom3.h"
#include "Math/QuasiRandom.h"

using namespace std;

int main(int argc, char **argv) {
	TApplication theApp("APP", &argc, argv);
	int N=5;             // N dimensions
	double vol;
	double xin;
	double xout;
	//srand48(time(NULL));
	TRandom3 *r0 = new TRandom3();
	r0->SetSeed(0);
	//cout << "Enter a number for N dimensions: " << endl;
	//cin >> N;
	double n_vol = pow(M_PI, double(N/2.0)) / exp(lgamma(double(N/2.0)+1.0));  // volume eq. for N-spheres
	double error[7];
	double npoint[7];
	for (int npoints=0; npoints<7; npoints++){
		double hit=0;
		for (int i = 0; i < pow(10,(npoints+1)); i++) {
			double r = 0;
			for (int j = 0; j < N; j++) {
				int np = pow(10,(npoints+1));
				int randomv = rand()%np;
				double randomr = randomv/(pow(10,(npoints+1)));
				double x = 2*(randomr-.5);
				r += x*x;
			}
			if (sqrt(r) < 1) {
				hit += 1;
			}
		}
		vol = ( pow(2,N) * hit ) / (pow(10,(npoints+1)));
		error[npoints]=log10(fabs(vol-n_vol));
		npoint[npoints]=(npoints+1);
	}
	TGraph *trandom3 = new TGraph(7, npoint, error);
	TCanvas *c1 = new TCanvas("c1", "Graph draw option",200,10,600,400);
	trandom3->Draw("AC*");
	trandom3->SetTitle("log error VS log # of points in fixed grid");
	theApp.SetIdleTimer(30,".q");  // set up a failsafe timer to end the program
	theApp.Run(true);
	c1->Close();
}
