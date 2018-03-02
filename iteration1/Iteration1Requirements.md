
>Your software is a reflection of your understanding of the requirements as specified in this document. If you do not understand any portion of the requirements or you think that the requirements are underspecified, it is your responsibility to get clarification from the instructor or a TA. Please read this document carefully and review it prior to turning in your iteration for assessment.

# Robot Simulator: Iteration 1

<span style="color:red">

| Date | Item | Description |
|:----:|:-----|:------------|
| TUE, Feb 20, 11:55pm | UML diagram of base code | submit via Github |
| TUE, Feb 27, 11:55pm | Preliminary code tests   | Pass automated tests |
| TUE, Mar 06, 11:55pm | Documentation and Code Implementation | Automated tests and inspection |

</span>

Your project should demonstrate thoughtful software development with good design quality, using good process. This iteration will help you to establish those good habits. Unit tests will be provided for automated testing of
functionality. You will create design documents including a UML diagram. _doxygen_ will be used to automatically generate code documentation. Code style will comply to the Google Style Guide. Intermediate deadlines will keep you on
track in this iterative process.

#### Deliverables and Submission Process

Everything will be submitted via Github in your **__PROJECT__** repo. We will pull your repository at the specified due dates and grade according to the contents at that time.

> Please verify that your submission compiles on a cselabs machine and it is complete. You will be heavily penalized if your code does not compile upon submission.

The schedule is very tight, and it is important that you keep up with the project. The project will continue to build throughout the semester, and if you get behind, it will be very difficult to catch up. For this reason, **late
assignments will not be accepted**, but you will receive partial credit for partial completion of the requirements.

You can convert this requirements document to pdf using this tool: http://www.markdowntopdf.com/

<hr>

## Documentation and Code Implementation Requirements

### Overview

The goal of this software project is to develop a rudimentary robot simulator in which robot behavior is visualized within a graphics window. The exact use of the application is yet to be determined. It might be that it is used more
like a video game in which users control the robots. Alternatively, it might be a test environment for experimenting with autonomous robot control using sensor feedback, or it might be a visualization of real robots operating in a remote
location. Due to the ambiguity of future use, it is important that you plan for change through good design.

In this iteration, you will put all the pieces in place for development including libraries, base code, unit tests with Google Test, class structure, Google style guide compliance, design documentation using UML, doxygen
documentation, Git usage, and self-documenting code (i.e. good organization and naming conventions). Teaching staff will also be working diligently to provide the structure and support for development, testing, and documentation. Automation in unit testing, style compliance, in-house github testing, and documentation will make this an easier process, however it means that you will have to develop within the constraints of these systems. Often there is a learning curve and a lot of systems trouble-shooting to get it all working, so start early!

In the first iteration, the robot simulator is more like a video game. A user controls the robot with the arrow keys. The objective of the game is to touch all of the bases without running into (eventually moving) obstacles or walls. The robot is given a fixed number of lives at the beginning of the game, but it will lose a life with every collision (except for when colliding with a base).

### Functional Requirements

You are being provided with a significant initial code base. The first iteration is focused on enhancing functionality and getting practiced in the software development process. It is also a drop into the depths of C++ syntax. If you have any questions about the provided code, please ask. We do not expect you to understand all the constructs in this code. Below is an outline of the required functionality.

The code is organized such that robot behavior in the arena (i.e. the model) is separate from visualization (i.e. the view), which allows for automated unit testing using Google Test. There is also a controller that handles the communication between the model and the view. The Robot class is composed of many other classes that control various aspects of robot behavior and environment interaction. You will need to maintain this class structure to interface with Google Tests.

#### Robot Arena

The robot arena has a robot, 1 obstacle, and 1 stationary base initially, but you will be adding more entities. The intent is for the robot to touch all bases while avoiding collisions with obstacles and the wall. If a robot bumps into something, it will stop moving and await input from the user to get out of its situation. If an obstacle collides with something, it will reverse in an arc for a fixed amount of time in an attempt to avoid the object. The user can change the speed and direction of the robot using the arrow keys. If the robot touches all bases, the user wins. If the robot runs out of lives, the user loses. None of this functionality is implemented in the base code.

