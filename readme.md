# Naive Bayes

Well Hello! This is a Naive Bayes classifer that predicts the likely action of a vehicle based on its position on the lane.
This is one of the quizzes in the Udacity Self Driving Engineer ND.

No feature engineering is used, so it's really naive. Terrible puns aside, the classifer has a 84.4% accuracy on the test data.
This can likely be improved, but a python envirnment is a better medium for establishing features.


I didn't include images because I don't know if I can share that!



The following is the problem description from the Udacity Quiz:

>In this exercise you will implement a Gaussian Naive Bayes classifier to predict the behavior of vehicles on a highway. In the image below you can see the behaviors you'll be looking for on a 3 lane highway (with lanes of 4 meter width). The dots represent the d (y axis) and s (x axis) coordinates of vehicles as they either...
>
>change lanes left (shown in blue)
>keep lane (shown in black)
>or change lanes right (shown in red)
>Your job is to write a classifier that can predict which of these three maneuvers a vehicle is engaged in given a single coordinate (sampled from the trajectories shown below).
>
>Each coordinate contains 4 pieces of information:
>
>s

>d

>(del)​s

>(del)​d

>​

>You also know the lane width is 4 meters (this might be helpful in engineering features for your algorithm).
