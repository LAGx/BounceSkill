#pragma once
#include "Wall.h"

const ClassId Wall::gameClassId = 3;

Wall::Wall(const WallData& data)
	: collider(data.pointA, data.pointB)
	, drawableLine(data.pointA, data.pointB, 2, { 100, 200, 100, 255 }){
	collider.gameObject = this;
}

void Wall::render(sf::RenderWindow& window) const {
	drawableLine.render(window);
}

const ICollider* Wall::getCollider() const {
	return &collider; 
}

ClassId Wall::getClassId() const{
	return gameClassId;
}

void Wall::simulate(const TimeInfo&){
}
