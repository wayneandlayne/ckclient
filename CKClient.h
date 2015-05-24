#ifndef ckclient_h
#define ckclient_h
#include "WProgram.h"	
#include "Print.h"
#include "Stream.h"
#include "Client.h"

class CKClient : public Client {

public:
  CKClient();
  CKClient(uint8_t);
  CKClient(uint8_t *, uint16_t);

  uint8_t status();
  uint8_t connect();
  int connect(const char*, uint16_t);
  int connect(IPAddress ip, uint16_t port);
  size_t write(uint8_t);
  size_t write(const char *str);
  size_t write(const uint8_t *buf, size_t size);
  int available();
  int read();
  int read(uint8_t *buf, size_t size);
  int peek();
  void flush();
  void stop();
  uint8_t connected();
  //uint8_t operator==(int);
  //uint8_t operator!=(int);
  operator bool();

  friend class Server;

private:
  static uint16_t _srcport;
  uint8_t _sock;
  uint8_t *_ip;
  uint16_t _port;
  TCPSocket _socket;
  IPSTATUS _ipstatus;
};

#endif
