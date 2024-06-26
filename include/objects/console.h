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

#define PIXEL_WIDTH 1280
#define PIXEL_HEIGHT 800


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

    virtual int sync() override;
    
    ConsoleScreen GetScreen();
};

class Console
{
public:
    void Init();
    void Render(Color fontColor = WHITE, Color fontPaperColor = BLACK, Color bgColor = BLANK);
    void Draw();
    void Draw(Rectangle dst);
    void Draw(float marginX, float marginY);
    std::ostream& GetStream();

public:
    
    Rectangle get_glyph(unsigned char code);
    Texture2D font;
    //static ConsoleBuffer buffer;
    //std::ostream stream = std::ostream(&buffer);
    std::deque<std::string> screenBuffer;
    RenderTexture2D renderTexture;
};

#include <string>
#include "core/program.h"
#include "objects/console.h"
#include "graphics/transition.h"
#include "objects/commandproc.h"

class Terminal : public Program
{
public:
    Terminal(CommandProcessor *command);
    Terminal() {cmd = new CommandProcessor; };
    ~Terminal() { if(cmd) delete cmd; };
    void Init() override;
    void Update(float deltaTime) override;
    void SoftRender() override;
    void Render() override;

    FadeTransition trans = FadeTransition(0.5f, DARKBLUE);

    bool FadeIn() override { return trans.FadeIn(); };
    bool FadeOut() override { return trans.FadeOut(); };


    Console console;
    CommandProcessor* cmd = nullptr;
};