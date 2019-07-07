#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int s;
	struct sockaddr_in server, client;
	int c, l;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("Eroare la crearea socketului server\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 1;
	}

	listen(s, 16);
	srand(time(NULL));

	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	while (1) {
		uint32_t nr, nr_rand, resp, tries;
		c = accept(s, (struct sockaddr *) &client, &l);
		tries = 0;
		nr_rand = rand() % 100 + 1;
		printf("S-a conectat un client. Numarul sau este %u.\n", nr_rand);
		// deservirea clientului
		while (1) {
			++tries;
			recv(c, &nr, sizeof(nr), MSG_WAITALL);
			nr = ntohl(nr);
			printf("%u\n", nr);
			if (nr < nr_rand) resp = '<';
			if (nr > nr_rand) resp = '>';
			if (nr == nr_rand) resp = '=';
			resp = htonl(resp);
			send(c, &resp, sizeof(resp), 0);
			if (nr == nr_rand) break;
		}
		tries = htonl(tries);
		send(c, &tries, sizeof(tries), 0);
		close(c);
		// sfarsitul deservirii clientului;
	}
}

