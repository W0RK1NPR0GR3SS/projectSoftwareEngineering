#include <gtest/gtest.h>

#include "MetroNet.h"
#include "MetroNetImporter.h"
#include "MetroNetUtils.h"


class MetroNetExportTest: public ::testing::Test {
protected:
	friend class MetroNet;
	// You should make the members protected s.t. they can be
	// accessed from sub-classes.

	Tram tram;
	Station station;
  MetroNet metronet;

};

TEST_F(MetroNetExportTest, FileCompareTest) {
	ASSERT_TRUE(DirectoryExists("_testOutput"));

	std::ofstream myfile;
	myfile.open("_testOutput/file1.txt");
	myfile.close();
	myfile.open("_testOutput/file2.txt");
	myfile.close();

	EXPECT_TRUE(FileExists("_testOutput/file1.txt"));
	EXPECT_TRUE(FileExists("_testOutput/file2.txt"));
	EXPECT_TRUE(FileIsEmpty("_testOutput/file1.txt"));
	EXPECT_TRUE(FileIsEmpty("_testOutput/file2.txt"));


	//compare 2 empty files
	EXPECT_TRUE(FileCompare("_testOutput/file1.txt", "_testOutput/file2.txt"));
	EXPECT_TRUE(FileCompare("_testOutput/file2.txt", "_testOutput/file1.txt"));

	//compare an empty and a non-empty files
	myfile.open("_testOutput/file1.txt");
	myfile << "xxx" << std::endl << "yyy";
	myfile.close();
	EXPECT_TRUE(FileExists("_testOutput/file1.txt"));
	EXPECT_FALSE(FileIsEmpty("_testOutput/file1.txt"));
	EXPECT_FALSE(FileCompare("_testOutput/file1.txt", "_testOutput/file2.txt"));
	EXPECT_FALSE(FileCompare("_testOutput/file2.txt", "_testOutput/file1.txt"));

	//compare two equal files
	myfile.open("_testOutput/file2.txt");
	myfile << "xxx" << std::endl << "yyy";
	myfile.close();
	EXPECT_TRUE(FileExists("_testOutput/file2.txt"));
	EXPECT_FALSE(FileIsEmpty("_testOutput/file2.txt"));
	EXPECT_TRUE(FileCompare("_testOutput/file1.txt", "_testOutput/file2.txt"));
	EXPECT_TRUE(FileCompare("_testOutput/file2.txt", "_testOutput/file1.txt"));

	//compare 2 non-empty files which are off by a character in the middle
	myfile.open("_testOutput/file2.txt");
	myfile << "xxx" << std::endl << "xyy";
	myfile.close();
	EXPECT_FALSE(FileCompare("_testOutput/file1.txt", "_testOutput/file2.txt"));
	EXPECT_FALSE(FileCompare("_testOutput/file2.txt", "_testOutput/file1.txt"));

	//compare 2 non-empty files where one is one character shorter than the other
	myfile.open("_testOutput/file2.txt");
	myfile << "xxx" << std::endl << "yy";
	myfile.close();
	EXPECT_FALSE(FileCompare("_testOutput/file1.txt", "_testOutput/file2.txt"));
	EXPECT_FALSE(FileCompare("_testOutput/file2.txt", "_testOutput/file1.txt"));

	//compare existing against non existing file
	EXPECT_FALSE(
			FileCompare("_testOutput/file1.txt", "_testOutput/nonexisting.txt"));
	EXPECT_FALSE(
			FileCompare("_testOutput/nonexisting.txt", "_testOutput/file1.txt"));
}

