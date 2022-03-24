#ifndef ATARGET_HPP
#define ATARGET_HPP

#include <iostream>
#include <string>
#include "ASpell.hpp"

class ASpell;

class ATarget
{
private:
	std::string type;

public:
	ATarget();
	ATarget(std::string type);
	virtual ~ATarget();
	ATarget(const ATarget &other);
	ATarget &operator=(const ATarget &other);
	const std::string &getType() const;
	virtual ATarget *clone() const = 0;
	void getHitBySpell(const ASpell &obj) const;

};

#endif
