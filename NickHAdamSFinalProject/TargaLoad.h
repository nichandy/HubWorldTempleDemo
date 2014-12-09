#ifndef TARGALOAD_H
#define TARGALOAD_H
typedef struct
    {
        unsigned char imageTypeCode;
        short int imageWidth;
        short int imageHeight;
        unsigned char bitCount;
        unsigned char *imageData;
} TGAFILE;

class TargaLoad
{
public:
    TargaLoad();
    virtual ~TargaLoad();
    int LoadTGAFile(char *filename, TGAFILE *tgaFile);
protected:
private:
};

#endif // TARGALOAD_H
