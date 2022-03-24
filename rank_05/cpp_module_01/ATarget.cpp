#include "ATarget.hpp"

ATarget::ATarget() {}
ATarget::~ATarget() {}

ATarget::ATarget(std::string type) : type(type) {}
ATarget::ATarget(const ATarget &other)
{
	*this = other;
}

ATarget &ATarget::operator=(const ATarget &other)
{
	this->type = other.type;
	return (*this);
}

const std::string &ATarget::getType() const
{
	return type;
}

void ATarget::getHitBySpell(const ASpell &obj) const
{
	std::cout << type << " has been " << obj.getEffects() << "!" << std::endl;
}
