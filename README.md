# StrokeEngine-Patterns
A centralized repository for stroke engine patterns to make it easier to find new patterns!

# $${\color{red}WARNING}$$
All the patterns here should be used with caution until sufficiently tested. We're still figuing out a workflow for verifying the safety of patterns. **use your best judgement**
# $${\color{red}WE \space TAKE \space NO \space RESPONSIBILITY \space FOR \space WHAT \space OCCURS \space DURING \space PLAY \space WITH \space THESE \space PATTERNS}$$
Always test a new pattern on your machine before play even if it's been vetted by others.
Roll through the ranges of speed, depth, stroke, and sensation if applicable to make sure nothing unexpected or dangerous happens.
If you notice any issues, please contact the creator of the pattern or post an issue so we can pull the pattern down & fix it before someone gets hurt.

## Formatting
The format of all patterns in this repo should be fairly straightforward. Here is the "Simple Stroke" pattern from the default Stroke Engine repo as an example!
```cpp
/**************************************************************************/
/*!
  @brief  Simple Stroke Pattern. It creates a trapezoidal stroke profile
  with 1/3 acceleration, 1/3 coasting, 1/3 deceleration. Sensation has 
  no effect.
*/
/**************************************************************************/
class SimpleStroke : public Pattern {
    public:
        SimpleStroke(const char *str) : Pattern(str) {}

        void setTimeOfStroke(float speed = 0) { 
             // In & Out have same time, so we need to divide by 2
            _timeOfStroke = 0.5 * speed; 
        }   

        motionParameter nextTarget(unsigned int index) {
            // maximum speed of the trapezoidal motion 
            _nextMove.speed = int(1.5 * _stroke/_timeOfStroke);

            // acceleration to meet the profile
            _nextMove.acceleration = int(3.0 * _nextMove.speed/_timeOfStroke);

            // odd stroke is moving out    
            if (index % 2) {
                _nextMove.stroke = _depth - _stroke;
            
            // even stroke is moving in
            } else {
                _nextMove.stroke = _depth;
            }

            _index = index;
            return _nextMove;
        }
};
```
have the plain/human readable name for the pattern be within quotation marks in the file name for the pattern like below. (this will be referred to as `"pattern_plain_name"` below)
and the file's name would be "Patern (Simple Stroke) V1.h"

