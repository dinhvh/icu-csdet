## icu-csdet ##

A charset detection engine library, extracted from ICU.

See [ICU documentation about charset detection](http://userguide.icu-project.org/conversion/detection)

```
#include <icu-ucsdet/icu-ucsdet.h>

int main(int argc, char ** argv)
{
	char * input_data;
	size_t input_data_size;
	icu_csdet * det;
	icu_csmatch * match;
	const char * charset;
	
	// read data from file.
	
	det = icu_csdet_new();
	icu_csdet_set_text(det, input_data, input_data_size);
	match = icu_csdet_detect(icu_csdet * det);
	// check result.
	
	charset = icu_csmatch_get_name(icu_csmatch * match);
	printf("charset is: %s\n", charset);
	icu_csdet_free(det);
}
```

## Building ##

```
cd /path/to/icu-csdet
mkdir build
cd build
cmake ..
make
```

## License ##

icu-csdet is licensed under ICU License.

<blockquote>
ICU is released under a nonrestrictive [open source license](http://source.icu-project.org/repos/icu/icu/trunk/license.html) that is suitable for use with both commercial software and with other open source or free software.
</blockquote>
