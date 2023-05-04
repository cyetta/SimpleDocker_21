#include <fcgi_stdio.h>
#include <stdio.h>

int main (void) {
	while(FCGI_Accept() >= 0) {
		printf("Status: 200 OK\r\n");
		printf("Content-type: text/html\r\n\r\n");
		printf("<!DOCTYPE html>");
		printf("<html lang=\"en\">");
		printf("<head>");
		printf("<meta charset=\"UTF-8\">");
		printf("<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
		printf("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
		printf("<title>Hello world!</title>");
		printf("</head>");
		printf("<body>");
		printf("<H2>Hello world!</H2>");
		printf("</body>");
		printf("</html>");
	}
	return 0;
}