#ifndef SHA_HPP
#define SHA_HPP

/**
 * \file sha.hpp
*/


/** 
 * \class Sha
 * \brief Class representing a SHA 
 * from the hygiene csv file. 
*/
class Sha
{
	private:
		unsigned person_id = -1; // -1 = ambiguité : on ne sait pas à qui attribuer le SHA
		unsigned code_sha = -1; // 8 or 10
		bool sure = false; /* Is the SHA sure or not ? */
		
		
	public:
		Sha(Sha* sha);
		Sha(unsigned code_sha, unsigned person, bool sure_or_not);
		Sha();
		~Sha();
		
		bool get_sure();
		unsigned get_code_sha() ;
		unsigned get_person_id();
		
		void set_person_id(unsigned p_id);
};
	

#endif
