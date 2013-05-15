<<<<<<< HEAD
#include <stdio.h>
#include <iostream>
using std::cout;
using std::cin;
=======
//http://buzzard.ups.edu/sdes/sdes.html
>>>>>>> 57e23a3d9d8fcc187bc2a7f1c8e9bcd3da779454
typedef struct{
	char key_1;
	char key_2;
} SDES_KEYS;
SDES_KEYS CreateKeys(int key_in);
int SDES_KEY_P10(int key_in);
char SDES_LS1(char data);
char SDES_LS2(char data);
int SDES_KEY_P8(int key_in);
char SDES_EP(char char_in);
char SDES_P4(char char_in);
char SDES_SBOXES(char in);
char SDES_Decrypt(char plain_text, SDES_KEYS keys);
char SDES_Encrypt(char plain_text, SDES_KEYS keys);
char SDES_IP(char data_in);
char SDES_IP_inverse(char data_in);

int main()
{
	char selection;
	//Enter key generating character
	bool done = false;
	while (!done)
	{
		done = false;
		while (!done)
		{
		cout << "Encrypt (e) or Decrypt(d): ";
		cin >> selection;
		if( toupper(selection) == 'E' || toupper(selection) == 'D')
		{
			done = true;
		}
		}
		cout << "\nEnter charactor used to generate the key: ";
		char keygen;
		cin >> keygen;
		SDES_KEYS keys = CreateKeys(keygen);
		char plain_text;
		char cypher_text;
		if(toupper(selection) == 'E')
		{
			cout << "Enter charactor to be encrypted: ";
			cin >> plain_text;
			cout << "Encrypted data: ";
			cypher_text = SDES_Encrypt(plain_text,keys);
			cout << cypher_text;
		}
		else
		{
			cout << "Enter charactor to be decrypted: ";
			cin >> cypher_text;
			cout << "\nDecrypted data: ";
			plain_text = SDES_Decrypt(cypher_text,keys);
			cout << plain_text;
		}
		cout << "\nQuit(Q) or Continue(C): ";
		cin >> selection;
		if(toupper(selection) == 'Q')
		{
			done = true;
		}
		else
		{
			done = false;
		}
	}
}

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
	char out = (data >> 1) | ((data & 0x01) << 4);
	out = out & 0x1F;
	return out;
}

char SDES_LS2(char data)
{
	char out = (data >> 2) | ((data & 0x01) << 3) | ((data & 0x02) << 3);
	out = out & 0x1F;
	return out;
}

int SDES_KEY_P8(int key_in)
{
	int ret = 0;
	ret = ((key_in & 0x04) >> 1) |
		  ((key_in & 0x08)) |
		  ((key_in & 0x10) << 1) |
		  ((key_in & 0x20) >> 5) |
		  ((key_in & 0x40) >> 4) |
		  ((key_in & 0x80) >> 3) |
		  ((key_in & 0x100) >> 1) |
		  ((key_in & 0x200) >> 3);
		  return ret;
}




/*
char SDES_EP(char in)
{
	char out = (char_in & 0x01) |
				(char_in & 0x01) << 6) |
				(char_in & 0x02) << 2) |
				(char_in & 0x02) << 4) |
				(char_in & 0x04) |
				(char_in & 0x04) << 6) |
				(char_in & 0x08) >> 2) |
				(char_in & 0x08 << 4);
	return out;

}
*/

char SDES_EP(char char_in)
{
	char_in = ((char_in & 0xF0) >> 4) | (char_in & 0xF0);
	char out = ((char_in & 0x01) << 1) |
				((char_in & 0x02) << 1) |
				((char_in & 0x04) << 1) |
				((char_in & 0x08) >> 3) |
				((char_in & 0x10) << 3) |
				((char_in & 0x20) >> 1) |
				((char_in & 0x40) >> 1) |
				((char_in & 0x80) >> 1);
				
	return out;
}

/*
char SDES_P4(char in)
{
	char out = (char_in & 0x01) |
				((char_in & 0x02) << 2) |
				((char_in & 0x04) >> 1) |
				((char_in & 0x08) >> 1);
	return out;
}

*/

char SDES_P4(char char_in)
{
	char out = ((char_in & 0x01)  << 3)|
				((char_in & 0x02) >> 1) |
				((char_in & 0x04)) |
				((char_in & 0x08) >> 2);
	return out;
}



