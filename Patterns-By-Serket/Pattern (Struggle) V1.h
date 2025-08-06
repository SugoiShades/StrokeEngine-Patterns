/**************************************************************************/
/*!
  @brief Struggle: This pattern slows down the end of the stroke uses the
  sensation param to vary how much of the end of the stroke is slowed down.
  theoretically 0 sensation would be the entire stroke is slow and -+100
  sensation would be none of the stroke is slowed. However, those extremes
  are unwanted behavior in this context, so I bounded it to a min of 0.5
  and a max of 0.9 to keep its behavior inline with expectations.
  Conceptualized with the idea of using knotted toys.
*/
/**************************************************************************/
class Struggle : public Pattern {
    public:
        Struggle(const char *str) : Pattern(str){}
            void setTimeOfStroke(float speed = 0) {
                _timeOfStroke = 0.5 * speed;
            }
            void setSensation(float sensation) {
                _sensation = ((abs(sensation) / 250) + 0.5);
            }

            motionParameter nextTarget(unsigned int index) {
                _nextMove.speed = int(1.5 * _stroke/_timeOfStroke);
                _nextMove.acceleration = int(3.0 * _nextMove.speed/_timeOfStroke);

                if (index % 3 == 1) {
                    _nextMove.acceleration = int(6 * _nextMove.speed/_timeOfStroke);
                    _nextMove.speed = int(1.5 * _stroke/_timeOfStroke);
                    _nextMove.stroke = int((_depth - _stroke) + (_stroke * float(_sensation)));
                }
                else if (index % 3 == 2) {
                    _nextMove.acceleration = int(3 * _nextMove.speed/_timeOfStroke);
                    _nextMove.speed = int(0.5 * _stroke/_timeOfStroke);
                    _nextMove.stroke = _depth;
                }
                else  {
                    _nextMove.acceleration = int(3 * _nextMove.speed/_timeOfStroke);
                    _nextMove.speed = int(1.5 * _stroke/_timeOfStroke);
                    _nextMove.stroke = _depth - _stroke;
                }

                _index = index;
                return _nextMove;
            }
            
};