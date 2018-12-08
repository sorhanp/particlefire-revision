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

//This is the main-function of the program which includes the game loop and calls to the methods of classes.

//Include C++ system libraries
#include <ctime>

//Include local headers
#include "swarm.h"

int main(int argc, char *args[]) {

	//Provide seed to the rand-function later used in the particle class
	srand((unsigned int)time(NULL));

	//Create object from Swarm-class with default constructor
	particlefire::Swarm swarm;

	//Use the object to call the init from inherited Screen-class to initialize SDL-window. If it fails returns 1 from main function.
	if (swarm.Init() == false) {
		return 1;
	}

	//A boolean variable to test the game loop (while) below.
	bool quit = false;

	//"Game loop" for program so that the window stays open and called methods are executeduntil certain event,
	//in case this program is closed by user via either esc-key or closing of the window. 
	//Game loop runs as long as quit is false.
	while (!quit) {

		//This function is used to get the number of milliseconds since the SDL library initialization.
		Uint32 elapsed(SDL_GetTicks());

		//Set color values of the particles
		swarm.SetParticleColorValue(elapsed);

		//Update position of particles
		swarm.Update(elapsed);

		//Apply blur effect to particles
		swarm.ApplyBoxBlur();

		//Update the screen to show particles
		swarm.UpdateScreen();

		//Check for events if user wants to quit
		if (swarm.ProcessEvents() == false) {
			quit = true;
		}

		//Set limit for how many times in a second this "game loop" can execute
		swarm.LimitFPS(elapsed);
	}

	return 0;
}