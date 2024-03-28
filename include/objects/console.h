#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <deque>
#include <raylib.h>

#include <thread>
#include <atomic>

#define WIDTH 80
#define HEIGHT 25

#define PIXEL_WIDTH 720
#define PIXEL_HEIGHT 400


struct ConsoleScreen
{
    char data[HEIGHT][WIDTH];
};

class ConsoleBuffer : public std::stringbuf
{
    std::atomic<bool> threadRunning = false;

    std::atomic<bool> threadFree = true;

    std::atomic<bool> init = false;

    std::deque<char> threadString;

    std::deque<std::string> lineBuffer;

    void NewLine();

    void NewLineClear();

    static void SyncThread(ConsoleBuffer *ptr);

    std::thread consoleSyncThread;

public:

    ~ConsoleBuffer()
    {
        if(threadRunning)
        {
            threadRunning = false;
            consoleSyncThread.join();
        }
    }

    virtual int sync();

    ConsoleScreen GetScreen();
};

class Console
{
public:
    void Init();
    void Render(Color fontColor = WHITE, Color fontPaperColor = BLACK, Color bgColor = BLANK);
    void Draw();
    std::ostream& GetStream();

private:
    
    Rectangle get_glyph(unsigned char code);
    Texture2D font;
    ConsoleBuffer buffer;
    std::ostream stream = std::ostream(&buffer);
    std::deque<std::string> screenBuffer;
    RenderTexture2D renderTexture;
};