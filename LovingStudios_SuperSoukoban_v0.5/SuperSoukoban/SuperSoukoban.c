#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <stdbool.h>
#define NUM_TEXTURES  6
#define NUM_MUSIC 9
#define COLLISION_KEY KEY_F2
#define GODMODE_KEY KEY_F1
#define WIN_KEY KEY_F3
#define LOSE_KEY KEY_F4
#define HITBOX_SIZE 32

typedef enum Anim { Lados = 0, Up, Down } Anim;
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, WIN, FAIL } GameScreen;
typedef struct {
    float x;
    float y;
} Posiciones;
bool CollitionMode = false;

int main()
{ 
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 480;
    const int screenHeight = 320;
    GameScreen currentScreen = LOGO;//primera pantalla
    const int PjVel = 2; 
    InitWindow(screenWidth, screenHeight, "Super Soukoban");
    InitAudioDevice();
    Music music[NUM_MUSIC] = {0}; //cargar diferentes musicas
    
    
    Anim currentAnim = Lados;// cambiar animacion
    
    Texture2D marco = LoadTexture ("Assets/Images/ScoreFrame.png");//cargar marco puntuacion
    Texture2D fondo = LoadTexture ("Assets/Images/TileSet.png");//cargar Texturas
    
    Texture2D pj = LoadTexture ("Assets/Sprites/Pj.png"); //cargar animaciones pj
    
    Texture2D textures[NUM_TEXTURES] = { 0 };//cargar diferentes texturas

    textures[0] = LoadTexture("Assets/Images/InitialScreen.png");//primera textura
    textures[1] = LoadTexture("Assets/Images/MenuPrincipalJ.png");//segunda textura
    textures[3] = LoadTexture("Assets/Images/LoseLevel.png");//tercera textura
    textures[4] = LoadTexture("Assets/Images/NextlevelMessage.png");//cuarta textura 
    
    music[0] = LoadMusicStream("Assets/Audio/Docs_Music_02 Title Screen.ogg");
    music[1] = LoadMusicStream("Assets/Audio/Docs_Music_04 Physical Labor.ogg");
    music[2] = LoadMusicStream("Assets/Audio/Docs_Music_07 Stage Complete.ogg");
    music[3] = LoadMusicStream("Assets/Audio/Docs_Music_08 Failure.ogg");
    music[4] = LoadMusicStream("Assets/Audio/09 Staff Roll.ogg");
    
    bool PjMoving = false;//comprovacion de si se mueve el pj
    bool tocar = false;//win condition
    bool paso = false;//lose condition
    bool diosito = false;//Good Mode
    
    int pasos = 0; //pasos del pj Nivel
    int nivel = 1; //Nivel en el que estamos 
    int limitepasos = 20; //maximo de pasos en el nivel
    int framesCounter = 0;
    int numFrames = 8; //frames del pj
    int FrameWidth = pj.width/numFrames;//ancho que ocupa cada dibujo de la animacion
    int tilesetancho = 32;//ancho que ocupa cada dibujo del tileset
    int tilesetlargo = 32;//largo que ocupa cada dibujo del tileset
    
    unsigned FrameDelay = 5;
    unsigned FrameDelayCounter = 0;
    
   
    
    
   
    
    Rectangle naranja = {0.0f, 0.0f, (float)tilesetlargo, (float)tilesetancho};//carga textura del fondo
    Rectangle ladrillo = {32.0f, 0.0f, (float)tilesetlargo, (float)tilesetancho}; //carga textura de los ladrillos
    Rectangle suelo = {64.0f, 0.0f, (float)tilesetlargo, (float)tilesetancho}; //carga textura del suelo
    
    Rectangle caja = {0.0f, 32.0f, (float)tilesetlargo, (float)tilesetancho}; //carga textura caja
    Rectangle rosa = {64.0f, 32.0f, (float)tilesetlargo, (float)tilesetancho}; //carga el punto donde dejar las cajas
    
    Rectangle frameRec = {0.0f, 0.0f, (float)24, (float)30};//animacion 1
    Rectangle frameRecDown = {0.0f, 32.0f, (float)24, (float)30}; //animacion 2
    Rectangle frameRecUp = {0.0f, 64.0f, (float)24, (float)30}; //animacion 3
    
    Vector2 pjPosition = {192.0f, 74.0f};//vector de posicion del pj, spawn del personaje Lvl1
    Vector2 pjVelocity = {0.0f, 0.0f};//vector de velocidad del pj
    
    SetTargetFPS(60);           
    //--------------------------------------------------------------------------------------
    
    Posiciones suelos[] = {
    {0.0f, 0.0f},{32.0f, 0.0f},{64.0f, 0.0f},{96.0f, 0.0f},{128.0f, 0.0f},{160.0f, 0.0f},{192.0f, 0.0f},{224.0f, 0.0f},{256.0f, 0.0f},{288.0f, 0.0f},{320.0f, 0.0f},{352.0f, 0.0f},{384.0f, 0.0f},{416.0f, 0.0f},{448.0f, 0.0f},
    
    {0.0f, 32.0f},{32.0f, 32.0f},{64.0f, 32.0f},{96.0f, 32.0f},{128.0f, 32.0f},{160.0f, 32.0f},{192.0f, 32.0f},{224.0f, 32.0f},{256.0f, 32.0f},{288.0f, 32.0f},{320.0f, 32.0f},{352.0f, 32.0f},{384.0f, 32.0f},{416.0f, 32.0f},{448.0f, 32.0f},
    
    {0.0f, 64.0f},{32.0f, 64.0f},{64.0f, 64.0f},{96.0f, 64.0f},{128.0f, 64.0f},{160.0f, 64.0f},{192.0f, 64.0f},{224.0f, 64.0f},{256.0f, 64.0f},{288.0f, 64.0f},{320.0f, 64.0f},{352.0f, 64.0f},{384.0f, 64.0f},{416.0f, 64.0f},{448.0f, 64.0f},
    
    {0.0f, 96.0f},{32.0f, 96.0f},{64.0f, 96.0f},{96.0f, 96.0f},{128.0f, 96.0f},{160.0f, 96.0f},{192.0f, 96.0f},{224.0f, 96.0f},{256.0f, 96.0f},{288.0f, 96.0f},{320.0f, 96.0f},{352.0f, 96.0f},{384.0f, 96.0f},{416.0f, 96.0f},{448.0f, 96.0f},
    
    {0.0f, 128.0f},{32.0f, 128.0f},{64.0f, 128.0f},{96.0f, 128.0f},{128.0f, 128.0f},{160.0f, 128.0f},{192.0f, 128.0f},{224.0f, 128.0f},{256.0f, 128.0f},{288.0f, 128.0f},{320.0f, 128.0f},{352.0f, 128.0f},{384.0f, 128.0f},{416.0f, 128.0f},{448.0f, 128.0f},
    
    {0.0f, 160.0f},{32.0f, 160.0f},{64.0f, 160.0f},{96.0f, 160.0f},{128.0f, 160.0f},{160.0f, 160.0f},{192.0f, 160.0f},{224.0f, 160.0f},{256.0f, 160.0f},{288.0f, 160.0f},{320.0f, 160.0f},{352.0f, 160.0f},{384.0f, 160.0f},{416.0f, 160.0f},{448.0f, 160.0f},
    
    {0.0f, 192.0f},{32.0f, 192.0f},{64.0f, 192.0f},{96.0f, 192.0f},{128.0f, 192.0f},{160.0f, 192.0f},{192.0f, 192.0f},{224.0f, 192.0f},{256.0f, 192.0f},{288.0f, 192.0f},{320.0f, 192.0f},{352.0f, 192.0f},{384.0f, 192.0f},{416.0f, 192.0f},{448.0f, 192.0f},
    
    {0.0f, 224.0f},{32.0f, 224.0f},{64.0f, 224.0f},{96.0f, 224.0f},{128.0f, 224.0f},{160.0f, 224.0f},{192.0f, 224.0f},{224.0f, 224.0f},{256.0f, 224.0f},{288.0f, 224.0f},{320.0f, 224.0f},{352.0f, 224.0f},{384.0f, 224.0f},{416.0f, 224.0f},{448.0f, 224.0f},
    
    {0.0f, 256.0f},{32.0f, 256.0f},{64.0f, 256.0f},{96.0f, 256.0f},{128.0f, 256.0f},{160.0f, 256.0f},{192.0f, 256.0f},{224.0f, 256.0f},{256.0f, 256.0f},{288.0f, 256.0f},{320.0f, 256.0f},{352.0f, 256.0f},{384.0f, 256.0f},{416.0f, 256.0f},{448.0f, 256.0f},
    
    {0.0f, 288.0f},{32.0f, 288.0f},{64.0f, 288.0f},{96.0f, 288.0f},{128.0f, 288.0f},{160.0f, 288.0f},{192.0f, 288.0f},{224.0f, 288.0f},{256.0f, 288.0f},{288.0f, 288.0f},{320.0f, 288.0f},{352.0f, 288.0f},{384.0f, 288.0f},{416.0f, 288.0f},{448.0f, 288.0f},
    
};

    int paredes[] = {19, 20, 21, 22, 23, 24, 25, 
                 34, 40,
                 49, 53, 54, 55, 56,
                 63, 64, 65, 71,
                 78, 82, 84, 86,
                 93, 97, 101,
                 108, 112, 113, 114, 115, 116,
                 123, 124, 125, 126, 127,
                };
                 
    int suelogris[] = {35, 35, 36, 37, 38, 39,
                 50, 51, 52,
                 66, 67, 68, 69, 70,
                 79, 80, 81, 83, 85,
                 94, 95, 96, 98, 99, 100,
                 109, 110, 111,
                };

    int cajaduras[] = {66, 83, 95,};
        
    int setas[] = {37, 38, 39,};        
    
    // Main game loop
    PlayMusicStream(music[4]);
    while (!WindowShouldClose())// Detect window close button or ESC key 
    {
        switch(currentScreen)
        {
            case LOGO:
            {
                UpdateMusicStream(music[4]);
                if (IsKeyPressed(KEY_ENTER))
                {
                    PlayMusicStream(music[0]);
                    StopMusicStream(music[4]);
                    currentScreen = TITLE;
                     
                }
            } break;
            case TITLE:
            {
                UpdateMusicStream(music[0]);
                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER))
                {
                    PlayMusicStream(music[1]);
                    StopMusicStream(music[0]);
                    currentScreen = GAMEPLAY;
                    
                }
            } break;
            case GAMEPLAY:
            {
                if (IsKeyPressed(COLLISION_KEY)){CollitionMode = !CollitionMode;}
                if (IsKeyPressed(GODMODE_KEY)){diosito = !diosito;}
                if (IsKeyPressed(WIN_KEY)){
                    pasos=0;
                    tocar = false;
                    pjPosition.x =192.0f;
                    pjPosition.y =74.0f;//vector de posicion del pj, spawn del personaje Lvl1
                    PlayMusicStream(music[2]);
                    StopMusicStream(music[1]);
                    currentScreen = WIN;
                    }
                if (IsKeyPressed(LOSE_KEY)){ 
                    pasos=0;
                    paso = false;
                    pjPosition.x =192.0f;
                    pjPosition.y =74.0f;
                    PlayMusicStream(music[3]);
                    StopMusicStream(music[2]);
                    currentScreen = FAIL;
                }
                UpdateMusicStream(music[1]);
                if(!paso){
                    if(!tocar){
                        if (IsKeyDown(KEY_RIGHT)){
                            currentAnim = Lados;
                            pjVelocity.x = PjVel; //cambiar velocidad en x
                            pjVelocity.y = 0.0f; //parar velocidad pj en y
                            if(frameRec.width <0){
                                frameRec.width = -frameRec.width;//voltear animacion de andar
                            }
                        }else if(IsKeyDown(KEY_LEFT)){
                            currentAnim = Lados;
                            pjVelocity.x = -PjVel;//cambiar velocidad en x
                            pjVelocity.y = 0.0f; //parar velocidad pj en y
                            if(frameRec.width > 0){
                                frameRec.width = -frameRec.width;//voltear animacion de andar
                            }
                        }else if(IsKeyDown(KEY_UP)){
                            currentAnim = Up;
                            pjVelocity.y = -PjVel;//cambiar velocidad en y
                            pjVelocity.x = 0.0f;//parar velocidad pj en x
                
                        }else if(IsKeyDown(KEY_DOWN)){
                            currentAnim = Down;
                            pjVelocity.y = PjVel;//cambiar velocidad en y
                            pjVelocity.x = 0.0f;//parar velocidad pj en x
                
                        }else{
                            pjVelocity.x = 0.0f;//parar velocidad pj en x
                            pjVelocity.y = 0.0f;//parar velocidad pj en y
                        }
            
                        bool PjMoving = pjVelocity.x != 0.0f || pjVelocity.y != 0.0f;// comprobar si se mueve el pj
                        pjPosition = Vector2Add(pjPosition, pjVelocity);
            
                        ++FrameDelayCounter;
                        if(FrameDelayCounter > FrameDelay){
                            FrameDelayCounter = 0;
                        if(PjMoving){ 
                            if(currentAnim == Lados){
                                ++framesCounter;
                                if(!diosito){++pasos;}
                                framesCounter %= numFrames;
                                frameRec.x = (float) FrameWidth * framesCounter;
                                if(pasos > limitepasos){
                                    paso = true;                    
                                }
                            }else if(currentAnim == Down){
                                ++framesCounter;
                                if(!diosito){++pasos;}
                                framesCounter %= numFrames;
                                frameRecDown.x = (float) FrameWidth * framesCounter;
                                if(pasos > limitepasos){
                                    paso = true;                    
                                }
                            }else if(currentAnim == Up){
                                ++framesCounter;
                                if(!diosito){++pasos;}
                                framesCounter %= numFrames;
                                frameRecUp.x = (float) FrameWidth * framesCounter;
                                if(pasos > limitepasos){
                                    paso = true;                    
                                }
                            }
                        }
           
                    }
        
            for (int m = 0; m < sizeof(paredes) / sizeof(paredes[0]); m++) {
                Rectangle pared = {suelos[paredes[m]].x, suelos[paredes[m]].y, (float)tilesetlargo, (float)tilesetancho};
                Rectangle crosa = {235.f, 75.f, (float)8, (float)8};
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRec.width, frameRec.height}, crosa)){ 
                    pjPosition = Vector2Subtract(pjPosition, pjVelocity);
                    tocar=true;
                }
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUp.width, frameRecUp.height}, crosa)){ 
                    pjPosition = Vector2Subtract(pjPosition, pjVelocity);
                    tocar=true;
                }
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDown.width, frameRecDown.height}, crosa)){ 
                    pjPosition = Vector2Subtract(pjPosition, pjVelocity);
                    tocar=true;
                }
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRec.width, frameRec.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUp.width, frameRecUp.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDown.width, frameRecDown.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
            }
        
        // Detección y corrección de colisiones con las paredes de ladrillos
        
        }else{
            //pasar a pantalla win
                pasos=0;
                tocar = false;
                pjPosition.x =192.0f;
                pjPosition.y =74.0f;//vector de posicion del pj, spawn del personaje Lvl1
                PlayMusicStream(music[2]);
                StopMusicStream(music[1]);
                currentScreen = WIN;
            };}else{
            //pasar a pantalla lose
                pasos=0;
                paso = false;
                pjPosition.x =192.0f;
                pjPosition.y =74.0f;
                PlayMusicStream(music[3]);
                StopMusicStream(music[2]);
                currentScreen = FAIL;
            };

              
            } break;
            case WIN:
            {
                pasos=0;
                tocar = false;
                // TODO: Update ENDING screen variables here!
                UpdateMusicStream(music[2]);
                // Press enter to return to TITLE screen currentScreen = TITLE;
                
                if (IsKeyPressed(KEY_ENTER))
                {
                   PlayMusicStream(music[0]);
                    StopMusicStream(music[2]);
                    currentScreen = TITLE;
                }
            } break;
            case FAIL:
            {
                pasos=0;
                paso = false;
                // TODO: Update ENDING screen variables here!
                UpdateMusicStream(music[3]);
                // Press enter to return to TITLE screen currentScreen = TITLE;
                if (IsKeyPressed(KEY_ENTER))
                {
                    PlayMusicStream(music[0]);
                    StopMusicStream(music[3]);
                    currentScreen = TITLE;
                }
            } break;
            default: break;
        }

        //----------------------------------------------------------------------------------

        // Draw      
        BeginDrawing();

           switch(currentScreen)
            {
                case LOGO:
                {
                    ClearBackground(RAYWHITE);//limpiar pantalla
                    DrawRectangle(1, 0, screenWidth, screenHeight, BLACK);//fondo negro
                    DrawTexture(textures[0], 0, 0, WHITE);

                } break;
                case TITLE:
                {
                    ClearBackground(RAYWHITE);//limpiar pantalla
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);//fondo negro
                    DrawTexture(textures[1], 0, 0, WHITE);

                } break;
                case GAMEPLAY:
                {
                    ClearBackground(RAYWHITE);//limpiar pantalla
                     int x;
                      int i;
       
        for(i=0;i<screenWidth;i+= tilesetancho){ //dibujar a lo ancho
            for(x =0;x<screenHeight;x += tilesetlargo){ // dibujar a lo alto
            Vector2 bloques = {i, x};//vector de posicion bloques
             DrawTextureRec(fondo, naranja, bloques, WHITE);//dibujar textura naranja en pantalla usando un rectangulo
            }
        }//cargar fondo del mapa
        
        // Dibujar las paredes
        for (int i = 0; i < sizeof(suelos) / sizeof(suelos[0]); i++) {
                    for (int j = 0; j < sizeof(paredes) / sizeof(paredes[0]); j++) {
            DrawTextureRec(fondo, ladrillo, (Vector2){suelos[paredes[j]].x, suelos[paredes[j]].y}, WHITE);
                    }
                    for (int p = 0; p < sizeof(suelogris) / sizeof(suelogris[0]); p++) {
            DrawTextureRec(fondo, suelo, (Vector2){suelos[suelogris[p]].x, suelos[suelogris[p]].y}, WHITE);
                    }
                    for (int z = 0; z < sizeof(cajaduras) / sizeof(cajaduras[0]); z++) {
            DrawTextureRec(fondo, caja, (Vector2){suelos[cajaduras[z]].x, suelos[cajaduras[z]].y}, WHITE);
                    }
                    for (int s = 0; s < sizeof(setas) / sizeof(setas[0]); s++) {
            DrawTextureRec(fondo, rosa, (Vector2){suelos[setas[s]].x, suelos[setas[s]].y}, WHITE);
                    }
        }
        
        if (CollitionMode)
                {
                    // Iterar sobre las paredes y dibujar sus rectángulos de colisión
                    for (int i = 0; i < sizeof(paredes) / sizeof(paredes[0]); i++) {
                        Rectangle pared = {suelos[paredes[i]].x, suelos[paredes[i]].y, (float)tilesetlargo, (float)tilesetancho};
                        Rectangle crosa = {235.f, 75.f, (float)8, (float)8};
                        DrawRectangleLines(pared.x, pared.y, pared.width, pared.height, RED);
                        DrawRectangleLines(crosa.x, crosa.y, crosa.width, crosa.height, RED);
                    }
                    Vector2 hitboxPosition = {pjPosition.x, pjPosition.y};

                    // Dibujar el cuadrado de la hitbox encima del personaje
                    DrawRectangleLines(hitboxPosition.x, hitboxPosition.y, 22, 32, BLUE);

                    // Resto de rectángulos de colisión a dibujar...
                }
        
        DrawText(TextFormat("STAGE: %d", nivel), 355, 3, 20, BLACK);//nivel en el que estas
        DrawText(TextFormat("STEP: %d", pasos), 355, 25, 20, BLACK);//Pasos que ha dado el pj
        DrawText(TextFormat("LIMIT: %d", limitepasos), 355, 45, 20, BLACK);//maximo de pasos que se pueden dar por pantalla
        DrawTexture(marco, 350, 0, WHITE);//dibujar marco puntuacion
            switch(currentAnim)
            {
                 case Lados:
                {
                    DrawTextureRec(pj, frameRec, pjPosition, WHITE);

                } break;
                case Up:
                {
                    DrawTextureRec(pj, frameRecUp, pjPosition, WHITE);

                } break;
                case Down:
                {
                    DrawTextureRec(pj, frameRecDown, pjPosition, WHITE);

                } break;
                default: break;
            }

                } break;
                case WIN:
                {
                    DrawTexture(textures[4], 0, 0, WHITE);//textura ganar
                    DrawText("PRESS ENTER to TITLE SCREEN", 10, 280, 25, WHITE);//texto

                } break;
                case FAIL:
                {
                    DrawTexture(textures[3], 0, 0, WHITE);//textura perder
                    DrawText("PRESS ENTER to TITLE SCREEN", 10, 280, 25, WHITE);//texto 

                } break;
                default: break;
            }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    for (int i = 0; i < NUM_TEXTURES; i++) UnloadTexture(textures[i]);
    UnloadTexture(pj);
    UnloadTexture(marco);
    UnloadMusicStream(music[0]);
    UnloadMusicStream(music[1]);
    UnloadMusicStream(music[2]);
    UnloadMusicStream(music[3]);
    CloseAudioDevice();
    CloseWindow();       
   
    return 0;
}
