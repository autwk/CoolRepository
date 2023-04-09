#include "cstring.h"

size_t Strlen(const char* str) {
  size_t len = 0;
  while (*str != 0) {
    ++len;
    ++str;
  }

  return len;
}

int Strcmp(const char* first, const char* second) {
  while ((*first == *second) && (*first != 0) && (*second != 0)) {
    ++first;
    ++second;
  }

  return *first - *second;
}

int Strncmp(const char* first, const char* second, size_t count) {
  while ((count > 0) && (*first == *second) && (*first != 0) && (*second != 0)) {
    ++first;
    ++second;
    --count;
  }

  return ((count != 0) ? *first - *second : 0);
}

char* Strcpy(char* dest, const char* src) {
  char* ptr = dest;
  while (*src != 0) {
    *ptr = *src;
    ++ptr;
    ++src;
  }

  *ptr = '\0';
  return dest;
}

char* Strncpy(char* dest, const char* src, size_t count) {
  char* ptr = dest;
  while (*src != 0 && (count != 0)) {
    *ptr = *src;
    ++ptr;
    ++src;
    --count;
  }

  while (count > 0) {
    *ptr = '\0';
    ++ptr;
    --count;
  }

  return dest;
}

char* Strcat(char* dest, const char* src) {
  int desl = Strlen(dest);
  int srcl = Strlen(src);

  for (int i = desl; i < desl + srcl; ++i) {
    dest[i] = src[i - desl];
  }

  return dest;
}

char* Strncat(char* dest, const char* src, size_t count) {
  int desl = Strlen(dest);
  int srcl = Strlen(src);
  int k = count;

  if (k > srcl) {
    return Strcat(dest, src);
  }

  for (int i = desl; i < desl + k; ++i) {
    dest[i] = src[i - desl];
  }

  return dest;
}

const char* Strchr(const char* str, char symbol) {
  while ((*str != symbol) && (*str != 0)) {
    ++str;
  }

  return ((*str == symbol) ? str : nullptr);
}

const char* Strrchr(const char* str, char symbol) {
  const char* ptr = nullptr;
  while (*str != 0) {
    if (*str == symbol) {
      ptr = str;
    }

    ++str;
  }

  return ((symbol == '\0') ? str : ptr);
}

size_t Strspn(const char* dest, const char* src) {
  size_t count = 0;
  while (*dest != 0) {
    const char* ptr = src;
    while (*ptr != *dest && *ptr != 0) {
      ++ptr;
    }

    if (*ptr == 0) {
      return count;
    }
    ++count;
    ++dest;
  }
  return count;
}

size_t Strcspn(const char* dest, const char* src) {
  size_t count = 0;
  while (*dest != 0) {
    const char* ptr = src;
    while (*ptr != *dest && *ptr != 0) {
      ++ptr;
    }

    if (*ptr != 0) {
      return count;
    }
    ++count;
    ++dest;
  }
  return count;
}

const char* Strpbrk(const char* dest, const char* breakset) {
  while (*dest != 0) {
    const char* ptr = breakset;
    while (*ptr != *dest && *ptr != 0) {
      ++ptr;
    }

    if (*ptr != 0) {
      return dest;
    }
    ++dest;
  }
  return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
  int strl = Strlen(str);
  int patl = Strlen(pattern);

  for (int i = 0; i <= strl - patl; ++i) {
    int j = 0;

    while ((j < patl) && (str[i + j] == pattern[j])) {
      ++j;
    }

    if (j == patl) {
      return &str[i];
    }
  }

  return nullptr;
}