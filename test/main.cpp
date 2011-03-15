/*
 * This file includes the magic necessary in order to get your unit tests
 * that you create with UnitTest++ to automatically run. There should
 * never be a reason to modify this file. For an example unit test,
 * see "sanity_check.cpp". For a reference on creating tests, see "test.h".
 *
 */
#include "test.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <iSpike/Reader/ReaderFactory.hpp>
#include <iSpike/Reader/FileAngleReader.hpp>
#include <iSpike/Reader/ReaderDescription.hpp>
#include <iSpike/Property.hpp>
#include <iSpike/Channel/InputChannel/InputChannelFactory.hpp>
#include <iSpike/Channel/InputChannel/JointInputChannel.hpp>
#include <boost/lexical_cast.hpp>
#include <iSpike/Channel/OutputChannel/OutputChannelDescription.hpp>
#include <iSpike/Channel/OutputChannel/OutputChannelFactory.hpp>
#include <iSpike/Channel/OutputChannel/OutputChannel.hpp>
#include <iSpike/Writer/WriterFactory.hpp>
#include <iSpike/Writer/WriterDescription.hpp>
#include <iSpike/Writer/Writer.hpp>
//#include <iSpike/ChannelController.hpp>
//#include <iSpike/YarpConnection.hpp>
//#include <iSpike/Reader/YarpTextReader.hpp>
//#include <iSpike/Reader/YarpVisualReader.hpp>
//#include <iSpike/Channel/InputChannel/VisualInputChannel.hpp>
//#include <iSpike/Bitmap.hpp>
#include <iSpike/Common.hpp>
//#include <boost/thread/thread.hpp>
//#include <boost/date_time/posix_time/posix_time_types.hpp>