#### Graphics Environment

The graphics environment consists primarily of a single window with robots, obstacles, and bases. All objects (except for the wall) in the environment will be drawn as circles, which greatly simplifies collision detection. You are welcome to add graphics enhancements, such as color, text, or decorations provided it does not interfere with required functionality. The basic graphics window framework has been provided. You will need to get familiar with the graphics library and provided code to learn how to draw objects of particular shape in the environment.

#### GUI and User Input

A basic GUI with user buttons and input via mouse and keyboard has been provided. The user should have the following controls:

- With UI buttons: Pause, Play, and Start a New Game
- With left and right arrow keys, change the direction of the robot
- With up and down arrow keys, change the speed of the robot (no reverse)

<hr>

**REQUIREMENTS you need to fulfill**

> This is just functionality. Along the way, please document the code using
Doxygen syntax and test for Google Style compliance using cpplint.

The iterative method identifies and prioritizes feature enhancements and code refactoring over short intervals called sprints. Below is a prioritized list of feature enhancements, fixes, and refactoring of the code. **Complete all functionality in one priority level before moving on to the next.** In this way, if we run out of time, the low priority items will be dropped from the requirements.

#### Priority Level 1 : Arena Entities and Robot Behavior

- When the simulation begins, there should be 1 robot, 4 immobile obstacles, and 3 immobile bases, all randomly placed. Obstacles should be randomly sized and bases should be uniformly sized.

- When the user presses an arrow key (a single keypress - not continuous), the robot behavior should be modified in the following way:
  - Up arrow increases speed of both wheels, up to a defined limit.
  - Down arrow decreases speed of both wheels, down to 0 (no negative speeds).
  - Right arrow increases the speed of the left wheel and decreases the speed of the right wheel by some default value.
  - Left arrow increases the speed of the right wheel and decreases the speed of the left wheel by some default value.

- When the robot collides with an object, the robot should stop.

- Implement winning and losing.
  - When a robot collides with an obstacle or a wall, it should lose a life.
  - When the robot collides with a base, the base should change color to indicate that the robot has already tagged that one.
	- If the robot collides with all bases, the user has won. There should be some obvious visual indication that the game has been won.
  - If the robot loses all its lives, the user has lost. There should be some obvious visual indication that the game has been lost.
  - Upon a win or loss, the game should stop and wait for the user to select "New Game" before resetting the environment to a new start state.

#### Priority Level 2 : Mobile Obstacles and Game Control

- Obstacles should be made mobile using two-wheeled motion, although when moving forward, both wheels should have the same speed, thus they only go in a straight line.

- When an obstacle's touch sensor is activated, it should reverse in an arc for a fixed amount of time, then proceed forward which should move it around the obstacle. For the wall, it might end up hitting the wall multiple times before orienting back towards the center of the arena.

- All game control based on the GUI should go through the controller, which will appropriately pass commands to the arena.

- When the game begins, all entities are not moving. The user has to push a "Play" button to begin. Once the button is pushed, the button text should change to "Pause".

- When the user pushes the "Pause" button, the play should pause and the button text should change to "Play."

- When the game begins, a button "New Game" is available. If the user selects this, the simulator will reset the environment to a new start state.

- The number of lives remaining should be depicted within the body of the robot

#### Priority Level 3 : Extending the game

- Add more obstacles.

- [Mercy invincibility]
  - When the robot collides with an obstacle, the robot will stop and lose a life.
  - To provide a chance for the player to escape, the robot will be given momentary invincibility. Any collisions during the 2 second after a collision will not reduce the lives of the robot. It can still collide with obstacles (and will need to stop) but if the collision occurred during these invincibility frames, the number of lives will not decrease.
  - Ideally, this mercy invincibility will be indicated by having the robot flash: either disappear and reappear or change between the default color and another color at a speed of your choosing.

