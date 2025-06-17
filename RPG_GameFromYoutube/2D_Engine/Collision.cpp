#include "Collision.hpp"
#include "ECS/ColliderComponent.hpp"

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {
	
	bool result = rectA.x + rectA.w >= rectB.x
		&& rectB.x + rectB.w >= rectA.x
		&& rectA.y + rectA.h >= rectB.y
		&& rectB.y + rectB.h >= rectA.y;

	return result;

}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB) {
	bool result = AABB(colA.collider, colB.collider);
	if(result)
		std::cout << colA.tag << " hit: " << colB.tag << std::endl;

	return result;
}