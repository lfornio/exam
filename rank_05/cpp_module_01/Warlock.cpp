#include "Warlock.hpp"

Warlock::Warlock(std::string name, std::string title) : name(name), title(title)
{
	std::cout << getName() << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock()
{
	std::cout << getName() << ": My job here is done!" << std::endl;
	std::map<std::string, ASpell *>::iterator it_begin = this->arr.begin();
	std::map<std::string, ASpell *>::iterator it_end = this->arr.end();
	while(it_begin != it_end)
	{
		delete it_begin->second;
		++it_begin;
	}
	this->arr.clear();
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
	if(obj)
		arr.insert(std::pair<std::string, ASpell *>(obj->getName(), obj->clone()));
}

void Warlock::forgetSpell(std::string str)
{
	std::map<std::string, ASpell *>::iterator it = arr.find(str);
	if(it != arr.end())
		delete it->second;
	arr.erase(str);

}
void Warlock::launchSpell(std:: string name, ATarget const &obj)
{
	ASpell *tmp = arr[name];
	if(tmp)
		tmp->launch(obj);
}
