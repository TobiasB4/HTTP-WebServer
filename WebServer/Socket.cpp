#include "Socket.h"

namespace my_socket {
  ServerSocket::ServerSocket() {}
  ServerSocket::~ServerSocket() { 
    WSACleanup();
  }
  
  ServerSocket* ServerSocket::_server_socket = nullptr;

  ServerSocket *ServerSocket::GetInstance() { 
    if (_server_socket == nullptr) {
      _server_socket = new ServerSocket();
    }
    return _server_socket;
  }

  void ServerSocket::ReleaseInstance() { 
    if (_server_socket != nullptr) {
      delete _server_socket;
      _server_socket = nullptr;
    }
    std::cout << "Release Instance" << std::endl;
  }
  

  bool ServerSocket::CreateSocket() {
    int iResult;
    iResult = WSAStartup(MAKEWORD(2, 2), &_wsaData);
    if (iResult != 0) {
      std::cout << "WSAStartup failed: " << iResult << std::endl;
      return false;
    }
    std::cout << "WSAStartup Succeeded!" << std::endl;

    ZeroMemory(&_hints, sizeof(_hints));
    _hints.ai_family = AF_INET;
    _hints.ai_socktype = SOCK_STREAM;
    _hints.ai_protocol = IPPROTO_TCP;
    _hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &_hints, &_socket_info);
    if (iResult != 0) {
      std::cout << "getaddrinfo failed: " << iResult << std::endl;
      WSACleanup();
      return false;
    }
    std::cout << "getaddrinfo Succeeded!" << std::endl;

    _listener = socket(_socket_info->ai_family, _socket_info->ai_socktype,
                       _socket_info->ai_protocol);

    if (_listener == INVALID_SOCKET) {
      std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
      freeaddrinfo(_socket_info);
      WSACleanup();
      return false;
    }

    std::cout << "Socket created!" << std::endl;
    return true;
  }

  bool ServerSocket::BindSocket() { 
    int iResult =
        bind(_listener, _socket_info->ai_addr, static_cast<int>(_socket_info->ai_addrlen));
    if (iResult == SOCKET_ERROR) {
      std::cout << "Bind failed with error: " << WSAGetLastError() << std::endl;
      freeaddrinfo(_socket_info);
      closesocket(_listener);
      WSACleanup();
      return false;

    }

    freeaddrinfo(_socket_info);
    std::cout << "Bind succeeded!" << std::endl;
    return true;
  }

  bool ServerSocket::ListenSocket() {
    if (listen(_listener, SOMAXCONN) == SOCKET_ERROR) {
      std::cout << "Listen failed with error: " << WSAGetLastError()
                << std::endl;
      closesocket(_listener);
      WSACleanup();
      return false;
    }
    return true;
  }

  bool ServerSocket::SetupSocket() { 
    if(!CreateSocket()) return false;
    if (!BindSocket()) return false;
    return (!ListenSocket());
  }
  bool ServerSocket::AcceptSocket(SOCKET &clientSocket) {
    // TODO: Finish Implementation 
    return false;
  }
  }