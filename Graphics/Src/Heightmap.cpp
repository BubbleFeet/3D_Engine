#include "Precompiled.h"
#include "Heightmap.h"

using namespace Graphics;

namespace 
{
	inline uint32_t GetIndex(uint32_t x, uint32_t y, uint32_t width)
	{
		return x + (y * width);
	}
}

Heightmap::Heightmap()
	: mHeightValues(nullptr)
	, mColumns(0)
	, mRows(0)
{
}

Heightmap::~Heightmap() 
{
	ASSERT(mHeightValues == nullptr, "[Heightmap] Height values not freed!");
}

void Heightmap::GenerateFromRAW(const char* filename, uint32_t columns, uint32_t rows)
{
	ASSERT(mHeightValues = nullptr, "[Heightmap] Heightmap is already initialized");
	ASSERT(columns > 0, "[Heightmap] Invalid value for columns.");
	ASSERT(rows > 0, "[Heightmap] Invalid value for rows.");

	// Homework :: use file io to read the RAW file and get normalized height values
	

	mHeightValues = new float[columns * rows];
	mColumns = columns;
	mRows = rows;
	
	for (uint32_t y = 0; y < rows; ++y)
	{
		for (uint32_t x = 0; x < columns; ++x)
		{
			const uint32_t index = x + (y * columns);
			float height = (float)(x + y) / (float)columns;
			while (height > 1.0f)
			{
				height -= 1.0f;
			}
			mHeightValues[index] = height;
		}
	}
}

void Heightmap::Clear()
{
	SafeDeleteArray(mHeightValues);
	mColumns = 0;
	mRows = 0;
}

float Heightmap::GetHeight(uint32_t x, uint32_t y) const
{
	ASSERT(x < mColumns, "[Heightmap] Invalid value for x.");
	ASSERT(y < mRows, "[Heightmap] Invalid value for y.");
	return mHeightValues[GetIndex(x, y, mColumns)];

}