# Intro
Hello! This is a short into to my patterns.
I go by Serket but you may see me under the usernames SugoiShades or DirkStrider.
This folder contains all of the patterns I have made so far in the format described in the main README file.

## Struggle V1
Initial Public Version
This is the first pattern I made & it was designed with the express purpose of making the OSSM look like it's exerting additional force at the end of a stroke. i.e. it's harder to complete the last bit of the stroke.
**Sensation**: The sensation parameter is used in this pattern to vary how much of the end of the stroke is slowed down. A sensation of 0 would mean the entirety of the stroke would be done at the slower speed, A sensation of +-100 would be full speed/none of the stroke is slowed. However, as those are not desired behaviors I bounded the range to a minimum of 50% of the stroke and 90% of the stroke.

## Slammin V1
Initial Public Version
This is the second pattern I made. Fairly simplistic in it's goal, It's specifically meant to slam the end effector of your OSSM in with a greater relative velocity. This isn't actually any faster than the same given speed, depth, and stroke values for simple stroke, it just slows down the outward stroke to make it appear more aggressive. A pause is also added to the end of the stroke for dramatic effect.
**Sensation**: The sensation parameter for this pattern is used to slow down the speed of the outward stroke relative to the speed of the inward stroke. I tried to figure out fancy maths for scaling down the speed as the stroke or speed increased but couldn't. Being able to control it with the sensation slider is the best tradeoff I could manage. Behaves the same on the + and - sides of the sensation slider. Consider the default to be half way in either direction (couldn't figure out how to do that either)

## Knot V1
Initial Public Version
A variation of my previous struggle pattern made at the request of someone on the KinkyMakers Discord.
The main difference is that sensation changes the speed of the slow portion of the stroke rather than how much of the stroke is slow. There is also a short pause added to the end of the stroke as well for dramatic effect.
**Sensation**: As stated above, sensation changes the speed of the end of the stroke rather than the amount of the stroke that is slow.


### Contact info/methods
If you notice any dangerous behavior with any of my patterns please submit a [issue here on the github](https://github.com/SugoiShades/StrokeEngine-Patterns/issues) or contact me on the KM discord.