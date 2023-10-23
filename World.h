
#ifndef _WORLD_BUILDER_H_
#define _WORLD_BUILDER_H_

class World
{
private:
	int width;
	int height;
	int channels;

public:
	World(const char* path);
};

#endif // !_WORLD_BUILDER_H_