#include <iostream>
#include "sha.hpp"

using namespace std;
		
Sha::Sha(unsigned code, unsigned person, bool sure_or_not) : code_sha(code), person_id(person), sure(sure_or_not)
{

}
		
Sha::Sha(Sha* sha)
{
	this->code_sha = sha->code_sha;
	this->person_id = sha->person_id;
	this->sure = sha->sure;
}

Sha::Sha() { }
Sha::~Sha() { }
unsigned Sha::get_person_id() { return person_id; }
bool Sha::get_sure() { return sure; }
unsigned Sha::get_code_sha() { return code_sha; }

void Sha::set_person_id(unsigned person_id) { this->person_id = person_id; }
void Sha::set_SHA(unsigned code_sha, unsigned p_id, bool sure)
{ 
	this->code_sha = code_sha;
	this->person_id = person_id; 
	this->sure = sure; 
}
