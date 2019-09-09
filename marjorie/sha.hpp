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
		unsigned code_sha = -1; // 8 or 10
		int person_id = -1; // -1 = ambiguité : on ne sait pas à qui attribuer le SHA		
		bool sure = false; /* Is the SHA sure or not ? */
		
		
	public:
		Sha(Sha* sha);
		Sha(unsigned code_sha, int person, bool sure_or_not);
		Sha();
		~Sha();
		
		int get_person_id();
		unsigned get_code_sha() ;
		bool get_sure();
		
		void set_person_id(int person_id);
		void set_SHA(unsigned code_sha, int p_id, bool sure);
};
	

#endif
