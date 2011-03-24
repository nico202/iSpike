/*
 * Property.hpp
 *
 *  Created on: 12 Mar 2011
 *      Author: Edgars Lazdins
 */

#ifndef PROPERTY_HPP_
#define PROPERTY_HPP_

#include <string>

/**
 * Describes a general Channel, Reader or Writer Property
 */
class Property
{
 public:
    enum ValueType {
          Integer,
          Double,
          String,
       };
  protected:
    ValueType type;
    std::string name;
    std::string description;

  public:

    ValueType getType()
    {
      return this->type;
    }

    std::string getName()
    {
      return this->name;
    }

    std::string getDescription()
    {
      return this->description;
    }

};

/*
 * Describer an Integer Property
 */
class IntegerProperty : public Property
{
  private:
    int value;

  public:

    int getValue()
    {
      return this->value;
    }

    IntegerProperty(std::string paramName, int paramValue, std::string paramDescription)
    {
      this->name = paramName;
      this->value = paramValue;
      this->description = paramDescription;
      this->type = Property::Integer;
    }
};

/**
 * Describes a Double Property
 */
class DoubleProperty : public Property
{
  private:
    double value;

  public:

    double getValue()
    {
      return this->value;
    }

    DoubleProperty(std::string paramName, double paramValue, std::string paramDescription)
    {
      this->name = paramName;
      this->value = paramValue;
      this->description = paramDescription;
      this->type = Property::Double;
    }
};

/*
 * Describes a String Property
 */
class StringProperty : public Property
{
  private:
    std::string value;

  public:

    std::string getValue()
    {
      return this->value;
    }

    StringProperty(std::string paramName, std::string paramValue, std::string paramDescription)
    {
      this->name = paramName;
      this->value = paramValue;
      this->description = paramDescription;
      this->type = Property::String;
    }
};


#endif /* PROPERTY_HPP_ */