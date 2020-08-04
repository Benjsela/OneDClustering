#include<stdio.h>
#include<boost/random.hpp>
#include<math.h>
#include<boost/math/distributions.hpp>
#include<random>
#include<vector>
#include<set>

#ifndef distsHELLO
#define distsHELLO



//reviewer::S = new randomSource();

//std::uniform_real_distribution<> * reviewer::dist{ new std::uniform_real_distribution<>(0,1) };

/**
 * Abstract class for distribution generation
 */
class DistGen_Abstract{
public:
  virtual int sample() = 0;
  virtual double sampleF() = 0;
  virtual double discreteCDF(double x) = 0;
  //  virtual double CDF(int item);
  virtual std::string * to_string() = 0;
  virtual double getMax() = 0;
  virtual double getMin() = 0;
  virtual double PDF(double x) = 0;
  virtual std::pair<double *,double *> * plotPDF(double min, double max, int NumPoints) = 0;
};



/**
 * Impelementation of uniform distribution over reals
 * TODO: delete (functionality is covered by UniformGen)
 */
class UniformRGen : public DistGen_Abstract {
public:
  //======= attributes =================================
  std::mt19937 gen;
  double min;
  double max;
  std::uniform_real_distribution<> * dist;


  double PDF(double x);

  std::pair<double *,double *> * plotPDF(double min, double max, int NumPoints);
  /**
   * UniformRGen constructor
   *
   * @param a the lower bound of the universe
   * @param b the upper bound of the universe
   */
  UniformRGen(double a,double b);

  //========= member functions ========================
  /**
   * Print the attributes of the distribution
   */
  std::string * to_string();

  /**
   * Sample an int from the distribution
   *
   * @returns an int sampled from the distribution
   */
  int sample();

  /**
   * Sample a double from the distribution
   *
   * @returns a double sampled from the distribution
   */
  double sampleF(); // TODO why F?

  /**
   * Get the value of the discrete cumulative density 
   *    function (CDF) at the integer x.
   *
   * @param x integer value at which to evaluate CDF
   *
   * @returns a double representing the cumulative
   *    density at x for this distribution.
   */
  double discreteCDF(double x);


  double getMax();

  double getMin();
};



/**
 * Implementation of beta distribution
 *
 * A beta distribution is parametrized by two parameters,
 * alpha and beta, as Beta(\alpha, \beta)
 */
class BetaGen : public DistGen_Abstract {
public:
  //======= attributes =================================
  boost::random::mt19937 gen;
  double alpha;
  double beta;
  int min;
  int max;
  boost::random::beta_distribution<> * dist;



  double PDF(double x);

  std::pair<double *,double *> * plotPDF(double min, double max, int N);
  /**
   * BetaGen constructor
   *
   * @param alpha the alpha parameter of the beta distribution
   * @param beta the beta parameter of the beta distribution
   * @param a the lower bound of the universe
   * @param b the upper bound of the universe
   */
  BetaGen(double alpha, double beta, int min, int max);
  /**
   * BetaGen destructor
   */
  ~BetaGen();

  //========= member functions ========================
  /**
   * Print the attributes of the distribution
   */
  std::string * to_string();
  
  /**
   * Sample an int from the distribution
   *
   * @returns an int sampled from the distribution
   */
  int sample();
  /**
   * Sample a double from the distribution
   *
   * @returns a double sampled from the distribution
   */
  double sampleF();

  /**
   * Get the value of the discrete cumulative density 
   *    function (CDF) at the integer x.
   *
   * @param x integer value at which to evaluate CDF
   *
   * @returns a double representing the cumulative
   *    density at x for this distribution.
   */
  double discreteCDF(double x);

  double getMin();

  double getMax();
};


class composite_Dist : public DistGen_Abstract {
public:
  double min;
  double max;
  int numDistributions;
  std::vector<DistGen_Abstract *> * distributions;
  std::vector<double> * weights;
  composite_Dist(double min, double max,std::vector<double> * weights , std::vector<DistGen_Abstract *> * Distributions);
  int sample();
  double sampleF();
  double getMin();
  double getMax();
  double discreteCDF(double x);
  std::string * to_string();
  double PDF(double x);
  std::pair<double *,double *> * plotPDF(double min, double max, int NumPoints);
  std::vector<std::pair<double *, double *>*> * plotAllComps(double min, double max, int numPoints);
};


class binomialDist : public DistGen_Abstract {
public:
  double p;
  int N;
  boost::random::binomial_distribution<int> * dist;
  boost::random::mt19937 gen;
  binomialDist(double p, int N);
  int sample();
  double sampleF();
  double getMin();
  double getMax();
  double discreteCDF(double x);
  std::string * to_string();
  double PDF(double x);
  std::pair<double *,double*> * plotPDF(double min, double max, int NumPoints);


};

class NormalDist : public DistGen_Abstract {
public:
  int bounded;//boolean
  double min;
  double max;
  double mean;
  double stdev;
  boost::random::mt19937 gen;
  boost::normal_distribution<> * dist;
  NormalDist(double mean, double stdev);
  NormalDist(double mean, double stdev, double min, double max);
  int sample();
  double boundedSampleF();
  double sampleF();
  double getMin();
  double getMax();
  double discreteCDF(double x);
  std::string * to_string();
  double PDF(double x);
  std::pair<double *,double*> * plotPDF(double min, double max, int NumPoints);

};




/*
class ConstantValue : public DistGen_Abstract {
  int value;
  ConstantValue(double value);
  int sample();
  double sampleF();
  double getMin();
  double getMax();
  double discreteCDF(double x);
  std::string * to_string();
  
  
  
};
*/

/**
 * \class UniformGen
 *
 * \brief Implementation of uniform distribution over integers
 */

class UniformGen : public DistGen_Abstract {
public:
  //======= attributes =================================
  std::mt19937 gen;
  int min;
  int max;
  std::uniform_int_distribution<> * dist;

  /**
   * UniformGen constructor
   *
   * @param a the lower bound of the universe
   * @param b the upper bound of the universe
   */
  UniformGen(int a,int b);

  //========= member functions ========================
  /**
   * Print the attributes of the distribution
   */
  std::string * to_string();
  
  /**
   * Sample an int from the distribution
   *
   * @returns an int sampled from the distribution
   */
  int sample();
  /**
   * Sample a double from the distribution
   *
   * @returns a double sampled from the distribution
   */
  double sampleF();

  /**
   * Get the value of the discrete cumulative density 
   *    function (CDF) at the integer x.
   *
   * @param x integer value at which to evaluate CDF
   *
   * @returns a double representing the cumulative
   *    density at x for this distribution.
   */
  double discreteCDF(double x);

  double PDF(double x);

  std::pair<double *,double*> * plotPDF(double min, double max, int NumPoints);
  
  double getMax();

  double getMin();
};








#endif
