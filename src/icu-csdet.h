#ifndef ICU_UCSDET_H

#define ICU_UCSDET_H

#include <sys/types.h>

/** Charset detector opaque data structure. */
struct icu_csdet;
typedef struct icu_csdet icu_csdet;

/** Detected charset opaque data structure. */
struct icu_csmatch;
typedef struct icu_csmatch icu_csmatch;

/** Creates a new charset detector. */
icu_csdet * icu_csdet_new(void);

/** Destroy the charset detector. */
void icu_csdet_free(icu_csdet * det);

/** Sets the input bytes to detect. Use -1 for len if the string is null terminated. */
void icu_csdet_set_text(icu_csdet * det, const char * text, ssize_t len);

/** Returns the charset that best matches.
The returned icu_csmatch will be valid until the icu_csdet is destroyed or the input is reset. */
icu_csmatch * icu_csdet_detect(icu_csdet * det);
    
/** Returns all the charset that matches the input.
The result will be stored in (* p_matches) and the number of results in (* p_count).
The icu_csmatch will be valid until the icu_csdet is destroyed or the input is reset. */
void icu_csdet_detect_all(icu_csdet * det, icu_csmatch *** p_matches, unsigned int * p_count);

/** Returns whether HTML and XML tags should be filtered from the input before detecting the charset. */
int icu_csdet_is_input_filter_enabled(icu_csdet * det);

/** Sets whether HTML and XML tags should be filtered from the input before detecting the charset. */
void ucsdet_set_input_filter_enabled(icu_csdet * det, int enabled);

/** Returns the name of the detected charset. */
const char * icu_csmatch_get_name(icu_csmatch * match);

/** Returns the confidence of the result charset. */
unsigned int icu_csmatch_get_confidence(icu_csmatch * match);

/** Returns the detetected language of the input.
An empty string will be returned if the language could not be detected. */
const char * icu_csmatch_get_language(icu_csmatch * match);

/** Returns an array of all detected charset. The returned data should not be freed. */
void icu_csdet_get_all_detectable_charsets(const char *** p_charsets, unsigned int * p_count);

#endif

