# Задачи за проект

Вече нашата игра става онлайн и за целта ще са ни нужни следните функции.

1. Да се направи механизъм, който проверява цялостта на файла(дали е манипулиран или има грешки)
2. Да се реализира функции(или функция), които "криптират" и "декриптират" файл на записан World при дадена парола(това ще е администраторската). Да се имплементира при четене и при писане, тоест да не се пази некриптиран файл.
3. Да се направи структура user с парола и име, вътре в файла да може да се достъпва само след логване на определени user-и, тоест register, която дава достъп на определен потребител и login която му дава достъп да чете файла. Това трябва да се направи на ниво файл, тоест ако не е "логнат" нито един от разрешените потребители, никой файлът да е нечетим.
4. Някои мрежови протоколи изискват данните да се раздробят на chunk-ове. Получателят обикновенно ги получава в случаен ред. Да се направят следните функции:
   - Функция, която раздробява файл на малки файлчета според даден chunkSize
   - Функция, която сглобява файлчетата на един голям идващи в произволен ред.

# Задача за хората, които не правят проекта (Времева база данни)

Този тип бази данни се ползват от софтуери произвеждащи голямо количество подобни данни през фиксиран интервал примерно домашни сензори или информация за устройство на потребителя.

- За всяка от долните задача трябва да се грижите вашата памет да е изтрита и ако станат неочаквани грешки по време на изпълнението на вашата програма те да бъдат обработени, както трябва да се грижите и за правилно засичане на лоши входни даннни.
- Вие решавата с какви член данни ще запълните структурите.

1. Направете структура Файл и дефинирайте следните функции
   - `File* open(const char* filename)` - отваря файла.
   - `void close(File*& file)` - затваря файла.
   - `void readAt(File* file, size_t location, size_t bytes, char* toBeRead)` - чете на дадена локация във файла дадения брой байтове в буфера.
   - `void writeAt(File* file, size_t location, size_t bytes, char* toBeWriten)` - пише на дадена локация във дайла дадения брой байтове ot буфера.
2. Функции за валидност на файл
   - Формата на нашата файлова система е следната 6 байта `TIMEDB` след това 1 байт число за верия на файловата система, 1 байт падинг, след това 8 байта брой елементи (по-късно ще ги разгледаме) като цяло число
   - `bool validFile(File* file)` - проверява дали файла е валидна файлова система, тоест дали почва с `CFSS`, дали версията е по-малка от 1
   - `Configuration` сттруктура и функция асоцирана с нея `Configuration* createConfiguration(File* file)`
3. Функция за четене на информация

- Всеки елемент от файла съдържа следното 8 байта число и 8 байта float-number, напишете следните две функции.
- `bool readElement(File* file, size_t index, Element& element)`, чете един елемент от базата данни на дадения индекс.
- `Element* appendElement(File* file, size_t timestamp, double value)`, добавя един елемент в края на файла, замислете се дали трябва да направите нещо друго освен да апенднете в края на файла.
- Бонус задачи: Пробвайте се да имплементирате следните два алгоритъма във вашето решение [Delta compresion](https://en.wikipedia.org/wiki/Delta_encoding), [XOR compresion](https://clemenswinter.com/2024/04/07/the-simple-beauty-of-xor-floating-point-compression/)
