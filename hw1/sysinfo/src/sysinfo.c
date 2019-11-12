#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>

int main()
{
	char hostbuffer[256];
	int hostname;
	struct sysinfo info;	

	// To retrieve hostname
	hostname = gethostname(hostbuffer, sizeof(hostbuffer));
	
	// To retrieve system informations
	if(sysinfo(&info) != 0){
		printf("sysinfo: error reading system statistics\n");	
	}
	
	printf("Hostname: %s\n", hostbuffer);
	printf("Uptime: %ld:%ld:%ld\n", info.uptime/3600, info.uptime%3600/60, info.uptime%60);	
	printf("Total Ram: %ld Byte\n", info.totalram);
	printf("Free Ram: %ld Byte\n", info.freeram);
	printf("Process count: %d\n", info.procs);
	printf("Page size: %ld bytes\n", sysconf(_SC_PAGESIZE));
	
	return 0;
}
