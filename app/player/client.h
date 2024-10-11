#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Client
{
public:
    int cSocket = socket(AF_INET, SOCK_STREAM, 0);
    int running = true;

    sockaddr_in sAddress;

    char message[1024] = {0};
    
    Client() 
    {
        sAddress.sin_family = AF_INET;
        sAddress.sin_port = htons(8080);
        sAddress.sin_addr.s_addr = INADDR_ANY; 
        sAddress.sin_addr.s_addr = INADDR_ANY;
    }

    ~Client() 
    {
        close(cSocket);
    }

    bool connectToServer()
    {
        if (connect(cSocket, (struct sockaddr*)&sAddress, sizeof(sAddress)) < 0)
            return false;

        return true;
    }

    void run()
    {
        while (running)
        {
            recv(cSocket, message, sizeof(message), 0); 
            std::cout << "Message from Server: " << message << std::endl;
        }
    }

    void sendToOpponent(const char *message)
    {   
        send(cSocket, message, strlen(message), 0);
    }
};
