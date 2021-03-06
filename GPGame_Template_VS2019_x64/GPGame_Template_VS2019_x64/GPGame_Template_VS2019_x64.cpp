// Simplified Renderer application for GP course
// Features:
// Reduced OpenGL version from 4.5 to 3.3 to allow it to render in older laptops.
// Added Shapes library for rendering cubes, spheres and vectors.
// Added examples of matrix multiplication on Update.
// Added resize screen and keyboard callbacks.
// Added FPS camera functionality
// Update 2019/01 updated libraries and created project for VS2017 including directory dependant links to libraries.
// Update 2020/01 updated libraries for x64 and for VS2020, also adding MAC compiled Libraries.

// Suggestions or extra help please do email me at S.Padilla@hw.ac.uk

// Standard C++ libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
using namespace std;

// Helper graphic libraries
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "graphics.h"
#include "shapes.h"
#include "particle.h"
#include "emitter.h"
#include "Game.h"
#include "GameObject.h"
#include "TestCube.h"
using namespace std::this_thread;

// MAIN FUNCTIONS
void startup(Game* game);
void updateCamera(Game game);
void updateSceneElements(Game* game);
void renderScene(Game* game);

// CALLBACK FUNCTIONS
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void onMouseMoveCallback(GLFWwindow* window, double x, double y);
void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);

// VARIABLES    // Keep track of time per frame.
// variable to keep overall time.
Game	game;

// MAIN GRAPHICS OBJECT
Graphics    myGraphics;        // Runing all the graphics in this object

// Some global variable to do the animation.
float t = 0.001f;            // Global variable for animation
int loop = 0;

void startup(Game *game) {
	// Keep track of the running time
	GLfloat currentTime = (GLfloat)glfwGetTime();    // retrieve timelapse
	game->deltaTime = currentTime;                        // start delta time
	game->lastTime = currentTime;                           // Save for next frame calculations.

	// Callback graphics and key update functions - declared in main to avoid scoping complexity.
	// More information here : https://www.glfw.org/docs/latest/input_guide.html
	glfwSetWindowSizeCallback(myGraphics.window, onResizeCallback);            // Set callback for resize
	glfwSetKeyCallback(myGraphics.window, onKeyCallback);                    // Set Callback for keys
	glfwSetMouseButtonCallback(myGraphics.window, onMouseButtonCallback);    // Set callback for mouse click
	glfwSetCursorPosCallback(myGraphics.window, onMouseMoveCallback);        // Set callback for mouse move
	glfwSetScrollCallback(myGraphics.window, onMouseWheelCallback);            // Set callback for mouse wheel.

	// Calculate proj_matrix for the first time.
	myGraphics.aspect = (float)myGraphics.windowWidth / (float)myGraphics.windowHeight;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);

	Shapes figure;

//Setting up colors - This part might be quite unecessary while this can be done int the subclasses of GameObject class. Feel free to set up the colors directly in theses classes.
	for (int i=0 ; i < game->game_element.size(); i++)
	{
		switch (game->game_element[i].type)
		{
			case 1: // 1 for wall, 2 for ground, else is a default cube;
					if (game->game_element[i].subtype == 1)
						{
							figure = game->game_element[i].getShape();
							figure.fillColor = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);// You can change the shape fill colour, line colour or linewidth
							figure.lineColor = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
							game->game_element[i].setShape(figure);
						}
					else if (game->game_element[i].subtype == 2)
						{
						figure = game->game_element[i].getShape();
						figure.fillColor = glm::vec4(130.0f / 255.0f, 96.0f / 255.0f, 61.0f / 255.0f, 1.0f);// You can change the shape fill colour, line colour or linewidth
						figure.lineColor = glm::vec4(130.0f / 255.0f, 96.0f / 255.0f, 61.0f / 255.0f, 1.0f);
						game->game_element[i].setShape(figure);// Sand again
						}
					break;
			case 2: //For any spheres
					figure = game->game_element[i].getShape();
					figure.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); // You can change the shape fill colour, line colour or linewidth
					game->game_element[i].setShape(figure); 
					break;
			case 3: //For any Cylinders
					
					figure = game->game_element[i].getShape();
					figure.fillColor = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);// You can change the shape fill colour, line colour or linewidth
					figure.lineColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
					game->game_element[i].setShape(figure);

					break;
			case 4: //For arrows, whih include the axis ones
					if (game->game_element[i].subtype == 1)
					{

						figure = game->game_element[i].getShape();
						figure.fillColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); // You can change the shape fill colour, line colour or linewidth
						figure.lineColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
						game->game_element[i].setShape(figure);
					}
					else if (game->game_element[i].subtype == 2)
					{
						figure = game->game_element[i].getShape();
						figure.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); // You can change the shape fill colour, line colour or linewidth
						figure.lineColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
						game->game_element[i].setShape(figure);
					}
					else if (game->game_element[i].subtype == 3)
					{
						figure = game->game_element[i].getShape();
						figure.fillColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); // You can change the shape fill colour, line colour or linewidth
						figure.lineColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
					}
					break;
			case 6: // for particule explosion
				for (int j=0; j < game->game_element[i].nbPcl; j++) {
					game->game_element[i].particles[j]->setColor();
					game->game_element[i].particles[j]->shapePcl.Load();
				}
		}

	}
		// Optimised Graphics
		myGraphics.SetOptimisations();        // Cull and depth testing
}


