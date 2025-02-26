// Don't forget to `delete[]` the result when you're done with it!
char* concatAll(const char** stringArray, size_t arraySize) {
  size_t resultSize = 1;
  for (size_t i = 0; i < arraySize; ++i) {
    resultSize += strlen(stringArray[i]);
  }

  char* result = new char[resultSize];
  result[0] = '\0';

  for (size_t i = 0; i < arraySize; ++i) {
    strcat(result, stringArray[i]);
  }
  return result;
}

void task2() {
  const char* stringArray[] = {"Hello", ",", " ", "World", "!"};
  size_t arraySize = sizeof(stringArray) / sizeof(stringArray[0]);

  char* allConcatenated = concatAll(stringArray, arraySize);
  cout << allConcatenated << endl;
  delete[] allConcatenated;
}
