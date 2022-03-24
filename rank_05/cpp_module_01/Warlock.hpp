#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <iostream>
#include <string>
#include <map>
#include "ASpell.hpp"
#include "ATarget.hpp"

class Warlock
{
private:
	std::string name;
	std::string title;
	Warlock();
	Warlock(const Warlock &other);
	Warlock &operator=(const Warlock &other);
	std::map<std::string, ASpell *> arr;

public:
	Warlock(std::string name, std::string title);
	~Warlock();
	const std::string &getName() const;
	const std::string &getTitle() const;
	void setTitle(const std::string &title);
	void introduce() const;
	void learnSpell(ASpell *obj);
	void forgetSpell(std::string str);
	void launchSpell(std:: string name, ATarget const &obj);

};

#endif