#### King of the Hill Challenge [NOTE: This is UNGRADED, only for fun.]
  If you get all your work done, you can enhance your game with _King of the Hill_ rules in which the robot must hit a base and stay next to the base for
  2 seconds without getting hit by an obstacle to capture the base. All bases must be captured to win the game.


<hr>

### Unit Testing with Google Test

https://github.com/google/googletest

Unit tests are essential in a large-scale project, because the entire code base can be tested regularly, automatically,
as it undergoes development. In the strictest application of Test-Driven Development (TDD), the tests are written
_before_ the code, which helps solidify requirements and write testable code.

While not strictly TDD, the provided code for this project iteration will include tests written in Google Test. The
functionality of the various functions and class methods must pass each of these tests (which are a subset of the
complete tests used for assessment) to receive full credit. **Note what was just stated: these are a subset of tests
used for assessment, thus also write and use your own tests.**

Tests will be provided via a separate test repository within the 3081 organization. This repository must be a sibling to your project repository for the course. For example, if your username is _smith01_, when you did an `ls` in the directory that holds your repo, you would see `project-smith01` and `public-tests`. When you compile the tests, they will include your source code and produce a report of pass or fail of each unit test. The requirement of the preliminary code submission is the passing of all unit test for the Priority Level 1 functionality. **__If you are failing any test, you need to modify your code to work with the tests. You should never modify the files in _public-tests_ to work with your code.__**

### File Structure

A **__new repository has been created for you within the course organization__** that should be used exclusively for project development. This repo is named `project-<username>`. Please continue to use the repo `repo-<username>` for labs and in-class exercises. You must follow the file structure provided. It follows the conventions of code development, with some specific requirements added as part of the Google style guide. Not being compliant with the structure will likely break compilation and testing. Even if it doesn't, you will lose points for not maintaining the provided file structure.

### Google Style Guide Compliance

https://google.github.io/styleguide/cppguide.html

Consistency in code organization, naming conventions, file structure, and formatting makes code easier to read and integrate. There are many options with various merits, so it is up to the development team to establish these
conventions, or in the words of Kevin Wendt "The only style guide that really matters is the one your boss uses." We decided to use the Google style guide because it is published, documented, and has automated tests. We don't agree with every decision, but we are complying so that we are all coding to a single standard.

To test your code for Google style compliance, you can run cpplint on a cselabs machine:

```
cd src
cpplint.py --root=.. *.h
cpplint.py *.cc
```

The tag `--root=.` impacts the header guard. The header guards provided in the base code all start with `SRC`. If you are getting errors due to the header guard because it is expecting `INCLUDE_SRC` or no `SRC` **do not change the header guard.** Instead, check that the flag is set properly. If the `--root` flag is not working, please notify staff so that we can figure out how to fix it.

