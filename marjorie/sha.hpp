#ifndef SHA_HPP
#define SHA_HPP

/**
 * \file sha.hpp
*/


/** 
 * \class Sha
 * \brief Class representing an event  
 * from the hygiene csv file. 
*/
class Sha
{
	private:
		unsigned unique_id; 
		bool sure = false;
		
		
	public:
		Sha(Sha* sha);
		Sha(unsigned id, bool sure_or_not);
		Sha();
		~Sha();
		
		bool get_sure();
		unsigned get_unique_id();
};
	

#endif
