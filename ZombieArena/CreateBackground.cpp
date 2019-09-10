#include "pch.h"
#include "ZombieArena.h"

int createBackground(VertexArray& rVA, IntRect arena)
{
	//anything we do to rVA we are actually doing
	//to background (in main function)
	//how big is each tile/texture

	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERIS_IN_QUAD = 4;

	int worldWidth = arena.width / TILE_SIZE;
	int worldHeight = arena.height / TILE_SIZE;

	//what type of primitive are we using?
	rVA.setPrimitiveType(Quads);

	//set the size of the vertex array
	rVA.resize(worldWidth * worldHeight * VERIS_IN_QUAD);

	//start at the beginning of hte vertex array
	int currentVertex = 0;

	for (int w = 0; w < worldWidth; w++)
	{
		for (int h = 0; h < worldHeight; h++)
		{
			//position each vertext int the current QUAD
			rVA[currentVertex + 0].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);	
			rVA[currentVertex + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE)	+ TILE_SIZE);
			rVA[currentVertex + 3].position = Vector2f((w * TILE_SIZE), (h * TILE_SIZE)	+ TILE_SIZE);

			//define th eposition in the texture for current quad
			//either grass, stone, bush, or wall
			if (h == 0 || h == worldHeight - 1 ||
				w == 0 || w == worldWidth - 1)
			{
				//use wall texture
				rVA[currentVertex + 0].texCoords =
					Vector2f(0, 0 + 
						TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 1].texCoords =
					Vector2f(TILE_SIZE, 0 + 
						TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 2].texCoords =
					Vector2f(TILE_SIZE, TILE_SIZE + 
						TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 3].texCoords =
					Vector2f(0, TILE_SIZE + 
						TILE_TYPES * TILE_SIZE);
			}
			else
			{
				//use a random floor texture
				srand((int)time(0) + h * w - h);
				int mOrg = (rand() % TILE_TYPES);
				int verticalOffSet = mOrg * TILE_SIZE;

				rVA[currentVertex + 0].texCoords =
					Vector2f(0, 0 + verticalOffSet);
				rVA[currentVertex + 1].texCoords =
					Vector2f(TILE_SIZE, 0 + verticalOffSet);
				rVA[currentVertex + 0].texCoords =
					Vector2f(TILE_SIZE, TILE_SIZE + verticalOffSet);
				rVA[currentVertex + 0].texCoords =
					Vector2f(0, TILE_SIZE + verticalOffSet);
			}
			//position ready for the next vertices
			currentVertex = currentVertex + VERIS_IN_QUAD;
		}
	}
	return TILE_SIZE;
}