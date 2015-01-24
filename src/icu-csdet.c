#include "icu-csdet.h"

#include "unicode/ucsdet.h"

#include <stdlib.h>
#include <string.h>
#include <pthread.h>

icu_csdet * icu_csdet_new(void)
{
  UErrorCode err = U_ZERO_ERROR;
  UCharsetDetector * det = ucsdet_open(&err);
  if (err != U_ZERO_ERROR) {
    return NULL;
  }
  return (icu_csdet *) det;
}

void icu_csdet_free(icu_csdet * det)
{
  ucsdet_close((UCharsetDetector *) det);
}

void icu_csdet_set_text(icu_csdet * det, const char * text, ssize_t len)
{
  UErrorCode err = U_ZERO_ERROR;
  ucsdet_setText((UCharsetDetector *) det, text, len, &err);
}

int icu_csdet_is_input_filter_enabled(icu_csdet * det)
{
  return ucsdet_isInputFilterEnabled((UCharsetDetector *) det);
}

void ucsdet_set_input_filter_enabled(icu_csdet * det, int enabled)
{
  ucsdet_enableInputFilter((UCharsetDetector *) det, enabled);
}

icu_csmatch * icu_csdet_detect(icu_csdet * det)
{
  UErrorCode err = U_ZERO_ERROR;
  return (icu_csmatch *) ucsdet_detect((UCharsetDetector *) det, &err);
}
    
void icu_csdet_detect_all(icu_csdet * det, icu_csmatch *** p_matches, unsigned int * p_count)
{
  UErrorCode err = U_ZERO_ERROR;
  int32_t matchesCount = 0;
  icu_csmatch ** matches = (icu_csmatch **) ucsdet_detectAll((UCharsetDetector *) det, &matchesCount, &err);
  * p_count = matchesCount;
  * p_matches = matches;
}

const char * icu_csmatch_get_name(icu_csmatch * match)
{
  UErrorCode err = U_ZERO_ERROR;
  return ucsdet_getName((const UCharsetMatch *) match, &err);
}

unsigned int icu_csmatch_get_confidence(icu_csmatch * match)
{
  UErrorCode err = U_ZERO_ERROR;
  return (unsigned int) ucsdet_getConfidence((const UCharsetMatch *) match, &err);
}

const char * icu_csmatch_get_language(icu_csmatch * match)
{
  UErrorCode err = U_ZERO_ERROR;
  return ucsdet_getLanguage((const UCharsetMatch *) match, &err);
}

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static char ** charsets = NULL;
static unsigned int charsets_count = 0;

void icu_csdet_get_all_detectable_charsets(const char *** p_charsets, unsigned int * p_count)
{
  pthread_mutex_lock(&lock);
  if (charsets == NULL) {
    UCharsetDetector * detector;
    UEnumeration * iterator;
    UErrorCode err = U_ZERO_ERROR;
    unsigned int count;
    
    detector = ucsdet_open(&err);

    charsets_count = 0;
    iterator = ucsdet_getAllDetectableCharsets(detector, &err);
    while (1) {
        const char * validCharset = uenum_next(iterator, NULL, &err);
        if (err != U_ZERO_ERROR)
            break;
        if (validCharset == NULL)
            break;
        charsets_count ++;
    }
    uenum_close(iterator);
    
    charsets = malloc(sizeof(* charsets) * charsets_count);
    
    count = 0;
    iterator = ucsdet_getAllDetectableCharsets(detector, &err);
    while (1) {
        const char * validCharset = uenum_next(iterator, NULL, &err);
        if (err != U_ZERO_ERROR)
            break;
        if (validCharset == NULL)
            break;
        charsets[count] = strdup(validCharset);
        count ++;
    }
    uenum_close(iterator);

    ucsdet_close(detector);
  }
  pthread_mutex_unlock(&lock);
  
  * p_charsets = (const char **) charsets;
  * p_count = charsets_count;
}
