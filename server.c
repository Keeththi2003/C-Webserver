#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define PORT 8080

void handleClient(int clientfd);
void sendFile(int clientfd, char *file);
char *getFileType(char *path);

int main()
{
    printf("Server running at: http://localhost:%d/\n", PORT);

    int serverfd, clientfd;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t clientfdLength = sizeof(clientaddr);

    serverfd = socket(AF_INET, SOCK_STREAM, 0); // create tcp socket

    if (serverfd < 0)
    {
        printf("Socket creation failed\n");
        exit(1);
    }

    serveraddr.sin_family = AF_INET;         // for use IPv4
    serveraddr.sin_addr.s_addr = INADDR_ANY; // listen all network interfaces
    serveraddr.sin_port = htons(PORT);       // set port

    if (bind(serverfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        printf("Bind failed\n");
        close(serverfd);
        exit(1);
    }

    if (listen(serverfd, 6) < 0)
    {
        printf("Listen failed\n");
        close(serverfd);
        exit(1);
    }

    while (1)
    {
        clientfd = accept(serverfd, (struct sockaddr *)&clientaddr, &clientfdLength);

        if (clientfd < 0)
        {
            printf("Accept failed\n");
            close(serverfd);
            exit(1);
        }

        printf("Connected\n");

        handleClient(clientfd);

        printf("Disconnected\n");
    }

    close(serverfd);

    return 0;
}

void handleClient(int clientfd)
{
    char *method, *path, *protocol;
    char request[10000];

    ssize_t bytesRead = read(clientfd, request, sizeof(request));

    if (bytesRead < 0)
    {
        printf("Read failed\n");
        close(clientfd);
        exit(1);
    }

    printf("Client request = %s\n", request);

    method = strtok(request, " ");
    path = strtok(NULL, " ");
    protocol = strtok(NULL, " ");

    printf("Method = %s\n", method);
    printf("Path = %s\n", path);

    if (strncmp(method, "GET", 3) != 0)
    {
        printf("Unsupported Method\n");

        // Handle unsupported methods
        char response[10000];
        sprintf(response, "HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n<html><body><h1>405 Method Not Allowed</h1></body></html>");
        write(clientfd, response, strlen(response));
        close(clientfd);
        return;
    }

    if (path == NULL || strcmp(path, "/") == 0)
    {
        path = "/index.html";
    }

    sendFile(clientfd, path);
}

void sendFile(int clientfd, char *path)
{
    FILE *filePath;
    char *fileType;
    char file_buffer[10000];
    char response[10000];

    filePath = fopen(path + 1, "r"); // Skip the leading "/"

    if (filePath == NULL)
    {
        filePath = fopen("404.html", "r");

        if (filePath == NULL)
        {
            sprintf(response,
                    "HTTP/1.1 404 Not Found\r\n"
                    "Content-Type: text/html\r\n"
                    "Connection: close\r\n\r\n"
                    "<html><body><h1>404 Not Found</h1></body></html>");

            write(clientfd, response, strlen(response));
        }
        else
        {
            sprintf(response,
                    "HTTP/1.1 404 Not Found\r\n"
                    "Content-Type: text/html\r\n"
                    "Connection: close\r\n\r\n");

            write(clientfd, response, strlen(response));

            while (fgets(file_buffer, sizeof(file_buffer), filePath) != NULL)
            {
                write(clientfd, file_buffer, strlen(file_buffer));
            }
        }
    }
    else
    {
        fileType = getFileType(path);

        if (fileType == NULL)
        {
            fileType = "application/octet-stream"; // Default type for unknown files
        }

        sprintf(response,
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: %s\r\n"
                "Connection: close\r\n\r\n",
                fileType);

        write(clientfd, response, strlen(response));

        size_t bytes;
        while ((bytes = fread(file_buffer, 1, sizeof(file_buffer), filePath)) > 0)
        {
            write(clientfd, file_buffer, bytes);
        }
    }

    printf("Server response %s\n", response);

    fclose(filePath);

    close(clientfd);
}

char *getFileType(char *path)
{
    if (strstr(path, ".html"))
    {
        return "text/html";
    }
    if (strstr(path, ".css"))
    {
        return "text/css";
    }
    if (strstr(path, ".js"))
    {
        return "application/javascript";
    }
    if (strstr(path, ".jpg") || strstr(path, ".jpeg"))
    {
        return "image/jpeg";
    }
    if (strstr(path, ".png"))
    {
        return "image/png";
    }
    if (strstr(path, ".mp4"))
    {
        return "video/mp4";
    }
    if (strstr(path, ".mp3"))
    {
        return "audio/mp3";
    }
    if (strstr(path, ".pdf"))
    {
        return "application/pdf";
    }
    return NULL; // Return NULL if no match is found
}
