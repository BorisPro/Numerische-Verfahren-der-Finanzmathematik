/*
 * Cpp11UniformDice_test.cpp
 *
 *  Created on: 17.04.2014
 *      Author: BlueCrescent
 */

#include "Cpp11UniformDice.h"

#include "gtest/gtest.h"

#include <vector>
#include <algorithm>

std::vector<double> generateVectorWithRandomUniformValues(double lower, double upper) {
  std::vector<double> values;
  Cpp11UniformDice dice;
  for (unsigned int i = 0; i < 10000; ++i) {
    values.push_back(dice.roll());
  }
  return values;
}

TEST(Cpp11UniformDistributionTest, IsIn01Boundaries)
{
  const double upper = 1., lower = 0.;
  std::vector<double> values = generateVectorWithRandomUniformValues(lower, upper);
  const double max = *std::max_element(values.begin(), values.end());
  const double min = *std::min_element(values.begin(), values.end());
  ASSERT_LE(lower, min);
  ASSERT_GE(upper, max);
}


