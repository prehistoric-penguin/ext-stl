#pragma once
#include <chrono>
#include <iomanip>

class ostream;
class StopWatch {
  using ClockType = std::chrono::high_resolution_clock;
  using TimePoint = std::chrono::time_point<ClockType>;
  using ElapseType = std::common_type<typename ClockType::duration,
                                      typename ClockType::duration>::type;

 public:
  StopWatch() { Restart(); };
  void Stop() { end_ = ClockType::now(); }
  void Restart() { start_ = ClockType::now(); }
  ElapseType GetElapse() { return end_ - start_; }
  std::ostream& PrintElapse(std::ostream& os) {
    using MicroSecond = std::chrono::microseconds;
    uint64_t micro_secnds =
        std::chrono::duration_cast<MicroSecond>(GetElapse()).count();
    os.setf(std::ios_base::fixed, std::ios_base::floatfield);
    if (micro_secnds > 100) {
      os << std::setprecision(1) << micro_secnds / 1000.0 << "ms";
    } else {
      os << micro_secnds << "us";
    }
    return os;
  }

  friend std::ostream& operator<<(std::ostream& os, StopWatch& sw) {
    return sw.PrintElapse(os);
  }

 private:
  TimePoint start_;
  TimePoint end_;
};

