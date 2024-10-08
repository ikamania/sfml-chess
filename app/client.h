#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Client
{
public:
    int Role;
    int Player;
    int sSocket;
    int cSocket;

    char message[1024] = { 0 };
    sockaddr_in sAddress;

    Client(int Player)
    {
        sSocket = socket(AF_INET, SOCK_STREAM, 0);

        sAddress.sin_family = AF_INET;
        sAddress.sin_port = htons(8080);
        sAddress.sin_addr.s_addr = INADDR_ANY;
    };

    ~Client() 
    { 
        close(sSocket); 
    };

    void play()
    {
        if (connServer())
            Role = sSocket;
        else    
            makeServer(); Role = cSocket;

        listenToOpponent();
    }
    
    void listenToOpponent()
    {
        while (1)
        {
            recv(Role, message, sizeof(message), 0);

            std::cout << message << std::endl;
            memset(message, 0, sizeof(message));
        }
    }

    void sendMessage()
    {
        const char* message = "Hello, server!";
        
        send(Role, message, strlen(message), 0);
    }

    bool connServer()
    {
        if (connect(sSocket, (struct sockaddr*)&sAddress, sizeof(sAddress)) < 0)
            return false;

        return true;
    }

    void makeServer()
    {
        bind(sSocket, (struct sockaddr*)&sAddress, sizeof(sAddress)); listen(sSocket, 5);

        cSocket = accept(sSocket, nullptr, nullptr);
    }
};
