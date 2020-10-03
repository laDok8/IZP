/**
* IZP druhy projekt - Iteracni vypocty
* Autor: Ladislav Dokoupil, <xdokou14@stud.fit.vutbr.cz>
* Datum: 20.11.2019
*/ 

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define I_0 1e-12//saturation current A
#define U_T 25.8563e-3//thermal voltage V
#define LIMIT 1000

double I_p(double u){
	return I_0*(exp(u/U_T)-1);
}
double I_r(double u, double u0, double r){
	return (u0 - u) / r;
}
//calculate diference I_p I_r for inerval choice
double i_diff(double u, double u0, double r){
	return I_p(u) - I_r(u, u0, r);
}
//calculate diode voltage
double diode(double u0, double r, double eps){
	double uMin = 0, uMax = u0;
	double uMid;
	double delta, delta2;
	int iter = 0;

		do{
			uMid = (uMin + uMax)/2;
			delta = i_diff(uMid, u0, r);
			delta2 = uMax-uMid;
			iter++;

			if (delta > 0){
				uMax = uMid;
			}
			else{
				uMin = uMid;
			}	
		}
		while(delta2 > eps && iter < LIMIT);

	return uMid;
}
/**
//argv[1] = U_0
//argv[2] = R
//argv[3] = EPS
*/
int main(int argc, char **argv){
	double uMin, r, eps, up;
	int works[3];
	
	if(argc	>=	4){
		works[0] = sscanf(argv[1], "%lf", &uMin);
		works[1] = sscanf(argv[2], "%lf", &r);
		works[2] = sscanf(argv[3], "%lf", &eps);
		eps = fabs(eps);

		if(uMin >= 0 && r > 0 && works[0] && works[1] && works[2]){
			up = diode(uMin, r, eps);
			printf("Up=%g V\n", up);
			printf("Ip=%g A\n", I_p(up));
		}
		else{
			fprintf(stderr, "error: invalid arguments\n");
			return 1;
		}
	}
	else{
		fprintf(stderr, "error: not enough args\n");
		return 2;
	}
	return 0;
}