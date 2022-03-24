#include "SpellBook.hpp"

SpellBook::SpellBook() {}
SpellBook::~SpellBook()
{
	std::map<std::string, ASpell *>::iterator it_begin = this->arr_spell.begin();
	std::map<std::string, ASpell *>::iterator it_end = this->arr_spell.end();
	while(it_begin != it_end)
	{
		delete it_begin->second;
		++it_begin;
	}
	this->arr_spell.clear();

}

void SpellBook::learnSpell(ASpell *obj)
{
	if(obj)
		arr_spell.insert(std::pair<std::string, ASpell *>(obj->getName(), obj->clone()));
}

void SpellBook::forgetSpell(std::string const &str)
{
	std::map<std::string, ASpell *>::iterator it = arr_spell.find(str);
	if(it != arr_spell.end())
		delete it->second;
	arr_spell.erase(str);
}

ASpell* SpellBook::createSpell(std::string const &str)
{
	std::map<std::string, ASpell *>::iterator it = arr_spell.find(str);
	if(it != arr_spell.end())
		return arr_spell[str];
	return NULL;
}
