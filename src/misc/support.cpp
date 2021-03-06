/*
 *  Copyright (C) 2002-2017  The DOSBox Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 *  Wengier: LFN and LPT support
 */


#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cctype>
#include <string>
#include "dosbox.h"
#include "debug.h"
#include "support.h"
#include "video.h"
#include "cross.h"
#include "jega.h"


void upcase(std::string &str) {
	int (*tf)(int) = std::toupper;
	std::transform(str.begin(), str.end(), str.begin(), tf);
}

void lowcase(std::string &str) {
	int (*tf)(int) = std::tolower;
	std::transform(str.begin(), str.end(), str.begin(), tf);
}
  

/* 
	Ripped some source from freedos for this one.

*/


/*
 * replaces all instances of character o with character c
 */


void strreplace(char * str,char o,char n) {
	while (*str) {
		if (*str==o) *str=n;
		str++;
	}
}
char *ltrim(char *str) { 
	while (*str && isspace(*reinterpret_cast<unsigned char*>(str))) str++;
	return str;
}

char *rtrim(char *str) {
	char *p;
	p = strchr(str, '\0');
	while (--p >= str && *reinterpret_cast<unsigned char*>(p) != '\f' && isspace(*reinterpret_cast<unsigned char*>(p))) {};
	p[1] = '\0';
	return str;
}

char *trim(char *str) {
	return ltrim(rtrim(str));
}

char * upcase(char * str) {
    //for (char* idx = str; *idx ; idx++) *idx = toupper(*reinterpret_cast<unsigned char*>(idx));
	bool flag = false;
	Bit8u *pt = (Bit8u *)str;
	while(*pt != '\0') {
		if(flag) {
			flag = false;
		} else {
			if(isKanji1(*pt)) {
				flag = true;
			} else {
				*pt = toupper(*pt);
			}
		}
		pt++;
	}
    return str;
}

char * lowcase(char * str) {
	//for(char* idx = str; *idx ; idx++)  *idx = tolower(*reinterpret_cast<unsigned char*>(idx));
	bool flag = false;
	Bit8u *pt = (Bit8u *)str;
	while(*pt != '\0') {
		if(flag) {
			flag = false;
		} else {
			if(isKanji1(*pt)) {
				flag = true;
			} else {
				*pt = tolower(*pt);
			}
		}
		pt++;
	}
	return str;
}



bool ScanCMDBool(char * cmd,char const * const check) {
	char * scan=cmd;size_t c_len=strlen(check);
	while ((scan=strchr(scan,'/'))) {
		/* found a / now see behind it */
		scan++;
		if (strncasecmp(scan,check,c_len)==0 && (scan[c_len]==' ' || scan[c_len]=='\t' || scan[c_len]=='/' || scan[c_len]==0)) {
		/* Found a math now remove it from the string */
			memmove(scan-1,scan+c_len,strlen(scan+c_len)+1);
			trim(scan-1);
			return true;
		}
	}
	return false;
}

/* This scans the command line for a remaining switch and reports it else returns 0*/
char * ScanCMDRemain(char * cmd) {
	char * scan,*found;;
	if ((scan=found=strchr(cmd,'/'))) {
		while ( *scan && !isspace(*reinterpret_cast<unsigned char*>(scan)) ) scan++;
		*scan=0;
		return found;
	} else return 0; 
}

char * StripWord(char *&line) {
	char * scan=line;
	scan=ltrim(scan);
	if (*scan=='"') {
		char * end_quote=strchr(scan+1,'"');
		if (end_quote) {
			*end_quote=0;
			line=ltrim(++end_quote);
			return (scan+1);
		}
	}
	char * begin=scan;
	for (char c = *scan ;(c = *scan);scan++) {
		if (isspace(*reinterpret_cast<unsigned char*>(&c))) {
			*scan++=0;
			break;
		}
	}
	line=scan;
	return begin;
}

char * StripArg(char *&line) {
	char * scan=line;
	int q=0;
	scan=ltrim(scan);
	char * begin=scan;
	for (char c = *scan ;(c = *scan);scan++) {
		if (*scan=='"') {
			q++;
		} else if (q/2*2==q && isspace(*reinterpret_cast<unsigned char*>(&c))) {
			*scan++=0;
			break;
		}
	}
	line=scan;
	return begin;
}

Bits ConvDecWord(char * word) {
	bool negative=false;Bitu ret=0;
	if (*word=='-') {
		negative=true;
		word++;
	}
	while (char c=*word) {
		ret*=10;
		ret+=c-'0';
		word++;
	}
	if (negative) return 0-ret;
	else return ret;
}

Bits ConvHexWord(char * word) {
	Bitu ret=0;
	while (char c=toupper(*reinterpret_cast<unsigned char*>(word))) {
		ret*=16;
		if (c>='0' && c<='9') ret+=c-'0';
		else if (c>='A' && c<='F') ret+=10+(c-'A');
		word++;
	}
	return ret;
}

double ConvDblWord(char * word) {
	return 0.0f;
}


static char buf[1024];           //greater scope as else it doesn't always gets thrown right (linux/gcc2.95)
void E_Exit(const char * format,...) {
#if C_DEBUG && C_HEAVY_DEBUG
 	DEBUG_HeavyWriteLogInstruction();
#endif
	va_list msg;
	va_start(msg,format);
	vsprintf(buf,format,msg);
	va_end(msg);
	strcat(buf,"\n");

	throw(buf);
}

#if defined(LINUX)
#include <iconv.h>

void utf8_to_sjis_copy(char *dst, const char *src, int len)
{
	iconv_t ic;
	char *psrc, *pdst;
	size_t srcsize, dstsize;
	ic = iconv_open("Shift_JIS", "UTF-8");
	psrc = (char *)src;
	pdst = dst;
	srcsize = strlen(src);
	dstsize = len;
	iconv(ic, &psrc, &srcsize, &pdst, &dstsize);
	iconv_close(ic);
	*pdst = 0;
}

void sjis_to_utf8_copy(char *dst, const char *src, int len)
{
	iconv_t ic;
	char *psrc, *pdst;
	size_t srcsize, dstsize;
	ic = iconv_open("UTF-8", "Shift_JIS");
	psrc = (char *)src;
	pdst = dst;
	srcsize = strlen(src);
	dstsize = len;
	iconv(ic, &psrc, &srcsize, &pdst, &dstsize);
	iconv_close(ic);
	*pdst = 0;
}

void sjis_to_utf16_copy(char *dst, const char *src, int len)
{
	iconv_t ic;
	char *psrc, *pdst;
	size_t srcsize, dstsize;
	ic = iconv_open("UTF-16LE", "Shift_JIS");
	psrc = (char *)src;
	pdst = dst;
	srcsize = strlen(src);
	dstsize = len;
	iconv(ic, &psrc, &srcsize, &pdst, &dstsize);
	iconv_close(ic);
	*pdst = 0;
}

void ChangeUtf8FileName(char *fullname)
{
	char *dst, *src;
	char temp[CROSS_LEN];
	sjis_to_utf8_copy(temp, fullname, CROSS_LEN);
	src = temp;
	dst = fullname;
	while(*src != '\0') {
		if(*src == (char)0xe2 && *(src + 1) == (char)0x80 && *(src + 2) == (char)0xbe) {
			*dst = '~';
			src += 2;
		} else if(*src == (char)0xc2 && *(src + 1) == (char)0xa5) {
			*dst = '/';
			src++;
		} else {
			*dst = *src;
		}
		src++;
		dst++;
	}
	*dst = 0;
}

#endif


