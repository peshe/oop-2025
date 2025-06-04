//// std::ifstream -> Input File Stream
//// std::ofstream -> Output File Stream
//// std::fstream -> File Stream
////
//// std::ios::app -> отива в края на файла преди всяко писане
//// std::ios::in -> отваря за четене
//// std::ios::out -> отваря за писане
//// std::ios::trunc -> изтрива съдържанието на файла при отваряне
//// std::ios::ate -> отива в края на файла след отваряне
////
//// >> - оператор за четене до whitespace (' ', '\n', '\t') (като std::cin)
//// << - оператор за писане (като std::cout)
//// getline() - четене до нов ред
//// 
//// tellg() -> коя е позицията от която ще четем (кой байт)
//// seekg() -> сетваме позицията от която ще четем
//// 
//// tellp() -> коя е позицията на която ще пишем (кой байт)
//// seekp() -> сетваме позицията на която ще пишем
////
//// можем да слагаме потоци в условията на if/while и подобни
//// good() -> казва дали всичко е ОК
//// eof() -> казва дали сме в края на файла
//// fail() -> има грешка, ама може да се възстанови от нея
//// bad() -> има грешка, ама тя е фатална
//// 
//
////std::fstream file;
////file.open("zdr.txt", std::ios::out | std::ios::app);
//
////file << "Hello, World!" << std::endl;
//
////file.close();
//
//std::fstream file2;
//file2.open("zdr.txt", std::ios::in);
//file2.seekg(16);
//
//char buff[1024];
//
//std::cout << file2.tellg() << std::endl; // 0
//file2 >> buff;
//std::cout << buff << std::endl;
//
//std::cout << file2.tellg() << std::endl; // 8
//
//file2 >> buff;
//std::cout << buff << std::endl;
//
//std::cout << file2.tellg() << std::endl; // 16
//
//file2.seekg(0);
//while (file2.getline(buff, 1023)) {
//	std::cout << buff << std::endl;
//}
//
//file2.close();
//file2.open("zdr.txt", std::ios::in);
//
//file2.seekg(0);
//
//std::cout << "Curr: " << file2.tellg() << std::endl;
//file2 >> buff;
//std::cout << buff << std::endl;
//
//std::cout << "Curr: " << file2.tellg() << std::endl;
//file2.getline(buff, 1023);
//std::cout << "'" << buff << "'" << std::endl;
//
//std::cout << "Curr: " << file2.tellg() << std::endl;
//file2.getline(buff, 1023);
//std::cout << "'" << buff << "'" << std::endl;
//
//file2.close();