To check Google style compliance on your personal machine, you will need to install cpplint (https://github.com/cpplint/cpplint).

Obviously, if you are doing this on your own laptop you need Python 3.x installed.

<hr>

## Documentation

- UML diagram
- Doxygen generated web pages including mainpage.h
- Self-Documenting code that is Google Style compliant

Code documentation comes in many forms for many audiences. For this project, **your audience is other programmers**, who need to understand class interfaces, function parameters, function behavior, code organization, class organization, and code logic. Self-documenting code (i.e. using good organization and naming conventions) is an efficient means of communicating, since you have to write the code anyway. _Good_ comments - not too much, not too little - help guide others through the logic and class interfaces. For the larger picture of code and class structure, use UML diagrams and Doxygen-generated (automatic) web pages.

#### UML

The UML diagram is a visual aid that helps other programmers better understand the code structure. It should include only those aspects that are essential, otherwise your diagram will get too cluttered and overwhelm the reader. Here are some things to keep in mind as you are designing your UML:

- Make the most important classes prominent in the layout (i.e. your eye tends to focus in that general area when you first look at it).
- Lay out the classes so that the connections have as few crossovers as possible.
- Do not include setters and getters in your methods list unless there is something special about them that you need to communicate.
- You do not need to include structs or enumerated types unless they add value to the understanding of the overall code structure.
- If a class is composed of another class, you can show that association with a solid line arrow (if there is only 1) or using the _compose_ diamond.
- Include cardinality where appropriate.
- Add comments to classes and/or relationships to clarify the interaction or to point out subtleties that are essential to using the code.

The UML diagram is part of the "W" writing requirement in this course. It will undergo multiple drafts and upon submission should match the state of the code. For example, the first UML draft is of the provided base code. The iteration 1 UML should reflect the changes you made while completing the code requirements. We will be looking for proper use of UML components, and a correct depiction of the code structure.

There are many free tools that you can use to create the UML. **Submit your UML as a .pdf or some other easily readable format**. 

#### Doxygen

Doxygen automatically generates documentation of class and code structure when you follow some simple conventions for commenting within your code (_see_ http://www.stack.nl/~dimitri/doxygen/). We will be discussing Doxygen in class and in lab. To start with, look over the documentation provided with the code base to understand how to document classes, methods, parameters, and even _todo's_ and _bugs_ in your code. In lab, you will learn how to compile with your Doxyfile and generate web pages. Please look over the generated web pages for missing and incorrect information. The requirements for Doxygen include:

- the file `/docs/Doxyfile` to generate documentation (this file is provided, so you shouldn't have to do anything with regard to this requirement).

- a _mainpage.h_ file that serves as the homepage of your automated documentation. This is an introduction to the code to other programmers who might be new to the project and need to understand it to contribute to the project.

- fully documented classes and methods.

- The /html directory should not be in your repo in github.

> As part of your fresh clone prior to submission, please also compile the Doxygen and look at the generated webpages.

All of these elements of documentation will be assessed, accounting for half of your grade for each iteration. Think about these two extremes: 1) your code functions perfectly and you have almost no documentation - you will likely fail
on this iteration; 2) your code is not functional and will only compile when you comment most of it out, but you have complete, great documentation - you will likely get a decent grade on this iteration. Get in the habit of creating the documentation along with the code.

<hr>

## Assessment

Your software **must compile on a cselabs machine or it will not be graded**. We will not grade your project unless it compiles. As long as you provide a version that compiles, we will evaluate those aspects that are partially functional for partial credit. In other words, <u>comment it out if it breaks compilation</u>.

Your software will be assessed through automatic testing and by the TA. You will receive immediate feedback whenever you push to github (although not now - we will let you know when those scripts are in place). At the deadline, all submissions will be downloaded and the automated testing will no longer be available. Through both automated testing and the TAs, the process for testing will be to `make clean` then `make`. We **highly encourage** you too freshly clone your repo on a **cselabs machine** and also `make clean` and `make` to confirm all is working well.

This is the breakdown for point distribution:

23% : Iteration \#1
- 10% : UML (base code, draft). Refine for submission with Final Documentation.
- 10% : Preliminary Code Submission
- 40% : Final Documentation
- 40% : Final Code

### Documentation Assessment ( 50% )

#### Draft of UML Diagrams ( 10% )

Early in the iteration, you will construct a UML diagram of the provided code that helps other programmers better understand the code structure. **__At this point in time, the reality is that it is YOU who needs to understand the code and this exercise will be a tremendous help in that regard, saving you hours when you start to code.__**  Keep in mind that UML is a visual aid and should include only those aspects that are essential, otherwise your diagram will get too cluttered and overwhelming to the reader. Keep in mind that you can add notes and clarification within the document.

This is a draft of the final product, and we anticipate that it will be revised and improved. We will be looking for proper use of UML components, and a correct depiction of the code structure. **Submit your UML as a .pdf or some other easily readable format**.

#### Complete Iteration Documentation ( 40% )

#### Design Document and UML

Documentation includes an overview of the design provided in mainpage.h in /src and the final UML diagram saved in /docs. The mainpage overview should be written in prose and be at least 1 page of text (if it were on an 8.5x11 paper), probably not more than 2. It should highlight important design elements, such as the separation of the graphics from arena, and the composition of the robot. We will
look for a well written and well organized document that clearly articulates the design. It must stand alone in the
sense that anyone reading it should not have to look at code to understand the design.

#### Google Style Compliance

We will run the automated test using 'cpplint' to check compliance. There are a few additional elements for compliance
that _cpplint_ does not check for, thus TAs will inspect for those.

#### Doxygen Documentation

We will compile the code to generate _Doxygen_ web pages. All classes and major functions must be documented as
specified in the _Doxygen_ documentation.

#### <s>Readme.md</s> BugReport.md

The github submission must include a _/docs/bugreport.md_ that communicates to the TAs. For every file in the project, you should detail all bugs and provide a potential fix. If there are no bugs in a file, state that there are no known bugs to report (never say that there aren't bugs, because we know that that is typically not the case :-). We anticipate that a few bugs will exist in your project that reveal themselves during testing. If you have a few bugs AND you report them, then you will lose few to none points, provided they aren't preventing the game from being played. Also, keep in mind that development will continue throughout the semester, and if you can't fix your code this iteration, you might have an opportunity in the next one, so keep track of all your bugs.

#### Self-Documenting Code

TAs will inspect code for good naming conventions, good code organization, and internal comments to highlight logic. You should not nest conditional statements too deep. Methods should not be more than a screen full, if possible. Names should be descriptive of the variable's or function's purpose. Like elements should be next to each other in the file.

### Code Assessment ( 50% )

#### Preliminary Code Submission ( 10% )

In the week prior to the due date of the completed iteration, we will run a subset of the automated tests. You must pass all the tests for Priority Level 1 to receive full points for the preliminary submission. There will be no inspection of the code at this point -- it is strictly a test for completed functionality. There will be transparency in this process in that you will know what functionality will be tested, and you will see the results. Points earned at this stage are independent of the 40% points for the final submission.

#### Completed Iteration Code ( 40% )

Code functionality will be tested with automated tests through Github, which in turn run the automated unit tests of Google Test. The provided unit tests are a subset of the final tests run for this iteration. Review the automated
feedback prior to final submission, as it will identify any issues with directory structure, compilation issues, or failed unit tests. Assessment will also include a visual inspection of the game, as well as a visual inspection of the code.

<hr>

## Getting Started

AFTER reading this document, pull the public class repository to obtain the base code. Copy the iteration1/src directory to your individual PROJECT class repository /iteration1/src directory on a cselabs machine while maintaining the file structure. These folders have been provided for you in your `project-<username>` repo. Follow the directions for compilation and start it up!

> **NOTE**: Graphics code has been compiled and made available on the cselabs machines. You are linking with this code,
> thus it should not appear in your repo. If you want to develop on your personal machine, then you need to recreate
> this set-up. Do not put this code in your repo.


<hr>

## Resources

Graphics Libraries :
- https://github.com/wjakob/nanogui
- https://nanogui.readthedocs.io/en/latest/
- https://github.com/memononen/NanoVG
- https://www.opengl.org/

Local System and Compilation:
- Repo: https://github.umn.edu/umn-csci-3081F17/class-repo-public
- Linking library: `/project/3081cf17/`
- Compilation: https://gcc.gnu.org/
- Linux quick reference: http://www-users.cs.umn.edu/~larson/repo-website-resources/website/examples/csresources/linux.html
- Makefile Resources: http://www-users.cs.umn.edu/~larson/repo-website-resources/website/examples/csresources/cpp.html

Testing:
- https://github.com/google/googletest
- Unit Testing: https://martinfowler.com/bliki/UnitTest.html

Style:
- https://google.github.io/styleguide/cppguide.html
- https://github.com/google/styleguide/tree/gh-pages/cpplint
- https://www.python.org/downloads/

Documentation:
- http://www.stack.nl/~dimitri/doxygen/
- https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet

IDEs:
- Xemacs: https://www.xemacs.org/
- vi: http://www.lagmonster.org/docs/vi.html
- Atom: https://atom.io/
- Sublime: https://www.sublimetext.com/
- Eclipse: https://eclipse.org/

<hr>

### Response to Forum Inquiry:

We will respond here for important changes due to conversations held in Piazza.
