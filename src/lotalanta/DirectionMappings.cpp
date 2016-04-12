#include "../../include/lotalanta/DirectionMappings.h"

std::map<Direction, Direction> DirectionMappings::leftOf = DirectionMappings::createLeftOf();
std::map<Direction, Direction> DirectionMappings::rightOf = DirectionMappings::createRightOf();
std::map<Direction, Direction> DirectionMappings::oppositeOf = DirectionMappings::createOppositeOf();
std::map<Direction, int> DirectionMappings::polarityOf = DirectionMappings::createPolarityOf();
std::map<Direction, Axis> DirectionMappings::axisOf = DirectionMappings::createAxisOf();

Direction DirectionMappings::getLeftOf(Direction dir){
	return DirectionMappings::leftOf[dir];
}

Direction DirectionMappings::getRightOf(Direction dir){
	return DirectionMappings::rightOf[dir];
}

Direction DirectionMappings::getOppositeOf(Direction dir){
	return DirectionMappings::oppositeOf[dir];
}

int DirectionMappings::getPolarityOf(Direction dir){
	return DirectionMappings::polarityOf[dir];
}

Axis DirectionMappings::getAxisOf(Direction dir){
	return DirectionMappings::axisOf[dir];
}

