#include "notify.h"
#include "../hh_exceptions/hh_exceptions.h"



hh::filesystem::INotify::INotify() : BaseFD<int>()
{
    __fd = inotify_init();
    if(__fd == -1)
    {
        throw ErrnoException();
    }

}

int hh::filesystem::INotify::add_watcher(const std::string &fialename,
                                     unsigned int masck)
{
 int whatcher_fd = inotify_add_watch(this->__fd,
                                     fialename.c_str(), masck);
 if(whatcher_fd < 0)
 {
     throw ErrnoException();
 }
 else
 {
     __map_watchers_fd.insert(std::pair<int, INotifyWatcher>
     {whatcher_fd, INotifyWatcher(whatcher_fd, masck)
                                           });

 }

 return whatcher_fd;
}

std::list<inotify_event> hh::filesystem::INotify::read_events()
{

    auto n = __map_watchers_fd.size();
    std::size_t max_size_ev = __max_len_filename_in_event +
            sizeof(inotify_event) + 1;
    std::vector<unsigned char> buf;
    buf.resize(n * max_size_ev);

    auto s = read(__fd,buf.data(),buf.size());

    if(s < 0)
    {
        throw ErrnoException();
    }

    buf.resize(s);
    std::list<inotify_event> v;

    for(auto ptr = buf.data();
        ptr < (buf.data() + buf.size());)
    {

        inotify_event ev = *((inotify_event*) ptr);
        v.push_back(ev);
        ptr = ptr + sizeof(inotify_event) + ev.len;
    }




    return v;
}

hh::filesystem::INotifyWatcher::INotifyWatcher(const INotify &notify,
                                               const std::string &path,
                                             const unsigned int& masck)
{
    __wd = inotify_add_watch(notify.get_file_discriptror(),
                      path.c_str(),
                      masck);
    if(__wd == -1)
    {
        throw ErrnoException();
    }
    curent_mask = masck;
}

void hh::filesystem::INotify::remove_whatcher(const int &watcher_descriptor)
{
    if(inotify_rm_watch(this->__fd, watcher_descriptor) == -1)
    {
        throw ErrnoException();
    }
}



