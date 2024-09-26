/*
  NAME:
  Unit tests of application library "gbj_appfilter" for filtering data with
  valid difference.

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
const float DIFFERENCE = 10.3;

const float SAMPLE_LIST[] = { 15.4, -8.7, -9.6, 38.9, 38.9,
                              45.0, 56.7, 61.7, 42.3 };
const byte SAMPLES = sizeof(SAMPLE_LIST) / sizeof(SAMPLE_LIST[0]);

gbj_appfilter<float> filterFloat =
  gbj_appfilter<float>(MAXIMUM, MINIMUM, -1 * DIFFERENCE);

//******************************************************************************
// Tests
//******************************************************************************
void test_difference(void)
{
  float valActual, valExpected;
  valExpected = DIFFERENCE;
  valActual = filterFloat.getDifference();
  TEST_ASSERT_EQUAL_FLOAT(valExpected, valActual);
}

void test_change(void)
{
  float valInput, valOutput, valActual, valExpected;
  filterFloat.init();
  for (byte i = 0; i < SAMPLES; i++)
  {
    valInput = SAMPLE_LIST[i];
    // Algorithm
    valExpected = i > 0 ? valInput - valOutput : 0;
    valOutput = valInput;
    // Testee
    filterFloat.setValue(valInput);
    valActual = filterFloat.getChange();
    String msg = "i=" + String(i);
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(valExpected, valActual, msg.c_str());
  }
}

void test_jump(void)
{
  float valInput, valOutput;
  bool valActual;
  filterFloat.init();
  for (byte i = 0; i < SAMPLES; i++)
  {
    valInput = SAMPLE_LIST[i];
    String msg = "i=" + String(i);
    // Testee
    valActual = filterFloat.isJump(valInput);
    // Algorithm
    if (i > 0 && DIFFERENCE > 0 && fabs(valInput - valOutput) > DIFFERENCE)
    {
      TEST_ASSERT_TRUE_MESSAGE(valActual, msg.c_str());
    }
    else
    {
      TEST_ASSERT_FALSE_MESSAGE(valActual, msg.c_str());
    }
    valOutput = valInput;
  }
}

void test_decr(void)
{
  float valInput, valOutput;
  bool valActual;
  filterFloat.init();
  for (byte i = 0; i < SAMPLES; i++)
  {
    valInput = SAMPLE_LIST[i];
    String msg = "i=" + String(i);
    // Testee
    valActual = filterFloat.isDecr(valInput);
    // Algorithm
    if (i > 0 && valInput < valOutput)
    {
      TEST_ASSERT_TRUE_MESSAGE(valActual, msg.c_str());
    }
    else
    {
      TEST_ASSERT_FALSE_MESSAGE(valActual, msg.c_str());
    }
    valOutput = valInput;
  }
}

void test_incr(void)
{
  float valInput, valOutput;
  bool valActual;
  filterFloat.init();
  for (byte i = 0; i < SAMPLES; i++)
  {
    valInput = SAMPLE_LIST[i];
    String msg = "i=" + String(i);
    // Testee
    valActual = filterFloat.isIncr(valInput);
    // Algorithm
    if (i > 0 && valInput > valOutput)
    {
      TEST_ASSERT_TRUE_MESSAGE(valActual, msg.c_str());
    }
    else
    {
      TEST_ASSERT_FALSE_MESSAGE(valActual, msg.c_str());
    }
    valOutput = valInput;
  }
}

void test_equal(void)
{
  float valInput, valOutput;
  bool valActual;
  filterFloat.init();
  for (byte i = 0; i < SAMPLES; i++)
  {
    valInput = SAMPLE_LIST[i];
    String msg = "i=" + String(i);
    // Testee
    valActual = filterFloat.isEqual(valInput);
    // Algorithm
    if (i == 0 || valInput == valOutput)
    {
      TEST_ASSERT_TRUE_MESSAGE(valActual, msg.c_str());
    }
    else
    {
      TEST_ASSERT_FALSE_MESSAGE(valActual, msg.c_str());
    }
    valOutput = valInput;
  }
}

//******************************************************************************
// Run
//******************************************************************************
void setup()
{
  delay(2000);
  UNITY_BEGIN();
  //
  RUN_TEST(test_difference);
  RUN_TEST(test_change);
  RUN_TEST(test_jump);
  RUN_TEST(test_decr);
  RUN_TEST(test_incr);
  RUN_TEST(test_equal);

  UNITY_END();
}

void loop() {}