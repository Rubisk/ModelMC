#include <iostream>
#include <crtdbg.h>
#include <gtest/gtest.h>

using namespace std;

namespace testing {

class MemoryLeakDetector : public EmptyTestEventListener {
public:
  virtual void OnTestStart(const TestInfo&) {
    _CrtMemCheckpoint(&memState_);
  }

  virtual void OnTestEnd(const TestInfo& test_info) {
    if (test_info.result()->Passed()) {
      _CrtMemState stateNow, stateDiff;
      _CrtMemCheckpoint(&stateNow);
      int diffResult = _CrtMemDifference(&stateDiff, &memState_, &stateNow);
      if (diffResult) {
        FAIL() << "Memory leak of " << stateDiff.lSizes[1] << " byte(s) detected.";
      }
    }
  }

private:
  _CrtMemState memState_;
};
}

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::UnitTest::GetInstance()->listeners().Append(new testing::MemoryLeakDetector());

  RUN_ALL_TESTS();
  system("pause");
}