For more examples, check the [Patterns-By-Serket](https://github.com/SugoiShades/StrokeEngine-Patterns/tree/main/Patterns-By-Serket) folder.

## Installation
We have all these patterns, now how can we use them? Unfortunately it does require some manual work for the time being and the abilty to compile the OSSM Codebase. There isn't a path to making this process doable on the web flashers at this time.
### Environment Setup
Grab a copy of it from the [Official OSSM github](https://github.com/KinkyMakers/OSSM-hardware) here or your choice of fork (such as the [M5-Stroke repo](https://github.com/ortlof/OSSM-Stroke)) and then follow these instructions from the Research and Desire YouTube channel to get your dev environment setup [Setting Up For OSSM Development - Follow Along Guide](https://www.youtube.com/watch?v=5f4FZcFFXaA)
After you've successfully flashed the default firmware onto your OSSM, you're ready to start adding patterns!
## Adding Patterns to the OSSM-Hardware (official OSSM) repo
In Visual Studio, navigate to `/lib/StrokeEngine/src/pattern.h` With the pattern file open, scroll down to the bottom, you should see the Insist pattern's code and the Array that hold all the names for patterns.
right below the `};` add a new line with the enter key and paste in the code from your desired pattern file. The formatting should be the same as the other patterns already in the pattern.h file. After that, go to the bottom of the pattern array 
```cpp
/**************************************************************************/
/*
  Array holding all different patterns. Please include any custom pattern here.
*/
/**************************************************************************/
static Pattern *patternTable[] = { 
  new SimpleStroke("Simple Stroke"),
  new TeasingPounding("Teasing or Pounding"),
  new RoboStroke("Robo Stroke"),
  new HalfnHalf("Half'n'Half"),
  new Deeper("Deeper"),
  new StopNGo("Stop'n'Go"),
  new Insist("Insist")
  // <-- insert your new pattern class here!
 };
```
(just above it's `};`) and type in `new [pattern_class_name]("pattern_plain_name")` [pattern class name] should be the name of the pattern right underneath the explaination about the pattern & right after where it says class. and as a rule of thumb the name of the pattern in the file name should be this plain name. Ultimately what goes within the quotation marks doesn't matter, it should just change the display name of the pattern on your remote, so you could just call any pattern "cheese" or something if you want lol. We'll also need to add a comma to the end of the previous line/pattern entry for syntax reasons (rule of thumb, every pattern line should end with a comma except for the final pattern on the list)
For example let's add Simple Stroke to the list a 2nd time. the `pattern_class_name` for Simple Stroke is `SimpleStroke` and the `pattern_plain_name` is `"Simple Stroke"` That should look like this!
```cpp
/**************************************************************************/
/*
  Array holding all different patterns. Please include any custom pattern here.
*/
/**************************************************************************/
static Pattern *patternTable[] = { 
  new SimpleStroke("Simple Stroke"),
  new TeasingPounding("Teasing or Pounding"),
  new RoboStroke("Robo Stroke"),
  new HalfnHalf("Half'n'Half"),
  new Deeper("Deeper"),
  new StopNGo("Stop'n'Go"),
  new Insist("Insist"),
  new SimpleStroke("Simple Stroke")
  // <-- insert your new pattern class here!
 };
```
Press ctrl + s to save your changes and re-compile & upload the firmware to your OSSM and you should be good to go!

## Adding Patterns to the OSSM-Stroke (M5 OSSM Stroke) repo
In Visual Studio, navigate to `/OSSM-Stroke/lib/StrokeEngine/src/pattern.h` With the pattern file open, scroll down to the bottom, you should see the Insist pattern's code and the Array that hold all the names for patterns. right below the `};` add a new line with the enter key and paste in the code from your desired pattern file. The formatting should be the same as the other patterns already in the pattern.h file. After that, go to the bottom of the pattern array (just above it's `};`) and type in `new [pattern class name]("pattern Plain name")` [pattern class name] should be the name of the pattern right underneath the explaination about the pattern & right after where it says class. and as a rule of thumb the name of the pattern in the file name should be this plain name. Ultimately what goes within the quotation marks doesn't matter, it should just change the display name of the pattern on your remote, so you could just call any pattern anything you think is funny or memorable **remember what you write here, you'll need it for later**.
add a comma to the end of the previous line/pattern entry for syntax reasons (rule of thumb, every pattern line should end with a comma except for the final pattern on the list)
Look above at the [Official OSSM section](https://github.com/SugoiShades/StrokeEngine-Patterns/tree/main?tab=readme-ov-file#adding-patterns-to-the-ossm-hardware-official-ossm-repo) for an visual example of adding Simple Stroke a 2nd time.
Press ctrl + s to save your changes and re-compile & upload the firmware to your OSSM.

This is where M5 Diverges from the default OSSM repo. You'll need to pull down the repo for the M5 Remote ([OSSM-M5-Remote](https://github.com/ortlof/OSSM-M5-Remote)) separately from the M5 OSSM-Stroke repo ([OSSM-Stroke](https://github.com/ortlof/OSSM-Stroke))
After you have that pulled down into Visual Studio, navigate to the `/OSSM-M5-Remote/src/language.h` and `/OSSM-M5-Remote/src/ui/ui.c` files and open them.
in `language.h` scroll down to lines 40-50ish, they should look something like this
```cpp
#define T_Patterns          "Pattern:"
#define T_SimpleStroke      "Simple Stroke"
#define T_TeasingPounding   "Teasing or Pounding"
#define T_RoboStroke        "Robo Stroke"
#define T_HalfnHalf         "Half 'n' Half"
#define T_Deeper            "Deeper"
#define T_StopNGo           "Stop'n'Go"
#define T_Insist            "Insist"
```
add a new line that follows this syntax `#define T_[pattern_class_name]  "pattern_plain_name"` so for the simple stroke pattern, the `pattern_class_name` is `SimpleStroke` and the `pattern_plain_name` is `"Simple Stroke"` resulting in `#define T_SimpleStroke  "Simple Stroke"
Press ctrl + s to save this file.
in `ui.c` go down to line 1656, you should see a list of the patterns in a different format that looks like this
```cpp
    ui_PatternS = lv_roller_create(ui_Pattern);
    lv_roller_set_options(ui_PatternS,
                          "SimpleStroke\nTeasingPounding\nRoboStroke\nHalfnHalf\nDeeper\nStopNGo\nInsist",
                          LV_ROLLER_MODE_NORMAL);
```
add a `\n` to the end of end of the list before the quotation mark along with the `pattern_class_name` for example, if we were to add Simple Stroke a 2nd time, the line would look like this now
```cpp
    ui_PatternS = lv_roller_create(ui_Pattern);
    lv_roller_set_options(ui_PatternS,
                          "SimpleStroke\nTeasingPounding\nRoboStroke\nHalfnHalf\nDeeper\nStopNGo\nInsist\nSimpleStroke",
                          LV_ROLLER_MODE_NORMAL);
```
Press ctrl + s to save this file, and then compile and flash your M5 Remote with the modified firmware.
After that you should be ready to go!

## How to create new patterns
The official docs for Stroke Engine are here on the github repo for StrokeEngine itself [Pattern.md on Stroke Engine repo](https://github.com/theelims/StrokeEngine/blob/main/Pattern.md#contribute-a-pattern) at the contribute a pattern section.
At a later date I'll paraphrase it elsewhere on this github repo as a "Stroke Engine for dummies" with some examples for specifc things you may want to do with it.