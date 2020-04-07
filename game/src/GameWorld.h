//
//  GameWorld.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 06/04/2020.
//

#ifndef _GAME_WORLD_H
#define _GAME_WORLD_H

#include "LucusTypes.h"
#include "LucusWorld.h"

class GameWorld : public LucusEngine::World
{
public:
	GameWorld();
	virtual ~GameWorld();

	virtual void InitActors() override;
protected:
    virtual LucusEngine::Component* GetComponent(cc8* name) override;
};

#endif /* _GAME_WORLD_H */
