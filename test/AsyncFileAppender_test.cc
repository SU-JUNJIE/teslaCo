#include "Log.h"

#include <unistd.h>
#include <iostream>
#include <sys/time.h>

void bench(tesla::AsyncFileAppender& appender) {
	std::string oneKbStr("aaaaa");

	for (int i = 0; i < 1024; i++) {
		appender.append(oneKbStr);
	}
}

int main() {

	tesla::AsyncFileAppender file_appender("aaaxx");
	file_appender.start();

	bench(file_appender);
    //getchar();
    return 0;
}
