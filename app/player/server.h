#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Server 
{
public:
    int sSocket = socket(AF_INET, SOCK_STREAM, 0);
    int running = true;
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

    ~Server()
    {
        close(sSocket);
    }

    void run() 
    {
        std::cout << "SERVER RUNED" << std::endl;
        bind(sSocket, (struct sockaddr*)&sAddress, sizeof(sAddress));
        listen(sSocket, 5);

        cSocket = accept(sSocket, nullptr, nullptr);
        std::cout << "accepted" << std::endl;

        while (running)
        {
            recv(cSocket, message, sizeof(message), 0); 
            std::cout << "Message from client: " << message << std::endl;
        }
    }

    void sendToOpponent(const char *message)
    {   
        send(cSocket, message, strlen(message), 0);
    }
};
