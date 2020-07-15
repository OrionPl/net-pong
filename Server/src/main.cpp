#include <iostream>

#include "Networking.hpp"
#include "Server.hpp"

int main(int argc, char*[])
{
    Networking* net = new Networking(66666);
    Server* serv = net->GetServer();
    
    system("pause");
    return 0;
}