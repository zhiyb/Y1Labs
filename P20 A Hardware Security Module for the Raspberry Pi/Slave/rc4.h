#ifndef RC4_H
#define RC4_H

class rc4
{
public:
	rc4(const char *key, const unsigned short length) {regen(key, length);}
	void regen(const char *key, const unsigned short length);
	unsigned char output(void);
	void codec(unsigned char *buff, const unsigned short length);

private:
	unsigned char i, j;
	unsigned char s[256];
};

#endif
