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

 //This is the class definition file of the Screen-class.

//Header guards for SCREEN_H_
#ifndef SCREEN_H_
#define SCREEN_H

//Include C++ system libraries
#include <fstream>
#include <sstream>
#include <string>

//Include other libraries
#include <SDL.h>

//Create a namespace for this the use of this class
namespace particlefire {

	//Create a class Screen inside namespace ParticleFire.
	class Screen {

		//Private data members of a Screen-class:
	private:
		SDL_Window *m_window;
		SDL_Renderer *m_renderer;
		SDL_Texture *m_texture;
		Uint32 *m_buffer;

		//Protected data members of a Screen-class:
	protected:
		static int screen_width_;
		static int screen_height_;
		static unsigned int target_fps_;

		//Public data members of a Screen-class:
	public:

		//Constructors and destructor of a Screen-class:
	public:
		Screen();//Constructor for Screen-class
		~Screen();//Destructor is used to deallocate processes and variables stored in to heap

		//Private data methods of a Screen-class:
	private:
		bool ReadConfig();//Method for getting settings from a file

		//Public data methods of a Screen-class:
	public:
		bool Init();//Method for initializing SDL-library. Returns true(1) if init was successful, else false(0)
		void UpdateScreen();//Method for updating the window
		void SetPixel(int x, int y, Uint8 red, Uint8  green, Uint8 blue);//Method for setting pixel value on the screen
		void ApplyBoxBlur();//Method for blurring the particles
		bool ProcessEvents();//Method for event processing
		void LimitFPS(int elapsed);//Method for limiting frames per second(FPS)
	};

} /* end of namespace ParticleFire */


#endif /* SCREEN_H */