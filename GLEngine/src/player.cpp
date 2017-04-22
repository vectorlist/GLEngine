#include "player.h"
#include <Application.h>
#include <shader.h>
#include <vml.h>
#include <renderer.h>
#include <shadertool.h>
#include <texture.h>

	/*-------------------- player --------------------*/

void Player::inputStateEvent()
{
	auto state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_W]) {
		currentRunSpeed = PLAYER_RUN_SPEED;
	}
	else if (state[SDL_SCANCODE_S]) {
		currentRunSpeed = -PLAYER_RUN_SPEED;
	}
	else {
		//nothing
	}
	if (state[SDL_SCANCODE_D]) {
		curruntTurnSpeed = -PLAYER_TURN_SPEED;
	}
	else if (state[SDL_SCANCODE_A]) {
		curruntTurnSpeed = PLAYER_TURN_SPEED;
	}
	else {
		//nothing
	}
	if (state[SDL_SCANCODE_SPACE]) {
		if(!on_air)
			jump();
	}
}

uint32_t Player::current_terrain_id(const std::vector<terrain_ptr> &terrains)
{
	if (position().x < 0.f && position().z > 0)  return 0;
	else if (position().x >= 0.f && position().z >= 0) return 1;  //x 0-800 z 0-800
	else if (position().x >= 0.0f && position().z < 0) return 2;  //0 -- 800 0 --- -800
	else if (position().x < 0.0f && position().z < 0) return 3;  //0 -- -800 0 --- -800
	//LOG_ERROR("failed to get terrain id");
	//return 0;
	
}

void Player::moveProcess(std::vector<terrain_ptr> &terrains)
{
	//set terrain ID
	debug_terrain_id = current_terrain_id(terrains);
	Terrain *terrain = terrains[debug_terrain_id].get();

	inputStateEvent();
	rotation(0, curruntTurnSpeed * APP_CURRENT_TIME, 0);
	const auto distance = (currentRunSpeed * APP_CURRENT_TIME);
	const auto dx = distance * sin(radians(ry()));
	const auto dz = distance * cos(radians(ry()));
	//moving by rotation axis
	translate(dx, 0, dz);

	currentUpwardSpeed += PLAYER_GRAVITY * APP_CURRENT_TIME;
	translate(0, currentUpwardSpeed * APP_CURRENT_TIME, 0);

	//test for terrain collision
	// --- 0(800) --- 1(-800) ---- 2(800) -------3(-800) terrain
	//vector<Terrain> swtich to by id
	//realworld position
	
	//not camera position 
	debug_height = terrain->getHeightOfTerrain(position().x, position().z);
	//LOG << "collision height : " << collision_height<< ENDL;
	//check player pos.y and collision height
	if (position().y < debug_height) {
		currentUpwardSpeed = 0;
		on_air = false;
		position().y = debug_height;
	}
	else if(position().y > debug_height){
		on_air = true;
	}

	currentRunSpeed = 0;
	curruntTurnSpeed = 0;

}

void Player::moving_forward()
{
	currentRunSpeed = PLAYER_RUN_SPEED;
}

void Player::moving_back()
{
	currentRunSpeed = -PLAYER_RUN_SPEED;
}

void Player::jump()
{
	currentUpwardSpeed += PLAYER_JUMP_INTENSITY;
}
