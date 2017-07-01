#ifndef PID_H
#define PID_H

#include <vector>
#include <limits>
#include <numeric>
#include <iostream>
#include <math.h>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double total_error_;
  double sum_total_error_;

  /*
  * Coefficients
  */
  double Kp;
  double Ki;
  double Kd;

  double cte_;
  double prev_cte_;
  double cte_sum_;
  std::vector<double> p_;
  std::vector<double> dp_;
  int no_params_;
  double best_err_;
  int step;
  int number_steps;

  bool twiddle;
  bool added;
  bool subtracted;
  int param_index;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp0, double Ki0, double Kd0);

  void SetParams(double Kp0, double Ki0, double Kd0);

  void AddParam(int index, double value);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  void TwiddleInit();
};

#endif /* PID_H */
