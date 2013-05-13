


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

char SDES_EP(char in)
{
	char out = ((char_in & 0x01) << 1 |
				((char_in & 0x01) << 7) |
				((char_in & 0x02) << 1) |
				((char_in & 0x02) << 3) |
				((char_in & 0x04) << 1) |
				((char_in & 0x04) << 3) |
				((char_in & 0x08) >> 3) |
				((char_in & 0x08) << 3);
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

char SDES_P4(char in)
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
	char left_nibble_row = (left_nibble_start & 0x01) | ((left_nibble_start & 0x8) << 2);
	char left_nibble_col = ((left_nibble_start & 0x02) >> 1) | ((left_nibble_start & 0x04) >> 1);
	
	char right_nibble_start = in >> 4;
	char right_nibble_row = (in & 0x01) | ((in & 0x8) << 2);
	char right_nibble_col = ((in & 0x02) >> 1) | ((in & 0x04) >> 1);
	
	
	out = (s0[left_nibble_row][left_nibble_col] & 0x3) | ((s1[right_nibble_row][right_nibble_col] & 0x3) << 2);
	
	return out;
}


SDES_Encrypt(char plain_text, SDES_KEYS keys)
{

	char initial_permuation_out = SDES_IP(plain_text);
	// perform E/P on right four bits of IP.
	char ep_out = EP(initial_permutation_out);
	
	char k1_ep_xor_out = keys.key_1 ^ ep_out;
	char sbox_out = SDES_SBOXES(k1_ep_xor_out);
	char sdes_p4_out = SDES_P4(sbox_out);
	char xor_ip_left_nibble_with_p4 = sdes_p4_out ^ (initial_permuation_out & 0x0F);
	char combine_ip_right_nibble_with_above = (initial_permuation_out & 0xF0) >> 4) | (xor_ip_left_nibble_with_p4 << 4);
	char swap_two_halves = ((combine_ip_right_nibble_with_above & 0xF0) >> 4) | ((combine_ip_right_nibble_with_above & 0x0F) << 4);
	char ep_of_right_nibble_swap = SDES_EP((swap_two_halves & 0xF0) >> 4);
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