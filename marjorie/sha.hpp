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
		unsigned unique_id; /* id unique of the event (primary key) */
		unsigned person_id = -1; // -1 = ambiguité : on ne sait pas à qui attribuer le SHA
		bool sure = false; /* Is the SHA sure or not ? */
		
		
	public:
		Sha(Sha* sha);
		Sha(unsigned id, unsigned person, bool sure_or_not);
		Sha();
		~Sha();
		
		bool get_sure();
		unsigned get_unique_id();
		
		unsigned get_person_id();
		void set_person_id(unsigned p_id);
};
	

#endif
