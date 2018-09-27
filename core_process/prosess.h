
#include<map>
#include <unistd.h>
#include <vector>
namespace processes
{
class Process
{
	public:
	~Process();

	void strart(std::is_function<void()> f);
    void stop();
	void delete_self();
	void run_file(std::string exe_file_name,const char* argv[]);
	void fork();
	private:
	friend class ProcessFubric;
	Process();
	int group;
	int user;
    std::vector<Process> childrens;
    Process* parent;	
};

class ProcessFubric
{
	public:
		static Process rvCreateProcess();
};


}



