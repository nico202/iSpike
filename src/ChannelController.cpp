/*
 * ChannelController.cpp
 *
 *  Created on: 7 Jan 2011
 *      Author: cembo
 */
#include <string>
#include <iostream>
#include <iSpike/ChannelController.hpp>
#include <iSpike/YarpConnection.hpp>
#include <iSpike/Reader/FileVisualReader.hpp>
#include <iSpike/Reader/YarpVisualReader.hpp>
#include <iSpike/Reader/YarpAngleReader.hpp>
#include <iSpike/Channel/VisualInputChannel.hpp>
#include <iSpike/Channel/JointInputChannel.hpp>
#include <iSpike/Channel/JointOutputChannel.hpp>
#include <iSpike/Writer/YarpAngleWriter.hpp>

void ChannelController::getInputChannels()
{

}

void ChannelController::getOutputChannels()
{

}

std::vector< std::vector<int> > ChannelController::getFiring(int channelId)
{
  std::map<int, InputChannel*>::iterator iter = inputChannelDirectory->find(channelId);
  if (iter != inputChannelDirectory->end() )
  {
    return iter->second->getFiring();
  } else {
    std::cout << "Iterator is empty!" << std::endl;
  }
}

void ChannelController::setFiring(int channelId, std::vector<int>* spikes)
{
  std::map<int, OutputChannel*>::iterator iter = outputChannelDirectory->find(channelId);
  if (iter != outputChannelDirectory->end() )
  {
    return iter->second->setFiring(spikes);
  } else {
    std::cout << "Iterator is empty!" << std::endl;
  }
}

ChannelController::ChannelController()
{
  inputChannelDirectory = new std::map<int, InputChannel*>();
  YarpInterface::initialise("127.0.0.1", "10006");
  //YarpAngleReader* headJoints = new YarpAngleReader("/icubSim/head/state:o");
  //const char* filename = "C:\\Users\\cembo\\workspace\\SpikeAdapter\\bin\\image.ppm";
  //FileVisualReader* fileReader = new FileVisualReader(filename);
  //this->inputChannelDirectory->insert(std::pair<int, InputChannel*>(1, new VisualInputChannel(fileReader)));
  //this->inputChannelDirectory->insert(std::pair<int, InputChannel*>(1, new JointInputChannel(headJoints)));
  this->outputChannelDirectory = new std::map<int, OutputChannel*>();
  YarpAngleWriter* headJoints = new YarpAngleWriter("/icubSim/left_arm/rpc:i");
  this->outputChannelDirectory->insert(std::pair<int, OutputChannel*>(1, new JointOutputChannel(headJoints)));
}

void ChannelController::inputChannelSubscribe(int channelId)
{
  std::map<int, InputChannel*>::iterator iter = inputChannelDirectory->find(channelId);
  if (iter != inputChannelDirectory->end() )
  {
    iter->second->start();
  } else {
    std::cout << "Iterator is empty!" << std::endl;
  }
}
void ChannelController::outputChannelSubscribe(int channelId)
{
  std::map<int, OutputChannel*>::iterator iter = outputChannelDirectory->find(channelId);
  if (iter != outputChannelDirectory->end() )
  {
    iter->second->start();
  } else {
    std::cout << "Iterator is empty!" << std::endl;
  }
}