char SDES_SBOXES(char in)
{
	char s0[4][4] = { 1, 0, 3, 2,
					  3, 2, 1, 0,
					  0, 2, 1, 3,
					  3, 1, 3, 2};
					  
	char s1[4][4] = { 0, 1, 2, 3,
					  2, 0, 1, 3,
					  3, 0, 1, 0,
					  2, 1, 0, 3};
	
	char out;
	char left_nibble_start = in & 0x0F;
	//char left_nibble_row = (left_nibble_start & 0x01) | ((left_nibble_start & 0x8) << 2);
	char left_nibble_row = ((left_nibble_start & 0x01) << 1) | ((left_nibble_start & 0x8) >> 3);
	char left_nibble_col = ((left_nibble_start & 0x02) | ((left_nibble_start & 0x04) >> 2));
	//char left_nibble_col = ((left_nibble_start & 0x02) >> 1) | ((left_nibble_start & 0x04) >> 1);
	
	char right_nibble_start = in >> 4;
	//char right_nibble_row = (in & 0x01) | ((in & 0x8) << 2);
	//char right_nibble_col = ((in & 0x02) >> 1) | ((in & 0x04) >> 1);
	char right_nibble_row = ((right_nibble_start & 0x01) << 1) | ((right_nibble_start & 0x8) >> 3);
	char right_nibble_col = ((right_nibble_start & 0x02)) | ((right_nibble_start & 0x04) >> 2);
	char out_lower = (s0[left_nibble_row][left_nibble_col] & 0x3);
	out_lower = ((out_lower & 0x01) << 1) | ((out_lower & 0x02) >> 1);
	
	char out_higher = ((s1[right_nibble_row][right_nibble_col] & 0x3));
	out_higher = ((((out_higher & 0x01) << 1) | ((out_higher & 0x02) >> 1)) << 2);
	
	//out = (s0[left_nibble_row][left_nibble_col] & 0x3) | ((s1[right_nibble_row][right_nibble_col] & 0x3) << 2);
	out = out_lower | out_higher;
	
	return out;
}

char SDES_Decrypt(char plain_text, SDES_KEYS keys)
{
	SDES_KEYS decrypt_key;
	decrypt_key.key_1 = keys.key_2;
	decrypt_key.key_2 = keys.key_1;
	return SDES_Encrypt(plain_text,decrypt_key);
}
char SDES_Encrypt(char plain_text, SDES_KEYS keys)
{

	char initial_permuation_out = SDES_IP(plain_text);
	// perform E/P on right four bits of IP.
	char ep_out = SDES_EP(initial_permuation_out);
	
	char k1_ep_xor_out = keys.key_1 ^ ep_out;
	char sbox_out = SDES_SBOXES(k1_ep_xor_out);
	char sdes_p4_out = SDES_P4(sbox_out); //???? does this work?
	char xor_ip_left_nibble_with_p4 = sdes_p4_out ^ (initial_permuation_out & 0x0F);
	char combine_ip_right_nibble_with_above = ((initial_permuation_out & 0xF0)) | ((xor_ip_left_nibble_with_p4));
	char swap_two_halves = ((combine_ip_right_nibble_with_above & 0xF0) >> 4) | ((combine_ip_right_nibble_with_above & 0x0F) << 4);
	char ep_of_right_nibble_swap = SDES_EP((swap_two_halves & 0xF0));
	char xor_with_key2 = ep_of_right_nibble_swap ^ keys.key_2;
	char sbox2_out = SDES_SBOXES(xor_with_key2);
	char p4_on_sbox2_out = SDES_P4(sbox2_out);
	char xor_p4_on_sbox2_out_with_earlier_swap_left_nibble = p4_on_sbox2_out ^ ((swap_two_halves & 0x0F));
	char replace_left_nibble_of_first_swap = (swap_two_halves & 0xF0) | (xor_p4_on_sbox2_out_with_earlier_swap_left_nibble & 0x0F);
	char apply_inverse_ip = SDES_IP_inverse(replace_left_nibble_of_first_swap);
	return apply_inverse_ip;
}


char SDES_IP(char data_in)
{
	char ret = 0;
	ret = ((data_in & 0x01) << 3) |
		  ((data_in & 0x02) >> 1) |
		  ((data_in & 0x04)) |
		  ((data_in & 0x08) << 1) |
		  ((data_in & 0x10) << 2) |
		  ((data_in & 0x20) >> 4) |
		  ((data_in & 0x40) << 1) |
		  ((data_in & 0x80) >> 2);
		  return ret;
}
char SDES_IP_inverse(char data_in)
{
	char ret = 0;
	ret = ((data_in & 0x01) << 1) |
		  ((data_in & 0x02) << 4) |
		  ((data_in & 0x04)) |
		  ((data_in & 0x08) >> 3) |
		  ((data_in & 0x10) >> 1) |
		  ((data_in & 0x20) << 2) |
		  ((data_in & 0x40) >> 2) |
		  ((data_in & 0x80) >> 1);
		  return ret;
}
