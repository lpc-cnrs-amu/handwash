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
		bool sure = false; /* Is the SHA sure or not ? */
		
		
	public:
		Sha(Sha* sha);
		Sha(unsigned id, bool sure_or_not);
		Sha();
		~Sha();
		
		bool get_sure();
		unsigned get_unique_id();
};
	

#endif
