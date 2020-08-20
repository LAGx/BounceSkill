#pragma once
#include "TimeValue.h"
#include "NumberCircle.h"

namespace rofle {

	typedef f64 FPS;

	class FPSController {
	public:
		FPSController();
		void setTargetFPS(FPS);
		FPS getSmoothFPS();
		DeltaTimeValue getFrameDelta();
		void seek();

	private:

		FPS deltaToFPS(DeltaTimeValue);
		DeltaTimeValue FPSToDelta(FPS);

		DeltaTimeValue targetDelta;
		DeltaTimeValue payloadDeltaTime;
		DeltaTimeValue summaryDelta;

		std::chrono::time_point<std::chrono::steady_clock> lastTime;

		NumberCircle<FPS, 20> smoothFps;
	};

}