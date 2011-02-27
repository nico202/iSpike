#include "iSpike/Reader/YarpTextReader.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

std::string YarpTextReader::getData()
{
  boost::mutex::scoped_lock lock(this->mutex);
  return this->buffer;
}

void YarpTextReader::workerFunction()
{
  std::map<std::string, YarpPortDetails*>* portMap = this->yarpConnection->getPortMap();
  std::map<std::string, YarpPortDetails*>::iterator iter = portMap->find(this->getPortName());
  std::string ip;
  std::string port;
  std::string type;
  if (iter != portMap->end() )
  {
      ip = iter->second->getIp();
      port = iter->second->getPort();
      type = iter->second->getType();
      std::cout << "IP: " << ip << std::endl;
  } else {
    std::cout << "Iterator is empty!" << std::endl;
  }
  this->yarpConnection->connect_to_port(ip, port);
  this->yarpConnection->prepare_to_read_text();
  while(true)
  {
    boost::mutex::scoped_lock lock(this->mutex);
    this->buffer = this->yarpConnection->read_until("\n");
  }
}

YarpTextReader::YarpTextReader(std::string portName, std::string yarpIP, std::string yarpPort)
{
  this->setPortName(portName);
  this->yarpConnection = new YarpConnection(yarpIP, yarpPort);
  this->setThreadPointer(boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&YarpTextReader::workerFunction, this))));
}