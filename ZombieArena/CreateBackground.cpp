#include "pch.h"
#include "ZombieArena.h"

int createBackground(VertexArray& rVA, IntRect arena)
{
	//anything we do to rVA we are actually doing
	//to the background (in the main function)
	//how big is each tile/texture
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERIS_IN_QUAD = 4;

	int worldWidth = arena.width / TILE_SIZE;
	int worldHeight = arena.height / TILE_SIZE;

	//what types of primitives are we using?
	rVA.setPrimitiveType(Quads);

	//set the size of the vertex array
	rVA.resize(worldWidth * worldHeight * VERIS_IN_QUAD);

	//start at the beginning of the vertex arrray
	int currentVertex = 0;

	for (int w = 0; w < worldWidth; w++)
	{
		for (int h = 0; h < worldHeight; h++) 
		{
			//position each vertex in the current quad
			rVA[currentVertex + 0].position =
				Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 1].position =
				Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);

			rVA[currentVertex + 2].position =
				Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE)
					+ TILE_SIZE);
			rVA[currentVertex + 3].position =
				Vector2f((w * TILE_SIZE), (h * TILE_SIZE)
					+ TILE_SIZE);

			//define the position in the texture for the current quad
			//either grass, stone, bush , or wall
			if (h == 0 || h == worldHeight - 1 ||
				w == 0 || w == worldWidth - 1)
			{
				//use the wall texture
				rVA[currentVertex + 0].texCoords =
					Vector2f(0, 0 + TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 1].texCoords =
					Vector2f(TILE_SIZE, 0 + TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 2].texCoords =
					Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 0].texCoords =
					Vector2f(0, TILE_SIZE + TILE_TYPES * TILE_SIZE);
			}
			else
			{
				//use a random floor texture
				srand((int)time(0) + h * w - h);
				int mOrG = (rand() % TILE_TYPES);
				int verticalOffset = mOrG * TILE_SIZE;

				rVA[currentVertex + 0].texCoords =
					Vector2f(0, 0 + verticalOffset);
				rVA[currentVertex + 1].texCoords =
					Vector2f(TILE_SIZE, 0 + verticalOffset);
				rVA[currentVertex + 2].texCoords = 
					Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				rVA[currentVertex + 3].texCoords =
					Vector2f(0, TILE_SIZE + verticalOffset);
			}

			//position ready for the next 4 vertices
			currentVertex = currentVertex + VERIS_IN_QUAD;
		}
	}

	return TILE_SIZE;
}