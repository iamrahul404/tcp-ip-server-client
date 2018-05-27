
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXPENDING 5


int main(){
    int serverSock,clntSock,clntLen;
    struct sockaddr_in servAddr;
    struct sockaddr_in clntAddr;
    unsigned int servPort;
    servPort = 8877;
    if((serverSock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
        printf("Problem in creating socket\n");
    memset(&servAddr,0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(servPort);
    if (bind(serverSock,(struct sockaddr*)&servAddr, sizeof(servAddr))<0)
        printf("error in binding");

    if (listen(serverSock,MAXPENDING)<0)
        printf("error here at listening");

    for (;;) {
        clntLen = 0;
        if ((clntSock = accept(serverSock,(struct sockaddr*)&clntAddr,&clntLen))<0)
            printf("error here at accepting the message");
        else
            printf("connection accepted\n");

        printf("Handling client %s\n",inet_ntoa(clntAddr.sin_addr));

        int n = 0;
        int len = 0, maxlen = 100;
        char buffer[maxlen];
        char* pbuffer = buffer;

        // will remain open until the server terminates the connection
        while ((n = recv(clntSock, pbuffer, maxlen, 0)) > 0) {
            pbuffer += n;
            maxlen -= n;
            len += n;

            buffer[len] = '\0';
            printf("received: '%s'\n", buffer);

            // sending back to the client
            send(clntSock,buffer,len,0);
            }
        close(clntSock);
        }
    close(serverSock);
    return 0;

}