#include "apps/app_chip8.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#define WIDTH 64
#define HEIGHT 32

namespace vaxe
{
    int vApp_Chip8::Run()
    {
        vWindow window { WIDTH * 8, HEIGHT * 8, "CHIP-8" };
        vRenderer renderer { window.GetSDLWindow(), SDL_RENDERER_ACCELERATED};
        SDL_RenderSetLogicalSize(renderer.GetRenderer(), WIDTH, HEIGHT);

        SDL_GLContext gl_context = SDL_GL_CreateContext(window.GetSDLWindow());
        SDL_GL_SetSwapInterval(0);  // Enable vsync

        vFramebuffer framebuffer {renderer.GetRenderer(), WIDTH, HEIGHT};

        InitializeValues();

        /* Loop until the user closes the window */
        while (!quit)
        {
            SDL_Event event;
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) quit = true;
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
                }
            }

            /// Emulate Cycle

            // Access Opcode
            opcode = memory[programCounter] << 8 | memory[programCounter + 1];
            printf ("pc:%x\n",programCounter);
            printf ("Executing Opcode: 0x%x\n", opcode);

            x = (opcode & 0x0F00) >> 8;
            y = (opcode & 0x00F0) >> 4;
            n = (opcode & 0x000F);
            nn = (opcode & 0x00FF);
            nnn = opcode - (opcode & 0xF000);

            printf ("x:%x\n",x);
            printf ("y:%x\n",y);
            printf ("n:%x\n",n);
            printf ("nn:%x\n",nn);
            printf ("nnn:%x\n\n",nnn);

            // Decode Opcode
            switch (opcode & 0xF000)
            {
                default:
                    printf ("Unknown Opcode! 0x%x\n", opcode);
                    exit(3);
                    break;
                
                case 0x0000:
                    switch (n)
                    {
                        case 0x0000: //0x00E0: Clear Screen
                            framebuffer.ClearBuffer();
                            programCounter += 2;
                            break;

                        case 0x000E: //0x00EE: Return from subroutine
                            stackPointer--;
                            programCounter = stack[stackPointer];
                            programCounter += 2;
                            break;

                        default:
                            printf ("Unknown Opcode! 0x%x\n", opcode);
                            exit(3);
                            break;
                    }
                    break;

                case 0x1000: // 1NNN: Jump to address NNN
                    printf ("Jump! 0x%x\n", nnn);
                    programCounter = nnn;
                    break;

                case 0x2000: // 2NNN: Call subroutine at nnn
                    stack[stackPointer] = programCounter;
                    stackPointer++;
                    programCounter = nnn;
                    break;

                case 0x3000: // 3XNN: Skip if v[X] is equal to NN
                    if (v[x] == nn)
                    {
                        programCounter += 4;
                    }
                    else
                    {
                        programCounter += 2;
                    }
                    break;

                case 0x4000: // 4XNN: Skip if v[X] is NOT equal to NN
                    if (v[x] != nn)
                    {
                        programCounter += 4;
                    }
                    else
                    {
                        programCounter += 2;
                    }
                    break;

                case 0x5000: // 5XY0: Skip if v[X] is equal to v[y]
                    if (v[x] == v[y])
                    {
                        programCounter += 4;
                    }
                    else
                    {
                        programCounter += 2;
                    }
                    
                    break;
                
                case 0x6000: // 6XNN: Sets v[X] to NN
                    v[x] = nn;
                    programCounter += 2;
                    break;

                case 0x7000: // 7XNN: Adds NN to v[X]
                    v[x] += nn;
                    programCounter += 2;
                    break;

                case 0x8000:
                    switch (n)
                    {
                        

                        case 0x0000: //8XY0: Sets v[X] to v[Y]
                            v[x] = v[y];
                            programCounter += 2;
                            break;

                        case 0x0001: //8XY1: Sets v[X] |= v[Y]
                            v[x] |= v[y];
                            programCounter += 2;
                            break;

                        case 0x0002: //8XY2: Sets v[X] &= v[Y]
                            v[x] &= v[y];
                            programCounter += 2;
                            break;

                        case 0x0003: //8XY3: Sets v[X] ^= v[Y]
                            v[x] ^= v[y];
                            programCounter += 2;
                            break;

                        case 0x0004: //8XY4: Adds v[Y] to v[X]
                            v[x] += v[y];
                            if(v[y] > (0xFF - v[x]))
                                v[0xF] = 1; //carry
                            else
                                v[0xF] = 0;
                            programCounter += 2;
                            break;

                        case 0x0005: //8XY5: Subtracts v[Y] from v[X]
                            if(v[y] > v[x])
                                v[0xF] = 0; // there is a borrow
                            else
                                v[0xF] = 1;
                            v[x] -= v[y];
                            programCounter += 2;
                            break;

                        case 0x0006: //8XY6: Sets v[X] >>= v[Y]
                            v[0xF] = v[x] & 0x1;
                            v[x] >>= 1;
                            programCounter += 2;
                            break;

                        case 0x0007: //8XYE: Sets v[X] = v[Y] - v[X]
                            if(v[x] > v[y])	// VY-VX
                                v[0xF] = 0; // there is a borrow
                            else
                                v[0xF] = 1;
                            v[x] = v[y] - v[x];
                            break;

                        case 0x000E: //8XYE: Sets v[X] <<= v[Y]
                            v[0xF] = v[x] >> 7;
                            v[x] <<= 1;
                            programCounter += 2;
                            break;

                        default:
                            printf ("Unknown Opcode! 0x%x\n", opcode);
                            exit(3);
                            break;
                    }
                    break;

                case 0x9000: // 5XY0: Skip if v[X] is NOT equal to v[y]
                    if (v[x] != v[y])
                    {
                        programCounter += 4;
                    }
                    else
                    {
                        programCounter += 2;
                    }
                    
                    break;

                case 0xA000: // ANNN: Sets indexRegister to the address NNN
                    indexRegister = nnn;
                    programCounter += 2;
                    break;
                
                case 0xB000:
                    programCounter = nnn + v[0];
                    break;

                case 0xC000: // CXNN: Sets v[x] = rand()
                    v[x] = (rand() % 0x100) & nn;
                    programCounter += 2;
                    break;

                case 0xD000: // DXYH: Draw Sprite
                    DrawSprite(&framebuffer, v[x], v[y], n);

                    programCounter += 2;
                    break;
                
                case 0xE000:
                    printf ("Unknown Opcode! 0x%x\n", opcode);
                    programCounter += 2;

                    //exit(3);
                    break;

                case 0xF000: // FX##
                    switch (nn)
                    {
                        case 0x0007: //Sets v[X] to the value of the delay timer
                            v[x] = delayTimer;
                            programCounter += 2;
                            break;

                        case 0x0015: //Set delay timer to v[x]
                            delayTimer = v[x];
                            programCounter += 2;
                            break;
                        
                        case 0x001E: //Add v[X] to indexRegister
                            indexRegister += v[x];
                            programCounter += 2;
                            break;

                        case 0x0029: //Set indexRegister to location of sprite in v[x]
                            indexRegister = v[x] * 5;
                            programCounter += 2;
                            break;

                        case 0x0033: //Decimal stuff
                            memory[indexRegister] = v[x] / 100;
                            memory[indexRegister + 1] = (v[x] / 10) % 10;
                            memory[indexRegister + 2] = (v[x] % 100) % 10;
                            programCounter += 2;
                            break;

                        case 0x0055: //Stores v[0] to v[x] in memory at indexRegister
                            for (int i = 0; i <= x; ++i)
                            {
                                memory[indexRegister + i] = v[i];
                            }
                            programCounter += 2;
                            break;

                        case 0x0065: //Stores memory in v[0] to v[x] at indexRegister
                            for (int i = 0; i <= x; ++i)
                            {
                                v[i] = memory[indexRegister + i];
                            }
                            programCounter += 2;
                            break;

                        default:
                            printf ("Unknown Opcode! 0x%x\n", opcode);
                            exit(3);
                            break;
                    }
                    break;
            }

            // Update Timers

            if (delayTimer > 0) --delayTimer;
            if (soundTimer > 0)
            {
                if (soundTimer == 1) printf("BEEP\n");
                --soundTimer;
            }


            /// Perform Render! All operations should be done by here.

            if (opcode == 0x00E0)
            {
                framebuffer.UpdateTexture();
            }

            renderer.PerformRender(framebuffer.GetTexture());

            SDL_Delay(1000 / 60);
        }
        
        return 0;
    }

    void vApp_Chip8::InitializeValues()
    {
        // Reset important values

        opcode = 0x0;
        indexRegister = 0x0;
        programCounter = 0x200;
        stackPointer = 0x0;

        memory.ClearMemory();

        delayTimer = 0x0;
        soundTimer = 0x0;

        memset(stack, 0x00, 32);
        memset(key, 0x00, 16);
        memset(v, 0x00, 16);

        for (int i = 0; i < 80; i++)
        {
            memory[i] = fonts[i];
        }

        palette.ClearPalette();
        palette.AddColor({0,0,0,255});
        palette.AddColor({255,255,255,255});

        memory.InsertRom(rom, romSize, 0x200);

    }

    void vApp_Chip8::DrawSprite(vFramebuffer* framebuffer, unsigned short _x, unsigned short _y, unsigned short _height)
    {
        unsigned short pixel;
        v[0xF] = 0;

        for (int yline = 0; yline < _height; yline++)
        {
            pixel = memory[indexRegister + yline];
            for (int xline = 0; xline < 8; xline++)
            {
                int framebufferIndex = (WIDTH * (_y+yline) + (_x + xline));
                if ((pixel & (0x0080 >> xline)) != 0)
                {
                    bool isOnInBuffer = framebuffer->GetColor(indexRegister).r;
                    if (isOnInBuffer)
                    {
                        framebuffer->SetColor(framebufferIndex, palette[0]);
                        v[0xF] = 1;
                    }
                    else
                    {
                        framebuffer->SetColor(framebufferIndex, palette[1]);
                    }
                    
                    
                }

                
                
            }
        }

        framebuffer->UpdateTexture();
    }
}