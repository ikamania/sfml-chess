#include <iostream>
#include <cstring>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Server 
{
public:
    int counter = 0;
    int sSocket = socket(AF_INET, SOCK_STREAM, 0);
    int cSocket;

    sockaddr_in sAddress;

    char message[1024] = {0};

    Server()
    {
        sAddress.sin_family = AF_INET;
        sAddress.sin_port = htons(8080);
        sAddress.sin_addr.s_addr = INADDR_ANY;
        sAddress.sin_addr.s_addr = INADDR_ANY;
    }

    ~Server() {}

    void run(std::string &message) 
    {
        std::cout << "PLAYER 1" << std::endl;
        
        int opt = 1;

        setsockopt(sSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        bind(sSocket, (struct sockaddr*)&sAddress, sizeof(sAddress));
        
        listen(sSocket, 5);

        cSocket = accept(sSocket, nullptr, nullptr);

        while (1)
        {
            recv(cSocket, &message[0], message.size(), 0);
        }

        close(cSocket);
        close(sSocket);
    }

    void sendToOpponent(std::string message)
    {   
        send(cSocket, message.c_str(), message.size(), 0);
    }
};
