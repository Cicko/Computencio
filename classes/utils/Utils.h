#ifndef _UTILS_H_
#define _UTILS_H_



string intToString(int num) {
  return static_cast<ostringstream*>( &(ostringstream() << num) )->str();
}

float noise(int x, int y) {
    int n = x + y * 57;
    n = (n << 13) ^ n;
    return (1.0 - ((n * ((n * n * 15731) + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}




#endif
