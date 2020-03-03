#pragma once
	
template<typename TAG>
class Handle
{
	union
	{
		enum
		{
			MAX_BIT_INDEX = 16,
			MAX_BIT_MAGIC = 16,

			MAX_INDEX = (1 << MAX_BIT_INDEX) - 1,
			MAX_MAGIC = (1 << MAX_BIT_MAGIC) - 1,
		};

		struct 
		{
			unsigned m_Index : MAX_BIT_INDEX;
			unsigned m_Magic : MAX_BIT_MAGIC;
		};
		unsigned int m_Hanle;
	};
public:
	Handle(void) : m_Hanle(0) {}
	void Init(unsigned int index);
};
template<typename TAG>
void Handle<TAG>::Init(unsigned int index)
{

	static unsigned int s_AutoMagic = 0;
	if (++s_AutoMagic > MAX_MAGIC)
	{
		s_AutoMagic = 1;
	}
	m_Index = index;
	m_Magic = s_AutoMagic;
}

