#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp0, double Ki0, double Kd0) {
  p_error = 0.0f;
  i_error = 0.0f;
  d_error = 0.0f;
  total_error_ = 0.0f;
  SetParams(Kp0, Ki0, Kd0);
  cte_ = 0.0f;
  prev_cte_ = 0.0f;
  cte_sum_ = 0.0f;

  // Twiddle params
  step = 1;
  number_steps = 2500;
  sum_total_error_ = 0.0f;
  twiddle = false;
  added = false;
  subtracted = false;
  param_index = 0;
}

void PID::SetParams(double Kp0, double Ki0, double Kd0) {
  Kp = Kp0;
  Ki = Ki0;
  Kd = Kd0;
}

void PID::AddParam(int index, double value) {
  switch (index) {
    case 0:
      Kp += value;
      break;
    case 1:
      Kd += value;
      break;
  }
}

void PID::UpdateError(double cte) {
  prev_cte_ = cte_;
  cte_ = cte;
  cte_sum_ += cte;

  p_error = Kp * cte_;
  i_error = Ki * cte_sum_;
  d_error = Kd * (cte_ - prev_cte_);
  if (step % (100 + number_steps) > 100) { // Every {number_steps} steps after 100 initial steps
    float error = (p_error + i_error + d_error);
    sum_total_error_ += fabs(error);
  }
  if (twiddle && step % (number_steps + 100) == 0) {
    if (sum_total_error_ < best_err_) {
      cout << "===== IMPROVEMENT ======" << endl;
      best_err_ = sum_total_error_;
      dp_[param_index] *= 1.1;
      param_index = (param_index + 1) % no_params_;
      added = subtracted = false;
    }
    if (!added && !subtracted) {
      cout << "===== TRY ADDING ======" << endl;
      AddParam(param_index, dp_[param_index]);
      added = true;
    } else if (added && !subtracted) {
      cout << "===== TRY SUBTRACTING ======" << endl;
      AddParam(param_index, dp_[param_index] * -2);
      subtracted = true;
    } else {
      cout << "===== MOVE TO NEXT PARAM ======" << endl;
      AddParam(param_index, dp_[param_index]);
      dp_[param_index] *= .9;
      param_index = (param_index + 1) % no_params_;
      added = subtracted = false;
    }
    cout << "Step: " << step / (number_steps + 100) << endl;
    cout << "Total error: " << sum_total_error_ << endl;
    cout << "Best error: " << best_err_ << endl;
    cout << "Param: " << param_index << endl;
    cout << "Parameters:" << endl;
    cout << "P: " << Kp << " I: " << Ki << " D: " << Kd << endl;
    sum_total_error_ = 0.0;
  }
  step += 1;
}

double PID::TotalError() {
  total_error_ = p_error + i_error + d_error;
  return total_error_;
}


void PID::TwiddleInit() {
  no_params_ = 2;
  dp_ = {.1*Kp,.1*Kd};
  best_err_ = std::numeric_limits<double>::infinity();
}
