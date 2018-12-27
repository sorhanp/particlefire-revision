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

 //This is the class implementation file of the Swarm-class.

//Include local headers
#include "Swarm.h"

//Create a namespace for this the use of this class
namespace particlefire {

	//Setting default values to static data members. These are used if config-file is missing or has wrong inputs.
	int Swarm::nparticles_ = 5000;
	double Swarm::red_speed_ = 0.0009;
	double Swarm::green_speed_ = 0.00005;
	double Swarm::blue_speed_ = 0.00002;

	Swarm::Swarm() {
		//Constructor that creates array of Particle-objects and saves their location to pointer m_pParticles.
		ReadSettings();
		m_particles = new Particle[nparticles_];

		//Initialize variable to zero
		m_lastTime = 0;
	}

	Swarm::~Swarm() {
		//Destructor that deallocates array of particles where m_pParticles is pointing.
		delete[] m_particles;
	}

	//Method for getting settings from a file
	bool Swarm::ReadSettings() {
		//Access the file "settings.cfg" and store it's position to variable file
		std::ifstream file("settings.cfg");
		//Variable where to save each line of the file
		std::string line;

		//Variables for storing the values from file
		int nparticles(0);
		double red_speed(0.0);
		double green_speed(0.0);
		double blue_speed(0.0);

		//Loop that goes throught the file line by line
		while (std::getline(file, line)) {
			std::istringstream sin(line.substr(line.find("=") + 1));

			//If any of the following text snippets are found from the file these if-else statements are true and values are saved to variables
			if (line.find("#") != -1) {
				//do nothing, since lines starting with #-character are ignored
			}
			else if (line.find("NPARTICLES") != -1) {
				sin >> nparticles;
			}
			else if (line.find("redSpeed") != -1) {
				sin >> red_speed;
			}
			else if (line.find("greenSpeed") != -1) {
				sin >> green_speed;
			}
			else if (line.find("blueSpeed") != -1) {
				sin >> blue_speed;
			}
		}

		//Check that the number of particles from the file are greater than zero
		if (nparticles > 0) {
			//Save values to data members
			nparticles_ = nparticles;
			red_speed_ = red_speed;
			green_speed_ = green_speed;
			blue_speed_ = blue_speed;
			//Close the file "settings.cfg"
			file.close();
		}
		//If values are negative or zero file is closed and function returns false.
		else {
			//Close the file "settings.cfg"
			file.close();
			return false;
		}

		return true;
	}

	//Method for updating particles
	void Swarm::Update(int elapsed) {

		//Calculate the the value between last time and elapsed time
		//This is used to make particles move constantly on every setting
		int interval = elapsed - m_lastTime;

		//Run update method for each Particle object.
		for (int i = 0; i < particlefire::Swarm::nparticles_; i++) {
			m_particles[i].UpdatePosition(interval);
		}

		//Store the elapsed time to variabe so that next run it can be calculated again with correct values.
		m_lastTime = elapsed;
	}

	//Method for setting particle's color value
	void Swarm::SetParticleColorValue(int elapsed)
	{

		//These three variables are used to store value from algorithm that vary the number between 0 - 255 where 0 is complete black and 255 is complete white.
		//Their value changes during programs run depending on the setting from the each _speed_-variable.
		Uint8 red(((1 + sin(elapsed * red_speed_)) * 128));
		Uint8 green(((1 + sin(elapsed * green_speed_)) * 128));
		Uint8 blue(((1 + sin(elapsed * blue_speed_)) * 128));

		//Loop that goes through every particle on the screen and sends the values to SetPixel-function so that they can be drawn on the screen
		for (int i = 0; i < nparticles_; i++) {

			//Store particles position to variables x and y in pixel format
			int x((m_particles[i].GetXpos() + 1) * particlefire::Screen::screen_width_ / 2);
			int y(m_particles[i].GetYpos() * particlefire::Screen::screen_width_ / 2 + particlefire::Screen::screen_height_ / 2);

			//Call SetPixel on each loop on each particle
			particlefire::Screen::SetPixel(x, y, red, green, blue);
		}
	}

}/* end of namespace ParticleFire */