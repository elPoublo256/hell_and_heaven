
#include "../core_files/notify.h"
#include <thread>
#include <iostream>
#include <fstream>
#include <stdio.h>
int main()
{
    hh::filesystem::INotify __inotify;
    auto wd = __inotify.add_watcher("./", hh::filesystem::CREATE);
    std::cout << "create whatcher "<<wd<<std::endl;
    auto f = [](inotify_event ev){ std::cout << "get event in whatcher:" <<ev.wd<<std::endl;
                                    std::cout << "mask "<<ev.mask << std::endl;
                                    std::cout << "name :"<<ev.name << std::endl<<std::endl;};

    auto t_ptr = __inotify.read_in_thread_backcall(f);
    std::ofstream of("./test.txt");
    of << "qwerty";
    of.close();
    auto wd1 = __inotify.add_watcher("./test.txt", hh::filesystem::DELETE);

    std::ofstream of2("./test2.txt");
    of2 << "qwerty";
    of2.close();


    //t_ptr->join();
    //t_ptr = __inotify.read_in_thread_backcall(f);
    remove("./test.txt");
    remove("./test2.txt");
    //t_ptr = std::shared_ptr<std::thread>();
    return 0;
}
