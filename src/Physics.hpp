#pragma once

#include "Vec2.hpp"
#include "Entity.hpp"
#include "Components.hpp"

#include <memory>

struct Intersect
{
    bool result = false;
    Vec2f pos;
};

namespace Physics
{
    // return overlap rectangle size of the bounding boxes of entity a and b
    Vec2f GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
    {
        float xDiff = abs(a->get<CTransform>().pos.x - b->get<CTransform>().pos.x); // > 0 if (center of) a to the right of (center of) b
        float yDiff = abs(a->get<CTransform>().pos.y - b->get<CTransform>().pos.y); // > 0 if (center of) a above (center of) b

        float xOverlap = a->get<CAnimation>().animation.getSize().x / 2 + b->get<CAnimation>().animation.getSize().x / 2 - xDiff;
        float yOverlap = a->get<CAnimation>().animation.getSize().y / 2 + b->get<CAnimation>().animation.getSize().y / 2 - yDiff;

        return Vec2f(xOverlap, yOverlap); // if xOverlap > 0, AABB overlap of xOverlap in the x-direction
    }

    // return previous overlap rectangle size of the bounding boxes of entity a and b
    Vec2f GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
    {
        float xDiff = abs(a->get<CTransform>().prevPos.x - b->get<CTransform>().pos.x);
        float yDiff = abs(a->get<CTransform>().prevPos.y - b->get<CTransform>().pos.y);

        float xOverlap = a->get<CAnimation>().animation.getSize().x / 2 + b->get<CAnimation>().animation.getSize().x / 2 - xDiff;
        float yOverlap = a->get<CAnimation>().animation.getSize().y / 2 + b->get<CAnimation>().animation.getSize().y / 2 - yDiff;

        return Vec2f(xOverlap, yOverlap); // if xOverlap > 0, AABB overlap of xOverlap in the x-direction
    }

    bool IsInside(const Vec2f &pos, std::shared_ptr<Entity> e)
    {
        // TODO

        return false;
    }

    Intersect LineIntersect(const Vec2f &a, const Vec2f &b, const Vec2f &c, const Vec2f &d)
    {
        // TODO
        
        return {};
    }

    // line of sight stuff
    bool EntityIntersect (const Vec2f &a, const Vec2f &b, std::shared_ptr<Entity> e)
    {
        // TODO

        return false;
    }
}