int main(int argc, char* argv[])
{
      std::cout << "Select the type of Channel you want to create" << std::endl;
      std::cout << "(1)Input Channel (2)Output Channel" << std::endl;
      int typeOfChannel;
      std::cin >> typeOfChannel;
      std::cin.ignore();
      if(typeOfChannel == 1)
      {
        ReaderFactory readerFactory;
        InputChannelFactory channelFactory;
        //get all input channels and output them to the console
        std::vector<InputChannelDescription> inputChannelDescriptions = channelFactory.getAllChannels();
        std::cout << "Available Input Channels:" << std::endl;
        for(int i = 0; i < inputChannelDescriptions.size(); i++)
        {
          std::cout << i << ": " << inputChannelDescriptions[i].getChannelName() << ": " << inputChannelDescriptions[i].getChannelDescription() << std::endl;
        }

        //let the user pick a channel
        std::cout << "Please select a channel:" << std::endl;
        int selectedChannel = -1;
        while(selectedChannel < 0 || selectedChannel > (inputChannelDescriptions.size() - 1))
        {
          std::cin >> selectedChannel;
        }
        std::cin.ignore();

        //get the properties for that channel and let the user provide values
        std::map<std::string,Property*> channelProperties = inputChannelDescriptions[selectedChannel].getChannelProperties();
        std::map<std::string, Property*> constructedChannelProperties = Common::getProperties(channelProperties);

        //now find all Readers that are supported by that channel
        std::string readerType = inputChannelDescriptions[selectedChannel].getReaderType();
        std::vector<ReaderDescription> readerDescriptions = readerFactory.getReadersOfType(readerType);
        std::cout << "Available Readers for this Channel:" << std::endl;
        for(int i = 0; i < readerDescriptions.size(); i++)
        {
          std::cout << i << ": " << readerDescriptions[i].getReaderName() << ": " << readerDescriptions[i].getReaderDescription() << std::endl;
        }

        //let the user pick a reader
        std::cout << "Please select a reader:" << std::endl;
        int selectedReader = -1;
        while(selectedReader < 0 || selectedReader > (readerDescriptions.size() - 1))
        {
          std::cin >> selectedReader;
        }
        std::cin.ignore();

        //get the properties for that reader and let the user provide values
        std::map<std::string,Property*> readerProperties = readerDescriptions[selectedReader].getReaderProperties();
        std::map<std::string, Property*> constructedReaderProperties = Common::getProperties(readerProperties);

        Reader* reader = readerFactory.create(readerDescriptions[selectedReader].getReaderName(), constructedReaderProperties);
        InputChannel* channel = channelFactory.create(inputChannelDescriptions[selectedChannel].getChannelName(), reader, constructedChannelProperties);
        channel->start();
      } else if(typeOfChannel == 2)
      {
        OutputChannelFactory outputFactory;
        WriterFactory writerFactory;
        //get all output channels and output them to the console
        std::vector<OutputChannelDescription> outputChannelDescriptions = outputFactory.getAllChannels();
        std::cout << "Available Output Channels:" << std::endl;
        for(int i = 0; i < outputChannelDescriptions.size(); i++)
        {
          std::cout << i << ": " << outputChannelDescriptions[i].getChannelName() << ": " << outputChannelDescriptions[i].getChannelDescription() << std::endl;
        }

        //let the user pick a channel
        std::cout << "Please select a channel:" << std::endl;
        int selectedChannel = -1;
        while(selectedChannel < 0 || selectedChannel > (outputChannelDescriptions.size() - 1))
        {
          std::cin >> selectedChannel;
        }
        std::cin.ignore();

        //get the properties for that channel and let the user provide values
        std::map<std::string,Property*> channelProperties = outputChannelDescriptions[selectedChannel].getChannelProperties();
        std::map<std::string, Property*> constructedChannelProperties = Common::getProperties(channelProperties);

        //now find all Writers that are supported by that channel
        std::string writerType = outputChannelDescriptions[selectedChannel].getWriterType();
        std::vector<WriterDescription> writerDescriptions = writerFactory.getWritersOfType(writerType);
        std::cout << "Available Writers for this Channel:" << std::endl;
        for(int i = 0; i < writerDescriptions.size(); i++)
        {
          std::cout << i << ": " << writerDescriptions[i].getWriterName() << ": " << writerDescriptions[i].getWriterDescription() << std::endl;
        }

        //let the user pick a writer
        std::cout << "Please select a writer:" << std::endl;
        int selectedWriter = -1;
        while(selectedWriter < 0 || selectedWriter > (writerDescriptions.size() - 1))
        {
          std::cin >> selectedWriter;
        }
        std::cin.ignore();

        //get the properties for that reader and let the user provide values
        std::map<std::string,Property*> writerProperties = writerDescriptions[selectedWriter].getWriterProperties();
        std::map<std::string, Property*> constructedWriterProperties = Common::getProperties(writerProperties);

        Writer* writer = writerFactory.create(writerDescriptions[selectedWriter].getWriterName(), constructedWriterProperties);
        OutputChannel* channel = outputFactory.create(outputChannelDescriptions[selectedChannel].getChannelName(), writer, constructedChannelProperties);
        channel->start();
      }
      return 1;
}

      /*std::vector< std::vector<int> > spikes;

      while(true)
      {
        //get fired spikes
        spikes = channel->getFiring();
        channel->step();
        std::cout << spikes.size() << std::endl;

        if(spikes.size() > 0)
        {
          /*for(unsigned int i = 0; i < spikes.size(); i++)
          {
            controller->setFiring(1, &(spikes.at(i)));
            controller->stepOutputChannel(1);
          }*/
         /* std::cout << "[";
          for(unsigned int i = 0; i < spikes.front().size(); i++)
          {
            std::cout << spikes.front().at(i) << ",";
          }
          std::cout << "]" << std::endl;
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(200));
      }

      return 1;
}*/

      /*ChannelController* controller = new ChannelController();
      std::map<int, std::string>::iterator i;
      std::map<int,std::string>* inputChannels = controller->getInputChannels();
      std::cout << "Input Channels:" << std::endl;
      for (i = inputChannels->begin(); i != inputChannels->end(); i++)
        std::cout << i->first << "," << i->second << std::endl;
      std::map<int,std::string>* outputChannels = controller->getOutputChannels();
      std::cout << "Output Channels:" << std::endl;
      for (i = outputChannels->begin(); i != outputChannels->end(); i++)
        std::cout << i->first << "," << i->second << std::endl;

      char* inputValues[] = {"0", "2", "-90", "90", "20"};
      std::vector<std::string> inputArguments(inputValues, inputValues + sizeof(inputValues) / sizeof(char*) );
      controller->inputChannelSubscribe(1);
      char* outputValues[] = {"-90", "90", "0.1", "20"};
      std::vector<std::string> outputArguments(outputValues, outputValues + sizeof(outputValues) / sizeof(char*) );
      controller->outputChannelSubscribe(1, outputArguments);
      std::vector< std::vector<int> > spikes;

      while(true)
      {
        //get fired spikes
        controller->stepInputChannel(1);
        spikes = controller->getFiring(1);
        std::cout << spikes.size() << std::endl;

        if(spikes.size() > 0)
        {
          for(unsigned int i = 0; i < spikes.size(); i++)
          {
            controller->setFiring(1, &(spikes.at(i)));
            controller->stepOutputChannel(1);
          }
          std::cout << "[";
          for(unsigned int i = 0; i < spikes.front().size(); i++)
          {
            std::cout << spikes.front().at(i) << ",";
          }
          std::cout << "]" << std::endl;
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(200));
      }
  return 1;
}

//return UnitTest::RunAllTests();

if any spikes have been fired
if(spikes.size() > 0 )
{
  //create a grayscale image buffer
  unsigned char* buffer = new unsigned char[width * height];
  for(int i = 0; i < width * height; i++)
    buffer[i] = 0;

  //for each spike frame
  for(int i = 0; i < spikes.size(); i++)
  {
    //for each spike
    for(int j = 0; j < spikes.at(i).size(); j++)
    {
      if(buffer[spikes.at(i).at(j)] == 0)
      {
        double ratio = ((double)i / spikes.size());
        unsigned char pixelValue = (int) floor(255 * (1 - ratio) + 0.5);
        buffer[spikes.at(i).at(j)] = pixelValue;
      }
    }
  }
  Bitmap* image = Common::produceGrayscale(buffer, width, height);
  Common::savePPMImage("resultSpikes.ppm", image);
  delete buffer;
  delete image;
} else {
  std::cout << "length is zero" << std::endl;
}*/
