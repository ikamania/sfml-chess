#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Client
{
public:
    int cSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in sAddress;
    
    Client() 
    {
        sAddress.sin_family = AF_INET;
        sAddress.sin_port = htons(8080);
        sAddress.sin_addr.s_addr = INADDR_ANY;   
    }

    bool connectToServer()
    {
        if (connect(cSocket, (struct sockaddr*)&sAddress, sizeof(sAddress)) < 0)
            return false;
        
        const char* message = "Hello, server!";
        send(clientSocket, message, strlen(message), 0);
        return true;
    }

    void run()
    {

    }
};
