#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
  setenv("TZ", "/usr/share/zoneinfo/UTC", 1);
  unsigned n;
  scanf("%u", &n);
  while (n--) {
    struct tm time;
    unsigned width;
    scanf("%u%d%d%d%d%d%d", &width, &time.tm_year, &time.tm_mon, &time.tm_mday, &time.tm_hour, &time.tm_min, &time.tm_sec);
    time.tm_year -= 1900;
    time.tm_mon--;
    time.tm_isdst = 0;
    time_t timer = mktime(&time) + ((1U << (width - 1)) - 1);
    struct tm* end = localtime(&timer);
    printf("%d %d %d %d %d %d\n", end->tm_year + 1900, end->tm_mon + 1, end->tm_mday, end->tm_hour, end->tm_min, end->tm_sec);
  }
  return 0;
}
