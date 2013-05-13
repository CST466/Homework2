
typedef struct{
	char key_1;
	char key_2;
} SDES_KEYS;


SDES_KEYS CreateKeys(int key_in)
{
	char key_one_upper;
	char key_one_lower;
	SDES_KEYS keys;
	int key_p10 = SDES_KEY_P10(key_in);
	char p10_upper = (key_p10 & 0x1F0) >> 5;
	char p10_lower = (key_p10 & 0x1F);
	char ls1_upper = SDES_LS1(p10_upper);
	char ls1_lower = SDES_LS1(p10_lower);
	
	keys.key_1 = SDES_KEY_P8( (ls1_upper << 5) | (ls1_lower));
	
	char ls2_lower = SDES_LS2(ls1_lower);
	char ls2_upper = SDES_LS2(ls1_upper);
	
	keys.key_2 = SDES_KEY_P8( (ls2_upper << 5) | (ls2_lower));
	
	return keys;
	

}

int SDES_KEY_P10(int key_in)
{
	int key_out = ((key_in & 0x01) << 6) |
				  ((key_in & 0x02) << 1) |
				  ((key_in & 0x04) >> 2) |
				  ((key_in & 0x08) << 1) |
				  ((key_in & 0x10) >> 3) |
				  ((key_in & 0x20) << 4) |
				  ((key_in & 0x40) >> 2) |
				  ((key_in & 0x80) << 1) |
				  ((key_in & 0x100) >> 1) |
				  ((key_in & 0x200) >> 4);
				  
	return key_out;
}

char SDES_LS1(char data)
{
	char out = (data << 1) | ((data & 0x10) >> 4);
	out = out & 0x1F;
	return out;
}

char SDES_LS2(char data)
{
	char out = (data << 2) | ((data & 0x10) >> 3) | ((data & 0x08) >> 3);
	out = out & 0x1F;
	return out;
}

int SDES_KEY_P8(int key_in)
{
	int ret = 0;
	ret = ((key_in & 0x1) << 2) |
		  ((key_in & 0x2) >> 1) |
		  ((key_in & 0x4) << 1) |
		  ((key_in & 0x8) << 2) |
		  ((key_in & 0x10) << 3) |
		  ((key_in & 0x20) >> 3) |
		  ((key_in & 0x40) >> 2) |
		  ((key_in & 0x80) >> 1);
		  return ret;
}

