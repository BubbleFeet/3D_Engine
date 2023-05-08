#ifndef INCLUDED_GRAPHICS_HEIGHTMAP_H
#define	INCLUDED_GRAPHICS_HEIGHTMAP_H

namespace Graphics {

class Heightmap
{
public:
	Heightmap();
	~Heightmap();

	void GenerateFromRAW(const char* filename, uint32_t columns, uint32_t rows);
	void Clear();

	float GetHeight(uint32_t x, uint32_t y) const;

	uint32_t GetColumns() const {return mColumns;}
	uint32_t GetRows() const { return mRows; }

private:
	NONCOPYABLE(Heightmap);

	float* mHeightValues;
	uint32_t mColumns;
	uint32_t mRows;
};

}		// namespace Graphics

#endif // #ifndef INCLUDED_GRAPHICS_HEIGHTMAP_H