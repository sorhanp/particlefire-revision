/* The Particle Fire Simulation revision using SDL-library, demonstrating color pixel access and box blur algorithm.
   This program is part of the https://courses.caveofprogramming.com/p/c-beginners course by John Purcell (https://github.com/caveofprogramming).
   This version is modified so that the program perform bit faster and the code itself is commented and stylized using
	https://google.github.io/styleguide/cppguide.htm style guide as much as possible to make the code bit more readable to users.
	 Copyright(C) 2018 Hannupekka Sormunen

 This program is free software : you can redistribute it and/or modify
	 it under the terms of the GNU General Public License as published by
	 the Free Software Foundation version 3 of the License.

	 This program is distributed in the hope that it will be useful,
	 but WITHOUT ANY WARRANTY; without even the implied warranty of
	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
	 GNU General Public License for more details.

	 You should have received a copy of the GNU General Public License
	 along with this program. If not, see[http://www.gnu.org/licenses/].

 You can contact me by email: hannupekka dot(.) sormunen at gmail dot(.) com or visit my GitHub at https://github.com/sorhanp
 */

 //This is the class implementation file of the Particle-class.

//Include local headers
#include "particle.h"

//Create a namespace for this the use of this class
namespace particlefire {

	//Constructor of Particle-class
	Particle::Particle() {
		//Upon default initilization of an object, private data method Init is called
		Init();
	}

	//Destructor of Particle-class
	Particle::~Particle() {

	}

	//Method for initializing a single particle's position, traveling speed and direction
	void Particle::Init() {
		//Set particle to start at the middle of the screen.
		m_xpos = 0;
		m_ypos = 0;

		//Set the direction and speed by random 
		m_direction = (2 * M_PI * rand()) / RAND_MAX;//Direction in radians where 2 * PI is 360 degrees
		m_speed = (0.0004 * rand()) / RAND_MAX;
		
		//Increase the speed of certain particles. So everytime result from rand-function is smaller than 32.767 (32767 / 1000) adding little more randomness to the pattern
		if (rand() < RAND_MAX / 1000) {
		m_speed *= m_speed / 0.75;
		}
	}

	//Method for updating the particle position on the screen
	void Particle::UpdatePosition(int interval) {

		//Modify direction of a particle to rotate to left using negative value or right using positive value on each UpdatePosition call
		m_direction += interval * -0.0001;

		//Calculate where particle will travel
		double xspeed = m_speed * cos(m_direction);
		double yspeed = m_speed * sin(m_direction);

		//Change the new position for the particle according the speed and direction calculated above
		m_xpos += xspeed * interval;
		m_ypos += yspeed * interval;

		//Check if particle is out of bounds and call Init to create a new one at the middle of the screen
		if (m_xpos < -1 || m_xpos > 1 || m_ypos < -1 || m_ypos > 1) {
			Init();
		}

		//Call Init()-method, thus creating a particle middle of the screen, everytime result from rand-function is smaller than 163 (32767 / 200) adding little more randomness to the pattern
		if (rand() < RAND_MAX / 200) {
			Init();
		}

	}

} /* end of namespace ParticleFire */