bool		check_if_collision(GameObject first, GameObject second)
{

	return (first.min_figure_values.x < second.max_figure_values.x && first.max_figure_values.x > second.min_figure_values.x)
		&& (first.min_figure_values.y < second.max_figure_values.y && first.max_figure_values.y > second.min_figure_values.y)
		&& (first.min_figure_values.z < second.max_figure_values.z && first.max_figure_values.z > second.min_figure_values.z);
}


void updateCamera(Game* game) { // And by the way, A Move function

	// calculate movement for FPS camera
	GLfloat xoffset = myGraphics.mouseX - myGraphics.cameraLastX;
	GLfloat yoffset = myGraphics.cameraLastY - myGraphics.mouseY;    // Reversed mouse movement
	myGraphics.cameraLastX = (GLfloat)myGraphics.mouseX;
	myGraphics.cameraLastY = (GLfloat)myGraphics.mouseY;

	GLfloat sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	myGraphics.cameraYaw += xoffset;
	myGraphics.cameraPitch += yoffset;

	// check for pitch out of bounds otherwise screen gets flipped
	if (myGraphics.cameraPitch > 89.0f) myGraphics.cameraPitch = 89.0f;
	if (myGraphics.cameraPitch < -89.0f) myGraphics.cameraPitch = -89.0f;

	// Calculating FPS camera movement (See 'Additional Reading: Yaw and Pitch to Vector Calculations' in VISION)
	glm::vec3 front;
	front.x = cos(glm::radians(myGraphics.cameraYaw)) * cos(glm::radians(myGraphics.cameraPitch));
	front.y = sin(glm::radians(myGraphics.cameraPitch));
	front.z = sin(glm::radians(myGraphics.cameraYaw)) * cos(glm::radians(myGraphics.cameraPitch));

	myGraphics.cameraFront = glm::normalize(front);

	// Update movement using the keys
	GLfloat cameraSpeed = 3.0f * game->deltaTime;
	if (game->keyStatus[GLFW_KEY_W]) myGraphics.cameraPosition += cameraSpeed * myGraphics.cameraFront;
	if (game->keyStatus[GLFW_KEY_S]) myGraphics.cameraPosition -= cameraSpeed * myGraphics.cameraFront;
	if (game->keyStatus[GLFW_KEY_A]) myGraphics.cameraPosition -= glm::normalize(glm::cross(myGraphics.cameraFront, myGraphics.cameraUp)) * cameraSpeed;
	if (game->keyStatus[GLFW_KEY_D]) myGraphics.cameraPosition += glm::normalize(glm::cross(myGraphics.cameraFront, myGraphics.cameraUp)) * cameraSpeed;

	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;

	//Update Player position using the keys // We chose an id of 89 for his object

	//Here, before updating the camera, we implement the player's movement. We calculate eachtime he might collide
	//with his surroundings. We decided to let the walls of the map merge beteween themselves while moved to keep it playful instead of being realistic
	if (game->keyStatus[GLFW_KEY_LEFT])
		for (int i = 0; i < game->game_element.size(); i++)
			if (game->game_element[i].getId() == 89)
			{
				game->game_element[i].update_possible_transformation(glm::vec3(game->game_element[i].getTranslation().x, game->game_element[i].getTranslation().y, game->game_element[i].getTranslation().z+0.1f), game->game_element[i].getRotation(), game->game_element[i].getScale(), game->game_element[i].angle);
				game->game_element[i].figure_center(1);
				for (int a = 0; a < game->game_element.size(); a++)
				{
					if (game->game_element[a].type != 6 && game->game_element[a].getId() != 7 && game->game_element[a].getId() != 89)
						if (check_if_collision(game->game_element[i], game->game_element[a]) == true)
						{
							game->game_element[i].touched = true;
							translation = game->game_element[a].getTranslation();
							translation.z = translation.z + 0.1f;
							game->game_element[a].setTranslation(translation);
						}
				}
				if (game->game_element[i].touched == false)
				{
					game->game_element[i].touched = true;
					translation = game->game_element[i].getTranslation();
					translation.z = translation.z + 0.1f;
					game->game_element[i].setTranslation(translation);
				}
				game->game_element[i].touched = false;
				break;
			}
	if (game->keyStatus[GLFW_KEY_RIGHT])
		for (int i = 0; i < game->game_element.size(); i++)
			if (game->game_element[i].getId() == 89)
			{
				game->game_element[i].update_possible_transformation(glm::vec3(game->game_element[i].getTranslation().x, game->game_element[i].getTranslation().y, game->game_element[i].getTranslation().z - 0.1), game->game_element[i].getRotation(), game->game_element[i].getScale(), game->game_element[i].angle);
				game->game_element[i].figure_center(1);
				for (int a = 0; a < game->game_element.size(); a++)
				{
					if (game->game_element[a].type != 6 && game->game_element[a].getId() != 7 && game->game_element[a].getId() != 89)
						if (check_if_collision(game->game_element[i], game->game_element[a]) == true)
						{
							game->game_element[i].touched = true;
							translation = game->game_element[a].getTranslation();
							translation.z = translation.z - 0.1f;
							game->game_element[a].setTranslation(translation);
						}
				}
				if (game->game_element[i].touched == false)
				{
					game->game_element[i].touched = true;
					translation = game->game_element[i].getTranslation();
					translation.z = translation.z - 0.1f;
					game->game_element[i].setTranslation(translation);
				}
				game->game_element[i].touched = false;
			}

	if (game->keyStatus[GLFW_KEY_DOWN])
		for (int i = 0; i < game->game_element.size(); i++)
			if (game->game_element[i].getId() == 89)
			{
				game->game_element[i].update_possible_transformation(glm::vec3(game->game_element[i].getTranslation().x + 0.1f, game->game_element[i].getTranslation().y, game->game_element[i].getTranslation().z), game->game_element[i].getRotation(), game->game_element[i].getScale(), game->game_element[i].angle);
				game->game_element[i].figure_center(1);
				for (int a = 0; a < game->game_element.size(); a++)
				{
					if (game->game_element[a].type != 6 && game->game_element[a].getId() != 7 && game->game_element[a].getId() != 89)
						if (check_if_collision(game->game_element[i], game->game_element[a]) == true)
						{
							game->game_element[i].touched = true;
							translation = game->game_element[a].getTranslation();
							translation.x = translation.x + 0.1f;
							game->game_element[a].setTranslation(translation);
						}
					
				}
				if (game->game_element[i].touched == false)
				{
					game->game_element[i].touched = true;
					translation = game->game_element[i].getTranslation();
					translation.x = translation.x + 0.1f;
					game->game_element[i].setTranslation(translation);
				}
				game->game_element[i].touched = false;
				break;
			}

	if (game->keyStatus[GLFW_KEY_UP])
		for (int i = 0; i < game->game_element.size(); i++)
			if (game->game_element[i].getId() == 89)
			{
				game->game_element[i].update_possible_transformation(glm::vec3(game->game_element[i].getTranslation().x - 0.1f, game->game_element[i].getTranslation().y, game->game_element[i].getTranslation().z), game->game_element[i].getRotation(), game->game_element[i].getScale(), game->game_element[i].angle);
				game->game_element[i].figure_center(1);
				for (int a = 0; a < game->game_element.size(); a++)
				{
					if (game->game_element[a].type != 6 && game->game_element[a].getId() != 7 && game->game_element[a].getId() != 89)
					{
						if (check_if_collision(game->game_element[i], game->game_element[a]) == true)
						{
							game->game_element[i].touched = true;
							game->game_element[i].touched = true;
							translation = game->game_element[a].getTranslation();
							translation.x = translation.x - 0.1f;
							game->game_element[a].setTranslation(translation);

						}
					}
				}
				if (game->game_element[i].touched == false)
				{
					game->game_element[i].touched = true;
					translation = game->game_element[i].getTranslation();
					translation.x = translation.x - 0.1f;
					game->game_element[i].setTranslation(translation);
				}
				game->game_element[i].touched = false;
				break;
			}

	// IMPORTANT PART
	// Calculate my view matrix using the lookAt helper function
	if (game->mouseEnabled) {
		myGraphics.viewMatrix = glm::lookAt(myGraphics.cameraPosition,			// eye
			myGraphics.cameraPosition + myGraphics.cameraFront,					// centre
			myGraphics.cameraUp);												// up
	}
}



