/* in-place complex fft; adapted from the FORTRAN of
Cooley, Lewis, and Welch; from Rabiner & Gold (1975)*/
#include <stdio.h>
#include <strings.h>
#include <math.h>

int main() {
FILE *fopen(), *fdata;
#define dB(x) (((fabs(x))>(0.0))?(20.*log10(fabs(x))):(-1000.))
#define verbose 2  /* 2 = print input and output */
#define N 1024     /* length of transform */
#define M 10       /* log N */
#define M_PI    3.14159265358979323846
int i, j, k, L;    /* indexes */
int LE, LE1, ip;
int NV2, NM1;	   //N divided by 2 and N minus 1
double ar[N], ai[N]; /* array of points */
double t;            /* temp */
double Ur, Ui, Wr, Wi, Tr, Ti;  //r denotes real and i stands for imaginary
double Ur_old;
double freq_test;
double mag;

fdata = fopen("data", "w");
NV2 = N/2;
NM1 = N-1;

/* generate original signal */
freq_test = 133.;
for (i=0; i<N; i++)
 { ar[i] = cos(freq_test*2.*M_PI*((double)i/(double)N));
   ai[i] = sin(freq_test*2.*M_PI*((double)i/(double)N)); }

if(verbose >= 2)
{ printf("input:\n");
  printf("real: ");
  for (i=0; i<N; i++)
   printf("%6.4lf ", ar[i]);
  printf("\nimag: ");
  for (i=0; i<N; i++)
   printf("%6.4lf ", ai[i]);
  printf("\n\n"); }

/* shuffle */
j = 1;
for (i=1; i<=NM1; i++)
 { if(i<j)            /* swap a[i] and a[j] */
    { t = ar[j-1];
      ar[j-1] = ar[i-1];
      ar[i-1] = t;
      t = ai[j-1];
      ai[j-1] = ai[i-1];
      ai[i-1] = t; }

  k = NV2;		/* bit-reversed counter */
  while(k<j)
   { j -= k;

     k /= 2; }

   j += k; }

if(verbose >= 2)
{ printf("shuffled input:\n");
  printf("real: ");
  for (i=0; i<N; i++)
   printf("%6.4lf ", ar[i]);
  printf("\nimag: ");
  for (i=0; i<N; i++)
   printf("%6.4lf ", ai[i]);
  printf("\n\n"); }

LE = 1.;
for (L=1; L<=M; L++)    /* stage L */
 { LE1 = LE;            /* LE1 = LE/2 */
   LE *= 2;             /* LE = 2^L */
   Ur = 1.0;
   Ui = 0.;
   Wr = cos(M_PI/(double)LE1);
   Wi = -sin(M_PI/(double)LE1);
 /* Cooley, Lewis, and Welch have "+" here */
   for (j=1; j<=LE1; j++)

   { for (i=j; i<=N; i+=LE) /* butterfly */
      { ip = i+LE1;
        Tr = ar[ip-1]*Ur-ai[ip-1]*Ui;     // T = a*U where a=e^(i*theta) and U is complex
        Ti = ar[ip-1]*Ui+ai[ip-1]*Ur;
        ar[ip-1] = ar[i-1] - Tr;          // a(ip-1) = a(i-1)-T where LE = wikipedia's m OR a(k+j) = u - T source Wikipedia
        ai[ip-1] = ai[i-1] - Ti;          //Note: ip = i+m/2 (wikipedia) AND s (Wikipedia) =L
	ar[i-1] = ar[i-1] + Tr;           // a(i-1) = a(i-1)+T OR a(k+j+m/2) = u + T source Wikipedia
	ai[i-1] = ai[i-1] + Ti; }
/* end of butterfly */

      Ur_old = Ur;                        //Should there be a Ui old as well? No, we need this dummy variable for Ur becaue Ur is calculated before Ui
      Ur = Ur_old*Wr-Ui*Wi;               //U = U*W where the final U = W^k
      Ui = Ur_old*Wi+Ui*Wr; } /* end of j loop */

} /* end of stage L */

if (verbose>=2)
 { printf("output:\n");
   printf("real: ");
   for(i=0; i<N; i++)
    printf("%6.4lf ", ar[i]);
   printf("\nimag: ");
   for(i=0; i<N; i++)
    printf("%6.4lf ", ai[i]);
   printf("\n"); }

fprintf(fdata,"Hz     magnitude     dB\n");
for(i=0; i<N; i++)
 { mag = sqrt(ar[i]*ar[i]+ai[i]*ai[i]);
fprintf(fdata,"%6.4lf %le %lf\n",(double)i/(double)N, mag, dB(mag));}

return 0;
} /* main */
