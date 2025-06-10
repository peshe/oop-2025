#include "filesystem.h"
#include "regularfile.h"

#include <exception>
#include <iostream>

int main() {
  try {
    Directory &rootDir{*new Directory{}};
    RegularFile &foo{*new RegularFile{"foo.txt", 10}};
    RegularFile &bar{*new RegularFile{"bar.jpg", 1000, false, false, true}};
    RegularFile &baz{*new RegularFile{"baz.xxx", 666, true, false, false}};
    rootDir += foo;
    rootDir += bar;
    rootDir += baz;
    rootDir += "quux";
    Directory &user{*new Directory{"user", false, false, false, false}};
    RegularFile &important{
        *new RegularFile{"important.md", 234, false, false, true, true}};
    user += important;
    rootDir += user;
    Directory &config{*new Directory{"config", false, true, false, false}};
    RegularFile &donottouch{
        *new RegularFile{"donottouch.cfg", 50, false, true, false, true}};
    RegularFile &systemConf{
        *new RegularFile{"system.conf", 60, false, true, false, false}};
    RegularFile &networkConf{
        *new RegularFile{"network.conf", 70, false, true, true, false}};
    config += donottouch;
    config += systemConf;
    config += networkConf;
    rootDir += config;

    Filesystem fs{rootDir};
    std::cout << "Root directory:" << std::endl;
    fs.getRootDir().print();
    std::cout << "Current directory:" << std::endl;
    fs.getCurrentDir().print();
    fs.chdir("config");
    fs.getCurrentDir().print();
  } catch (const std::exception &e) {
    std::cerr << "error: " << e.what() << std::endl;
  }

  return 0;
}