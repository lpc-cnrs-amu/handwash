#include <iostream>
#include "sha.hpp"

using namespace std;
		
Sha::Sha(unsigned id, unsigned person, bool sure_or_not) : unique_id(id), person_id(person), sure(sure_or_not)
{

}
		
Sha::Sha(Sha* sha)
{
	this->unique_id = sha->unique_id;
	this->person_id = sha->person_id;
	this->sure = sha->sure;
}
Sha::Sha() { }
Sha::~Sha() { }
unsigned Sha::get_unique_id() {	return unique_id; }
unsigned Sha::get_person_id() { return person_id; }
bool Sha::get_sure() { return sure; }

void Sha::set_person_id(unsigned p_id) { person_id = p_id; }
