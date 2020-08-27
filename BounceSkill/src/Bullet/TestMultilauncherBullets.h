#pragma once
#include <vector>
#include <thread>

class TestMultilauncherBullets {
public:
	void init();
	void cleanup();

	void launcher(int i);

private:
	const static unsigned int threadsAmount;
	const static unsigned int bulletPerThreadAmount;
	std::vector<std::thread> threads;

};