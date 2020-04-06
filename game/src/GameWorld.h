//
//  GameWorld.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 06/04/2020.
//

#ifndef _GAME_WORLD_H
#define _GAME_WORLD_H

#include "LucusWorld.h"

class GameWorld : public LucusEngine::World
{
public:
	GameWorld();
	virtual ~GameWorld();

	virtual void InitWorld() override;
	virtual Component* CreateComponent(сс8* name) override;
};

#endif /* _GAME_WORLD_H */
