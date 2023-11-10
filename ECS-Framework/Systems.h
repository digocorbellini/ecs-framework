#pragma once

#include "Components.h"

const ComponentsMask PHYSICS_MASK({ ComponentType::ENTITY_TRANSFORM, ComponentType::PHYSICS_BODY });
const ComponentsMask RENDERER_MASK({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER });
const ComponentsMask CONTROLLER_MASK({ ComponentType::ENTITY_TRANSFORM, ComponentType::PLAYER_CONTROLLER });
