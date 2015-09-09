#include <QTime>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int N=1e9;
	QTime timer;
	FILE *inf,*outf;

	timer.start();
	unsigned char *X1=(unsigned char *)malloc(sizeof(unsigned char)*N);
	unsigned char *X2=(unsigned char *)malloc(sizeof(unsigned char)*N);
	printf("Memory allocation: %d ms; %g MB/sec\n",timer.elapsed(),2*N*1e-6/(timer.elapsed()*1e-3));

	timer.start();
	for (int i=0; i<N; i++) {
		X1[i]=12;
	}
	printf("Array filling: %d ms; %g MB/sec\n",timer.elapsed(),N*1e-6/(timer.elapsed()*1e-3));

	timer.start();
	memcpy(X2,X1,N);
	printf("memcpy: %d ms; %g MB/sec\n",timer.elapsed(),N*1e-6/(timer.elapsed()*1e-3));

	printf("Freeing file caches\n");
	system("echo 1 > /proc/sys/vm/drop_caches");

	timer.start();
	outf=fopen("/dev/shm/shmiotest1.dat","w");
	fwrite(X1,sizeof(unsigned char),N,outf);
	fflush(outf);
	fclose(outf);
	printf("Writing to /dev/shm: %d ms; %g MB/sec\n",timer.elapsed(),N*1e-6/(timer.elapsed()*1e-3));

	printf("Freeing file caches\n");
	system("echo 1 > /proc/sys/vm/drop_caches");

	timer.start();
	inf=fopen("/dev/shm/shmiotest1.dat","r");
	fread(X2,sizeof(unsigned char),N,inf);
	fflush(inf);
	fclose(inf);
	printf("Reading from /dev/shm: %d ms; %g MB/sec\n",timer.elapsed(),N*1e-6/(timer.elapsed()*1e-3));

	printf("Freeing file caches\n");
	system("echo 1 > /proc/sys/vm/drop_caches");

	timer.start();
	outf=fopen("/tmp/shmiotest2.dat","w");
	fwrite(X1,sizeof(unsigned char),N,outf);
	fflush(outf);
	fclose(outf);
	printf("Writing to /tmp: %d ms; %g MB/sec\n",timer.elapsed(),N*1e-6/(timer.elapsed()*1e-3));

	printf("Freeing file caches\n");
	system("echo 1 > /proc/sys/vm/drop_caches");

	timer.start();
	inf=fopen("/tmp/shmiotest2.dat","r");
	fread(X2,sizeof(unsigned char),N,inf);
	fflush(inf);
	fclose(inf);
	printf("Reading from /tmp: %d ms; %g MB/sec\n",timer.elapsed(),N*1e-6/(timer.elapsed()*1e-3));

	printf("Freeing file caches\n");
	system("echo 1 > /proc/sys/vm/drop_caches");

	timer.start();
	system("cp /dev/shm/shmiotest1.dat /dev/shm/shmiotest3.dat");
	printf("System file copy in /dev/shm: %d ms; %g MB/sec\n",timer.elapsed(),N*1e-6/(timer.elapsed()*1e-3));

	printf("Freeing file caches\n");
	system("echo 1 > /proc/sys/vm/drop_caches");

	timer.start();
	system("cp /tmp/shmiotest2.dat /tmp/shmiotest3.dat");
	printf("System file copy in /tmp: %d ms; %g MB/sec\n",timer.elapsed(),N*1e-6/(timer.elapsed()*1e-3));

	timer.start();
	free(X1);
	free(X2);
	printf("Memory deallocation: %d ms; %g MB/sec\n",timer.elapsed(),2*N*1e-6/(timer.elapsed()*1e-3));

	return 0;
}
