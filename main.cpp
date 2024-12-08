#include "app/app.h"

void run()
{
    Client *client = new Client();

    if (client->connectToServer())
        runThreads(client);
    else
    {
        Server *server = new Server();

        runThreads(server);

        delete client;
        delete server;
    }
}

int main(int argc, char *argv[])
{
    run();

    return 1;
}
