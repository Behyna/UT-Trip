#include "defines.hpp"
#include <random>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

double myMultiply(double d1, double d2)
{
  return d1 * d2;
}
double mySum(double d1, double d2)
{
  return d1 + d2;
}
double predictRating(vector<double> weights, vector<double> averageRatings)
{
  vector<double> tempVec(weights.size());
  transform(weights.begin(), weights.end(), averageRatings.begin(), tempVec.begin(), myMultiply);
  double sum = accumulate(tempVec.begin(), tempVec.end(), 0.0, mySum);
  double sumOfWeights = accumulate(weights.begin(), weights.end(), 0.0, mySum);
  return sum / sumOfWeights;
}

double randDouble()
{
  return (MAX_WEIGHT - MIN_WEIGHT) * double(rand()) / double(RAND_MAX) + MIN_WEIGHT;
}
vector<double> initWeights()
{
  vector<double> weights;
  srand(RANDOM_SEED);
  for(int i=0; i<NUM_WEIGHTS; i++)
    weights.push_back(randDouble());
  return weights;
}
double errorFunction(vector<double> weights, vector<double> averageRatings)
{
  return pow(predictRating(weights, averageRatings) - averageRatings[averageRatings.size()-1], 2);
}
vector<double> getDerivatives(vector<double> weights, vector<double> ratings)
{
  vector<double> derivatives;
  double d;
  for (int i=0; i<NUM_WEIGHTS; i++)
  {
    vector<double> newWeights = weights;
    newWeights[i] += EPSILON;
    d = errorFunction(newWeights, ratings) - errorFunction(weights, ratings);
    d = d / EPSILON;
    derivatives.push_back(d);
  }
  return derivatives;
}
double myWeightUpdate(double d1, double d2)
{
  return d1 - ALPHA * d2;
}
double myClamp(double d)
{
  if (d < MIN_WEIGHT)
    return MIN_WEIGHT;
  if (d > MAX_WEIGHT)
    return MAX_WEIGHT;
  return d;
}
vector<double> estimateWeights(vector<vector<double>> allRatings){
  vector<double> weights = initWeights();

  if (allRatings.size() < SUFFICIENT_RATINGS)
    return weights;

  vector<double> zeroVec(weights.size(), 0);
  vector<double> totalDerivatives(weights.size());
  vector<double> derivatives(weights.size());
  for (int i=0; i<MAX_ITERATIONS; i++)
  {
    copy(zeroVec.begin(), zeroVec.end(), totalDerivatives.begin());
    for (int j=0; j<allRatings.size(); j++)
    {
      derivatives = getDerivatives(weights, allRatings[j]);
      transform(derivatives.begin(), derivatives.end(), totalDerivatives.begin(), totalDerivatives.begin(), mySum);
    }
    transform(weights.begin(), weights.end(), totalDerivatives.begin(), weights.begin(), myWeightUpdate);
    transform(weights.begin(), weights.end(), weights.begin(), myClamp);
  }
  return weights;
}