# Replace Temp with Query or Chain

#### Changed files and methods:
<ul>
	<li><a href="#graphic">graphicsArenaViewer::DrawRobot</a>
    <li><a href="#motion">MotionHandlerRobot::UpdateVelocitybySensor</a>
    <li><a href="#sensor">Sensor::calculateReading</a>
</ul>


## <a name="graphic">graphic_arena_viewer.cc</a>
 - Temporary variable was defined in:
   ```cpp
   void GraphicsArenaViewer::DrawRobot(NVGcontext *stx, const Robot *const robt) 
   ```
    * line 140 ``` std::string robot_message_ = robot->get_name(); ```
   	* line 142 ```std::string robot_sensor_lf = "/";```
   	* line 146 ```std::string robot_sensor_rt = "\\";```
   
   I used ```robot->get_name()``` and the string '/', '\\' directly in ```nvgText()``` as a parameter, thus removing the need for these three temps.

## <a name="motion">motion_handler_robot.cc</a>

  - Temporary variable was defined in:
    ```cpp
    void MotionHandlerRobot::UpdateVelocitybySensor(Sensor* sensor)
    ```
    * line 62 ``` Pattern robotic_controls = sensor->get_pattern();```

    In line 66, I used ```!sensor->get_pattern().positive``` instead of ```!robotic_controls.positive``` to check the control pattern of the robot. Similarly, I don't need the temporary temp ```robotic_controls``` in line 70. Therefore. we can change the methods to support chaining and remove this temp.
#
   - Temporary variable was defined in:
     ```cpp
     void MotionHandlerRobot::UpdateVelocitybySensor(Sensor* sensor)
     ```
     * line 63 ``` double v_left = sensor->get_left_reading()/10.0;```
     * line 64 ```  double v_right = sensor->get_right_reading()/10.0;```

     I added new method ```void left_reading(Sensor* sensor)``` and ```void right_reading(Sensor* sensor)``` in ```MotionHandlerRobot``` to replace ```v_left``` and ```v_right```. 

     Since ```v_left``` and ```v_right``` are not final velocity of robot wheel, ```void left_reading(Sensor* sensor)```and ```void right_reading(Sensor* sensor)``` only returns the motified reading of the sensor. Besides, I checked four different connections other than the value of ```positive``` and ```direct```, so that I could set the velocity right  after checking the control connection, and the use of the temps can be avoided.
     
     ```cpp
     double left_reading(Sensor* sensor) {return sensor->get_left_reading()/10.0;}
     ```
     ```cpp
     double right_reading(Sensor* sensor) {return sensor->get_right_reading()/10.0;}
     ```
     ```cpp
      if (!sensor->get_pattern().positive && sensor->get_pattern().direct) {
        set_velocity(clamp_vel(get_max_speed() - left_reading(sensor)),
        clamp_vel(get_max_speed() - right_reading(sensor)));
      } else if (sensor->get_pattern().positive && sensor->get_pattern().direct) {
        set_velocity(clamp_vel(left_reading(sensor)),
        clamp_vel(right_reading(sensor)));
      } else if (sensor->get_pattern().positive && !sensor->get_pattern().direct){
        set_velocity(clamp_vel(right_reading(sensor)),
        clamp_vel(left_reading(sensor)));
      } else {
        set_velocity(clamp_vel(get_max_speed() - right_reading(sensor)),
        clamp_vel(get_max_speed() - left_reading(sensor)));
      }
      ```
     


## <a name="sensor">sensor.cc</a>
 
 - Temporary variable was defined in:
     ```cpp
	void Sensor::calculateReading(Pose p, double stimuliraius)
    ```
   	 * line 47, 48 ``` double dis = sqrt((p.x - robot_pose_.x) * (p.x - robot_pose_.x) +
     (p.y - robot_pose_.y)*(p.y - robot_pose_.y)) - stimuliraius;```
     * line 55 ```double delta_x_l = p.x - position_left_.x;```
     * line 56 ```double delta_y_l = p.y - position_left_.y;```
   	 * line 57 ```double dis_l = sqrt(delta_x_l * delta_x_l + delta_y_l*delta_y_l) - stimuliraius;```
   	 * line 60 ```double delta_x_r = p.x - position_right_.x;```
   	 * line 70 ```delta_y_r = p.y - position_right_.y;```
   	 * line 71```double dis_r = sqrt(delta_x_r * delta_x_r + delta_y_r*delta_y_r) - stimuliraius;```

	I created a genral method ```double distance(Pose p1, Pose p2, double r)``` in ```Sensor``` to calculate distance between two position. Therefore the temporary variables that previously used are not need any more. 
    
    ```dis``` which compute the distance between robot and stimuli can be relplaced as ```distance(p, robot_pose_, stimuliradius)```. Similary, ```dis_l``` which compute the distance between left sensor and stimuli can be relplaced as ```distance(p, position_left_, stimuliradius)```, and ```dis_r``` can be replaced as ```distance(p, position_right_, stimuliradius)```.
    ```cpp
    double distance(Pose p1, Pose p2, double r) {
     return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y)) - r;
   }
   ```
#
- Temporary variable was defined in:
	```cpp
	void Sensor::calculateReading(Pose p, double stimuliraius)
    ```
   	 * line 49 ``` bool food_consumption_temp = false;```

	I replaced this temp with neither query nor chain. I changed the logic of my code to avoid using this temp. I used ```food_consumption_ = food_consumption_ || food_consumption_temp``` to check if the robot consume any food, but I can simply set ```food_consumption_``` to be true once it consumes one food. 
#
- Temporary variable was defined in:
   ```cpp
   void Sensor::calculateReading(Pose p, double stimuliraius)
   ```
   	* line 54 ```double reading_temp_l;```
   	* line 68 ```double reading_temp_r;```
   	 
     I added a new method ```double  Sensor::calculateReadingbyDistance(double dis)``` in sensor.cc line 65-73. This new function is called when accumulating the reading in ```void Sensor::calculateReading(Pose p, double stimuliraius)```.
     ```calculateReadingbyDistance``` calculate the left and right reading for one stimuli here. This function basically calculates the reading accoring to the distance between the sensor and stimuli.
     ```cpp
     double  Sensor::calculateReadingbyDistance(double dis) {
        if (dis <= 0) {
          return MAX_READING_FOR_ONE;
        } else {
          return  coefficient_*1200 / dis < MAX_READING_FOR_ONE?
          coefficient_*1200 / dis: MAX_READING_FOR_ONE;
        }
      }
     ```
