#include "pch.h"
#include <cstdio>
#include <gtest/gtest.h>
#include "gtest-memleak.h"

GTEST_API_ int main(int argc, char * argv[])
{
	if ( argc > 0 )
	{
		testing::internal::FilePath arg(argv[0]);
		const auto name = arg.RemoveDirectoryName().RemoveExtension("exe").string();
		testing::GTEST_FLAG(output) = std::string("xml:") + name + ".xml";
	}
	testing::InitGoogleTest(&argc, argv);
#if defined(_MSC_VER)
	testing::UnitTest::GetInstance()->listeners().Append(new testing::MSVCMemoryLeakListener());
#endif // defined(_MSC_VER)
	return RUN_ALL_TESTS();
}
