

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXBUFFER 1024

int main(){
    int clntSock;
    struct sockaddr_in servAddr;
    char *servIP = "127.0.0.1";
    char *string;
    int stringLen;
    int totalBytesRcvd,bytesRcvd;

    if ((clntSock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
        printf("error here at socket creation");

    memset(&servAddr,0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(8877);
    servAddr.sin_addr.s_addr = inet_addr(servIP);
    if (connect(clntSock,(struct sockaddr *)&servAddr, sizeof(servAddr))<0)
        printf("error in connection making");
    //memset(string,'\0', sizeof(string));
    string = "Hello";
    stringLen = strlen(string);
    if (send(clntSock,string,stringLen,0) != stringLen)
        printf("Error in sending Data");

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
    }
    close(clntSock);

    return 0;
}