void updateSceneElements(Game* game) {

	glfwPollEvents();                                // poll callbacks

	// Calculate frame time/period -- used for all (physics, animation, logic, etc).
	GLfloat currentTime = (GLfloat)glfwGetTime();    // retrieve timelapse
	game->deltaTime = currentTime - game->lastTime;                // Calculate delta time
	game->lastTime = currentTime;                          // Save for next frame calculations.

	// Do not forget your ( T * R * S ) http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;

	Shapes collision;
	Shapes figure;

	// THIS FUNCTION UPDATES EVERY ELEMENTS MATRICES, BEFORE RENDERING THEM ON THE SCREEN
	for (int i = 0; i < game->game_element.size(); i++)
	{
		if (game->game_element[i].type != 6)
		{
			game->game_element[i].figure_center(0);

			figure = game->game_element[i].getShape();
			figure.proj_matrix = myGraphics.proj_matrix;
			figure.mv_matrix = myGraphics.viewMatrix *
				glm::translate(game->game_element[i].getTranslation()) *
				glm::rotate(glm::radians(game->game_element[i].angle), game->game_element[i].getRotation()) *
				glm::scale(game->game_element[i].getScale()) *
				glm::mat4(1.0f);
			game->game_element[i].setShape(figure);

			collision = game->game_element[i].getCollision();
			collision.mv_matrix = myGraphics.viewMatrix *
				glm::translate(glm::mat4(1), game->game_element[i].getTranslation()) *
				glm::scale(game->game_element[i].getCollisionScale()) *
				glm::mat4(1.0f);
			collision.proj_matrix = myGraphics.proj_matrix;
			game->game_element[i].setCollision(collision);
		}
		else {
			for (int j = 0; j < game->game_element[i].nbPcl; j++) {
				if (game->game_element[i].subtype == 1) // Fountain
				{
					game->game_element[i].particles[j]->updateFountain();
				}
				else if (game->game_element[i].subtype == 2) //Bouncing balls
				{
					game->game_element[i].particles[j]->updatePosPcl(80.0f, game->game_element[i].touched);

					translation = glm::vec3(game->game_element[i].particles[j]->position);
					game->game_element[i].setTranslation(translation);

					game->game_element[i].figure_center(0);

					//Check if there is a collision with others gameobjects elements, including particles
					for (int a = 0; a < game->game_element.size(); a++)
					{
						game->game_element[i].update_possible_transformation(game->game_element[i].getTranslation(), game->game_element[i].getRotation(), game->game_element[i].getScale(), game->game_element[i].angle);
						game->game_element[i].figure_center(1);
						for (int a = 0; a < game->game_element.size(); a++)
						{
							if (check_if_collision(game->game_element[i], game->game_element[a]) == true && a != i)
							{
								game->game_element[i].touched = true;
							}
						}
					}

					game->game_element[i].particles[j]->updatePosPcl(80.0f, game->game_element[i].touched);
				}

				glm::mat4 mv_matrix_sphere =
					glm::translate(glm::vec3(game->game_element[i].particles[j]->position)) *
					glm::scale(game->game_element[i].getScale()) *
					glm::mat4(1.0f);

				game->game_element[i].particles[j]->shapePcl.mv_matrix = myGraphics.viewMatrix * mv_matrix_sphere;
				game->game_element[i].particles[j]->shapePcl.proj_matrix = myGraphics.proj_matrix;

				game->game_element[i].touched = false;
			}
		}
		
	}

	t += 0.001f; // increment movement variable

	if (glfwWindowShouldClose(myGraphics.window) == GL_TRUE) game->quit = true; // If quit by pressing x on window.

}

