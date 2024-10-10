#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Server
{
public:
    int sSocket = socket(AF_INET, SOCK_STREAM, 0);
    int cSocket;

    sockaddr_in sAddress;

    Server()
    {
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(8080);
        serverAddress.sin_addr.s_addr = INADDR_ANY;
    }

    void run()
    {
        bind(sSocket, (struct sockaddr*)&sAddress, sizeof(sAddress));
        listen(sSocket, 5);

        cSocket = accept(sSocket, nullptr, nullptr);

        while (1)
        {
            char buffer[1024] = { 0 };
            recv(clientSocket, buffer, sizeof(buffer), 0); 
            std::cout << "Message from client: " << buffer << std::endl;
        }
    }
}
