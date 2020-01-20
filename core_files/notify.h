#pragma once

#include "psx_directory.h"
#include <sys/inotify.h>
#include <future>
#include <memory>
#include <stdarg.h>
#include <map>
#include <features.h>
#include <thread>
#include <future>
#include <functional>
namespace hh {
namespace filesystem {


enum MasckNotify
{
ACCESS =	 0x00000001,	/* File was accessed.  */
MODIFY =	 0x00000002,	/* File was modified.  */
ATTRIB =	 0x00000004,	/* Metadata changed.  */
CLOSE_WRITE =	 0x00000008,	/* Writtable file was closed.  */
CLOSE_NOWRITE = 0x00000010,	/* Unwrittable file closed.  */
CLOSE =	 (IN_CLOSE_WRITE | IN_CLOSE_NOWRITE), /* Close.  */
OPEN	 =	 0x00000020,	/* File was opened.  */
MOVED_FROM	= 0x00000040,	/* File was moved from X.  */
MOVED_TO    =  0x00000080,	/* File was moved to Y.  */
MOVE	 =	 (IN_MOVED_FROM | IN_MOVED_TO), /* Moves.  */
CREATE =	 0x00000100,	/* Subfile was created.  */
DELETE =	 0x00000200,	/* Subfile was deleted.  */
DELETE_SELF =	 0x00000400,	/* Self was deleted.  */
MOVE_SELF =	 0x00000800,	/* Self was moved.  */

UNMOUNT =	 0x00002000,	/* Backing fs was unmounted.  */
Q_OVERFLOW =	 0x00004000,	/* Event queued overflowed.  */
IGNORED =	 0x00008000,	/* File was ignored.  */

ONLYDIR =	 0x01000000,	// Only watch the path if it is a

DONT_FOLLOW	= 0x02000000,	/* Do not follow a sym link.  */
EXCL_UNLINK	= 0x04000000,	/* Exclude events on unlinked
ects.  */
MASK_ADD	 = 0x20000000,	/* Add to the mask of an already
sting watch.  */
ISDIR =	 0x40000000,	/* Event occurred against dir.  */
ONESHOT =	 0x80000000,	/* Only send event once.  */

ALL_EVENTS	= (IN_ACCESS | IN_MODIFY | IN_ATTRIB | IN_CLOSE_WRITE
              | IN_CLOSE_NOWRITE | IN_OPEN | IN_MOVED_FROM
              | IN_MOVED_TO | IN_CREATE | IN_DELETE
              | IN_DELETE_SELF | IN_MOVE_SELF)

};
class INotifyWatcher;
class INotifyEvent ;
class INotify : public hh::psx_file::BasePSXFile
{
public:
    INotify();
    /**
     * @brief add_watcher - add watcher to file/directory
     * @param fialename - file name for watching
     * @param masck
     * @return - discriptor of watching
     */
    int add_watcher(const std::string& fialename, unsigned int masck);
    auto get_num_whatchers(){return __map_watchers_file_descriptor.size();}
    //void remove_watcher(const std::string& fialename);




    /**
     * @brief read - read all events from all watchers
     * @return list of all
     */
    std::list<inotify_event> read_events();


    auto read_async_futer()
    {
        auto f = [](INotify* in){return in->read_events();};
        return std::async(f,this);
    }


    template <class  Function>
    std::shared_ptr<std::thread> read_in_thread_backcall(Function func)
    {
     return std::make_shared<std::thread>([&func](INotify* in)
     {
         for(;;)
         {         auto list_events = in->read_events();
         for(const auto& event : list_events)
         {
             func(event);
         }
         }
     },this);

    }









    INotifyWatcher& at(const int& watcher_descriptor);
    void remove_whatcher(const int& watcher_descriptor);

private:

    std::map<int, INotifyWatcher> __map_watchers_file_descriptor;
    std::size_t __max_len_filename_in_event = 256;

public:
    void set_max_len_filename_in_event(const std::size_t& max_len)
    {
        __max_len_filename_in_event = max_len;
    }

    auto get_max_len_filename_in_event(){return __max_len_filename_in_event;}


};


class INotifyWatcher
{
public:
    INotifyWatcher(const int& fd, const unsigned int& masck)
    {
        curent_mask = masck;
        __wd = fd;
    }

    INotifyWatcher(const INotify &notify,
                                   const std::string &path,
                                   const unsigned int& masck);


    void reset_mask(const unsigned int& masck);
    INotifyWatcher(const INotifyWatcher& copy)
    {
        curent_mask = copy.curent_mask;
        __wd = copy.__wd;

    }

private:
    unsigned int curent_mask;
    int __wd;


};



}
}
