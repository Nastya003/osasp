#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define PI 3.1415926535


float PowFloat(float value,int in)
{
    int i;
    float result=1;
    for(i=1;i<=abs(in);i++)
      result*=value;
    return result;
}

int PowMinusOne(int in)
{
    if((in%2)==0) return 1;
      else return -1;
}

int TailorFunction(int K, int N)
{
    FILE *input,*output;
    char InPath[]="./math.txt";
    char OuPath[]="./result.txt";

    if((input=fopen(InPath,"w+"))==NULL)
    {
        fprintf(stderr, "Input file open error\n");
        return 1;
    }

    long int factorial=1;
    int cnt=1;
    int sign;
    float degree;
    float perem=0;
    pid_t pid;

    for (int i=1;i<=N;i++)
    {
	for (int j=1;j<=K;j++)
	{
	   pid = fork();
           switch(pid) {
                case -1:
			fprintf(stderr, "Fork error!");
                        exit(1);
                case 0:
                        degree=PowFloat((2*PI*i/N),2*j+1);
                        sign=PowMinusOne(j+2);
                        perem=sign*degree/factorial;
                        cnt=cnt+2;
                        factorial=factorial*(cnt-1)*cnt;
                        fprintf(stdout,"PID=%d and perem[%d]=%.25f\n",getpid(),i,perem);
                        if(fprintf(input, "%d %d %.8lf\n", getpid(), i, perem) ==-1)
                        {
                                fprintf(stderr,"Input file error\n");
                                return 1;
                        }
                        exit(0);
                default:
                    break;
           }
	}
    }

    while (wait(NULL) > 0) { };

    if((output=fopen(OuPath,"w"))==NULL)
    {
        fprintf(stderr,"Output file open error\n");
        return 1;
    }

    double *result = alloca(sizeof(double)*N);
    memset(result, 0, sizeof(double)*N);
    rewind(input);

    int pidd, f;
    double member_value;
 
    for (int i = 0; i < N*K; i++) {
        if (fscanf(input, "%d %d %lf", &pidd, &f, &member_value) == -1){
        	fprintf(stderr, "Input file read error\n");
        	return 1;
        }
        result[f] += member_value;
    }

    for (int i = 0; i < N; i++)
    {
        if (fprintf(output, "y[%d]=%.8lf\n", i, result[i]) == -1)
	{
        	fprintf(stderr,"Output write error\n");
        	return 1;
        }
    }

    if(fclose(input)==-1)
    {
        perror("Close error:\n");
        return 1;
    }

    if(fclose(output)==-1)
    {
        perror("Close error:\n");
        return 1;
    }

    return 0;
}

int main(int argc,char *argv[])
{
    int K,N;
    if(argc<3)
    {
        fprintf(stderr,"Error:Too few arguments!\n");
        return 1;
    }

    K=atoi(argv[1]);
    N=atoi(argv[2]);
    TailorFunction(K,N);
    return 0;
}
