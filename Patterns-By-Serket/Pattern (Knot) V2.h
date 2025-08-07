/**************************************************************************/
/*!
  @brief  Knot: a modification of my Struggle pattern to have a pause added
  at the end of the stroke and to use sensation to change the speed of the
  slow portion of the stroke rather than how much of the stroke is slow.

  V1 Initial pattern made by Serket

  V2 tweaks made by Vampix (work in progress)
*/
/**************************************************************************/

class Knot : public Pattern {
    public:
        Knot(const char *str) : Pattern(str){}
            void setTimeOfStroke(float speed = 0) {
                _timeOfStroke = 0.5 * speed;
                _speed = speed;
            }
            void setSensation(float sensation) {
                _sensation = float(abs((sensation) / 1000) + 0.001);
            }
            void _updateDelay(int delayInMillis) {
                _delayInMillis = delayInMillis;
            }

            motionParameter nextTarget(unsigned int index) {
                _nextMove.acceleration = int(3 * _nextMove.speed/_timeOfStroke);
                //fancy equation to calculate the pause in milliseconds using the current speed as an input. put it into the Desmos web graphing calculator
                //with Y as the delay in ms and X as speed to get an idea for a given speed what the corrosponding delay would be. Tweak the 3 numbers in Desmos
                //and not here in the pattern as it's hard to conceptualize how it'll change.
                _delayInMillis = ((sqrt((350000 * _speed)+60000)) + 550);

                if (_isStillDelayed() == false) {
                    if (index % 5 == 1) {
                        _nextMove.acceleration = int(2 * _nextMove.speed/_timeOfStroke);
                        _nextMove.speed = int(0.8 * _stroke/_timeOfStroke);
                        //70% of the stroke looks good visually. tweak the below 0.70 to change the % of the in stroke is at normal speed
                        _nextMove.stroke = int((_depth - _stroke) + (_stroke * 0.70));
                    }
                    else if (index % 5 == 2) {
                        _startDelay();
                    }
                    else if (index % 5 == 3) {
                        _nextMove.acceleration = int(2.3 * _nextMove.speed/_timeOfStroke);
                        _nextMove.speed = int(_sensation * _stroke/_timeOfStroke);
                        _nextMove.stroke = _depth;
                        //Uncomment the following 2 lines to see the current speed value printed and then the corrosponding delay in ms. Useful for tweaking the equation for tweaking the delay curve.
                        Serial.println("Speed: " + String(_speed));
                        Serial.println("Delay in ms: " + String(_delayInMillis));
                    }
                    else if (index % 5 == 4) {
                        _startDelay();
                    }
                    else  {
                        _nextMove.acceleration = int(2 * _nextMove.speed/_timeOfStroke);
                        _nextMove.speed = int(1.0 * _stroke/_timeOfStroke);
                        _nextMove.stroke = _depth - _stroke;
                    }
                    _nextMove.skip = false;
                }
                else {
                    _nextMove.skip = true;
                }

            _index = index;
            return _nextMove;
        }
    private:
        float _speed;
};