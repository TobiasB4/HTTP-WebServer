#include <iostream>
#include "Socket.h"


int main() { 
  // Correct way to obtain an instance of ServerSocket using GetInstance()
  my_socket::ServerSocket *server_socket_instance =
      my_socket::ServerSocket::GetInstance();

  server_socket_instance->SetupSocket();
  my_socket::ServerSocket::ReleaseInstance();
  return 0;
}