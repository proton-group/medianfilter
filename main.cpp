#include "BitmapPlusPlus.hpp"
#include "medianfilter.hpp"

const int MINPARAM = 2;

int main(int argc, char* argv[])
{
    if(argc < MINPARAM)
    {
        return -1;
    }
    std::string buf;
    std::string data[4];
    std::ifstream in(argv[1]); // окрываем файл для чтения
    if (in.is_open())
    {
        int i = 0;
        while(std::getline(in, buf))
        {
            data[i] = buf;
            i++;
        }
    }
    in.close();
    bmp::Bitmap imagein;
    bmp::Bitmap imageout;
    imagein.Load(data[0]);
    try
    {
        imageout = medianfilter_from_image(imagein, std::stoi(data[1]), std::stoi(data[2]));
    }
    catch(WrongRange &)
    {
        std::cerr << "Wrong range data." << '\n';
        throw;
    }
    imageout.Save(data[3]);
    return 0;
}