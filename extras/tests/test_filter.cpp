/*
  NAME:
  Unit tests of application library "gbj_appfilter" for filtering data.

  DESCRIPTION:
  The test file provides test cases for filtering measures of various data
  types.
  - The test runner is Unity Project - ThrowTheSwitch.org.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the MIT License (MIT).

  CREDENTIALS:
  Author: Libor Gabaj
*/
#define SERIAL_NODEBUG
#include "gbj_appfilter.h"
#include <Arduino.h>
#include <unity.h>

//******************************************************************************
// Preparation
//******************************************************************************
const float MINIMUM = 40.0;
const float MAXIMUM = 60.0;

const float SAMPLE_LIST[] = { 38.9, 45.0, 56.7, 61.7, 42.3 };
const byte SAMPLES = sizeof(SAMPLE_LIST) / sizeof(SAMPLE_LIST[0]);

gbj_appfilter<float> filterFloat = gbj_appfilter<float>(MAXIMUM, MINIMUM);

gbj_appfilter<unsigned int> filterUint =
  gbj_appfilter<unsigned int>((unsigned int)MAXIMUM, (unsigned int)MINIMUM);

//******************************************************************************
// Tests
//******************************************************************************
void test_version(void)
{
  String version, valExpected, valActual;
  version = String(filterFloat.VERSION);
  valExpected = "GBJ_APPFILTER";
  valActual = version.substring(0, version.indexOf(" "));
  TEST_ASSERT_EQUAL_STRING(valExpected.c_str(), valActual.c_str());
}

void test_minimum_float(void)
{
  float valActual, valExpected;
  valExpected = MINIMUM;
  valActual = filterFloat.getMinimum();
  TEST_ASSERT_EQUAL_FLOAT(valExpected, valActual);
}

void test_maximum_float(void)
{
  float valActual, valExpected;
  valExpected = MAXIMUM;
  valActual = filterFloat.getMaximum();
  TEST_ASSERT_EQUAL_FLOAT(valExpected, valActual);
}

void test_value_float(void)
{
  float valInput, valActual, valExpected;
  for (byte i = 0; i < SAMPLES; i++)
  {
    valInput = SAMPLE_LIST[i];
    // Algorithm
    valExpected = valInput;
    // Testee
    filterFloat.limit(valInput);
    valActual = filterFloat.getValue();
    String msg = "i=" + String(i);
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(valExpected, valActual, msg.c_str());
  }
}

void test_float_limit(void)
{
  float valInput, valActual, valExpected;
  for (byte i = 0; i < SAMPLES; i++)
  {
    valInput = SAMPLE_LIST[i];
    // Algorithm
    if (valInput < MINIMUM)
    {
      valExpected = MINIMUM;
    }
    else if (valInput > MAXIMUM)
    {
      valExpected = MAXIMUM;
    }
    else
    {
      valExpected = valInput;
    }
    // Testee
    valActual = filterFloat.limit(valInput);
    String msg = "i=" + String(i);
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(valExpected, valActual, msg.c_str());
  }
}

void test_float_valid(void)
{
  float valInput;
  bool valActual;
  for (byte i = 0; i < SAMPLES; i++)
  {
    valInput = SAMPLE_LIST[i];
    String msg = "i=" + String(i);
    // Testee
    valActual = filterFloat.isValid(valInput);
    // Algorithm
    if (valInput < MINIMUM || valInput > MAXIMUM)
    {
      TEST_ASSERT_FALSE_MESSAGE(valActual, msg.c_str());
    }
    else
    {
      TEST_ASSERT_TRUE_MESSAGE(valActual, msg.c_str());
    }
  }
}

void test_float_invalid(void)
{
  float valInput;
  bool valActual;
  for (byte i = 0; i < SAMPLES; i++)
  {
    valInput = SAMPLE_LIST[i];
    String msg = "i=" + String(i);
    // Testee
    valActual = filterFloat.isInvalid(valInput);
    // Algorithm
    if (valInput < MINIMUM || valInput > MAXIMUM)
    {
      TEST_ASSERT_TRUE_MESSAGE(valActual, msg.c_str());
    }
    else
    {
      TEST_ASSERT_FALSE_MESSAGE(valActual, msg.c_str());
    }
  }
}

void test_float_islow(void)
{
  float valInput;
  bool valActual;
  for (byte i = 0; i < SAMPLES; i++)
  {
    valInput = SAMPLE_LIST[i];
    String msg = "i=" + String(i);
    // Testee
    valActual = filterFloat.isLow(valInput);
    // Algorithm
    if (valInput < MINIMUM)
    {
      TEST_ASSERT_TRUE_MESSAGE(valActual, msg.c_str());
    }
    else
    {
      TEST_ASSERT_FALSE_MESSAGE(valActual, msg.c_str());
    }
  }
}

