# Mainpage
# Overview
This is a Braitenberg Vehicles simulator. The robots simulate Braitenberg vehicles which sense light and food in arena.(resource: https://en.wikipedia.org/wiki/Braitenberg_vehicle)
There are four kinds of vehicle patterns: Coward, Love, Explore and Aggressive. In the stimulation, robots exhibit “coward” or "explore" towards light. All the robots exhibit “aggressive” towards food. The robots have four status-not hungry, hungry, really hungry and starve. When the simulation starts and after a robot consuming food, the robot is not hungry. When the robot is not hungry, it moves according to light sensors. When the robot is hungry, it moves according to either food sensor or light sensor, depending on which reading is larger. In other words, it reacts to the closer stimuli. When the robot gets really hungry, it ignores the light and go aggressively towards food. The simulation terminates when any of the robots starve.
A special case is that when there is no food in the simulation. The robot will never be hungry and the simulation can be stopped only by user input.
The food are immobile stimuli. All the other entities can pass through food.
The light are mobile stimuli. They can pass through everything except another light and the wall. We need to handle collision between stimuli itself and between stimuli and the wall.

# Developer Guide
### main class
- **arena**: Arena create food and the mobile Entity and the immobile Entity. For the mobile entity, we have motion handler and motion behavior class. Lights and robots have their own handler for dealing their movement. All the arena entity event is pass to arena and then pass to each arena entity. Light can pass through every non-light entities. All entities can pass through the food source. Therefore, we do not handle the collision between light and robot, food and entity. If an obstacle collides with something, it will reverse in an arc for a fixed amount of time in an attempt to avoid the object. 


- **graphics_arena_viewer**: The GraphicArenaViewer class initiate the arena which works as the interface of the robot world and the user, receiving user input. In the meantime, it reads the get the states of entities through arena class and draws the entities in the GUI window. The graphics environment consists primarily of a single window with robots, obstacles, and foods. All objects (except for the wall) in the environment will be drawn as circles. Inside the circle, the name of objects are shown.The sensors of robots are visible on the circle of the robot and each two sensors on the robot will move with the robot. 

- **robot**: The robot class represents a robot within the arena. Robots are composed of a motion handler, amotion behavior, touch sensor, light sensor, and food sensor. These classes interact to maintain the pose (position and heading) of the robot. At each time step, we update and check the status(hungry, really hungry, starve) of the robot in order to determine which type of the stimuli it is sensing and use the wheel velocities to calculate the next pose of the robot. The behavior calculates the new pose based on wheel velocities. The touch sensor is activated when the robot collides with an object. The heading is modified after a collision to move the robot away from the other object. The handler manages the pose and update the velocity by the sensor reading and the pattern of the robot. The light sensor and the food sensor are on the same place of the robot. They are used to get the readings and tell the motion handler how to update the velocity. 
- **sensor**: This class handle both the light and food sensors. The sensor has two main functions, update the position of themselves and calculate the reading. The sensor gets the position and radius of the stimuli from notification and get the position of the robot by calling the update in the robot class. The reading then will be got by the robot in order to determine its motion. An additional function of food sensor is that the sensor class would check if a robot consumes food by the distance and set the attribute ```food_consumption```.


### data structure
- **In arena:**
    - ```robot_``` is a vector of robot pointer.
    - ```entities_``` is vector of Arena entities.
    - ```mobile_entities_``` is a subset of the entities.

    If a robot is added in arena, a robot pointer will be pushed back in ```robot_```, ```entities_```, ```mobile_entities_```.

    ```ResetConfig()```can clear the ```robot_``` and ```entities_``` list, thus making all three vectors empty.

- **In food:**

    - ```sensors_``` is a vector of registered sensors on the robots in arena. 
    
    It can be expanded by ```RegisterSensor```.

- **In light:**

    - ```sensors_``` is a vector of registered sensors on the robots in arena. 
    
    It can be expanded by ```RegisterSensor```.

### design pattern
- **Observer pattern**

     In this iteration, I take all stimuli (light and food) as subjects, and all sensors as observers. Each robot will have both light and food sensors at the same place in addition to touch sensors from iteration 1. When simulation starts, these sensors will register as observers in Arena for their respective stimuli. We have 10 robots, 4 foods and 4 lights, thus, 10 light sensors will register as a sensors’ list in each four light and 10 food sensors will register as a sensors’ list in each four foods. 

    When stimuli update its position, it would notify each sensors of the new position to update the readings. Each of the sensors accumulates the reading that is calculated by the position of the stimuli it is observing. The lights will change position with each time step, so the light sensors will be notified each timestep. Although the food is immobile stimuli, food sensor reading still need to be calculated each timestep because the sensor position changes. It is also convenient for future enhancement.

    
- **Strategy pattern**

    Strategy pattern is utilized to implement how arena entities handle their motion. We have light, robot, which is mobile entity and base, which is immobile. All of the entities have to be able to reset, update each timestep and get their names. These are the behaviors that stays the same. The other behaviors like handle collision, get starve will change from entity to entity.

    We use arena mobile entity and arena immobile entity as an interface rather than implementation directly in light and robot. To create a specific implementation of an entity, we will extend the Arena Entity class and the Arena Immobile or Mobile Entity class, and in this way have access to the is_mobile, get_touch_sensor functions. This successfully separates the different behavior of arena entities. The diagram below gives an overhead view of how we implement the strategy pattern.

### how to contribute

If there is any issue, you can email me or submit an issue labelled bug on github. You may also add new stimuli in the simulation or add other features. See design documents for more details.   

# User Guide
### how to configure
GUI controls for configuring:
- the number of robots.
    
    A slider for specifying the number of robots in a simulation. The range is 0 to 10. The default value is 10. 
- the number lights.
    
    A slider for specifying the number of robots in a simulation. The range is 0 to 10. The default value is 4. 
- the ratio of robots that fear to those that explore with respect to lights

    A slider to specify the ratio of fear to exploratory robots with respect to lights. When the slider is in the middle, it should be an even split (e.g. 50% are fearful and 50% are exploratory). It should be possible to specify all robots as one or the other (e.g. when the slider is set to 0 or to 100%). The default value is 50%.
    
- the sensitivity/range of the light sensor

   A slider to specify the sensitivity of the light sensor on robots. The result of this slider value is used to manipulate the equation used to calculate the sensor reading. It modify the base value 1.08. The range is 0.5 to 2.5. The larger is the value, the more sensitive is the light sensor.
    
- the inclusion/exclusion of food in the simulation

    A bottun that can turn Food on or off. When food is selected ("no food" shown on the buttun), The arena will add food according to the value on the food number slider in the arena. When no food is selected, there is no food in the simulation, the robot will never be hungry and only sense light source.
    
- the number of food stimuli 

    A slider for specifying the number of food in a simulation. The range is 0 to 10. The default value is 5. When no food is selected, the input of this slider will be ignored.

### how to operate the simulator

1. Double click the excutable arenaviewer in iteration3/build/bin. Alternatively, type into the command line ```./arenaviewer``` in the working directory, then the application would get running.
2. The simulator is initialized by the default value (5 fear robots, 5 explore robots, 4 lights, 5 food). Press the play button and the simulation will start.
3. If you want to change the configuration, you should use GUI elements to configure the simulation when game is paused. Controls include the number of robots, number of lights, the ratio of fearful to exploratory robots, and the inclusion of food. 
4. Press the new game button, and you will see the entities of the number you sepecified are added into arena.
5. Press start button, and new simulation will start.
6. Press pause button whenever you want to pause the simulation.
7. If you want to change the configuration, go back to 3.


