#include "Components.h"

ComponentsMask::ComponentsMask()
{
	mask = 0;
}

ComponentsMask::ComponentsMask(const ComponentsMask& other)
{
	mask = other.mask;
}

ComponentsMask::ComponentsMask(long mask)
{
	this->mask = mask;
}

ComponentsMask::ComponentsMask(std::initializer_list<ComponentType> list)
{
	mask = 0;
	AddComponent(list);
}

void ComponentsMask::AddComponent(ComponentType comp)
{
	mask |= 1 << comp;
}

void ComponentsMask::AddComponent(std::initializer_list<ComponentType> list)
{
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		AddComponent(*it);
	}
}

void ComponentsMask::RemoveComponent(ComponentType comp)
{
	long inversedMask = 1 << comp;
	inversedMask = ~inversedMask;
	mask &= inversedMask;
}

void ComponentsMask::RemoveComponent(std::initializer_list<ComponentType> list)
{
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		RemoveComponent(*it);
	}
}

long ComponentsMask::GetMask()
{
	return mask;
}

bool ComponentsMask::operator==(ComponentsMask const& other) const
{
	return this->mask == other.mask;
}

bool ComponentsMask::operator!=(ComponentsMask const& other) const
{
	return this->mask != other.mask;
}

ComponentsMask ComponentsMask::operator&(const ComponentsMask& other)
{
	return ComponentsMask(mask & other.mask);
}
