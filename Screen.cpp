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

 You can contact me by email: Hannupekka dot(.) Sormunen at gmail dot(.) com or visit my GitHub at https://github.com/sorhanp
 */

 //This is the class implementation file of the Screen-class.

//Include local headers
#include "Screen.h"

//Create a namespace for this the use of this class
namespace particlefire {

	//Setting default values to static data members. They are used if config-file is missing or has wrong inputs.
	int Screen::screen_width_ = 800;
	int Screen::screen_height_ = 600;
	unsigned int Screen::target_fps_ = 60;

	//Constructor for Screen-class	
	Screen::Screen() :m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL) {
		//Constructor initializition list is used to set data members to NULL, otherwise SDL can't inform of failure or success when SDL instances are called.

		//Call ReadConfig data method to get settings from the config.cfg-file
		ReadConfig();

		//Allocate pixel buffer arrays in to heap-memory so that they can be accessed throught the program
		m_buffer = new Uint32[screen_width_*screen_height_];
	}

	//Destructor is used to deallocate processes and variables stored in to heap
	Screen::~Screen() {
		//Deallocate the memory of buffer, renderer, texture, window and SDL process itself
		delete[] m_buffer;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyTexture(m_texture);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	//Method for getting settings from a file
	bool Screen::ReadConfig() {
		//Access the file "config.cfg" and store it's position to variable file
		std::ifstream file("config.cfg");
		//Variable where to save each line of the file
		std::string line;
		//Variables for storing the values from file
		int screen_width(0);
		int screen_height(0);
		int target_fps(0);

		//Loop that goes throught the file line by line
		while (std::getline(file, line)) {
			std::istringstream sin(line.substr(line.find("=") + 1));

			//If any of the following text snippets are found from the file these if-else statements are true and values are saved to variables
			if (line.find("#") != -1) {
				//do nothing, since lines starting with #-character are ignored
			}
			else if (line.find("SCREEN_WIDTH") != -1) {
				sin >> screen_width;
			}
			else if (line.find("SCREEN_HEIGHT") != -1) {
				sin >> screen_height;
			}
			else if (line.find("TARGET_FPS") != -1) {
				sin >> target_fps;
			}

		}

		//Check that the values from the file are greater than zero
		if (screen_width > 0 && screen_height > 0 && target_fps > 0) {
			//Save values to data members
			screen_width_ = screen_width;
			screen_height_ = screen_height;
			target_fps_ = target_fps;
			//Close the file "config.cfg"
			file.close();
		}
		//If values are negative or zero file is closed and function returns false.
		else {
			//Close the file "config.cfg"
			file.close();
			return false;
		}

		return true;
	}

	//Method for initializing SDL-library. Returns true(1) if init was successful, else false(0)
	bool Screen::Init() {
		//Checks if SDL video initialization works, which returns value zero if everything is ok. Otherwise prints out error message from SDL_GetError() and returns false
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
			return false;
		}


		//This function is used to create a window with the specified position, dimensions, and flags. It is using predefined pointer m_window of Screen-class
		m_window = SDL_CreateWindow(
			"The Particle Fire Simulation", //Title of the window
			SDL_WINDOWPOS_CENTERED, //The position of the window on x-axis
			SDL_WINDOWPOS_CENTERED, //The position of the window on y-axis
			screen_width_, // the width of the window in pixels
			screen_height_, // the height of the window in pixels
			//Both height and width are defined in class as constant static data members
			SDL_WINDOW_SHOWN); //The final argument is for flags see SDL wiki for more info.

		//Checks if SDL window initialization works, which returns value NULL if there was an error and prints out error message from SDL_GetError(). Returns false before shutting down the SDL-process
		if (m_window == NULL) {
			SDL_Log("Unable to initialize SDL window: %s", SDL_GetError());
			SDL_Quit();
			return false;
		}


		//This function is used to create a 2D rendering context for a window
		m_renderer = SDL_CreateRenderer(
			m_window, //the window where rendering is displayed, in this case pointer called m_window.
			-1, //the index of the rendering driver to initialize, or -1 to initialize the first one supporting the requested flags
			SDL_RENDERER_ACCELERATED); //flags see SDL wiki for more info. Basically makes the program use hardware graphics rendering instead of software

		//Checks if SDL renderer initialization works, which returns value NULL if there was an error and  prints out error message from SDL_GetError(). Returns false before shutting down SDL-process.
		if (m_renderer == NULL) {
			SDL_Log("Unable to initialize SDL renderer: %s", SDL_GetError());
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}


		//This function is used to create a texture for a rendering context. 
		m_texture = SDL_CreateTexture(
			m_renderer,//renderer, The rendering context, where the texture is added on, meaning this case m_renderer-pointer, 
			SDL_PIXELFORMAT_RGB888,//format, one of the enumerated values in SDL_PixelFormatEnum; see Remarks for details. This uses one byte (255 in decimal) for each pixel
			SDL_TEXTUREACCESS_STREAMING,//access, one of the enumerated values in SDL_TextureAccess; see Remarks for details in the SDL wiki
			screen_width_,//the width of the texture in pixels
			screen_height_);//the height of the texture in pixels

		//Checks if SDL texture initialization works, which returns value NULL if there was an error and prints out error message from SDL_GetError(). 
		//Returns false after shutting down SDL-processes.
		if (m_texture == NULL) {
			SDL_Log("Unable to initialize SDL texture: %s", SDL_GetError());
			SDL_DestroyWindow(m_window);
			SDL_DestroyRenderer(m_renderer);
			SDL_Quit();
			return false;
		}


		//If everything was initialized correctly return 1
		return true;
	}

	//Screen updating method
	void Screen::UpdateScreen() {
		//This function is used to update the given texture rectangle with new pixel data. 
		SDL_UpdateTexture(
			m_texture, //texture, the texture to update, in this case pointer m_texture context
			NULL,//rect, an SDL_Rect structure representing the area to update, or NULL to update the entire texture.
			m_buffer,//pixels, the raw pixel data in the format of the texture, in this case it is value inside the memory location which is being pointed on by buffer.
			screen_width_ * sizeof(Uint32));//pitch, the number of bytes in a row of pixel data, including padding between lines. Row is screen width (800 as default) times sizeof(Uint32). 800 lines times each four layers (R)ed, (G)reen, (B)lue and (A)lpha).

		SDL_RenderClear(m_renderer); //Use this function to clear the current rendering target with the drawing color. () inside goes the the rendering context in this case pointer to renderer. This is used to initialize the renderer so that no garbage is being stored inside of it.

		//This function is used to copy a portion of the texture to the current rendering target. 
		SDL_RenderCopy(
			m_renderer,//renderer, the rendering context which is m_renderer pointer
			m_texture,//texture, the source texture; see Remarks for details in the wiki. This time pointer to m_texture context.
			NULL,//srcrect, the source SDL_Rect structure or NULL for the entire texture 
			NULL);//dstrect, the destination SDL_Rect structure or NULL for the entire rendering target; the texture will be stretched to fill the given rectangle

			//Use this function to update the screen with any rendering performed since the previous call. Renderer, the rendering context. In this case pointer to renderer.
		SDL_RenderPresent(m_renderer);
	}

	//Method for setting pixel value on the screen
	void Screen::SetPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
		//Check if pixels that is about the be set is out of range of resolution
		if (x < 1 || x >= screen_width_ - 1 || y < 1 || y >= screen_height_ - 1) {
			return;
		}

		//Initialize the 8 byte integer variable with zero value
		Uint32 color(0);

		//Setting up the red channel with value and shifting two bytes forward in variable to access different color
		color += red;
		color <<= 8;

		//Setting up the green channel with value and shifting two bytes forward in variable to access different color
		color += green;
		color <<= 8;

		//Setting up the blue channel with value, no need to shift bits anymore
		color += blue;

		//Setting value in the buffer, to get to right pixel y must be multiplied with SCREEN_WIDTH so that the y-axis moves down to correct row 
		//and then add x (column value) how far right we have to go from the left. 
		//With resolution 800x600 On the first run the value is 0 + 0 so the top leftmost pixel. After 800 runs value is 0 + 800 so the to rightmost pixel. 
		//Then the second row starts updating.
		m_buffer[(y * screen_width_) + x] = color;
	}

	//Method for blurring the particles
	void Screen::ApplyBoxBlur() {
		//Algorithm for applying boxblur. For more detailed explanation, please read the documentation
		for (int y = 1; y < screen_height_ - 1; y++) {
			for (int x = 1; x < screen_width_ - 1; x++) {
				Uint32 red_total(0);
				Uint32 green_total(0);
				Uint32 blue_total(0);

				for (int col = -1; col <= 1; col++) {
					for (int row = -1; row <= 1; row++) {
						int current_y(y + col);
						int current_x(x + row);
						
						Uint32 color(m_buffer[current_y * screen_width_ + current_x]);

						Uint8 blue(color);
						blue_total += blue;

						color >>=8;
						Uint8 green(color);
						green_total += green;

						color >>=8;
						red_total += color;

					}
				}


				Uint8 red(red_total / 9);
				Uint8 green(green_total / 9);
				Uint8 blue(blue_total / 9);

				SetPixel(x, y, red, green, blue);

			}
		}
	}

	//Method for event processing
	bool Screen::ProcessEvents() {
		//SDL_Event is a union that contains structures for the different event types.
		SDL_Event event;

		//SDL_PollEvent() removes the next event from the event queue. If there are no events on the queue it returns 0, otherwise it returns 1. While loop is used to process each event in turn
		while (SDL_PollEvent(&event)) {
			//Keydown event happens when esc-key is pressed. When that happens return false to main-program.
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
				return false;
			}
			//SDL_QUIT event happens when close-button is press on the window. When that happens return false to main-program.
			if (event.type == SDL_QUIT) {
				return false;
			}
		}

		return true;
	}

	//Method for limiting frames per second(FPS)
	void Screen::LimitFPS(int elapsed)
	{
		//This delays the program by the amount, which is stored into target_fps_-variable.
		//Better explanation how frame limiting works see documentation
		if ((1000 / target_fps_) > SDL_GetTicks() - elapsed) {
			SDL_Delay(1000 / target_fps_ - (SDL_GetTicks() - elapsed));
		}
	}

} /* end of namespace ParticleFire */