TEST_F(MetroNetExportTest, OutputHappyDayTest01) {
	ASSERT_TRUE(DirectoryExists("_testOutput"));
  ASSERT_TRUE(DirectoryExists("_testInput"));
  std::ofstream errors;
  std::ofstream output;
  std::ofstream movement;
  errors.open("_testOutput/happyDay01ErrorLog.txt");
  output.open("_testOutput/happyDay01.txt");
  movement.open("_testOutput/happyDay01MovementLog.txt");
  MetroNetImporter::importMetroNet("_testInput/happyDay01.xml", errors, metronet);
  metronet.writeToOutputStream(output);
  output.close();
  errors.close();
  movement.close();
  EXPECT_TRUE(FileCompare("_testOutput/happyDay01Expected.txt", "_testOutput/happyDay01.txt"));
  EXPECT_TRUE(FileCompare("_testOutput/happyDay01MovementLogExpected.txt", "_testOutput/happyDay01MovementLog.txt"));
  EXPECT_TRUE(FileCompare("_testOutput/happyDay01ErrorLogExpected.txt", "_testOutput/happyDay01ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputHappyDayTest02) {
  ASSERT_TRUE(DirectoryExists("_testOutput"));
  ASSERT_TRUE(DirectoryExists("_testInput"));
  std::ofstream errors;
  std::ofstream output;
  std::ofstream movement;
  errors.open("_testOutput/happyDay02ErrorLog.txt");
  output.open("_testOutput/happyDay02.txt");
  movement.open("_testOutput/happyDay02MovementLog.txt");
  MetroNetImporter::importMetroNet("_testInput/happyDay02.xml", errors, metronet);
  metronet.writeToOutputStream(output);
  for (int n = 1; n <= 5; n++) {
    movement << n << ".\n";
    std::set<int> alreadyMoved;
    for (auto mapIt = metronet.getAlleStations()->begin(); mapIt != metronet.getAlleStations()->end(); mapIt++) {
      if (mapIt->second->isTramInStation() && alreadyMoved.find(mapIt->second->getSpoor()) == alreadyMoved.end()) {
        alreadyMoved.insert(mapIt->second->getSpoor());
        metronet.moveTram(mapIt->second->getVolgende(), mapIt->second->getSpoor(), movement);
        metronet.movePassengers(mapIt->second->getVolgende(), mapIt->second->getSpoor(), movement, errors);
        movement << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
      }
    }
  }
  movement.close();
  output.close();
  errors.close();
  EXPECT_TRUE(FileCompare("_testOutput/happyDay02MovementLogExpected.txt", "_testOutput/happyDay02MovementLog.txt"));
  EXPECT_TRUE(FileCompare("_testOutput/happyDay02Expected.txt", "_testOutput/happyDay02.txt"));
  EXPECT_TRUE(FileCompare("_testOutput/happyDay02ErrorLogExpected.txt", "_testOutput/happyDay02ErrorLog.txt"));


}

TEST_F(MetroNetExportTest, OutputBadDayTest01MaxCapacityExceeded) {
  ASSERT_TRUE(DirectoryExists("_testOutput"));
  ASSERT_TRUE(DirectoryExists("_testInput"));
  std::ofstream errors;
  std::ofstream output;
  std::ofstream movement;
  errors.open("_testOutput/badDay01ErrorLog.txt");
  output.open("_testOutput/badDay01.txt");
  movement.open("_testOutput/badDay01MovementLog.txt");
  MetroNetImporter::importMetroNet("_testInput/badDay01.xml", errors, metronet);
  metronet.writeToOutputStream(output);
  for (int n = 1; n <= 5; n++) {
    movement << n << ".\n";
    std::set<int> alreadyMoved;
    for (auto mapIt = metronet.getAlleStations()->begin(); mapIt != metronet.getAlleStations()->end(); mapIt++) {
      if (mapIt->second->isTramInStation() && alreadyMoved.find(mapIt->second->getSpoor()) == alreadyMoved.end()) {
        alreadyMoved.insert(mapIt->second->getSpoor());
        metronet.moveTram(mapIt->second->getVolgende(), mapIt->second->getSpoor(), movement);
        metronet.movePassengers(mapIt->second->getVolgende(), mapIt->second->getSpoor(), movement, errors);
        movement << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
      }
    }
  }
  movement.close();
  output.close();
  errors.close();
  EXPECT_TRUE(FileCompare("_testOutput/badDay01MovementLogExpected.txt", "_testOutput/badDay01MovementLog.txt"));
  EXPECT_TRUE(FileCompare("_testOutput/badDay01Expected.txt", "_testOutput/badDay01.txt"));
  EXPECT_TRUE(FileCompare("_testOutput/badDay01ErrorLogExpected.txt", "_testOutput/badDay01ErrorLog.txt"));

}

TEST_F(MetroNetExportTest, OutputBadDayTest02InsufficientPassengers) {
	ASSERT_TRUE(DirectoryExists("_testOutput"));
  ASSERT_TRUE(DirectoryExists("_testInput"));

}
