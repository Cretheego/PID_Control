#ifndef PID_H
#define PID_H
#include <uWS/uWS.h>
class PID {
protected:
  /*
  * Errors
  */
  double p_error_;
  double i_error_;
  double d_error_;
  double total_error_;

  int numOfSteps_;
  /*
  * Coefficients
  */ 
  double Kp_;
  double Ki_;
  double Kd_;
  
  double dpp_ ;
  double dpi_ ;
  double dpd_ ;
  
  double p[3];
  double dp[3];
  double best_err = 1e9;
  double tol_ = 0.2;

  int numOfSteps;
  bool initialized_;
  bool up = true;

  double total_error;
  
public:
  int param;
  int phase;
  /*
  * Constructor
  */

  PID(int init);

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
  
  double getValue();

  int getNumberOfSteps() { return numOfSteps; }

  void setNumberOfSteps(int num) { numOfSteps = num; }
  
  void Restart(uWS::WebSocket<uWS::SERVER> ws);

  void init_param_phase() { param = 0;phase = 0; }

  double getErrorChange() { return d_error_; }

  void twiddle();
	
  double sum();
};

#endif /* PID_H */
