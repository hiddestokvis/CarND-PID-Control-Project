# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program


# Finding the right Parameters

I started off initiating the P, I and D parameters to 0.1. I used Twiddle to optimize the steering during the first 150 frames. This way I could find basic parameter settings that made the car drive in a straight line. You can see footage of the first optimization [here](https://youtu.be/pEGnSGUMG6c).

## The P or proportional parameter

The P parameter is most directly responsible for steering the car. It steers the car back towards the center line (CTE) in a proportional way.

## The I or integral parameter

The I parameter counteracts a bias in the CTE. In the lessons by Sebastian it was mentioned this can be used to counteract drift. It's also clear from the initial optimalizations that a high I level makes the car steer very unstable. As the simulator has no drift I set the I-parameter to 0 in the final settings.

## The D or differential parameter

The D component counteracts the P-components tendency to overshoot the center line.

# How where the hyper parameters tuned?

I started off with all hyper parameters set to 0.1 and I used twiddle to train the car during the first 150 steps. After a 150 steps the simulator was restarted and Twiddle updated the parameters. It took 71 iterations to get the total error below 5 and get the car to drive off in a reasonable straight line.

From here I started to increase the number of steps included in a twiddle optimalisation round. Also I set the integral parameter to 0 as the simulator has no bias and I adjusted the twiddle optimalisation to tune just the two (P&D) other parameters. Tuning up to just past the first corner showed me I needed to increase the D parameter further.

Finally I increased the number of steps to include a full circle around the lap and optimized until I was reasonably confident with my results.
