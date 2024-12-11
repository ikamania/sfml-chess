#include <iostream>
#include <cstring>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Client
{
public:
    int counter = 1;
    int cSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in sAddress;

    char message[1024] = {0};
    
    Client()
    {
        sAddress.sin_family = AF_INET;
        sAddress.sin_port = htons(8080);
        sAddress.sin_addr.s_addr = INADDR_ANY; 
        sAddress.sin_addr.s_addr = INADDR_ANY;
    }

    ~Client() {}

    bool connectToServer()
    {
        if (connect(cSocket, (struct sockaddr*)&sAddress, sizeof(sAddress)) < 0)
            return false;

        return true;
    }

    void run(std::string &message)
    {
        std::cout << "{ PLAYER 2 }" << std::endl;

        while (1)
        {
            recv(cSocket, &message[0], message.size(), 0);
 
            std::cout << "Server: " << message << std::endl;
        }

        close(cSocket);
    }

    void sendToOpponent(std::string message)
    {   
        std::cout << message << std::endl;
        send(cSocket, message.c_str(), message.size(), 0);
    }
};
