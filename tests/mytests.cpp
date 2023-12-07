#include <gtest/gtest.h>
#include <stdio.h>
#include "iostream"
#include <string>

#include "../BEJDecoder.c"
#include "../getFromDictionary.c"

using namespace std;


TEST(entryTest, firstElementTest){
    FILE* file;
    fopen_s(&file, "C:/Users/Nazar/Documents/BEJ/DSP8010_2023_1/dictionaries/Memory_v1.bin", "rb");
    entryData* data = getEntry(file, 12, 1);
    EXPECT_EQ(data[0].nameLength, 7);
    EXPECT_EQ(data[0].sequence, 0);
    EXPECT_EQ(data[0].format, 0);
    EXPECT_EQ(data[0].flags, 0);
    EXPECT_EQ(data[0].childCount, 74);
    EXPECT_EQ(data[0].childPointerOffset, 22);
    EXPECT_EQ(data[0].nameOffset, 3782);
    fclose(file);
    free(data);
}

TEST(entryTest, childElementTest){
    FILE* file;
    fopen_s(&file, "C:/Users/Nazar/Documents/BEJ/DSP8010_2023_1/dictionaries/Memory_v1.bin", "rb");
    cout << "test begin" << endl;
    entryData* data = getEntry(file, 12, 1);
    entryData* childEntry = getEntry(file, data[0].childPointerOffset, data[0].childCount);
    EXPECT_EQ(childEntry[0].nameLength, 8);
    EXPECT_EQ(childEntry[0].format, 0);
    EXPECT_EQ(childEntry[0].sequence, 0);
    EXPECT_EQ(childEntry[0].flags, 0);
    EXPECT_EQ(childEntry[0].childCount, 13);
    EXPECT_EQ(childEntry[0].childPointerOffset, 762);
    cout << "Name0 is ";
    char* nameZero = getName(childEntry[0].sequence, childEntry, file);
    for(int i = 0; i < childEntry[0].nameLength-1; i++){
      cout << nameZero[i];
    }
    cout << endl;

    EXPECT_EQ(childEntry[1].nameLength, 17);
    EXPECT_EQ(childEntry[1].sequence, 1);
    EXPECT_EQ(childEntry[1].format, 1);
    EXPECT_EQ(childEntry[1].flags, 2);
    EXPECT_EQ(childEntry[1].childCount, 1);
    EXPECT_EQ(childEntry[1].childPointerOffset, 892);
    cout << "Name1 is ";
    char* nameOne = getName(childEntry[1].sequence, childEntry, file);
    for(int i = 0; i < childEntry[1].nameLength-1; i++){
      cout << nameOne[i];
    }
    cout << endl;

    EXPECT_EQ(childEntry[11].nameLength,17);
    EXPECT_EQ(childEntry[11].sequence, 11);
    EXPECT_EQ(childEntry[11].format, 5);
    EXPECT_EQ(childEntry[11].flags,6);
    EXPECT_EQ(childEntry[11].childCount, 0);
    EXPECT_EQ(childEntry[11].childPointerOffset, 0);
    cout << "Name11 is ";
    char* nameEleven = getName(childEntry[11].sequence, childEntry, file);
    for(int i = 0; i < childEntry[11].nameLength-1; i++){
      cout << nameEleven[i];
    }
    cout << endl;
    fclose(file);
    free(data);
    free(childEntry);
}

TEST(decoderTest, tupleSeparaion){
  FILE* file;
  fopen_s(&file, "C:/Users/Nazar/Documents/BEJ/RDE-Dictionary/example.bin", "rb");
  bejTuple* res = separateInTuples(file, 7, 0);

  EXPECT_EQ(res[0].format, 0);
  EXPECT_EQ(res[0].sequence, 0);
  EXPECT_EQ(res[0].length, 63);
  //ASSERT_EQ((long long)res[0].children, 0);

  EXPECT_EQ(((bejTuple*)res[0].children)[0].format, 3);
  EXPECT_EQ(((bejTuple*)res[0].children)[1].format, 3);
  EXPECT_EQ(((bejTuple*)res[0].children)[2].format, 1);
  EXPECT_EQ(((bejTuple*)res[0].children)[3].format, 4);
  EXPECT_EQ(((bejTuple*)res[0].children)[4].format, 0);

  EXPECT_EQ(((bejTuple*)res[0].children)[0].sequence, 8);
  EXPECT_EQ(((bejTuple*)res[0].children)[1].sequence,10);
  EXPECT_EQ(((bejTuple*)res[0].children)[2].sequence, 2);
  EXPECT_EQ(((bejTuple*)res[0].children)[3].sequence, 18);
  EXPECT_EQ(((bejTuple*)res[0].children)[4].sequence, 38);

  EXPECT_EQ(((bejTuple*)res[0].children)[0].length, 3);
  EXPECT_EQ(((bejTuple*)res[0].children)[1].length, 1);
  EXPECT_EQ(((bejTuple*)res[0].children)[2].length, 10);
  EXPECT_EQ(((bejTuple*)res[0].children)[3].length, 2);
  EXPECT_EQ(((bejTuple*)res[0].children)[4].length, 14);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}