#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Client
{
public:
    int cPlayer;
    int sSocket;

    sockaddr sAddress;
    
    Client(int cPlayer) 
    {
        sAddress.sin_family = AF_INET;
        sAddress.sin_port = htons(PORT);
        sAddress.sin_addr.s_addr = INADDR_ANY;

        if (bind(sSocket, (struct sockaddr*)&sAddress, sizeof(sAddress)) < 0)
        {
            std::cout << "Failed to connect !" << std::endl;
            close(sSocket);
        } /// NEED
    };
    
};

