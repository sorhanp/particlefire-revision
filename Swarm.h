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

 //This is the class definition file the of Swarm-class.

//Header guards for SWARM_H_
#ifndef SWARM_H_
#define SWARM_H_

//Include local headers
#include "screen.h"
#include "particle.h"

//Create a namespace for this the use of this class
namespace particlefire {

	//Create a class Swarm inside namespace ParticleFire. This class devires from Screen-class.
	class Swarm : public Screen {

		//Private data members of a Swarm-class:
	private:
		Particle *m_particles;
		int m_lastTime;
		static int nparticles_;
		static double red_speed_;
		static double green_speed_;
		static double blue_speed_;

		//Public data members of a Swarm-class:
	public:

		//Constructors and destructor of Swarm-class
	public:
		Swarm();
		virtual ~Swarm();

		//Private data methods of a Swarm-class:
	private:
		bool ReadSettings();//Method for getting settings from a file

		//Public data methods of a Swarm-class:
	public:
		void Update(int elapsed);//Method for updating particles
		const Particle *const GetParticles() { return m_particles; };//Method for returning the pointer m_pParticles
		void SetParticleColorValue(int elapsed);//Method for setting particle's color value
	};
}/* end of namespace ParticleFire */

#endif /* SWARM_H_ */