#include "random.h"
#include <time.h>

/**
 Following Random number generation functions are from Numerical Recipe book
 */

/**
 * Return a random integer as the length of the next CPU burst
 * @param mean is the average CPU burst length, e.g. mean = 10
 */
int CPUBurstRandom(int mean) {
	static long n = -10;
	//static long n = time(NULL);
	float x = poidev((float) mean, &n);
	return (int) x;
}

/**
 * Return a random integer uniformly from the range of [min, max]
 */
int ranInt(int min, int max) {
	static long n = -1;
	float x = min + ran1(&n) * (max - min);
	return (int) x;
}

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

/**
 *	Minimal random number generator of Park and Miller with Bays-Durham shuffle and added
 *	safeguards. 
 *	@Return a uniform random deviate between 0.0 and 1.0 (exclusive of the endpoint values). 
 *  Call with idum a negative integer to initialize; thereafter, do not alter idum between 
 *  successive deviates in a sequence. RNMX should approximate the largest floating value that is
 *  less than 1.
 */
float ran1(long *idum)
{
	int j;
	long k;
	static long iy=0;
	static long iv[NTAB];
	float temp;

	if (*idum <= 0 || !iy) {
		if (-(*idum) < 1) *idum=1;
		else *idum = -(*idum);
		for (j=NTAB+7;j>=0;j--) {
			k=(*idum)/IQ;
			*idum=IA*(*idum-k*IQ)-IR*k;
			if (*idum < 0) *idum += IM;
			if (j < NTAB) iv[j] = *idum;
		}
		iy=iv[0];
	}
	k=(*idum)/IQ;
	*idum=IA*(*idum-k*IQ)-IR*k;
	if (*idum < 0) *idum += IM;
	j=iy/NDIV;
	iy=iv[j];
	iv[j] = *idum;
	if ((temp=AM*iy) > RNMX) return RNMX;
	else return temp;
}
#undef IA
#undef IM
#undef AM
#undef IQ
#undef IR
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX

/**
 * Compute the gamma function
 */
float gammln(float xx)
{
	double x,y,tmp,ser;
	static double cof[6]={76.18009172947146,-86.50532032941677,
		24.01409824083091,-1.231739572450155,
		0.1208650973866179e-2,-0.5395239384953e-5};
	int j;

	y=x=xx;
	tmp=x+5.5;
	tmp -= (x+0.5)*log(tmp);
	ser=1.000000000190015;
	for (j=0;j<=5;j++) ser += cof[j]/++y;
	return -tmp+log(2.5066282746310005*ser/x);
}

#define PI 3.141592654

/**
 * Returns as a floating-point number an integer value that is a random deviate drawn from a
 * Poisson distribution of mean xm, using ran1(idum) as a source of uniform random deviates.
 */
float poidev(float xm, long *idum)
{
	static float sq,alxm,g,oldm=(-1.0);
	float em,t,y;

	if (xm < 12.0) {
		if (xm != oldm) {
			oldm=xm;
			g=exp(-xm);
		}
		em = -1;
		t=1.0;
		do {
			++em;
			t *= ran1(idum);
		} while (t > g);
	} else {
		if (xm != oldm) {
			oldm=xm;
			sq=sqrt(2.0*xm);
			alxm=log(xm);
			g=xm*alxm-gammln(xm+1.0);
		}
		do {
			do {
				y=tan(PI*ran1(idum));
				em=sq*y+xm;
			} while (em < 0.0);
			em=floor(em);
			t=0.9*(1.0+y*y)*exp(em*alxm-gammln(em+1.0)-g);
		} while (ran1(idum) > t);
	}
	return em;
}
#undef PI
