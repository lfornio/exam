#include "Warlock.hpp"

Warlock::Warlock(std::string name, std::string title) : name(name), title(title)
{
	std::cout << getName() << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock()
{
	std::cout << getName() << ": My job here is done!" << std::endl;
}

const std::string &Warlock::getName() const
{
	return name;
}

const std::string &Warlock::getTitle() const
{
	return title;
}

void Warlock::setTitle(const std::string &title)
{
	this->title = title;
}

void Warlock::introduce() const
{
std::cout << getName() << ": I am " << getName() << ", " << getTitle() << "!" << std::endl;
}

void Warlock::learnSpell(ASpell *obj)
{
	book.learnSpell(obj);
}

void Warlock::forgetSpell(std::string str)
{
	book.forgetSpell(str);
}
void Warlock::launchSpell(std:: string name, ATarget const &obj)
{
	ATarget *t = 0;
	if(t == &obj)
		return;
	ASpell *tmp = book.createSpell(name);
	if(tmp)
		tmp->launch(obj);
}