void renderScene(Game* game) { //Rendering the scene
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();

	// Draw objects in screen

	for (int i = 0; i < game->game_element.size(); i++) {
		if (game->game_element[i].type != 6)
		{
			game->game_element[i].getShape().Draw();
		}
		else {
			for (int j = 0; j < game->game_element[i].nbPcl; j++) {
				if (game->game_element[i].particles[j]->dead == false)
				game->game_element[i].particles[j]->shapePcl.Draw();
			}
		}	// I don't draw the collision box, they just need to be calculated though.
	}
}


// CallBack functions low level functionality.
void onResizeCallback(GLFWwindow* window, int w, int h) {    // call everytime the window is resized
	//myGraphics.windowWidth = w;
	//myGraphics.windowHeight = h;

	glfwGetFramebufferSize(window, &myGraphics.windowWidth, &myGraphics.windowHeight);

	myGraphics.aspect = (float)w / (float)h;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { // Called everytime a key is pressed
	if (action == GLFW_PRESS) game.keyStatus[key] = true;
	else if (action == GLFW_RELEASE) game.keyStatus[key] = false;

	// toggle showing mouse.
	if (game.keyStatus[GLFW_KEY_M]) {
		game.mouseEnabled = !game.mouseEnabled;
		myGraphics.ToggleMouse();
	}
	// If exit key pressed.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

}

void onMouseMoveCallback(GLFWwindow* window, double x, double y) { //Mouse Move Callback
	int mouseX = static_cast<int>(x);
	int mouseY = static_cast<int>(y);

	myGraphics.mouseX = mouseX;
	myGraphics.mouseY = mouseY;

	// helper variables for FPS camera
	if (myGraphics.cameraFirstMouse) {
		myGraphics.cameraLastX = (GLfloat)myGraphics.mouseX; myGraphics.cameraLastY = (GLfloat)myGraphics.mouseY; myGraphics.cameraFirstMouse = false;
	}
}

void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
	int yoffsetInt = static_cast<int>(yoffset);
}


