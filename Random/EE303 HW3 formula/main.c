//Ryan Jensen
//2013-09-15
//Program for EE303 HW#3 Problem 3.53
//Plot Relative Fermi Energy Level as a function of the donor doping concentration

#include <stdio.h>
#include <math.h>

//begin program
int main(){
	
	//constants
	const double ni = 1.55e+12; // intrinsic carrier concentration at 400K (per cubic cm)
	
	//variables
	double Nd; // doner concentration (per cubic cm)
	double n0; // electron concentration (per cubic cm)
	double kT = 0.0259 * 400 / 300; // kT at 400 K
	double Ef_Efi; // Fermi Energy Level relative to the Intrinsic Fermi Energy Level.
	
	//the calculation loop
	for(Nd = 1e+14; Nd<=1e+18; Nd*=10){ // start at 10^14, end at 10^18, increment by a factor of 10.
		n0 = (Nd/2) + sqrt( (Nd*Nd/4) + ni*ni  ); // calculate n0
		Ef_Efi = kT * log(n0/ni); // calculate Ef - Efi
		printf("Nd = %e\t\t Ef - Efi = %.3f\n",Nd,Ef_Efi); // print the results
	}
	return 0; //end the program
}
