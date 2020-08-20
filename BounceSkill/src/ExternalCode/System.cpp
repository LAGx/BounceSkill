#include "System.h"
#include "TimeValue.h"

namespace rofle {

	std::chrono::time_point<std::chrono::steady_clock> GetTimeNow() {
		return std::chrono::high_resolution_clock::now();
	}

	DeltaTimeValue GetDeltaToNow(const std::chrono::time_point<std::chrono::steady_clock>& past) {
		return DeltaTimeValue::Microseconds<i64>(std::chrono::duration_cast<std::chrono::microseconds>(GetTimeNow() - past).count());
	}

	DeltaTimeValue GetDeltaTime(const std::chrono::time_point<std::chrono::steady_clock>& future, const std::chrono::time_point<std::chrono::steady_clock>& past) {
		return DeltaTimeValue::Microseconds<i64>(std::chrono::duration_cast<std::chrono::microseconds>(future - past).count());
	}

	void SleepThread(const DeltaTimeValue& delta) {
		std::this_thread::sleep_for(std::chrono::microseconds(delta.GetMicroseconds<i64>()));
	}

	hash_t GetPathHash(const std::filesystem::path& input)
	{
		auto absolutePath = std::filesystem::absolute(input);
		hash_t readyHash = std::hash<std::string>{}(absolutePath.string());
		return readyHash;
	}

};