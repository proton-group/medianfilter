#include "BitmapPlusPlus.hpp"
#include "medianfilter.hpp"
#include <sstream>
#include <gtest/gtest.h>

bmp::Bitmap image_create()
{
    bmp::Bitmap image(3, 3);
    bmp::Pixel point1 {std::uint8_t(1), std::uint8_t(1), std::uint8_t(1)};
    bmp::Pixel point2 {std::uint8_t(2), std::uint8_t(3), std::uint8_t(4)};
    image.Set(0,0, point2);
    image.Set(0,1, point2);
    image.Set(0,2, point2);
    image.Set(1,0, point2);
    image.Set(1,1, point1);
    image.Set(1,2, point2);
    image.Set(2,0, point2);
    image.Set(2,1, point2);
    image.Set(2,2, point2);
    return image;
}

TEST(Filter, Algorithm)
{   
    bmp::Bitmap image = image_create();
    bmp::Bitmap newImage = medianfilter_from_image(image, 3, 1);
    ASSERT_EQ(newImage.Get(1,1).r, 2);
    ASSERT_EQ(newImage.Get(1,1).g, 3);
    ASSERT_EQ(newImage.Get(1,1).b, 4);
    newImage = medianfilter_from_image(image, 3, 0);
    ASSERT_EQ(newImage.Get(1,1).r, 1);
    try
    {
        newImage = medianfilter_from_image(image, 3, -1);
    }
    catch(WrongRange &)
    {
        std::cout << "OK: Exception catch." << '\n';
    }
    
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}