/*
 * ReaderFactory.hpp
 *
 *  Created on: 13 Mar 2011
 *      Author: cembo
 */

#ifndef READERFACTORY_HPP_
#define READERFACTORY_HPP_

#include <vector>
#include <iSpike/Reader/Reader.hpp>
#include <iSpike/Reader/AngleReader.hpp>
#include <iSpike/Reader/FileAngleReader.hpp>
#include <iSpike/Reader/FileVisualReader.hpp>
#include <iSpike/Reader/ReaderDescription.hpp>

class ReaderFactory {

private:
  std::vector<ReaderDescription> readerList;

public:

  /*
   * Default constructor
   * Initialises the list of readers, if you've made a new reader, add it here!
   */
  ReaderFactory()
  {
    this->readerList.push_back(FileAngleReader().getReaderDescription());
    this->readerList.push_back(FileVisualReader().getReaderDescription());
  }

  /*
   * Returns all readers of a particular type
   */
  std::vector<ReaderDescription> getReadersOfType(std::string readerType)
  {
    std::vector<ReaderDescription> result;
    for(int i = 0; i < readerList.size(); i++)
    {
      if(readerList[i].getReaderType() == readerType)
        result.push_back(readerList[i]);
    }
    return result;
  }

  /*
   * Creates a particular reader
   */
  static Reader* create(std::string readerName, std::map<std::string,Property*> readerProperties)
  {
    Reader* result;
    if(readerName == "File Angle Reader")
    {
      result = new FileAngleReader();
    } else if(readerName == "File Visual Reader")
    {
      result = new FileVisualReader();
    } else {
      throw std::logic_error("Invalid reader type");
    }
    result->initialise(readerProperties);
    return result;
  }
};


#endif /* READERFACTORY_HPP_ */
