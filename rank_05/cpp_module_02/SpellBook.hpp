#ifndef SPELLBOOK_HPP
#define SPELLBOOK_HPP

#include <iostream>
#include <string>
#include <map>
#include "ASpell.hpp"

class SpellBook
{
private:
	std::map<std::string, ASpell *> arr_spell;

	SpellBook(const SpellBook &other);
	SpellBook &operator=(const SpellBook &other);

public:
	SpellBook();
	~SpellBook();
	void learnSpell(ASpell *obj);
	void forgetSpell(std::string const &str);
	ASpell* createSpell(std::string const &str);

};

#endif
