#include "PID.h"
#include <math.h>
#include <iostream>
#define MIN_NUMBER_STEPS 100

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID(int init):param(init),phase(init),numOfSteps(init) {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	Kp_ = Kp;
	Ki_ = Ki;
	Kd_ = Kd;
	
	p_error_ = 0;
  i_error_ = 0;
	d_error_ = 0;
	total_error_ = 0;
	
	numOfSteps_ = 0;
	dpp_ = Kp/4;
  dpi_ = Ki/4;
  dpd_ = .1;
  best_err = 1e9;
	initialized_ = true;
}
double PID::getValue() {
	double steeringAngle = -Kp_*p_error_ -Kd_*d_error_ - Ki_*i_error_;
	steeringAngle = steeringAngle<-1?-1:steeringAngle;
	steeringAngle = steeringAngle>1?1:steeringAngle;
	return steeringAngle;
}


void PID::UpdateError(double cte) {
	d_error_ = cte - p_error_;
	p_error_ = cte;
  i_error_ += cte;
	if(numOfSteps>MIN_NUMBER_STEPS);
	total_error += pow(cte,2) ;//+ .0001*pow(getValue(),2);
	numOfSteps++;
}

double PID::TotalError() {
	return total_error/(numOfSteps);
}

void PID::Restart(uWS::WebSocket<uWS::SERVER> ws){
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}

void PID::twiddle() {
	double err = TotalError();
	int numSteps = numOfSteps;
	total_error = 0;
	numOfSteps = 0;
	if(param == 0) {
		if(up) Kp_ += dpp_;
		else Kp_ -= 2*dpp_;
	}
	if(param == 1) {
		if(up) Ki_ += dpi_;
		else Ki_ -= 2*dpi_;
	}
	if(param == 2) {
		if(up) Kd_ += dpd_;
		else Kd_ -= 2*dpd_;
	}

	if(err < best_err && numSteps > 200) {
		best_err = err;
		if(param == 0) dpp_ *= 1.1;
		else if(param == 1) dpi_ *= 1.1;
		else dpd_ *= 1.1;
		param = (param+1)%3;
		up = true;
		std::cout << "New best Kp: " << Kp_ << " Kd: " << Kd_
				<< " Ki: " << Ki_ << " Error: " << best_err
				<< " Sum dpi: " << dpp_ + dpi_ + dpd_ << std::endl;

	} else {
		std::cout << "Skipped Kp: " << Kp_ << " Kd: " << Kd_
								<< " Ki: " << Ki_ << " Error: " << err
								<< " Sum dpi: " << dpp_ + dpi_ + dpd_ << std::endl;
		if(up == true) up = false;
		else {
			if (param == 0) {
				Kp_ += dpp_;
				dpp_ *= 0.9;
			}
			else if (param == 1) {
				Ki_ += dpi_;
				dpi_ *= .9;
			}
			else {
				Kd_ += dpd_;
				dpd_ *= .9;
			}
			param = (param + 1) % 3;
			up = true;
		}
	}
	
}