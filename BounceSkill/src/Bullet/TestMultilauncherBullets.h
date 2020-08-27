#pragma once
#include <vector>
#include <thread>

#define MULTILAUNCHER_THREAD_AMOUNT 4

class TestMultilauncherBullets {
public:
	void init();
	void cleanup();

	void launcher(int i);

private:
	std::vector<std::thread> threads;

};