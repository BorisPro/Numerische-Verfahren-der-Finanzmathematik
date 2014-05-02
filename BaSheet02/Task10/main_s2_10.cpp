/*
 * main02_09.cpp
 *
 *  Created on: 01.05.2014
 *      Author: boris
 */

#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "NumericalIntegrator.h"
#include "TrapezoidalIntegrator.h"
#include "ClenshawIntegrator.h"
#include "GaussLegendreIntegrator.h"
#include "MonteCarloIntegrator.h"

#include "CDFNormalDice.h"

using namespace std;

inline void writeIntegrationDataToFile(const NumericalIntegrator & Integrator, int maxLevel, const char * filename, double K);


void main_s2_10(){
  const int maxLevel = 11;

  writeIntegrationDataToFile(TrapezoidalIntegrator(),   maxLevel, "data_callF_Trapezodial_K=10",   10.);
  writeIntegrationDataToFile(ClenshawIntegrator(),      maxLevel, "data_callF_Clenshaw_K=10",      10.);
  writeIntegrationDataToFile(GaussLegendreIntegrator(), maxLevel, "data_callF_GaussLegendre_K=10", 10.);
  writeIntegrationDataToFile(MonteCarloIntegrator(),    maxLevel, "data_callF_MonteCarlo_K=10",    10.);

  writeIntegrationDataToFile(TrapezoidalIntegrator(),   maxLevel, "data_callF_Trapezodial_K=0",   0.);
  writeIntegrationDataToFile(ClenshawIntegrator(),      maxLevel, "data_callF_Clenshaw_K=0",      0.);
  writeIntegrationDataToFile(GaussLegendreIntegrator(), maxLevel, "data_callF_GaussLegendre_K=0", 0.);
  writeIntegrationDataToFile(MonteCarloIntegrator(),    maxLevel, "data_callF_MonteCarlo_K=0",    0.);
}

inline double callFunction(double x, double K){
  const double S0 = 10., mu = 0.1, sigma = 0.2, T = 2.;
  const double value = S0 * exp((mu - 0.5 * sigma * sigma) * T + sigma * sqrt(T) * x);
  return value > K ? value - K : 0.;
}

inline void openOutputFile(ofstream& myfile, const char * filename) {
  cout << "    opening " << filename << "... ";
  myfile.open(filename);
  myfile << std::setprecision(20);
  cout << "    writing data..." << endl;
}

inline void generateOutputDataWithCallFunc(int maxLevel, ostream & myfile, const NumericalIntegrator & Integrator, double K) {
  auto call_option_integrand = [](double x){return callFunction(CDFNormalDice::NormalCDFInverse(x), K);};
  for (int l = 1; l <= maxLevel; ++l) {
    myfile << l << " " << Integrator.integrate(l, call_option_integrand) << "\n";
  }
}

inline void writeIntegrationDataToFile(const NumericalIntegrator & Integrator, int maxLevel, const char * filename, double K) {
  ofstream outputFile;
  openOutputFile(outputFile, filename);

  generateOutputDataWithCallFunc(maxLevel, outputFile, Integrator, K);

  outputFile.close();
}

