/*
 * VisualDataReducer.hpp
 *
 *  Created on: 5 Feb 2011
 *      Author: Edgars Lazdins
 */

#ifndef VISUALDATAREDUCER_HPP_
#define VISUALDATAREDUCER_HPP_

#include <iSpike/Bitmap.hpp>
#include <iSpike/Reader/VisualReader.hpp>

/**
 * @class Visual Data Reducer
 * @brief Visual Data Reducer class
 *
 * This class represents a Visual Data Reducer
 *
 * @author Edgars Lazdins
 *
 */
class VisualDataReducer {
private:

  Bitmap* reducedImage;
  VisualReader* reader;
  int queryInterval;

public:

  virtual Bitmap getReducedImage() = 0;

};

#endif /* VISUALDATAREDUCER_HPP_ */
