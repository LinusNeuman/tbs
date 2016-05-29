#pragma once

class GridDweller;

class  GridTile
{
public:
	void AddDweller(const GridDweller & aDweller);

private:
	const GridDweller * myDweller;
};

void GridTile::AddDweller(const GridDweller & aDweller)
{
	myDweller = &aDweller;
}