void test_float_ishigh(void)
{
  float valInput;
  bool valActual;
  for (byte i = 0; i < SAMPLES; i++)
  {
    valInput = SAMPLE_LIST[i];
    String msg = "i=" + String(i);
    // Testee
    valActual = filterFloat.isHigh(valInput);
    // Algorithm
    if (valInput > MAXIMUM)
    {
      TEST_ASSERT_TRUE_MESSAGE(valActual, msg.c_str());
    }
    else
    {
      TEST_ASSERT_FALSE_MESSAGE(valActual, msg.c_str());
    }
  }
}

void test_uint_limit(void)
{
  unsigned int valInput, valActual, valExpected;
  for (byte i = 0; i < SAMPLES; i++)
  {
    valInput = SAMPLE_LIST[i];
    // Algorithm
    if (valInput < MINIMUM)
    {
      valExpected = MINIMUM;
    }
    else if (valInput > MAXIMUM)
    {
      valExpected = MAXIMUM;
    }
    else
    {
      valExpected = valInput;
    }
    // Testee
    valActual = filterUint.limit(valInput);
    String msg = "i=" + String(i);
    TEST_ASSERT_EQUAL_UINT_MESSAGE(valExpected, valActual, msg.c_str());
  }
}

void test_uint_valid(void)
{
  unsigned int valInput;
  bool valActual;
  for (byte i = 0; i < SAMPLES; i++)
  {
    valInput = SAMPLE_LIST[i];
    String msg = "i=" + String(i);
    // Testee
    valActual = filterUint.isValid(valInput);
    // Algorithm
    if (valInput < MINIMUM || valInput > MAXIMUM)
    {
      TEST_ASSERT_FALSE_MESSAGE(valActual, msg.c_str());
    }
    else
    {
      TEST_ASSERT_TRUE_MESSAGE(valActual, msg.c_str());
    }
  }
}

void test_uint_invalid(void)
{
  unsigned int valInput;
  bool valActual;
  for (byte i = 0; i < SAMPLES; i++)
  {
    valInput = SAMPLE_LIST[i];
    String msg = "i=" + String(i);
    // Testee
    valActual = filterUint.isInvalid(valInput);
    // Algorithm
    if (valInput < MINIMUM || valInput > MAXIMUM)
    {
      TEST_ASSERT_TRUE_MESSAGE(valActual, msg.c_str());
    }
    else
    {
      TEST_ASSERT_FALSE_MESSAGE(valActual, msg.c_str());
    }
  }
}

void test_uint_islow(void)
{
  unsigned int valInput;
  bool valActual;
  for (byte i = 0; i < SAMPLES; i++)
  {
    valInput = SAMPLE_LIST[i];
    String msg = "i=" + String(i);
    // Testee
    valActual = filterUint.isLow(valInput);
    // Algorithm
    if (valInput < MINIMUM)
    {
      TEST_ASSERT_TRUE_MESSAGE(valActual, msg.c_str());
    }
    else
    {
      TEST_ASSERT_FALSE_MESSAGE(valActual, msg.c_str());
    }
  }
}

void test_uint_ishigh(void)
{
  unsigned int valInput;
  bool valActual;
  for (byte i = 0; i < SAMPLES; i++)
  {
    valInput = SAMPLE_LIST[i];
    String msg = "i=" + String(i);
    // Testee
    valActual = filterUint.isHigh(valInput);
    // Algorithm
    if (valInput > MAXIMUM)
    {
      TEST_ASSERT_TRUE_MESSAGE(valActual, msg.c_str());
    }
    else
    {
      TEST_ASSERT_FALSE_MESSAGE(valActual, msg.c_str());
    }
  }
}

//******************************************************************************
// Run
//******************************************************************************
void setup()
{
  delay(2000);
  UNITY_BEGIN();

  RUN_TEST(test_version);
  //
  RUN_TEST(test_minimum_float);
  RUN_TEST(test_maximum_float);
  RUN_TEST(test_value_float);
  RUN_TEST(test_float_limit);
  RUN_TEST(test_float_valid);
  RUN_TEST(test_float_invalid);
  RUN_TEST(test_float_islow);
  RUN_TEST(test_float_ishigh);
  //
  RUN_TEST(test_uint_limit);
  RUN_TEST(test_uint_valid);
  RUN_TEST(test_uint_invalid);
  RUN_TEST(test_uint_islow);
  RUN_TEST(test_uint_ishigh);

  UNITY_END();
}

void loop() {}