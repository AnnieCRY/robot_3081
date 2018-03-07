### CSCI3081W: Iteration 1 Submission Checklist

> The iteration 1 code and documentation is due on TUESDAY, Mar 06 at 11:55pm

Please copy this file into your /docs folder. Place an 'x' in each of the `[ ]` boxes for items that are complete. Push this completed checklist to github. When it displays on Github, it will show an actual checkbox with a check mark.

### Compilation and Execution

- [ ] I cloned **fresh** from github onto a cselabs machine to test compilation
- [ ] Submission is on the master branch of the my project repo "project-<username>"
- [ ] _/iteration1_ folder exists
- [ ] _/build_ is not in the repo
- [ ] _/html_ is not in _docs_
- [ ] **__`make` from src completes without error.__**
- [ ] `./../build/bin/arenaviewer` executes without assert or a seg fault
- [ ] `cpplint.py *.cc` reports no errors
- [ ] `cpplint.py --root=.. *.h` reports no errors
- [ ] `doxygen Doxyfile` compiles

### Primary Functionality

> To make grading easier, we ask that you provide the status of each of the requirements. Do not lie about the status!! It makes us grumpy -- you want your grader to be happy when s/he grades! We will be inspecting the code to confirm,
but this status report can make it faster for us.

**__Please place an 'X' in the appropriate box for each requirement.__**
- Good = Fully Implemented. No _known_ bugs. No _obvious_ bugs.
- Okay = Works but some bugs (recorded in bug report).
- Help = Attempted but not working.
- Time = No to Little Progress

| Functionality | Good | Okay | Help | Time |
| -------- | -------- | -------- | -------- | --------- |
| **__Priority Level 1__** | 
| _Enitities_ are generated and placed according to the requirements |  |  |  |  |
| _Robot_ adjusts wheel velocities when pressing the arrow keys |  |  |  |  |
| _Robot_ stops when colliding with an object |  |  |  |  |
| _Robot_ loses a life when colliding with an obstacle or wall |  |  |  |  |
| _Base_ changes color when captured by _Robot_ |  |  |  |  |
| Game is won if robot captures all bases |  |  |  |  |
| Game is lost if the robot loses all its lives |  |  |  |  |
| Obvious visual indication of winning or losing game |  |  |  |  |
| Game stops and waits for the user upon a win or loss |  |  |  |   |
| **__Priority Level 2__** |
| _Obstacles_ are mobile with two same-speed wheels and moves straight |  |  |  |   |
| _Obstacles_ move in a reverse arc for a fixed time after collision |  |  |  |   |
| All entities are stationary before the "Play" button is pushed |  |  |  |   |
| Pressing the button changes button state from "Play" to "Pause" |  |  |  |   |
| Pressing the button changes the game state from playing to paused (or back) |  |  |  |  |
| "New Game" button is available to user |  |  |  |  |
| Pressing "New Game" begins a new game |  |  |  |  |
| Number of lives remaining is depicted within the body of the robot |  |  |  |   |
| **__Priority Level 3__** |
| Even more obstacles |  |  |  |   |
| Mercy invincibility is implemented |  |  |  |   |
| For Fun | 
| King of the Hill is implemented |  |  |  |   |

### Documentation
> Documentation should be in good _draft_ form.

- [ ] _UML_ file for the iteration 1 exists in _docs_
- [ ] The _UML_ reflects the current state of the code
- [ ] _mainpage.h_ exists in _src_
- [ ] Front page (mainpage) has a project description for programmer audience (1 to 2 pages)
- [ ] I inspected index.html in _docs/html_ folder
- [ ] Classes are documented in the doxygen web page class list
- [ ] _Classes_ list has documentation for each class, including members and methods
- [ ] I perused other classes to spot check documentation
- [ ] I commented my code where necessary

### Unit Tests, Linter, and Git
- [ ] The code passes all the unit tests WITHOUT modification to the provided tests.
- [ ] The code complies with naming conventions for classes, methods, and members.
- [ ] There exists a history of git commit messages to show effort.

### BugReport
- [ ] BugReport.md is in the /docs folder.
- [ ] The report includes a list of known bugs (or states "no known bugs") for each file.
  > If you report _minor_ bugs, you will lose few to no points for that functionality.
  > If you try to hide some obvious bugs and not report them, you will lose all the points for that functionality.

## Ready For Submission

When everything above is as you want it or it is 11:55pm on Tuesday, it is time to submit!

- [ ] I pushed this file and any changes resulting from this checklist.

_One more thing -- check that what you think you pushed was really pushed to github. If you can see it, we can see it. If you can't, we can't._

Congratulations on your submission!

