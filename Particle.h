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

 //This is the class definition file of the Particle-class.

//Header guards for PARTICLE_H_
#ifndef PARTICLE_H_
#define PARTICLE_H_

//Define guards for _USE_MATH_DEFINES, so that M_PI can be used.
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES

//Include C++ system libraries
#include <cmath>
#include <cstdlib>

//Create a namespace for this the use of this class
namespace particlefire {

	//Create a class Particle inside namespace ParticleFire.
	class Particle {

		//Private data members of a Particle-class:
	private:
		double m_speed;
		double m_direction;
		double m_xpos;
		double m_ypos;

		//Public data members of a Particle-class:
	public:

		//Constructors and destructor of a Particle-class:
	public:
		Particle();
		virtual ~Particle();

		//Private data methods of a Particle-class:
	private:
		void Init();//Method for initializing a single particle's position, traveling speed and direction

		//Public data methods of a Particle-class:
	public:
		void UpdatePosition(int interval);//Method for updating the particle position on the screen
		double GetXpos() { return m_xpos; };//Method for acquiring the position of a particle on a x-axis
		double GetYpos() { return m_ypos; };//Method for acquiring the position of a particle on a y-axis
	};

} /* end of namespace ParticleFire */

#endif /*_USE_MATH_DEFINES*/
#endif /* PARTICLE_H_ */