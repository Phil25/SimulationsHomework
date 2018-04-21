# Simulations Homework

Homework assignments for the simulations subject at PJWSTK (PSM)

### Sine calculator
#### 09.03.18

* Calculates sine function using Taylor Series.
* Includes optimizations:
	* calculate power of the next iteraton using the previous one,
	* calculate factorial of the next iteration using the previous one and
	* limit the radian argument to range to `[0, PI/2]`, adjust the result appropriately.
* User specifies:
	* whether their input is given in radians or degrees,
	* the argument to calculate,
	* the precision to calculate with (number of iterations).

### Incline Roll
#### 01.04.18

* Simulates a ball or a cylinder rolling down on an inclined plane.
	* Includes simulating the movement as well as rotation.
	* Provides graphs representing acceleration and rotation.
	* No collisions are implemented, inclined plane is drawn for reference only.
* Uses OpenGL and OpenGL Utility Toolkit for graphical representation.
* **References & Links**:
	* [Integration Basics](https://gafferongames.com/post/integration_basics/) by Glenn Fiedler

### Sun Orbit
#### 08.04.18

* Simulates body movements in zero-g with possibility to:
	* add arbitrary many bodies, defining mass, position and starting velocty of each,
	* scale the simulation for representation of real world values,
	* set the speed of the simulation,
	* use keys to dynamically spawn new bodies,
	* toggle drawing of trajectories and velocity vectors,
	* fix first body's position (usually sun) in one place,
	* confining all bodies within the simulation window (bounce off walls) (not implemented with scaling!=1).
* No collisions are implemented.
* **NOTE**: Scaling and/or speed adjustments may be done improperly. Therefor the simulation can be wrong if both are other than 1.
* Uses OpenGL and OpenGL Utility Toolkit for graphical representation.
* **References & Links**:
	* [Integration Basics](https://gafferongames.com/post/integration_basics/) by Glenn Fiedler
	* [Solar system simulation in MATLAB](http://personalpages.manchester.ac.uk/staff/paul.connolly/teaching/practicals/solar_system.html) by Paul Connolly at Manchester University

### Game of Life
#### 20.04.18

* Implementation of Conway's Game of Life with possibility to:
	* pause/resume the simulation at any time,
	* manually toggle cells at any point in the simulation using a brush,
	* set the iteration speed,
	* enter draw mode, which automatically enables cells under the brush,
	* spawn a glider.
* Includes wrap-around grid.
* Controls:
	* Q - quit application
	* Space - pause/resume
	* W/K - move up
	* S/J - move down
	* D/L - move right
	* A/H - move left
	* E - toggle cell under the brush
	* R - toggle draw mode
	* G - spawn glider
* Uses OpenGL and OpenGL Utility Toolkit for graphical representation.
