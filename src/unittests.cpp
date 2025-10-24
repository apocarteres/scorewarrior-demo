#include "Core/Map.h"

#include <cassert>

void mapCellIsAvailableByDefault()
{
	Map map{1, 1};
	assert(true == map.isAvailable(0, 0));
}

void mapCellIsValidIfInRange()
{
	Map map{1, 1};
	assert(true == map.isValid(0, 0));
}

void mapCellIsInValidIfOutOfRangeByXPositive()
{
	Map map{1, 1};
	assert(false == map.isValid(2, 0));
}

void mapCellIsInValidIfOutOfRangeByYPositive()
{
	Map map{1, 1};
	assert(false == map.isValid(0, 2));
}

void mapCellIsInValidIfOutOfRangeByXNegative()
{
	Map map{1, 1};
	assert(false == map.isValid(-1, 0));
}

void mapCellIsInValidIfOutOfRangeByYNegative()
{
	Map map{1, 1};
	assert(false == map.isValid(-1, 0));
}

void mapCellOccupiedWithRigidBody()
{
	Map map{1, 1};
	assert(true == map.isAvailable(0, 0));
	assert(true == map.occupy(1, true, 0, 0));
	assert(false == map.isAvailable(0, 0));
}

void mapCellNotOccupiedWithRigidBodyTwice()
{
	Map map{1, 1};
	assert(true == map.isAvailable(0, 0));
	assert(true == map.occupy(1, true, 0, 0));
	assert(false == map.occupy(1, true, 0, 0));
}

void mapCellNotOccupiedByShadow()
{
	Map map{1, 1};
	assert(true == map.isAvailable(0, 0));
	assert(true == map.occupy(1, false, 0, 0));
	assert(true == map.isAvailable(0, 0));
}

void mapLooksUpNeighborsInRange()
{
	Map map{10, 10};
	auto neighbors = map.lookupNeighbors(5, 5, 1);
	assert(true == neighbors.empty());
	map.occupy(100, true, 4, 4);
	map.occupy(101, true, 5, 4);
	map.occupy(102, true, 6, 4);
	map.occupy(103, true, 4, 5);
	map.occupy(104, true, 5, 5);  // this one is not a neighbor
	map.occupy(105, true, 6, 5);
	map.occupy(106, true, 4, 6);
	map.occupy(107, true, 5, 6);
	map.occupy(108, true, 6, 6);
	map.occupy(109, true, 7, 7);  // this one is not a neighbor
	neighbors = map.lookupNeighbors(5, 5, 1);
	assert(8 == neighbors.size());
}

void mapLooksUpNeighborsInLeftTopCorner()
{
	Map map{10, 10};
	map.occupy(100, true, 1, 0);
	map.occupy(101, true, 2, 0);
	map.occupy(102, true, 0, 1);
	map.occupy(103, true, 1, 1);
	map.occupy(104, true, 2, 1);
	map.occupy(105, true, 0, 2);
	map.occupy(106, true, 1, 2);
	map.occupy(107, true, 2, 2);
	map.occupy(108, true, 0, 3);
	map.occupy(109, true, 1, 3);
	map.occupy(110, true, 2, 3);
	auto neighbors = map.lookupNeighbors(0, 0, 1);
	assert(3 == neighbors.size());
}

void mapLooksUpNeighborsWithExceptOfSourceCell()
{
	Map map{3, 3};
	map.occupy(100, true, 1, 1);
	auto neighbors = map.lookupNeighbors(1, 1, 1);
	assert(0 == neighbors.size());
}

void mapMovesRigidObjectIfTargetCellIsAvailable()
{
	Map map{3, 3};
	map.occupy(100, true, 1, 1);
	assert(true == map.move(100, 0, 0, 1));
	assert(true == map.isAvailable(1, 1));
	assert(false == map.isAvailable(0, 0));
}

void mapDoesNotMoveRigidObjectIfTargetCellIsOccupied()
{
	Map map{3, 3};
	map.occupy(100, true, 1, 1);
	map.occupy(101, true, 0, 0);
	assert (false == map.move(100, 0, 0, 1));
	assert(false == map.isAvailable(1, 1));
	assert(false == map.isAvailable(0, 0));
}

void mapMovesShadowObjectIfTargetCellIsOccupied()
{
	Map map{3, 3};
	map.occupy(100, false, 1, 1);
	map.occupy(101, true, 0, 0);
	assert (true == map.move(100, 0, 0, 1));
	assert(true == map.isAvailable(1, 1));
	assert(false == map.isAvailable(0, 0));
}

void mapNeighborsIncludeShadows()
{
	Map map{3, 3};
	map.occupy(100, false, 0, 0);
	map.occupy(101, true, 0, 0);
	auto neighbors = map.lookupNeighbors(1, 1, 1);
	assert(2 == neighbors.size());
}

void mapCalcsDistanceCorrectly()
{
	Map map{3, 3};
	map.occupy(100, false, 0, 0);
	map.occupy(101, true, 2, 2);
	assert(2 == map.distance(100, 101));
}

void runUnitTests()
{
	mapCellIsAvailableByDefault();
	mapCellIsValidIfInRange();
	mapCellIsInValidIfOutOfRangeByXPositive();
	mapCellIsInValidIfOutOfRangeByYPositive();
	mapCellIsInValidIfOutOfRangeByXNegative();
	mapCellIsInValidIfOutOfRangeByYNegative();
	mapCellOccupiedWithRigidBody();
	mapCellNotOccupiedWithRigidBodyTwice();
	mapCellNotOccupiedByShadow();
	mapLooksUpNeighborsInRange();
	mapLooksUpNeighborsInLeftTopCorner();
	mapLooksUpNeighborsWithExceptOfSourceCell();
	mapMovesRigidObjectIfTargetCellIsAvailable();
	mapDoesNotMoveRigidObjectIfTargetCellIsOccupied();
	mapMovesShadowObjectIfTargetCellIsOccupied();
	mapNeighborsIncludeShadows();
	mapCalcsDistanceCorrectly();

}
