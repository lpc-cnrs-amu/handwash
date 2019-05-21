#include <iostream>
#include "sha.hpp"

using namespace std;
		
Sha::Sha(unsigned id, bool sure_or_not) : unique_id(id), sure(sure_or_not)
{

}
		
Sha::Sha(Sha* sha)
{
	this->unique_id = sha->unique_id;
	this->sure = sha->sure;
}
Sha::Sha() { }
Sha::~Sha() { }
unsigned Sha::get_unique_id() {	return unique_id; }
bool Sha::get_sure() { return sure; }
