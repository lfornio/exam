#include "ASpell.hpp"

ASpell::ASpell() {}
ASpell::~ASpell() {}

ASpell::ASpell(std::string name, std::string effects) : name(name), effects(effects) {}
ASpell::ASpell(const ASpell &other)
{
	*this = other;
}

ASpell &ASpell::operator=(const ASpell &other)
{
	this->name = other.name;
	this->effects = other.effects;
	return (*this);
}

const std::string &ASpell::getName() const
{
	return name;
}

const std::string &ASpell::getEffects() const
{
	return effects;
}

void ASpell::launch(ATarget const &obj) const
{
	obj.getHitBySpell(*this);
}