void		Load_Map(string filename, Game *game) // This function allows loading a map, this one contains alphanumeric characters that are translated into objects.
{
	ifstream file(filename);
	string	 line("");
	glm::vec3	map_coordinates;
	int		 index = 0;

	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;
	

	map_coordinates.y = 2.0;
	map_coordinates.z = 2.0;
	if (file)
		while (getline(file, line))
		{
			map_coordinates.x = 0;
			for (int i = 0; i < line.size(); i++)
			{
				switch (line[i])
				{
				case '0':
					map_coordinates.x -= 1;
					break;
				case '1':
				{
					NewCube Cube("Wall", rand());
					game->game_element.push_back(Cube);
				}
					if (game->game_element.size() == 0)
						index = 0;
					else
						index = game->game_element.size() - 1;
					translation = glm::vec3(map_coordinates.x - 0.01 - 0.5, map_coordinates.y - 1, map_coordinates.z - 0.2);
					game->game_element[index].setTranslation(translation);
					map_coordinates.x -= 1;
					break;
				case '2':
				{
					NewCube Cube("Wall", rand());
					game->game_element.push_back(Cube);
				}
					if (game->game_element.size() == 0)
						index = 0;
					else
						index = game->game_element.size() - 1;

					//The calculations here only depends on our mentally predefined walls dimensions and the map information.
					translation = (glm::vec3(map_coordinates.x - 0.01 - 0.2, map_coordinates.y - 1, map_coordinates.z - 1));
					game->game_element[index].setTranslation(translation);
					scale = glm::vec3(2.0f, 2.0f, 0.4f);
					game->game_element[index].setScale(scale);
					rotation = glm::vec3(0.0f, 1.0f, 0.0f);
					game->game_element[index].setRotation(rotation);
					game->game_element[index].angle = 90.0f;
					map_coordinates.x -= 0.4;
					break;
				}
			}
			map_coordinates.z -= 2;
		}
	else
		exit(0);
}


int main()
{
	int errorGraphics = myGraphics.Init();			// Launch window and graphics context
	if (errorGraphics) return 0;
	ifstream infile;								// In order to read the file containing the map data
	string		filename("map.txt");				// File of the Map

	NewCube Cube("Cube", 88);						//Regular Cube we're choosing to instanciate with an id, and add it to the game elements vector


	Load_Map(filename, &game);						// Load a map stored in a file

	game.game_element.push_back(GameObject(7, 1, 2));
	game.game_element.push_back(GameObject(89, 1, 0));	//2 Ways to add element, either precise the type o f element, as for the cube previously, either instanciate a GameObject with his type predefined in the GameObject.h
	game.game_element.push_back(Cube);	
	//game.game_element.push_back(GameObject(10, 6, 1)); //Activate The fountain
	//game.game_element.push_back(GameObject(10, 6, 2)); //Activate the bouncing balls
	
	
	startup(&game);										// Setup all necessary information for startup (aka. load texture, shaders, models, etc).

	// MAIN LOOP run until the window is closed
	while (!game.quit) {

		// Update the camera transform based on interactive inputs or by following a predifined path.
		updateCamera(&game);

		// Update position, orientations and any other relevant visual state of any dynamic elements in the scene.
		updateSceneElements(&game);

		// Render a still frame into an off-screen frame buffer known as the backbuffer.
		renderScene(&game);

		// Swap the back buffer with the front buffer, making the most recently rendered image visible on-screen.
		glfwSwapBuffers(myGraphics.window);        // swap buffers (avoid flickering and tearing)

		//while (1) {}
	}

	myGraphics.endProgram();            // Close and clean everything up...

   // cout << "\nPress any key to continue...\n";
   // cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}