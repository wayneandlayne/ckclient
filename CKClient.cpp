
#include <DEIPcK.h>

extern "C" {
  #include "string.h"
}

#include "WProgram.h"

#include "CKClient.h"

uint16_t CKClient::_srcport = 1024;


CKClient::CKClient(){
}

CKClient::CKClient(uint8_t sock) : _sock(sock) {
}

CKClient::CKClient(uint8_t *ip, uint16_t port) : _ip(ip),_port(port) {
}



uint8_t CKClient::connect() {

  int status = deIPcK.tcpConnect((const char*) _ip, _port, _socket);
  while (!status)
  {
    DEIPcK::periodicTasks();
    status = deIPcK.tcpConnect((const char*) _ip, _port, _socket);
  }
  return status;
}


int CKClient::connect(const char* addr, uint16_t port) {
  int status = deIPcK.tcpConnect(addr, port, _socket);
  while (!status)
  {
    DEIPcK::periodicTasks();
    status = deIPcK.tcpConnect(addr, port, _socket);
  }
  return status;
}

int CKClient::connect(IPAddress ip, uint16_t port)
{
        Serial.println("connect(IP, port) NOT IMPLEMENTED");
	return 1;
}

size_t CKClient::write(uint8_t b) {
	return write(&b, 1);
}

size_t CKClient::write(const char *str) {
  size_t s = strlen(str);
  return write((const uint8_t*) str, s);
}

size_t CKClient::write(const uint8_t *buf, size_t size) {
  //this basically ignores error checking
  uint16_t bytes_written = 0;
  uint16_t total_bytes_written = 0;
  while (total_bytes_written != size)
  {
    bytes_written += _socket.writeStream(buf, size); //, &status);
    if (bytes_written)
    {
      total_bytes_written += bytes_written;
    } else
    {
       //either no bytes written or an error?
       //if IsIPStatusAnError(status)
    }
    DEIPcK::periodicTasks();
  }
  return total_bytes_written;
}

int CKClient::available() {
    DEIPcK::periodicTasks();
    return _socket.available();
}

int CKClient::read() {
  DEIPcK::periodicTasks();
  uint8_t b;
  if (!_socket.available())
  {
    return -1; //no data available
  } else
  {
    return _socket.readByte();
  }
}

int CKClient::read(uint8_t *buf, size_t size) {
  DEIPcK::periodicTasks();
  return _socket.readStream(buf, size);
}

int CKClient::peek() {
  DEIPcK::periodicTasks();
	return _socket.peekByte();
}

void CKClient::flush() {
  DEIPcK::periodicTasks();
	_socket.discardReadBuffer();
}

void CKClient::stop() {
  DEIPcK::periodicTasks();
   
      if (! _socket.isConnected())
      {
        _socket.close();
      }
}

uint8_t CKClient::connected() {
  DEIPcK::periodicTasks();
   
   uint8_t rc;
   IPSTATUS* ipstatus;
   if (rc = _socket.isConnected(ipstatus))
   {
      if (!rc) _socket.close();
   }
   return rc;
}


uint8_t CKClient::status() {
  Serial.println("status NOT IMPLEMENTED");
	//TODO
	return 0;
}

// the next three functions are a hack so we can compare the client returned
// by Server::available() to null, or use it as the condition in an
// if-statement.  this lets us stay compatible with the Processing network
// library.

/*
uint8_t CKClient::operator==(int p) {
  return _sock == MAX_SOCK_NUM;
}

uint8_t CKClient::operator!=(int p) {
  return _sock != MAX_SOCK_NUM;
}
*/

CKClient::operator bool() {
  return true; //TODO
}
