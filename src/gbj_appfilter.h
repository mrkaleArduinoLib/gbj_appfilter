/*
  NAME:
  gbj_appfilter

  DESCRIPTION:
  Library manages filtering data item of various data type.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the license GNU GPL v3
  http://www.gnu.org/licenses/gpl-3.0.html (related to original code) and MIT
  License (MIT) for added code.

  CREDENTIALS:
  Author: Libor Gabaj
  GitHub: https://github.com/mrkaleArduinoLib/gbj_appfilter.git
*/
#ifndef GBJ_APPFILTER_H
#define GBJ_APPFILTER_H

#if defined(__AVR__)
  #include <Arduino.h>
  #include <inttypes.h>
#elif defined(ESP8266) || defined(ESP32)
  #include <Arduino.h>
#endif

#undef SERIAL_PREFIX
#define SERIAL_PREFIX "gbj_appfilter"

template<typename DAT = float>
class gbj_appfilter
{
public:
  const char *VERSION = "GBJ_APPFILTER 1.0.0";

  /*
    Constructor

    DESCRIPTION:
    Constructor creates the class instance object and sets operational
    parameters.

    PARAMETERS:
    valMax - Maximum of a valid range of a data item.
      - Data type: templated
      - Default value: none
    valMin - Minimum of a valid range of a data item.
      - Data type: templated
      - Default value: 0

    RETURN: object
  */
  inline gbj_appfilter(DAT valMax, DAT valMin = 0)
  {
    if (valMin > valMax)
    {
      minimum_ = valMax;
      maximum_ = valMin;
    }
    else
    {
      minimum_ = valMin;
      maximum_ = valMax;
    }
  }

  inline DAT limit(DAT data)
  {
    value_ = data;
    if (isLow())
    {
      return minimum_;
    }
    if (isHigh())
    {
      return maximum_;
    }
    return data;
  }
  inline DAT limit() { return limit(value_); }

  // Setters
  inline void setMinimum(DAT data) { minimum_ = data; }
  inline void setMaximum(DAT data) { maximum_ = data; }
  inline void setValue(DAT data) { value_ = data; }

  // Getters
  inline DAT getMinimum() { return minimum_; }
  inline DAT getMaximum() { return maximum_; }
  inline DAT getValue() { return value_; }
  //
  inline bool isLow() { return value_ < minimum_; }
  inline bool isLow(DAT data)
  {
    value_ = data;
    return isLow();
  }
  inline bool isHigh() { return value_ > maximum_; }
  inline bool isHigh(DAT data)
  {
    value_ = data;
    return isHigh();
  }
  inline bool isInvalid() { return isLow() || isHigh(); }
  inline bool isInvalid(DAT data)
  {
    value_ = data;
    return isInvalid();
  }
  inline bool isValid() { return !isInvalid(value_); }
  inline bool isValid(DAT data)
  {
    value_ = data;
    return isValid();
  }

private:
  DAT minimum_, maximum_, value_;
};

#endif
