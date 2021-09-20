#include "user.hpp"

using namespace std;

User::User(std::string usersname, std::string userspassword, std::string usersemail)
{
  nextReservationId = 1;
  username = usersname;
  password = userspassword;
  email = usersemail;
  credit = 0;
  accountTurnover.push_back(credit);
  defaultPriceFilter = true;
  sortParams = pair<string, string>(ID_KEYWORD, ASCENDING_KEYWORD);
  manualWeightsActive = false;
  estimatedWeightsAreValid = false;
}
bool User::checkingUsersInfo(string enteredEmail, string enteredPassword)
{
  if(enteredEmail == email)
  {
    if(enteredPassword == password)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}
bool User::isThisYourEmail(string enteredEmail)
{
  return email == enteredEmail;
}
bool User::isThisYourUserName(string enteredUsername)
{
  return username == enteredUsername;
}
void User::setFilters(Filter* newFilter)
{
  filters.push_back(newFilter);
}
void User::chargeMyAccount(int money)
{
  credit += money;
  accountTurnover.push_back(credit);
}

void User::payCredit(int money)
{
  if (money <= credit)
  {
    credit -= money;
    accountTurnover.push_back(credit);
  }
  else
  {
    throw NOT_ENOUGH_CREDIT_MSG;
  }
}

void User::addReserve(string hotelId, string type, int quantity, int cost, int checkIn, int checkOut, vector<Room*> foundRooms)
{
  int id = nextReservationId++;
  reservations.push_back(new Reservation(id, hotelId, type, quantity, cost, checkIn, checkOut, foundRooms));
}

void User::deleteReservation(int id)
{
  for (int i=0; i<reservations.size(); i++)
  {
    if (reservations[i]->getId() == id)
    {
      credit += reservations[i]->getCost() / 2;
      accountTurnover.push_back(credit);
      reservations[i]->unreserveRooms();
      reservations.erase(reservations.begin() + i);
      throw OK_MSG;
    }
  }
  throw NOT_FOUND_MSG;
}

vector<Reservation*> User::getReservations(){
  return reservations;
}

vector<int> User::getAccountTurnover(int count)
{
  vector<int> turnovers;
  count = min(count, int(accountTurnover.size()));
  for (int i=0; i<accountTurnover.size(); i++)
    turnovers.push_back(accountTurnover[accountTurnover.size() - i - 1]);
  return turnovers;
}

void User::deleteFilters()
{
  filters.clear();
}

double reservationCostSum(double r1, Reservation* r2)
{
  return r1 + r2->getCost();
}
int reservationQuantitySum(int r1, Reservation* r2)
{
  return r1 + r2->getQuantity();
}

double User::getReservationPricesMean()
{
  double costSum = accumulate(reservations.begin(), reservations.end(), 0, reservationCostSum);
  int quantitySum = accumulate(reservations.begin(), reservations.end(), 0, reservationQuantitySum);
  return costSum / quantitySum;
}
double reservationPriceSquareDistance(Reservation* r1, double mean)
{
  return r1->getQuantity() * pow(r1->getPrice() - mean, 2);
}
double User::getReservationPricesSD(double mean)
{
  vector<double> meanVec(reservations.size(), mean);
  vector<double> tempVec(reservations.size());
  transform(reservations.begin(), reservations.end(),meanVec.begin(), tempVec.begin(), reservationPriceSquareDistance);
  double sd = accumulate(tempVec.begin(), tempVec.end(), 0);
  int quantitySum = accumulate(reservations.begin(), reservations.end(), 0, reservationQuantitySum);
  sd = sd / (quantitySum-1);
  return sqrt(sd);
}
pair<double, double> User::getReservationPriceStats()
{
  double mean = getReservationPricesMean();
  double sd = getReservationPricesSD(mean);
  pair<double, double> stats(mean, sd);
  return stats;
}

void User::setDefaultPriceFilter(bool state)
{
  defaultPriceFilter = state;
}
bool User::prepareDefaultPriceFilter()
{
  if (defaultPriceFilter && (reservations.size() >= 10))
  {
    pair<double, double> stats = getReservationPriceStats();
    filters.push_back(new DefaultPriceFilter(stats));
    return true;
  }
  return false;
}
void User::setSortParams(string property, string order)
{
  sortParams = pair<string, string>(property, order);
}
void User::setManualWeights(bool active, std::vector<double> weights)
{
  manualWeightsActive = active;
  manualWeights = weights;
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
vector<double> User::getEstimatedWeights()
{
  if (!estimatedWeightsAreValid)
  {
    estimatedWeights = estimateWeights(allRatings);
    estimatedWeightsAreValid = true;
  }
  for (int i=0; i<estimatedWeights.size(); i++)
    cerr << estimatedWeights[i] << endl;
  return estimatedWeights;
}
vector<double> User::getWeights()
{
  if (manualWeightsActive)
    return getManualWeights();

  return getEstimatedWeights();
}
bool User::insufficientRatings()
{
  return (!manualWeightsActive) && (allRatings.size() < SUFFICIENT_RATINGS);
}
void User::addRatings(vector<double> ratings)
{
  allRatings.push_back(ratings);
  estimatedWeightsAreValid = false;
}