#include "tools/datapack.h"
#include <raylib.h>
#include <iostream>
#include <algorithm>
#include <string.h>

// Export data to code (.h), returns true on success
bool ExportDataAsCodeLG(const unsigned char *data, int dataSize, const char *fileName)
{
    bool success = false;

#ifndef TEXT_BYTES_PER_LINE
    #define TEXT_BYTES_PER_LINE     20
#endif

    // NOTE: Text data buffer size is estimated considering raw data size in bytes
    // and requiring 6 char bytes for every byte: "0x00, "
    char *txtData = (char *)RL_CALLOC(dataSize*6 + 2000, sizeof(char));

    int byteCount = 0;
    byteCount += sprintf(txtData + byteCount, "////////////////////////////////////////////////////////////////////////////////////////\n");
    byteCount += sprintf(txtData + byteCount, "//                                                                                    //\n");
    byteCount += sprintf(txtData + byteCount, "// DataAsCode exporter v2.0 GAMELIB - Raw data exported as an array of bytes          //\n");
    byteCount += sprintf(txtData + byteCount, "//                                                                                    //\n");
    byteCount += sprintf(txtData + byteCount, "// Copyright (c) 2022-2023 Ramon Santamaria (@raysan5)                                //\n");
    byteCount += sprintf(txtData + byteCount, "// Copyright (c) 2024 Max Fagerström                                                  //\n");
    byteCount += sprintf(txtData + byteCount, "//                                                                                    //\n");
    byteCount += sprintf(txtData + byteCount, "////////////////////////////////////////////////////////////////////////////////////////\n\n");

    // Get file name from path and convert variable name to uppercase
    char varFileName[256] = { 0 };

    std::string vfilename = GetFileName(fileName);
    std::replace( vfilename.begin(), vfilename.end(), '.', '_');
    
    strcpy(varFileName, vfilename.c_str());

    for (int i = 0; varFileName[i] != '\0'; i++) if ((varFileName[i] >= 'a') && (varFileName[i] <= 'z')) { varFileName[i] = varFileName[i] - 32; }

    byteCount += sprintf(txtData + byteCount, "#define %s_DATA_SIZE     %i\n\n", varFileName, dataSize);
    byteCount += sprintf(txtData + byteCount, "#define %s_DATA_PATH     \"%s\"\n\n", varFileName, GetFileName(fileName));

    byteCount += sprintf(txtData + byteCount, "static unsigned char %s_DATA[%s_DATA_SIZE] = { ", varFileName, varFileName);
    for (int i = 0; i < (dataSize - 1); i++) byteCount += sprintf(txtData + byteCount, ((i%TEXT_BYTES_PER_LINE == 0)? "0x%x,\n" : "0x%x, "), data[i]);
    byteCount += sprintf(txtData + byteCount, "0x%x };\n", data[dataSize - 1]);

    // NOTE: Text data size exported is determined by '\0' (NULL) character

    std::string outname;
    outname.append(fileName);
    outname.append(".inc.c");

    success = SaveFileText(outname.c_str(), txtData);

    RL_FREE(txtData);

    if (success != 0) printf("FILEIO: [%s] Data as code exported successfully", fileName);
    else printf("FILEIO: [%s] Failed to export data as code", fileName);

    return success;
}

void DisplayText(const char* text)
{
    int halfText = MeasureText(text, 20) / 2;
    DrawText(text, (GetScreenWidth() / 2) - halfText, GetScreenHeight() / 2, 20, WHITE);
}

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(600, 200, "FILE CONVERTER");
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        if(!DirectoryExists("../Data"))
        {
            std::cout << "ERROR: didnt find data dir at ../data" << std::endl;
            CloseWindow();
            return 1;
        }
        if (IsFileDropped())
        {
            FilePathList droppedFiles = LoadDroppedFiles();

            for (int i = 0; i < (int)droppedFiles.count; i++)
            {
                if(!FileExists(droppedFiles.paths[i])) 
                {
                    std::cout << "\nERROR: FILE " << droppedFiles.paths[i] << " NOT FOUND!" << std::endl;
                    continue;
                }
                int dataSize = 0;
                int cdataSize = 0;
                unsigned char* data = LoadFileData(droppedFiles.paths[i], &dataSize);
                unsigned char* cdata = CompressData(data, dataSize, &cdataSize);

                std::string outname;
                outname.append("../data/");
                outname.append(GetFileName(droppedFiles.paths[i]));

                bool ok = ExportDataAsCodeLG(cdata, cdataSize, outname.c_str());

                if(ok)
                {
                    std::cout << "\nFILE: " << outname << " PACKED OK" << std::endl;
                }
                else
                {
                    std::cout << "\nERROR: FILE: " << outname << " FAILED TO PACK!!" << std::endl;
                }

                std::cout << "SIZE ON DISK: " << dataSize << " BYTES" << std::endl;
                std::cout << "SIZE IN CODE: " << cdataSize << " BYTES" << std::endl;

                MemFree((void*)cdata);
                UnloadFileData(data);
                
            }

            UnloadDroppedFiles(droppedFiles);    // Unload filepaths from memory
        }

        BeginDrawing();
            ClearBackground(BLUE);
            DisplayText("Drop files to convert");
        EndDrawing();
    }

    CloseWindow();

}