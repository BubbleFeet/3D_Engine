#ifndef INCLUDED_GRAPHICS_SCREENMESHBUFFER_H
#define INCLUDED_GRAPHICS_SCREENMESHBUFFER_H

namespace Graphics
{

class ScreenMeshBuffer
{
	NONCOPYABLE(ScreenMeshBuffer);

public:

	ScreenMeshBuffer();
	~ScreenMeshBuffer();

	void Initialize();
	void Terminate();

	void Render();

private:
	ID3D11Buffer* mVertexBuffer;
};

}
#endif // !INCLUDED_GRAPHICS_SCREENMESHBUFFER_H