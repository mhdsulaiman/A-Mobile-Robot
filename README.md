# A-Mobile-Robot

<h3>Abstract:</h3>
<p>This project aims to design and build a self-driving robot capable to surpass obstacles that could hinder its way.
The robot has been tested using two ways, by a maze where we should determine the starting and ending points. Through using a specific search algorithm to find the shortest path, the robot can access to the final destination and bypass static obstacles without any human intervention; Or through the free motion that relies on using machine learning to make the robot avoiding the fixed or mobile obstacles.
This report presents the algorithms and tools that we used for building the robot. Moreover, it shows experiments that we have done to reach satisfactory results.</p>

<p>In this project, we designed the robot using 3D windows builder. You can find all the designs in the Project Designs Folder.</p>
<h3>A Simple Discerption for Robot’s work:</h3>
<p>First Practical procedure we did was moving the robot from point A to point B using Graphs to execute a programming map making the robot apply to surpass the obstacles that are already defended. Also, the obstacles that it may face during his movement to reach his final destination on this map.

The Second Practical Procedure, we made the robot apply to learn and study the environment surrounding him using Reinforcement Learning Algorithm called Q-learning.
We used Python as the main programing language for writing the Algorithms (Graphs – Q-learning). And, to control the movement of the robot like its brain.
For the hardware part, Arduino Mega has been used with 1 Bluetooth receiver shield (HC-05), 5 Distance Sensor Ultrasonic sensor (Hc-sr04), 1 motors controller shield(Module l298n H Bridge) and 2 Dc-motors.
The Arduino receive the data that he needs from python and he acts based on specific code wrote to control all the shield connected to it.</p>
<h3>References:</h3>
<ul>
  <li>1. https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-0001-introduction-to-computer-science-and-programming-in-python-fall-2016/</li>
  <li>2. https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-0002-introduction-to-computational-thinking-and-data-science-fall-2016/</li>
  <li>3. http://ai.berkeley.edu/course_schedule.html</li>
  <li>4. CJCH Watkins, P Dayan, “Q-learning” Machine learning Journal, Vol 8, p 279-292</li>
  <li>5. Sebastian Raschka & Vahid Mirjalili (2017) “python machine learning”, second edition, pp. 610-622</li>
</ul>
You can find the full Bachelor thesis:   
