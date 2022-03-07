#include "LogFile.h"

int main() {
	tesla::LogFile log_file("temfile");

	std::string log = "log log log log log";
	
	log_file.persist(log.c_str(), log.size());
	log_file.flush();

	return 0;
}
