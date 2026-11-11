#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "Logging/Logger.h"

using namespace lattice;

namespace {
	struct Entry {
		logging::Level level;
		logging::Category category;
		std::string msg;
	};

	// Sink that records into a vector owned by the test.
	class CaptureSink : public logging::Sink {
	public:
		explicit CaptureSink(std::vector<Entry>& out) : _out(out) {}
		void write(logging::Level level, logging::Category category, std::string_view msg, std::string_view) override
		{
			_out.push_back({ level, category, std::string(msg) });
		}
	private:
		std::vector<Entry>& _out;
	};

	// Swaps the logger's sinks for a capture sink for the duration of a test.
	class LoggerTest : public ::testing::Test {
	protected:
		void SetUp() override
		{
			Logger& logger = Logger::getInstance();
			_previousLevel = logger.getMinLevel();
			logger.clearSinks();
			logger.setMinLevel(logging::Level::Debug);
			logger.addSink(std::make_unique<CaptureSink>(entries));
		}

		void TearDown() override
		{
			Logger& logger = Logger::getInstance();
			logger.clearSinks();
			logger.setMinLevel(_previousLevel);
		}

		std::vector<Entry> entries;

	private:
		logging::Level _previousLevel = logging::Level::Info;
	};
}

// The short name must be the very same type, not a copy or a wrapper.
static_assert(std::is_same_v<lattice::Logger, lattice::logging::Logger>);

TEST(LogLevel, IsOrderedFromLeastToMostSevere)
{
	EXPECT_LT(logging::Level::Debug, logging::Level::Info);
	EXPECT_LT(logging::Level::Info, logging::Level::Warn);
	EXPECT_LT(logging::Level::Warn, logging::Level::Error);
	EXPECT_LT(logging::Level::Error, logging::Level::Critical);
}

TEST(LogToString, CoversLevelsAndCategories)
{
	EXPECT_EQ(toString(logging::Level::Debug), "DEBUG");
	EXPECT_EQ(toString(logging::Level::Critical), "CRITICAL");
	EXPECT_EQ(toString(logging::Category::Core), "CORE");
	EXPECT_EQ(toString(logging::Category::Physics), "PHYSICS");
}

TEST_F(LoggerTest, ForwardsMessagesToSinks)
{
	Logger::printMsg(logging::Level::Info, logging::Category::Renderer, "hello");

	ASSERT_EQ(entries.size(), 1u);
	EXPECT_EQ(entries[0].level, logging::Level::Info);
	EXPECT_EQ(entries[0].category, logging::Category::Renderer);
	EXPECT_EQ(entries[0].msg, "hello");
}

TEST_F(LoggerTest, FormatsArguments)
{
	LATTICE_LOG_WARN(Audio, "{} + {} = {}", 1, 2, 3);

	ASSERT_EQ(entries.size(), 1u);
	EXPECT_EQ(entries[0].level, logging::Level::Warn);
	EXPECT_EQ(entries[0].category, logging::Category::Audio);
	EXPECT_EQ(entries[0].msg, "1 + 2 = 3");
}

TEST_F(LoggerTest, DropsMessagesBelowMinimumLevel)
{
	Logger::getInstance().setMinLevel(logging::Level::Warn);

	LATTICE_LOG_DEBUG(Core, "debug");
	LATTICE_LOG_INFO(Core, "info");
	LATTICE_LOG_WARN(Core, "warn");
	LATTICE_LOG_ERROR(Core, "error");

	ASSERT_EQ(entries.size(), 2u);
	EXPECT_EQ(entries[0].msg, "warn");
	EXPECT_EQ(entries[1].msg, "error");
}

TEST_F(LoggerTest, CollapsesAndReportsConsecutiveDuplicates)
{
	Logger::printMsg(logging::Level::Info, logging::Category::Core, "same");
	Logger::printMsg(logging::Level::Info, logging::Category::Core, "same");
	Logger::printMsg(logging::Level::Info, logging::Category::Core, "same");
	Logger::printMsg(logging::Level::Info, logging::Category::Core, "other");

	ASSERT_EQ(entries.size(), 3u);
	EXPECT_EQ(entries[0].msg, "same");
	EXPECT_EQ(entries[1].msg, "[repeated 2 times] same");
	EXPECT_EQ(entries[1].level, logging::Level::Info);
	EXPECT_EQ(entries[2].msg, "other");
}

TEST_F(LoggerTest, DoesNotSwallowSameTextAtDifferentLevelOrCategory)
{
	Logger::printMsg(logging::Level::Info, logging::Category::Core, "boom");
	Logger::printMsg(logging::Level::Critical, logging::Category::Core, "boom");
	Logger::printMsg(logging::Level::Critical, logging::Category::Physics, "boom");

	ASSERT_EQ(entries.size(), 3u);
	EXPECT_EQ(entries[1].level, logging::Level::Critical);
	EXPECT_EQ(entries[2].category, logging::Category::Physics);
}

TEST_F(LoggerTest, FlushEmitsPendingRepeatCount)
{
	Logger::printMsg(logging::Level::Error, logging::Category::Core, "again");
	Logger::printMsg(logging::Level::Error, logging::Category::Core, "again");
	Logger::getInstance().flush();

	ASSERT_EQ(entries.size(), 2u);
	EXPECT_EQ(entries[1].msg, "[repeated 1 times] again");

	// After a flush, the same message is printed again instead of being counted.
	Logger::printMsg(logging::Level::Error, logging::Category::Core, "again");
	EXPECT_EQ(entries.size(), 3u);
}
