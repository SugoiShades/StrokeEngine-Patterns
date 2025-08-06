/**************************************************************************/
/*!
  @brief  Slammin: Slam the buisness end of your OSSM in with a bit more 
  aggression than usual and pause at the end of the stroke to make it
  feel more impactful and dramatic.

  Depth & Stroke charactaristics are the same as Simple Stroke and as such
  should behave the same.

  No idea why the pause seemingly gets noiceably longer if you adjust the
  speed at full extension. No real downsides other than aesthetic.

  The sensation slider behaves the same when + and - it's function is
  to lower the speed of the outwards stroke. I wasn't able to figure
  out some fancy math to scale down the speed as either stroke or speed
  increased, so my tradeoff was to just let it be configureable within
  a range. Consider the default to be half way between the center and
  one of the sides of the sensation slider. Couldn't get it to default
  there either lol

  Made with the longer toys in mind.
*/
/**************************************************************************/

class Slammin : public Pattern {
    public:
        Slammin(const char *str) : Pattern(str){}
            void setTimeOfStroke(float speed = 0) {
                _timeOfStroke = 0.5 * speed;
                _speed = speed;
            }
            void setSensation(float sensation = 40) {
                _sensation = float((abs(sensation) / 255) + 0.5);
            }
            void _updateDelay(int delayInMillis) {
                _delayInMillis = delayInMillis;
            }
            void setStroke(int stroke) {
                _stroke = stroke;
            }
            
            motionParameter nextTarget(unsigned int index) {
                //set default accel value
                _nextMove.acceleration = int(3.0 * _nextMove.speed/_timeOfStroke);
                //set a delay based on a given speed. Curve is based on some manual fishing for good set points followed by trying to match said points to a function in Desmos lol
                _delayInMillis = ((sqrt((350000 * _speed)+60000)) + 125);

                if (_isStillDelayed() == false) {
                    //Odd # stroke index is the slower out stroke (lower speed and lower accel)
                    if (index % 2) {
                        _nextMove.speed = int(_sensation * _stroke/_timeOfStroke);
                        _nextMove.acceleration = int(1.1 * _nextMove.speed/_timeOfStroke);
                        _nextMove.stroke = _depth - _stroke;
                    }
                    //Even # stroke index is faster than the average stroke giving the appearance of a faster more aggressive stroke even
                    //though it's only marginally faster than simple stroke (a multiplier of 1.6 vs 1.5) and even at a slightly reduced acceleration.
                    else {
                        _nextMove.speed = int(1.5 * _stroke/_timeOfStroke);
                        _nextMove.acceleration = int(2.8 * _nextMove.speed/_timeOfStroke);
                        _nextMove.stroke = _depth;
                        _startDelay();
                    }
                    _nextMove.skip = false;
                }
                else {
                    _nextMove.skip = true;
                }
                
            _index = index;
            return _nextMove; 
        }
    //had to declare the speed value for use in my delay calculation.
    private:
        float _speed;
};