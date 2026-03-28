#pragma once

struct StarCamera : Actor
{
	static constexpr u16 staticActorID = 0xb1;
};

static_assert(sizeof(StarCamera) == 0xd4, "sizeof(StarCamera) is incorrect!");