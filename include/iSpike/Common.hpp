/*
 * Common.hpp
 *
 *  Created on: 7 Feb 2011
 *      Author: Edgars Lazdins
 */

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <iSpike/Bitmap.hpp>
#include <iSpike/Property.hpp>
#include <map>

class Common {

public:

  static void savePPMImage(char* filename, Bitmap* image);
  static Bitmap* produceGrayscale(unsigned char* image, int width, int height);
  static unsigned char* normaliseImage(unsigned char* image, int size);

  /**
   * Asks the user for each property value, returns the new properties
   */
  static std::map<std::string, Property*> getProperties(std::map<std::string,Property*> defaultProperties);

};

#endif /* COMMON_HPP_ */
