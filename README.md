##CarND-PID-Control Project##

###Determination of the PID values ###

The PID values were determined using initial values  and then tuned by using the twiddle algorithm. The values are updated until the mean squared error of the cte doesn't decrease and no manual interaction happened, else the value is skipped as the parameters are assumed unstable. The manual interaction happening means the simulator is rested. 

####Proportional  value####

The proportional value  gives the proportional factor which converse the CTE to steer angle.  As the CTE error  is approximately between -5m and 5m on the pavement and the steering angle value is between -1 and 1, the proportional value is expected to have an magnitude of approx. 0.1 as this would lead a steering angle of approx. 0.5 when the cat is at the edge of the road.

####Differential value####

 The differential term captures the variation tendency of CTE and gives the proportional factor which converse the derivative of  CTE to steer angle value  so that the CTE approaches 0 smoothly.  Of course, over weighting this component can overcompensate and cause  oscillation. As the derivative CTE error is approximated by the difference between the last two values, the differential value should be bigger than  the proportional value, and I chosen in an magnitude of approx. 1. 

####Integral value####

The Integral value gives the conversion from all accumulated CTE errors to the steering angle value and I chosen the value in an magnitude of approx. 0.001～0.01. The integral component of the PID controller compensates for steady state error.  In the case of the racetrack,  although  the P and D components would adjust the steering,  but a large steering oscillation would result without this integral component. 

###Speed PID controller###

The PID controller performs reasonably well at modest speed, such as the default 0.3 throttle.  However, when the speed is increased, significant oscillation develops with the parameters set for slower speed.  This is, presumably, due to delay in the control path.  Assuming the simulator is physically accurate, steering cannot have an instantaneous effect, and increased speed results in increased offsets that overwhelm the controller responses.  To enable higher average speed, a second PID controller is used to track a target speed. The target speed is composed of  two parts, one is  relative to the steer angel which is in the range of -1 to 1, the other is a constant speed value when the steer angel is in the maximum/minimum.  

###Final Parameter Tuning###

Key to successful operation of a PID controller is good selection of the weights applied to the P, I, and D components. I chosen the initial values  manually and then running the twiddle algorithm to tune the final values. which is as follow:
- The final P-Value is 0.08
- The final I-Value is 0.001
- The final D-Value is 1
The fastest speed to safely go is 67mph.





