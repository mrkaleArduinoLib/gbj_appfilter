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
    difMax - Maximal consecutive change of values for its validity.
      - Data type: templated
      - Default value: 0

    RETURN: object
  */
  inline gbj_appfilter(DAT valMax, DAT valMin = 0, DAT difMax = 0)
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
    setDifference(difMax);
    init();
  }

  inline void init()
  {
    value_ = change_ = 0;
    flagInit_ = false;
  }

  inline DAT limit(DAT data)
  {
    setValue(data);
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
  inline void setMinimum(DAT data) { minimum_ = min(maximum_, data); }
  inline void setMaximum(DAT data) { maximum_ = max(minimum_, data); }
  inline void setDifference(DAT data)
  {
    difference_ = min(maximum_ - minimum_, absVal(data));
  }
  inline void setValue(DAT data)
  {
    if (flagInit_)
    {
      change_ = data - value_;
    }
    else
    {
      flagInit_ = true;
    }
    value_ = data;
  }

  // Getters
  inline DAT getMinimum() { return minimum_; }
  inline DAT getMaximum() { return maximum_; }
  inline DAT getDifference() { return difference_; }
  inline DAT getValue() { return value_; }
  inline DAT getChange() { return change_; }
  //
  inline bool isInit() { return flagInit_; }
  inline bool isLow() { return value_ < minimum_; }
  inline bool isLow(DAT data)
  {
    setValue(data);
    return isLow();
  }
  inline bool isHigh() { return value_ > maximum_; }
  inline bool isHigh(DAT data)
  {
    setValue(data);
    return isHigh();
  }
  inline bool isJump()
  {
    return flagInit_ && difference_ > 0 && difference_ < absVal(change_);
  }
  inline bool isJump(DAT data)
  {
    setValue(data);
    return isJump();
  }
  inline bool isDecr() { return flagInit_ && change_ < 0; }
  inline bool isDecr(DAT data)
  {
    setValue(data);
    return isDecr();
  }
  inline bool isIncr() { return flagInit_ && change_ > 0; }
  inline bool isIncr(DAT data)
  {
    setValue(data);
    return isIncr();
  }
  inline bool isEqual() { return flagInit_ && change_ == 0; }
  inline bool isEqual(DAT data)
  {
    setValue(data);
    return isEqual();
  }
  inline bool isInvalid() { return isLow() || isHigh() || isJump(); }
  inline bool isInvalid(DAT data)
  {
    setValue(data);
    return isInvalid();
  }
  inline bool isValid() { return !isInvalid(); }
  inline bool isValid(DAT data)
  {
    setValue(data);
    return isValid();
  }

private:
  DAT minimum_, maximum_, difference_, value_, change_;
  bool flagInit_;
  inline DAT absVal(DAT data)
  {
    if (data >= 0)
    {
      return data;
    }
    else
    {
      return -1 * data;
    }
  }
};

#endif
