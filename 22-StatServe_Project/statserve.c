#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "../05-Debugging_and_Macros/18-DebugMacros.h"
#include "../19-Ring_Buffer/42-RingBuffer_Library.h"
#include "statserve_protocol.h"

#define PORT 7899

int main(int argc, char *argv[])
{
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024];
    StatServer *srv = StatServer_create();

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    check(server_fd >= 0, "Socket failed.");

    check(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == 0, "Setsockopt failed.");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    check(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) >= 0, "Bind failed.");
    check(listen(server_fd, 3) >= 0, "Listen failed.");

    log_info("StatServe (Ex 48-51) started on port %d.", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) continue;

        log_info("Client connected.");

        while (1) {
            memset(buffer, 0, 1024);
            int valread = read(client_fd, buffer, 1024);
            if (valread <= 0) break;

            bstring input = bfromcstr(buffer);
            btrimws(input);
            bstring output = StatServer_process(srv, input);
            
            send(client_fd, bdata(output), blength(output), 0);
            
            bdestroy(input);
            bdestroy(output);
        }
        close(client_fd);
    }

    StatServer_destroy(srv);
    return 0;

error:
    return 1;
}
