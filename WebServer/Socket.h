#ifndef SOCKET_H_
#define SOCKET_H_
#include <iostream>
#include <memory>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_PORT "8080"
namespace my_socket {
class ServerSocket {
 private:
  WSADATA _wsaData;
  addrinfo *_socket_info{nullptr};
  addrinfo *_ptr{nullptr};
  addrinfo _hints;
  SOCKET _listener{INVALID_SOCKET};

protected:
  ServerSocket();
  static ServerSocket *_server_socket;
private:
  bool CreateSocket();
  bool BindSocket();
  bool ListenSocket();

 public:
  ~ServerSocket();
  ServerSocket(ServerSocket &other) = delete;
  void operator=(const ServerSocket &other) = delete;
  static ServerSocket *GetInstance();
  static void ReleaseInstance();

  bool SetupSocket();
  bool AcceptSocket(SOCKET &clientSocket);

};
}  // namespace socket
#endif
