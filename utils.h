#ifndef UTILS_H
#define UTILS_H

void clearInputBuffer(void);

int getInt(const char *prompt);
int getIntInRange(const char *prompt, int min, int max);
float getFloat(const char *prompt);
void pauseScreen(void);

#endif