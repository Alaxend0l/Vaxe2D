#include "apps/app_nes.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#define WIDTH 256
#define HEIGHT 240

namespace vaxe
{

    int vApp_NES::Run()
    {
        vWindow window { WIDTH * 3, HEIGHT * 3, "NES" };
        vRenderer renderer { window.GetWindow(), SDL_RENDERER_ACCELERATED};
        SDL_RenderSetLogicalSize(renderer.GetRenderer(), WIDTH, HEIGHT);

        SDL_GLContext gl_context = SDL_GL_CreateContext(window.GetWindow());
        SDL_GL_SetSwapInterval(0);  // Enable vsync

        vFramebuffer framebuffer {renderer.GetRenderer(), WIDTH, HEIGHT};

        InitializeValues();

        SDL_Event event;
        uint64_t previousCounter = SDL_GetPerformanceCounter();
        uint64_t countPerSecond = SDL_GetPerformanceFrequency();

        /* Loop until the user closes the window */
        while (!quit)
        {
            
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

            // Access Instruction
            instruction = bus.ram[pc];

            //opcode = memory[programCounter] << 8 | memory[programCounter + 1];
            //printf ("pc:%x\n",programCounter);
            //printf ("Executing Opcode: 0x%x\n", opcode);

            //x = (opcode & 0x0F00) >> 8;
            //y = (opcode & 0x00F0) >> 4;
            //n = (opcode & 0x000F);
            //nn = (opcode & 0x00FF);
            //nnn = opcode - (opcode & 0xF000);
            //printf ("x:%x\n",x);
            //printf ("y:%x\n",y);
            //printf ("n:%x\n",n);
            //printf ("nn:%x\n",nn);
            //printf ("nnn:%x\n\n",nnn);

            // Decode Opcode
            /*
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
                            //programCounter += 2;
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
            */


            /// Perform Render! All operations should be done by here.

            if (true)
            {
                framebuffer.UpdateTexture();
            }

            renderer.PerformRender(framebuffer.GetTexture());
            PrintDebugData();

            SDL_Delay(1000 / 60);
        }
        
        return 0;
    }

    void vApp_NES::InitializeValues()
    {
        // Reset important values

        bus.ram.ClearMemory();

        // Program Counter
        pc = 0xC000;

        // Stack Pointer
        sp = 0x0;

        //General Purpose Registers
        gpr_a = 0x0;
        gpr_x = 0x0;
        gpr_y = 0x0;

        //memset(stack, 0x00, 32);

        palette.ClearPalette();
        palette.AddColor(84, 84, 84, 255);
        palette.AddColor(0, 30, 116, 255);
        palette.AddColor(8, 16, 144, 255);
        palette.AddColor(48, 0, 136, 255);
        palette.AddColor(68, 0, 100, 255);
        palette.AddColor(92, 0, 48, 255);
        palette.AddColor(84, 4, 0, 255);
        palette.AddColor(60, 24, 0, 255);
        palette.AddColor(32, 42, 0, 255);
        palette.AddColor(8, 58, 0, 255);
        palette.AddColor(0, 64, 0, 255);
        palette.AddColor(0, 60, 0, 255);
        palette.AddColor(0, 50, 60, 255);
        palette.AddColor(0, 0, 0, 255);
        palette.AddColor(0, 0, 0, 255);
        palette.AddColor(0, 0, 0, 255);
        palette.AddColor(152, 150, 152, 255);
        palette.AddColor(8, 76, 196, 255);
        palette.AddColor(48, 50, 236, 255);
        palette.AddColor(92, 30, 228, 255);
        palette.AddColor(136, 20, 176, 255);
        palette.AddColor(160, 20, 100, 255);
        palette.AddColor(152, 34, 32, 255);
        palette.AddColor(120, 60, 0, 255);
        palette.AddColor(84, 90, 0, 255);
        palette.AddColor(40, 114, 0, 255);
        palette.AddColor(8, 124, 0, 255);
        palette.AddColor(0, 118, 40, 255);
        palette.AddColor(0, 102, 120, 255);
        palette.AddColor(0, 0, 0, 255);
        palette.AddColor(0, 0, 0, 255);
        palette.AddColor(0, 0, 0, 255);
        palette.AddColor(236, 238, 236, 255);
        palette.AddColor(76, 154, 236, 255);
        palette.AddColor(120, 124, 236, 255);
        palette.AddColor(176, 98, 236, 255);
        palette.AddColor(228, 84, 236, 255);
        palette.AddColor(236, 88, 180, 255);
        palette.AddColor(236, 106, 100, 255);
        palette.AddColor(212, 136, 32, 255);
        palette.AddColor(160, 170, 0, 255);
        palette.AddColor(116, 196, 0, 255);
        palette.AddColor(76, 208, 32, 255);
        palette.AddColor(56, 204, 108, 255);
        palette.AddColor(56, 180, 204, 255);
        palette.AddColor(60, 60, 60, 255);
        palette.AddColor(0, 0, 0, 255);
        palette.AddColor(0, 0, 0, 255);
        palette.AddColor(236, 238, 236, 255);
        palette.AddColor(168, 204, 236, 255);
        palette.AddColor(188, 188, 236, 255);
        palette.AddColor(212, 178, 236, 255);
        palette.AddColor(236, 174, 236, 255);
        palette.AddColor(236, 174, 212, 255);
        palette.AddColor(236, 180, 176, 255);
        palette.AddColor(228, 196, 144, 255);
        palette.AddColor(204, 210, 120, 255);
        palette.AddColor(180, 222, 120, 255);
        palette.AddColor(168, 226, 144, 255);
        palette.AddColor(152, 226, 180, 255);
        palette.AddColor(160, 214, 228, 255);
        palette.AddColor(160, 162, 160, 255);
        palette.AddColor(0, 0, 0, 255);
        palette.AddColor(0, 0, 0, 255);

        bus.ram.InsertRom(rom, romSize, 0x8000);

    }

    void vApp_NES::PrintDebugData()
    {
        // Program Counter
        printf("%x ", pc);

        // Instruction
        printf("%x ", instruction);

        // General Process Registers
        printf("a:%x ", gpr_a);
        printf("x:%x ", gpr_x);
        printf("y:%x ", gpr_y);

        // Cycle
        printf("cyc:%x ", cycle);

        // Return
        printf("\n");
    }
}