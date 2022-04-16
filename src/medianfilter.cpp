#include "medianfilter.hpp"
#include "BitmapPlusPlus.hpp"

namespace
{
    void matrix_to_vectors(int32_t x, 
                    int32_t y, 
                    int squadSize, 
                    bmp::Bitmap image, 
                    std::vector<bmp::Pixel>& color // TODO : STRUCT FOR SORT
                    )
    {
        int cur = squadSize/2;
        color.clear();
        for(int32_t xcur = x-cur; xcur <= x+cur; ++xcur)
        {
            for(int32_t ycur = y-cur; ycur <= y+cur; ++ycur)
            {
                if(xcur >= 0 && ycur >= 0 && xcur < image.Width() && ycur < image.Height())
                {
                    color.push_back(image.Get(xcur, ycur));
                }
                else
                {
                    bmp::Pixel zero = {0,0,0};
                    color.push_back(zero);
                }
            }
        }
    }
    bool greater_red(bmp::Pixel first, bmp::Pixel second)
    {
        return first.r > second.r ? true : false;
    }

    bool greater_blue(bmp::Pixel first, bmp::Pixel second)
    {
        return first.b > second.b ? true : false;
    }

    bool greater_green(bmp::Pixel first, bmp::Pixel second)
    {
        return first.g > second.g ? true : false;
    }
}


bmp::Bitmap medianfilter_from_image(const bmp::Bitmap image, int squadSize, int radius)
{
    if(radius < 0 || squadSize*squadSize <= radius)
    {
        throw WrongRange();
    }
    bmp::Bitmap image_cpy(image);
    uint8_t cred = 0;
    uint8_t cgreen = 0; 
    uint8_t cblue = 0;
    int max = (squadSize*squadSize)/2 + radius;
    int min = (squadSize*squadSize)/2 - radius;
    std::vector<bmp::Pixel> color;
    for (int32_t y = 0; y < image_cpy.Height(); ++y)
    {
        for (int32_t x = 0; x < image_cpy.Width(); ++x)
        {
            matrix_to_vectors(x, y, squadSize, image_cpy, color);
            sort(color.begin(), color.end(), greater_red);
            cred = std::clamp(image_cpy.Get(x,y).r, color[min].r, color[max].r);
            sort(color.begin(), color.end(), greater_green);
            cgreen = std::clamp(image_cpy.Get(x,y).g, color[min].g, color[max].g);
            sort(color.begin(), color.end(), greater_blue);
            cblue = std::clamp(image_cpy.Get(x,y).b, color[min].b, color[max].b);
            image_cpy.Set(x,y, bmp::Pixel(cred, cgreen, cblue));
        }
    }
    return image_cpy;
}