#pragma once
class BitHelp
{
public:
	static int GetTargetBit(int i, int pos)
	{
		int res = (i >> (pos - 1)) & 1;
		return res;
	}

	static void SetTargetBit(int& i, int pos, int value)
	{
		if (value == 1)
		{
			i = i | (1 << (pos - 1));
		}
		else if (value == 0)
		{
			i = i & ~(1 << (pos - 1));
		}
	}

};


