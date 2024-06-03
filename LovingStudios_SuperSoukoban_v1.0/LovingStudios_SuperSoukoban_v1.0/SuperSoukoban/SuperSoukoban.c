#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <stdbool.h>
#define NUM_TEXTURES  10
#define NUM_ANIM  87
#define FRAME_TIME 0.45f // Tiempo en segundos para mostrar cada imagen
#define NUM_MUSIC 9
#define MOVE_CAJAS KEY_F5
#define COLLISION_KEY KEY_F2
#define GODMODE_KEY KEY_F1
#define WIN_KEY KEY_F3
#define LOSE_KEY KEY_F4
#define HITBOX_SIZE 32

typedef enum Anim { Lados = 0, Up, Down, LadosP, UpP, DownP } Anim;
typedef enum GameScreen { LOGO = 0, ANIMATION, TITLE, SelectLevel, GAMEPLAY, WIN, FAIL } GameScreen;
typedef enum Nivel { UNO = 0, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, OCHO } Nivel;
typedef struct {
    float x;
    float y; 
} Posiciones;
bool CollitionMode = false;


int main()
{ 
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 480; //GetScreenWidth();   //480
    const int screenHeight = 320; //GetScreenHeight(); //320
    GameScreen currentScreen = LOGO;//primera pantalla
    Nivel NivelSelec = UNO;
    const int PjVel = 3; 
    InitWindow(screenWidth, screenHeight, "Super Soukoban");
    //ToggleFullscreen(); 
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
    textures[5] = LoadTexture("Assets/Images/Choosing Menu.png");//cuarta textura

    Texture2D animacion[NUM_ANIM] = { 0 };//cargar diferentes texturas
    float timer = 0.0f;
    float tolerancia = 5.5f;
    int currentFrame = 0;
    animacion[0] = LoadTexture("Assets/Images/Intro/introSS_001.png");
    animacion[1] = LoadTexture("Assets/Images/Intro/introSS_002.png");
    animacion[2] = LoadTexture("Assets/Images/Intro/introSS_003.png");
    animacion[3] = LoadTexture("Assets/Images/Intro/introSS_004.png");
    animacion[4] = LoadTexture("Assets/Images/Intro/introSS_005.png");
    animacion[5] = LoadTexture("Assets/Images/Intro/introSS_006.png");
    animacion[6] = LoadTexture("Assets/Images/Intro/introSS_007.png");
    animacion[7] = LoadTexture("Assets/Images/Intro/introSS_008.png");
    animacion[8] = LoadTexture("Assets/Images/Intro/introSS_009.png");
    animacion[9] = LoadTexture("Assets/Images/Intro/introSS_010.png");
    animacion[10] = LoadTexture("Assets/Images/Intro/introSS_011.png");
    animacion[11] = LoadTexture("Assets/Images/Intro/introSS_012.png");
    animacion[12] = LoadTexture("Assets/Images/Intro/introSS_013.png");
    animacion[13] = LoadTexture("Assets/Images/Intro/introSS_014.png");
    animacion[14] = LoadTexture("Assets/Images/Intro/introSS_015.png");
    animacion[15] = LoadTexture("Assets/Images/Intro/introSS_016.png");
    animacion[16] = LoadTexture("Assets/Images/Intro/introSS_017.png");
    animacion[17] = LoadTexture("Assets/Images/Intro/introSS_018.png");
    animacion[18] = LoadTexture("Assets/Images/Intro/introSS_019.png");
    animacion[19] = LoadTexture("Assets/Images/Intro/introSS_020.png");
    animacion[20] = LoadTexture("Assets/Images/Intro/introSS_021.png");
    animacion[21] = LoadTexture("Assets/Images/Intro/introSS_022.png");
    animacion[22] = LoadTexture("Assets/Images/Intro/introSS_023.png");
    animacion[23] = LoadTexture("Assets/Images/Intro/introSS_024.png");
    animacion[24] = LoadTexture("Assets/Images/Intro/introSS_025.png");
    animacion[25] = LoadTexture("Assets/Images/Intro/introSS_026.png");
    animacion[26] = LoadTexture("Assets/Images/Intro/introSS_027.png");
    animacion[27] = LoadTexture("Assets/Images/Intro/introSS_028.png");
    animacion[28] = LoadTexture("Assets/Images/Intro/introSS_029.png");
    animacion[29] = LoadTexture("Assets/Images/Intro/introSS_030.png");
    animacion[30] = LoadTexture("Assets/Images/Intro/introSS_031.png");
    animacion[31] = LoadTexture("Assets/Images/Intro/introSS_032.png");
    animacion[32] = LoadTexture("Assets/Images/Intro/introSS_033.png");
    animacion[33] = LoadTexture("Assets/Images/Intro/introSS_034.png");
    animacion[34] = LoadTexture("Assets/Images/Intro/introSS_035.png");
    animacion[35] = LoadTexture("Assets/Images/Intro/introSS_036.png");
    animacion[36] = LoadTexture("Assets/Images/Intro/introSS_037.png");
    animacion[37] = LoadTexture("Assets/Images/Intro/introSS_038.png");
    animacion[38] = LoadTexture("Assets/Images/Intro/introSS_039.png");
    animacion[39] = LoadTexture("Assets/Images/Intro/introSS_040.png");
    animacion[40] = LoadTexture("Assets/Images/Intro/introSS_041.png");
    animacion[41] = LoadTexture("Assets/Images/Intro/introSS_042.png");
    animacion[42] = LoadTexture("Assets/Images/Intro/introSS_043.png");
    animacion[43] = LoadTexture("Assets/Images/Intro/introSS_044.png");
    animacion[44] = LoadTexture("Assets/Images/Intro/introSS_045.png");
    animacion[45] = LoadTexture("Assets/Images/Intro/introSS_046.png");
    animacion[46] = LoadTexture("Assets/Images/Intro/introSS_047.png");
    animacion[47] = LoadTexture("Assets/Images/Intro/introSS_048.png");
    animacion[48] = LoadTexture("Assets/Images/Intro/introSS_049.png");
    animacion[49] = LoadTexture("Assets/Images/Intro/introSS_050.png");
    animacion[50] = LoadTexture("Assets/Images/Intro/introSS_051.png");
    animacion[51] = LoadTexture("Assets/Images/Intro/introSS_052.png");
    animacion[52] = LoadTexture("Assets/Images/Intro/introSS_053.png");
    animacion[53] = LoadTexture("Assets/Images/Intro/introSS_054.png");
    animacion[54] = LoadTexture("Assets/Images/Intro/introSS_055.png");
    animacion[55] = LoadTexture("Assets/Images/Intro/introSS_056.png");
    animacion[56] = LoadTexture("Assets/Images/Intro/introSS_057.png");
    animacion[57] = LoadTexture("Assets/Images/Intro/introSS_058.png");
    animacion[58] = LoadTexture("Assets/Images/Intro/introSS_059.png");
    animacion[59] = LoadTexture("Assets/Images/Intro/introSS_060.png");
    animacion[60] = LoadTexture("Assets/Images/Intro/introSS_061.png");
    animacion[61] = LoadTexture("Assets/Images/Intro/introSS_062.png");
    animacion[62] = LoadTexture("Assets/Images/Intro/introSS_063.png");
    animacion[63] = LoadTexture("Assets/Images/Intro/introSS_064.png");
    animacion[64] = LoadTexture("Assets/Images/Intro/introSS_065.png");
    animacion[65] = LoadTexture("Assets/Images/Intro/introSS_066.png");
    animacion[66] = LoadTexture("Assets/Images/Intro/introSS_067.png");
    animacion[67] = LoadTexture("Assets/Images/Intro/introSS_068.png");
    animacion[68] = LoadTexture("Assets/Images/Intro/introSS_069.png");
    animacion[69] = LoadTexture("Assets/Images/Intro/introSS_070.png");
    animacion[70] = LoadTexture("Assets/Images/Intro/introSS_071.png");
    animacion[71] = LoadTexture("Assets/Images/Intro/introSS_072.png");
    animacion[72] = LoadTexture("Assets/Images/Intro/introSS_073.png");
    animacion[73] = LoadTexture("Assets/Images/Intro/introSS_074.png");
    animacion[74] = LoadTexture("Assets/Images/Intro/introSS_075.png");
    animacion[75] = LoadTexture("Assets/Images/Intro/introSS_076.png");
    animacion[76] = LoadTexture("Assets/Images/Intro/introSS_077.png");
    animacion[77] = LoadTexture("Assets/Images/Intro/introSS_078.png");
    animacion[78] = LoadTexture("Assets/Images/Intro/introSS_079.png");
    animacion[79] = LoadTexture("Assets/Images/Intro/introSS_080.png");
    animacion[80] = LoadTexture("Assets/Images/Intro/introSS_081.png");
    animacion[81] = LoadTexture("Assets/Images/Intro/introSS_082.png");
    animacion[82] = LoadTexture("Assets/Images/Intro/introSS_083.png");
    animacion[83] = LoadTexture("Assets/Images/Intro/introSS_084.png");
    animacion[84] = LoadTexture("Assets/Images/Intro/introSS_085.png");
    animacion[85] = LoadTexture("Assets/Images/Intro/introSS_086.png");
    animacion[86] = LoadTexture("Assets/Images/Intro/introSS_087.png");
    animacion[87] = LoadTexture("Assets/Images/Intro/introSS_088.png"); 
    
    music[0] = LoadMusicStream("Assets/Audio/Docs_Music_02 Title Screen.ogg");
    music[1] = LoadMusicStream("Assets/Audio/Docs_Music_04 Physical Labor.ogg");
    music[2] = LoadMusicStream("Assets/Audio/Docs_Music_07 Stage Complete.ogg");
    music[3] = LoadMusicStream("Assets/Audio/Docs_Music_08 Failure.ogg");
    music[4] = LoadMusicStream("Assets/Audio/09 Staff Roll.ogg");
    music[5] = LoadMusicStream("Assets/Audio/Docs_Music_03 Stage Select & Vs. Mode.ogg");
    music[6] = LoadMusicStream("Assets/Audio/Docs_Music_05 Hard Labor.ogg");
    music[7] = LoadMusicStream("Assets/Audio/Docs_Music_01 Opening.ogg");
    
    bool PjMoving = false;//comprovacion de si se mueve el pj
    bool tocar = false;//win condition
    bool paso = false;//lose condition
    bool diosito = false;//Good Mode
    bool empuja = true;
    bool cajaEnSeta = false;
    bool cambio = false;
    
    int pasos = 0; //pasos del pj Nivel
    int nivel = 1; //Nivel en el que estamos 
    int limitepasos = 90; //maximo de pasos en el nivel
    int framesCounter = 0;
    int numFrames = 8; //frames del pj
    int FrameWidth = pj.width/numFrames;//ancho que ocupa cada dibujo de la animacion
    int tilesetancho = 32;//ancho que ocupa cada dibujo del tileset
    int tilesetlargo = 32;//largo que ocupa cada dibujo del tileset
    int f = 0;
    int niveldado = 1;
    
    unsigned FrameDelay = 5;
    unsigned FrameDelayCounter = 0;
    
    Rectangle naranja = {0.0f, 0.0f, (float)tilesetlargo, (float)tilesetancho};//carga textura del fondo
    Rectangle ladrillo = {32.0f, 0.0f, (float)tilesetlargo, (float)tilesetancho}; //carga textura de los ladrillos
    Rectangle suelo = {64.0f, 0.0f, (float)tilesetlargo, (float)tilesetancho}; //carga textura del suelo
    
    Rectangle caja = {0.0f, 32.0f, (float)tilesetlargo, (float)tilesetancho}; //carga textura caja
    Rectangle cajausada = {32.0f, 32.0f, (float)tilesetlargo, (float)tilesetancho}; //carga textura caja
    Rectangle rosa = {64.0f, 32.0f, (float)tilesetlargo, (float)tilesetancho}; //carga el punto donde dejar las cajas
    
    Rectangle frameRec = {0.0f, 0.0f, (float)24, (float)30};//animacion 1
    Rectangle frameRecDown = {0.0f, 32.0f, (float)24, (float)30}; //animacion 2
    Rectangle frameRecUp = {0.0f, 64.0f, (float)24, (float)30}; //animacion 3
    Rectangle frameRecDownP = {0.0f, 96.0f, (float)24, (float)30}; //animacion 4
    Rectangle frameRecUpP = {0.0f, 128.0f, (float)24, (float)30}; //animacion 5
    Rectangle frameRecP = {0.0f, 160.0f, (float)24, (float)30}; //animacion 6
    
    Vector2 pjPosition = {};
    Vector2 cajaNewPosition = {};
    //Vector2 pjPosition = {192.0f, 74.0f};//vector de posicion del pj, spawn del personaje Lvl1
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

Posiciones suelos2[] = {
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

/*----------------------------Nivel 1-----------------------------*/

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
    
    int cajadurasquenocambian[] = {66, 83, 95,};
    
    
    int cajayapuesta[] = {};
        
    int setas[] = {37, 38, 39,};  
    
    /*
    pjPosition.x =192.0f;
    pjPosition.y =74.0f;//vector de posicion del pj, spawn del personaje Lvl1
    */

/*----------------------------Nivel 2-----------------------------*/

   int paredes2[] = {3, 4, 5, 6, 7,
		18, 22,
		33, 37, 39, 40, 41,
		48, 52, 54, 56,
		63, 64, 65, 67, 68, 69, 71,
		79, 80, 86,
		94, 98, 101,
		109, 113, 114, 115, 116,
		124, 125, 126, 127, 128,
                };
                 
    int suelogris2[] = {19, 20, 21,
			34, 35, 36,
			49, 50, 51, 55,
			66, 70,
			81, 82, 83, 84, 85,
			95, 96, 97, 99, 100,
			110, 111, 112,
                };

    int cajaduras2[] = {35, 36, 50,};
    int cajadurasquenocambian2[] = {35, 36, 50,};
    
    int cajayapuesta2[] = {};
        
    int setas2[] = {55, 70, 85,};   
					
    /*
    pjPosition.x =128.0f;
    pjPosition.y =32.0f;//vector de posicion del pj, spawn del personaje Lvl2
    */

/*----------------------------Nivel 3-----------------------------*/

   int paredes3[] = {20, 21, 22, 23,
			34, 35, 38,
			49, 53,
			64, 65, 68, 69,
			79, 80, 84,
			94, 99,
			109, 114,
			124, 125, 126, 127, 128, 129,
                };
                 
    int suelogris3[] = {36, 37,
			50, 51, 52,
			66, 67,
			81, 82, 83,
			95, 96, 97, 98,
			110, 111, 112, 113,
                };

    int cajaduras3[] = {51, 66, 82, 96, 112,};
    
    int cajayapuesta3[] = {112};
        
    int setas3[] = {95, 110, 111, 113,}; 
	
    /*
    pjPosition.x =160.0f;
    pjPosition.y =96.0f;//vector de posicion del pj, spawn del personaje Lvl3
    */

/*----------------------------Nivel 4-----------------------------*/

   int paredes4[] = {18, 19, 20, 21, 22, 23, 24,
			33, 39, 40, 41,
			47, 48, 50, 51, 52, 56,
			62, 71,
			77, 81, 85, 86,
			92, 93, 96, 100,
			108, 109, 110, 111, 112, 113, 114, 115,
                };
                 
    int suelogris4[] = {34, 35, 36, 37, 38,
			49, 53, 54, 55,
			63, 64, 65, 66, 67, 68, 69, 70,
			78, 79, 80, 82, 83, 84,
			94, 95, 97, 98, 99,
                };

    int cajaduras4[] = {49, 66, 69, 83,};
    
    int cajayapuesta4[] = {};
        
    int setas4[] = {79, 80,
			94, 95,}; 
	
    /*
    pjPosition.x =128.0f;
    pjPosition.y =128.0f;//vector de posicion del pj, spawn del personaje Lvl4
    */

	
/*----------------------------Nivel 5-----------------------------*/

   int paredes5[] = {19, 20, 21, 22,
			34, 37, 38, 39,
			49, 54,
			63, 64, 65, 67, 69, 70,
			78, 80, 82, 85,
			93, 98, 100,
			108, 115,
			123, 124, 125, 126, 127, 128, 129, 130,
                };
                 
    int suelogris5[] = {35, 36,
			50, 51, 52, 53,
			66, 68,
			79, 81, 83, 84,
			94, 95, 96, 97, 99,
			109, 110, 111, 112, 113, 114,
                };

    int cajaduras5[] = {51, 95, 113,};
    
    int cajayapuesta5[] = {};
        
    int setas5[] = {79, 94, 109,}; 
	
    /*
    pjPosition.x =160.0f;
    pjPosition.y =64.0f;//vector de posicion del pj, spawn del personaje Lvl5
    */
	
/*----------------------------Nivel 6-----------------------------*/

   int paredes6[] = {21, 22, 23, 24, 25, 26,
			34, 35, 36, 41,
			48, 49, 53, 54, 56, 57,
			63, 72,
			78, 86, 87,
			93, 94, 95, 96, 97, 98, 101,
			113, 114, 115, 116,
                };
                 
    int suelogris6[] = {37, 38, 39, 40,
			50, 51, 52, 55,
			64, 65, 66, 67, 68, 69, 70, 71,
			79, 80, 81, 82, 83, 84, 85,
			99, 100,
                };

    int cajaduras6[] = {52, 66, 68, 82, 84,};
    
    int cajayapuesta6[] = {};
        
    int setas6[] = {50, 64, 65, 79, 80,}; 
	
    /*
    pjPosition.x =352.0f;
    pjPosition.y =128.0f;//vector de posicion del pj, spawn del personaje Lvl6
    */
	
/*----------------------------Nivel 7-----------------------------*/

   int paredes7[] = {36, 37, 38, 39, 40, 41,
			51, 56,
			64, 65, 66, 71,
			79, 86,
			94, 100, 101,
			109, 110, 111, 112, 115,
			127, 128, 129, 130,
                };
                 
    int suelogris7[] = {52, 53, 54, 55,
			67, 68, 69, 70,
			80, 81, 82, 83, 84, 85,
			95, 96, 97, 98, 99,
			113, 114,
                };

    int cajaduras7[] = {67, 68, 69, 82, 96,};
    
    int cajayapuesta7[] = {};
        
    int setas7[] = {83, 84, 97, 98, 99,}; 
	
    /*
    pjPosition.x =160.0f;
    pjPosition.y =160.0f;//vector de posicion del pj, spawn del personaje Lvl7
    */

/*----------------------------Nivel 8-----------------------------*/

   int paredes8[] = {20, 21, 22, 23, 24, 25, 26, 27,
			35, 39, 42,
			49, 50, 57,
			64, 69, 72,
			78, 79, 81, 82, 84, 86, 87,
			93, 102,
			108, 112, 117,
			123, 124, 125, 126, 127, 128, 129, 132,
			144, 145, 146, 147,
                };
                 
    int suelogris8[] = {36, 37, 38, 40, 41,
			51, 52, 53, 54, 55, 56,
			65, 66, 67, 68, 70, 71,
			80, 83, 85,
			94, 95, 96, 97, 98, 99, 100, 101,
			109, 110, 111, 113, 114, 115, 116,
			130, 131,
                };

    int cajaduras8[] = {53, 67, 83, 97, 100,};
    
    int cajayapuesta8[] = {70};
        
    int setas8[] = {40, 54, 55, 56, 71,};
	/*
    pjPosition.x =320.0f;
    pjPosition.y =256.0f;//vector de posicion del pj, spawn del personaje Lvl8
    */
    
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
                    PlayMusicStream(music[7]);
                    StopMusicStream(music[4]);
                    currentScreen = ANIMATION;
                    //currentScreen = TITLE;
                     
                }
            } break;
        case ANIMATION: 
            {
                UpdateMusicStream(music[7]);
                timer += GetFrameTime();   
             if (timer >= FRAME_TIME) {
                timer = 0.0f;
                currentFrame++;
                if (currentFrame >= NUM_ANIM) {
                    PlayMusicStream(music[0]);
                    StopMusicStream(music[7]);
                    currentScreen = TITLE;
                    currentFrame = 0; // Reiniciar la animación 
                }
                }    
                 
            } break;
            case TITLE:
            {
                UpdateMusicStream(music[0]);
                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER))
                {
                    PlayMusicStream(music[5]);
                    StopMusicStream(music[0]);
                    currentScreen = SelectLevel;
                    
                }
            } break;
            case SelectLevel:
            {
                UpdateMusicStream(music[5]);
                // Press enter to change to GAMEPLAY screen
            if (IsKeyPressed(KEY_ENTER)){    
                switch(niveldado){
                    case 1:
                    {
                      pjPosition.x =192.0f;
                      pjPosition.y =74.0f;//vector de posicion del pj, spawn del personaje Lvl1
                      /*
                      //int cajaduras[] = {66, 83, 95,};
                      DrawTextureRec(fondo, caja, (Vector2){suelos[66].x, suelos[66].y}, WHITE);
                      */
                      limitepasos = 90;
                      NivelSelec = UNO;
                      PlayMusicStream(music[1]);
                      StopMusicStream(music[5]);
                      currentScreen = GAMEPLAY;
                      
                    }break;
                    case 2:
                    {
                      limitepasos = 120;
                      NivelSelec = DOS;
                      PlayMusicStream(music[6]);
                      StopMusicStream(music[5]);
                      currentScreen = GAMEPLAY;
                    }break;
                    case 3:
                    {
                      limitepasos = 50;
                      NivelSelec = TRES;
                      PlayMusicStream(music[1]);
                      StopMusicStream(music[5]);
                      currentScreen = GAMEPLAY;
                    }break;
                    case 4:
                    {
                      limitepasos = 140;
                      NivelSelec = CUATRO;
                      PlayMusicStream(music[6]);
                      StopMusicStream(music[5]);
                      currentScreen = GAMEPLAY;
                    }break;
                    case 5:
                    {
                      limitepasos = 65;
                      NivelSelec = CINCO;
                      PlayMusicStream(music[1]);
                      StopMusicStream(music[5]);
                      currentScreen = GAMEPLAY;
                    }break;
                    case 6:
                    {
                      limitepasos = 60;
                      NivelSelec = SEIS;
                      PlayMusicStream(music[6]);
                      StopMusicStream(music[5]);
                      currentScreen = GAMEPLAY;
                    }break;
                    case 7:
                    {
                      limitepasos = 80;
                      NivelSelec = SIETE;
                      PlayMusicStream(music[1]);
                      StopMusicStream(music[5]);
                      currentScreen = GAMEPLAY;
                    }break;
                    case 8:
                    {
                      limitepasos = 160;  
                      NivelSelec = OCHO;
                      PlayMusicStream(music[6]);
                      StopMusicStream(music[5]);
                      currentScreen = GAMEPLAY;                      
                    }break;
                    }                 
                }
            } break; 
            case GAMEPLAY:
            {  if (NivelSelec == SIETE || NivelSelec == UNO || NivelSelec == TRES || NivelSelec == CINCO) {UpdateMusicStream(music[1]);}
               if (NivelSelec == DOS || NivelSelec == CUATRO || NivelSelec == SEIS || NivelSelec == OCHO) {UpdateMusicStream(music[6]);}
                if (IsKeyPressed(COLLISION_KEY)){CollitionMode = !CollitionMode;}
                if (IsKeyPressed(GODMODE_KEY)){diosito = !diosito;}
                if (IsKeyPressed(WIN_KEY)){
                    PlayMusicStream(music[2]);
                    if (NivelSelec == SIETE || NivelSelec == UNO || NivelSelec == TRES || NivelSelec == CINCO) {StopMusicStream(music[1]);}
                    if (NivelSelec == DOS || NivelSelec == CUATRO || NivelSelec == SEIS || NivelSelec == OCHO) {StopMusicStream(music[6]);}
                    currentScreen = WIN;
                    }
                if (IsKeyPressed(LOSE_KEY)){ 
                    PlayMusicStream(music[3]);
                     if (NivelSelec == SIETE || NivelSelec == UNO || NivelSelec == TRES || NivelSelec == CINCO) {StopMusicStream(music[1]);}
                     if (NivelSelec == DOS || NivelSelec == CUATRO || NivelSelec == SEIS || NivelSelec == OCHO) {StopMusicStream(music[6]);}
                    currentScreen = FAIL;
                }
               
                if(!paso){
                    if(!tocar){
                        if (IsKeyDown(KEY_RIGHT)){
                           if(empuja = true){currentAnim = Lados;}//else{currentAnim = LadosP;}                            
                            pjVelocity.x = PjVel; //cambiar velocidad en x
                            pjVelocity.y = 0.0f; //parar velocidad pj en y
                            if(frameRec.width <0){
                                frameRec.width = -frameRec.width;//voltear animacion de andar
                                frameRecP.width = -frameRecP.width;//voltear animacion de andar
                            }
                            
                        }else if(IsKeyDown(KEY_LEFT)){
                           if(empuja = true){currentAnim = Lados;}//else{currentAnim = LadosP;}
                            pjVelocity.x = -PjVel;//cambiar velocidad en x
                            pjVelocity.y = 0.0f; //parar velocidad pj en y
                            if(frameRec.width > 0){
                                frameRec.width = -frameRec.width;//voltear animacion de andar
                                frameRecP.width = -frameRecP.width;//voltear animacion de andar
                            }
                        }else if(IsKeyDown(KEY_UP)){
                            if(empuja = true){currentAnim = Up;}//else{currentAnim = UpP;}
                            pjVelocity.y = -PjVel;//cambiar velocidad en y
                            pjVelocity.x = 0.0f;//parar velocidad pj en x
                
                        }else if(IsKeyDown(KEY_DOWN)){
                            if(empuja = true){currentAnim = Down;}//else{currentAnim = DownP;}
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
                                ++framesCounter;
                                if(!diosito){++pasos;}
                                framesCounter %= numFrames;
                                frameRec.x = (float) FrameWidth * framesCounter;
                                frameRecDown.x = (float) FrameWidth * framesCounter;
                                frameRecUp.x = (float) FrameWidth * framesCounter;
                                frameRecP.x = (float) FrameWidth * framesCounter;
                                frameRecDownP.x = (float) FrameWidth * framesCounter;
                                frameRecUpP.x = (float) FrameWidth * framesCounter;
                                if(pasos > limitepasos){
                                    paso = true;                    
                                }
                        }
           
                    }
        
      switch(NivelSelec){
            case UNO:
            {
                cajaEnSeta = true; // Inicializar a true, asumiendo que todas las cajas están en su posición
                for (int m = 0; m < sizeof(paredes) / sizeof(paredes[0]); m++) {
               
                if (IsKeyPressed(MOVE_CAJAS)){
                        // Mover todas las cajas a las posiciones de las setas
                        for (int i = 0; i < sizeof(cajaduras) / sizeof(cajaduras[0]); i++) {
                            if (i < sizeof(setas) / sizeof(setas[0])) {
                                suelos[cajaduras[i]].x = suelos[setas[i]].x;
                                suelos[cajaduras[i]].y = suelos[setas[i]].y;
                            }
                        }
                    }
                
                //Colision pared jugador
                Rectangle pared = {suelos[paredes[m]].x, suelos[paredes[m]].y, (float)tilesetlargo, (float)tilesetancho};
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRec.width, frameRec.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUp.width, frameRecUp.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDown.width, frameRecDown.height}, pared)){pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDownP.width, frameRecDownP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUpP.width, frameRecUpP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecP.width, frameRecP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                
                //Colision jugador con caja
                for (int l = 0; l < sizeof(cajaduras) / sizeof(cajaduras[0]); l++) {
                Rectangle caja = {suelos[cajaduras[l]].x, suelos[cajaduras[l]].y, 30.0f, 30.0f};
                //frameRec Animación personaje 1
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, 24, 24}, caja)) {
                    
                   if(IsKeyDown(KEY_RIGHT)){currentAnim = LadosP;}
                   if(IsKeyDown(KEY_LEFT)){currentAnim = LadosP;}
                   if(IsKeyDown(KEY_UP)){currentAnim = UpP;}
                   if(IsKeyDown(KEY_DOWN)){currentAnim = DownP;}
                    pjPosition = Vector2Subtract(pjPosition, pjVelocity);
                    // Move box
                    Vector2 cajaNewPosition = Vector2Add((Vector2){caja.x, caja.y}, pjVelocity);
                    // Check if new box position collides with any wall
                    bool collisionWithWall = false;
                    bool collisionWithBox = false;
                    for (int n = 0; n < sizeof(paredes) / sizeof(paredes[0]); n++) {
                        Rectangle pared = {suelos[paredes[n]].x, suelos[paredes[n]].y, (float)tilesetlargo, (float)tilesetancho};
                        if (CheckCollisionRecs((Rectangle){cajaNewPosition.x, cajaNewPosition.y, caja.width, caja.height}, pared)) {
                            collisionWithWall = true;
                            break;
                        }
                    }
                     // Check for collision with other boxes
                    for (int b = 0; b < sizeof(cajaduras) / sizeof(cajaduras[0]); b++) {
                         if (b != l) { // Don't check collision with itself
                                Rectangle otherBox = {suelos[cajaduras[b]].x, suelos[cajaduras[b]].y, 30.0f, 30.0f};
                                    if (CheckCollisionRecs((Rectangle){cajaNewPosition.x, cajaNewPosition.y, caja.width, caja.height}, otherBox)) {
                                        collisionWithBox = true;
                                        break;
                                    }
                                }
                            }
                    // If no collision with wall, move the box
                    if (!collisionWithWall && !collisionWithBox) {
                        suelos[cajaduras[l]].x = cajaNewPosition.x;
                        suelos[cajaduras[l]].y = cajaNewPosition.y;
                    }
                }else{empuja = true;}
                }
            }
      
      // Verificar si todas las cajas están en las setas
        for (int i = 0; i < sizeof(cajaduras) / sizeof(cajaduras[0]); i++) {
            bool cajaEnSetaLocal = false;
            for (int j = 0; j < sizeof(setas) / sizeof(setas[0]); j++) {
                if (fabs(suelos[cajaduras[i]].x - suelos[setas[j]].x)<= tolerancia && fabs(suelos[cajaduras[i]].y - suelos[setas[j]].y) <= tolerancia) {
                    cambio = true;
                    cajaEnSetaLocal = true;
                    break;
                }
            }
            if (!cajaEnSetaLocal) {
                cajaEnSeta = false;
                //cambio = false;
                break;
            }
        }
        if (cajaEnSeta) {
            tocar = true;
        }
         if (IsKeyPressed(MOVE_CAJAS)) {
            // Mover todas las cajas a las posiciones de las setas
            for (int i = 0; i < sizeof(cajaduras) / sizeof(cajaduras[0]); i++) {
                if (i < sizeof(setas) / sizeof(setas[0])) {
                    suelos[cajaduras[i]].x = suelos[setas[i]].x;
                    suelos[cajaduras[i]].y = suelos[setas[i]].y;
                }
            }
        }
       }                 
        break;
        case DOS:
        {
                cajaEnSeta = true; // Inicializar a true, asumiendo que todas las cajas están en su posición
                for (int m = 0; m < sizeof(paredes2) / sizeof(paredes2[0]); m++) {
               
                if (IsKeyPressed(MOVE_CAJAS)){
                        // Mover todas las cajas a las posiciones de las setas
                        for (int i = 0; i < sizeof(cajaduras2) / sizeof(cajaduras2[0]); i++) {
                            if (i < sizeof(setas) / sizeof(setas[0])) {
                                suelos[cajaduras2[i]].x = suelos[setas2[i]].x;
                                suelos[cajaduras2[i]].y = suelos[setas2[i]].y;
                            }
                        }
                    }
                
                //Colision pared jugador
                Rectangle pared = {suelos[paredes2[m]].x, suelos[paredes2[m]].y, (float)tilesetlargo, (float)tilesetancho};
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRec.width, frameRec.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUp.width, frameRecUp.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDown.width, frameRecDown.height}, pared)){pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDownP.width, frameRecDownP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUpP.width, frameRecUpP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecP.width, frameRecP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                
                //Colision jugador con caja
                for (int l = 0; l < sizeof(cajaduras2) / sizeof(cajaduras2[0]); l++) {
                Rectangle caja = {suelos[cajaduras2[l]].x, suelos[cajaduras2[l]].y, 30.0f, 30.0f};
               
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, 24, 24}, caja)) {
                    
                   if(IsKeyDown(KEY_RIGHT)){currentAnim = LadosP;}
                   if(IsKeyDown(KEY_LEFT)){currentAnim = LadosP;}
                   if(IsKeyDown(KEY_UP)){currentAnim = UpP;}
                   if(IsKeyDown(KEY_DOWN)){currentAnim = DownP;}
                    pjPosition = Vector2Subtract(pjPosition, pjVelocity);
                    // Move box
                    Vector2 cajaNewPosition = Vector2Add((Vector2){caja.x, caja.y}, pjVelocity);
                    // Check if new box position collides with any wall
                    bool collisionWithWall = false;
                    bool collisionWithBox = false;
                    for (int n = 0; n < sizeof(paredes2) / sizeof(paredes2[0]); n++) {
                        Rectangle pared = {suelos[paredes2[n]].x, suelos[paredes2[n]].y, (float)tilesetlargo, (float)tilesetancho};
                        if (CheckCollisionRecs((Rectangle){cajaNewPosition.x, cajaNewPosition.y, caja.width, caja.height}, pared)) {
                            collisionWithWall = true;
                            break;
                        }
                    }
                     // Check for collision with other boxes
                    for (int b = 0; b < sizeof(cajaduras2) / sizeof(cajaduras2[0]); b++) {
                         if (b != l) { // Don't check collision with itself
                                Rectangle otherBox = {suelos[cajaduras2[b]].x, suelos[cajaduras2[b]].y, 30.0f, 30.0f};
                                    if (CheckCollisionRecs((Rectangle){cajaNewPosition.x, cajaNewPosition.y, caja.width, caja.height}, otherBox)) {
                                        collisionWithBox = true;
                                        break;
                                    }
                                }
                            }
                    // If no collision with wall, move the box
                    if (!collisionWithWall && !collisionWithBox) {
                        suelos[cajaduras2[l]].x = cajaNewPosition.x;
                        suelos[cajaduras2[l]].y = cajaNewPosition.y;
                    }
                }else{empuja = true;}
                }
            }
      
      // Verificar si todas las cajas están en las setas
        for (int i = 0; i < sizeof(cajaduras2) / sizeof(cajaduras2[0]); i++) {
            bool cajaEnSetaLocal = false;
            for (int j = 0; j < sizeof(setas2) / sizeof(setas2[0]); j++) {
                if (fabs(suelos[cajaduras2[i]].x - suelos[setas2[j]].x)<= tolerancia && fabs(suelos[cajaduras2[i]].y - suelos[setas2[j]].y) <= tolerancia) {
                    cambio = true;
                    cajaEnSetaLocal = true;
                    break;
                }
            }
            if (!cajaEnSetaLocal) {
                cajaEnSeta = false;
                break;
            }
        }
        if (cajaEnSeta) {
            tocar = true;
        }
         if (IsKeyPressed(MOVE_CAJAS)) {
            // Mover todas las cajas a las posiciones de las setas
            for (int i = 0; i < sizeof(cajaduras2) / sizeof(cajaduras2[0]); i++) {
                if (i < sizeof(setas2) / sizeof(setas2[0])) {
                    suelos[cajaduras2[i]].x = suelos[setas2[i]].x;
                    suelos[cajaduras2[i]].y = suelos[setas2[i]].y;
                }
            }
        }
       }
    break;
    case TRES:
    {
                cajaEnSeta = true; // Inicializar a true, asumiendo que todas las cajas están en su posición
                for (int m = 0; m < sizeof(paredes3) / sizeof(paredes3[0]); m++) {
               
                if (IsKeyPressed(MOVE_CAJAS)){
                        // Mover todas las cajas a las posiciones de las setas
                        for (int i = 0; i < sizeof(cajaduras3) / sizeof(cajaduras3[0]); i++) {
                            if (i < sizeof(setas3) / sizeof(setas3[0])) {
                                suelos[cajaduras3[i]].x = suelos[setas3[i]].x;
                                suelos[cajaduras3[i]].y = suelos[setas3[i]].y;
                            }
                        }
                    }
                
                //Colision pared jugador
                Rectangle pared = {suelos[paredes3[m]].x, suelos[paredes3[m]].y, (float)tilesetlargo, (float)tilesetancho};
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRec.width, frameRec.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUp.width, frameRecUp.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDown.width, frameRecDown.height}, pared)){pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDownP.width, frameRecDownP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUpP.width, frameRecUpP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecP.width, frameRecP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                
                //Colision jugador con caja
                for (int l = 0; l < sizeof(cajaduras3) / sizeof(cajaduras3[0]); l++) {
                Rectangle caja = {suelos[cajaduras3[l]].x, suelos[cajaduras3[l]].y, 30.0f, 30.0f};
                //frameRec Animación personaje 1
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, 24, 24}, caja)) {
                    
                   if(IsKeyDown(KEY_RIGHT)){currentAnim = LadosP;}
                   if(IsKeyDown(KEY_LEFT)){currentAnim = LadosP;}
                   if(IsKeyDown(KEY_UP)){currentAnim = UpP;}
                   if(IsKeyDown(KEY_DOWN)){currentAnim = DownP;}
                    pjPosition = Vector2Subtract(pjPosition, pjVelocity);
                    // Move box
                    Vector2 cajaNewPosition = Vector2Add((Vector2){caja.x, caja.y}, pjVelocity);
                    // Check if new box position collides with any wall
                    bool collisionWithWall = false;
                    bool collisionWithBox = false;
                    for (int n = 0; n < sizeof(paredes3) / sizeof(paredes3[0]); n++) {
                        Rectangle pared = {suelos[paredes3[n]].x, suelos[paredes3[n]].y, (float)tilesetlargo, (float)tilesetancho};
                        if (CheckCollisionRecs((Rectangle){cajaNewPosition.x, cajaNewPosition.y, caja.width, caja.height}, pared)) {
                            collisionWithWall = true;
                            break;
                        }
                    }
                     // Check for collision with other boxes
                    for (int b = 0; b < sizeof(cajaduras3) / sizeof(cajaduras3[0]); b++) {
                         if (b != l) { // Don't check collision with itself
                                Rectangle otherBox = {suelos[cajaduras3[b]].x, suelos[cajaduras3[b]].y, 30.0f, 30.0f};
                                    if (CheckCollisionRecs((Rectangle){cajaNewPosition.x, cajaNewPosition.y, caja.width, caja.height}, otherBox)) {
                                        collisionWithBox = true;
                                        break;
                                    }
                                }
                            }
                    // If no collision with wall, move the box
                    if (!collisionWithWall && !collisionWithBox) {
                        suelos[cajaduras3[l]].x = cajaNewPosition.x;
                        suelos[cajaduras3[l]].y = cajaNewPosition.y;
                    }
                }else{empuja = true;}
                }
            }
      
      // Verificar si todas las cajas están en las setas
        for (int i = 0; i < sizeof(cajaduras3) / sizeof(cajaduras3[0]); i++) {
            bool cajaEnSetaLocal = false;
            for (int j = 0; j < sizeof(setas3) / sizeof(setas3[0]); j++) {
                if (fabs(suelos[cajaduras3[i]].x - suelos[setas3[j]].x)<= tolerancia && fabs(suelos[cajaduras3[i]].y - suelos[setas3[j]].y) <= tolerancia) {
                    cambio = true;
                    cajaEnSetaLocal = true;
                    break;
                }
            }
            if (!cajaEnSetaLocal) {
                cajaEnSeta = false;
                break;
            }
        }
        if (cajaEnSeta) {
            tocar = true;
        }
         if (IsKeyPressed(MOVE_CAJAS)) {
            // Mover todas las cajas a las posiciones de las setas
            for (int i = 0; i < sizeof(cajaduras3) / sizeof(cajaduras3[0]); i++) {
                if (i < sizeof(setas3) / sizeof(setas3[0])) {
                    suelos[cajaduras3[i]].x = suelos[setas3[i]].x;
                    suelos[cajaduras3[i]].y = suelos[setas3[i]].y;
                }
            }
        }
       }
    break;
    case CUATRO:
     {
                cajaEnSeta = true; // Inicializar a true, asumiendo que todas las cajas están en su posición
                for (int m = 0; m < sizeof(paredes4) / sizeof(paredes4[0]); m++) {
               
                if (IsKeyPressed(MOVE_CAJAS)){
                        // Mover todas las cajas a las posiciones de las setas
                        for (int i = 0; i < sizeof(cajaduras4) / sizeof(cajaduras4[0]); i++) {
                            if (i < sizeof(setas4) / sizeof(setas4[0])) {
                                suelos[cajaduras4[i]].x = suelos[setas4[i]].x;
                                suelos[cajaduras4[i]].y = suelos[setas4[i]].y;
                            }
                        }
                    }
                
                //Colision pared jugador
                Rectangle pared = {suelos[paredes4[m]].x, suelos[paredes4[m]].y, (float)tilesetlargo, (float)tilesetancho};
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRec.width, frameRec.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUp.width, frameRecUp.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDown.width, frameRecDown.height}, pared)){pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDownP.width, frameRecDownP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUpP.width, frameRecUpP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecP.width, frameRecP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                
                //Colision jugador con caja
                for (int l = 0; l < sizeof(cajaduras4) / sizeof(cajaduras4[0]); l++) {
                Rectangle caja = {suelos[cajaduras4[l]].x, suelos[cajaduras4[l]].y, 30.0f, 30.0f};
                //frameRec Animación personaje 1
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, 24, 24}, caja)) {
                    
                   if(IsKeyDown(KEY_RIGHT)){currentAnim = LadosP;}
                   if(IsKeyDown(KEY_LEFT)){currentAnim = LadosP;}
                   if(IsKeyDown(KEY_UP)){currentAnim = UpP;}
                   if(IsKeyDown(KEY_DOWN)){currentAnim = DownP;}
                    pjPosition = Vector2Subtract(pjPosition, pjVelocity);
                    // Move box
                    Vector2 cajaNewPosition = Vector2Add((Vector2){caja.x, caja.y}, pjVelocity);
                    // Check if new box position collides with any wall
                    bool collisionWithWall = false;
                    bool collisionWithBox = false;
                    for (int n = 0; n < sizeof(paredes4) / sizeof(paredes4[0]); n++) {
                        Rectangle pared = {suelos[paredes4[n]].x, suelos[paredes4[n]].y, (float)tilesetlargo, (float)tilesetancho};
                        if (CheckCollisionRecs((Rectangle){cajaNewPosition.x, cajaNewPosition.y, caja.width, caja.height}, pared)) {
                            collisionWithWall = true;
                            break;
                        }
                    }
                     // Check for collision with other boxes
                    for (int b = 0; b < sizeof(cajaduras4) / sizeof(cajaduras4[0]); b++) {
                         if (b != l) { // Don't check collision with itself
                                Rectangle otherBox = {suelos[cajaduras4[b]].x, suelos[cajaduras4[b]].y, 30.0f, 30.0f};
                                    if (CheckCollisionRecs((Rectangle){cajaNewPosition.x, cajaNewPosition.y, caja.width, caja.height}, otherBox)) {
                                        collisionWithBox = true;
                                        break;
                                    }
                                }
                            }
                    // If no collision with wall, move the box
                    if (!collisionWithWall && !collisionWithBox) {
                        suelos[cajaduras4[l]].x = cajaNewPosition.x;
                        suelos[cajaduras4[l]].y = cajaNewPosition.y;
                    }
                }else{empuja = true;}
                }
            }
      
      // Verificar si todas las cajas están en las setas
        for (int i = 0; i < sizeof(cajaduras4) / sizeof(cajaduras4[0]); i++) {
            bool cajaEnSetaLocal = false;
            for (int j = 0; j < sizeof(setas4) / sizeof(setas4[0]); j++) {
                if (fabs(suelos[cajaduras4[i]].x - suelos[setas4[j]].x)<= tolerancia && fabs(suelos[cajaduras4[i]].y - suelos[setas4[j]].y) <= tolerancia) {
                    cambio = true;
                    cajaEnSetaLocal = true;
                    break;
                }
            }
            if (!cajaEnSetaLocal) {
                cajaEnSeta = false;
                break;
            }
        }
        if (cajaEnSeta) {
            tocar = true;
        }
         if (IsKeyPressed(MOVE_CAJAS)) {
            // Mover todas las cajas a las posiciones de las setas
            for (int i = 0; i < sizeof(cajaduras4) / sizeof(cajaduras4[0]); i++) {
                if (i < sizeof(setas4) / sizeof(setas4[0])) {
                    suelos[cajaduras4[i]].x = suelos[setas4[i]].x;
                    suelos[cajaduras4[i]].y = suelos[setas4[i]].y;
                }
            }
        }
       }
    break;
    case CINCO:
     {
                cajaEnSeta = true; // Inicializar a true, asumiendo que todas las cajas están en su posición
                for (int m = 0; m < sizeof(paredes5) / sizeof(paredes5[0]); m++) {
               
                if (IsKeyPressed(MOVE_CAJAS)){
                        // Mover todas las cajas a las posiciones de las setas
                        for (int i = 0; i < sizeof(cajaduras5) / sizeof(cajaduras5[0]); i++) {
                            if (i < sizeof(setas5) / sizeof(setas5[0])) {
                                suelos[cajaduras5[i]].x = suelos[setas5[i]].x;
                                suelos[cajaduras5[i]].y = suelos[setas5[i]].y;
                            }
                        }
                    }
                
                //Colision pared jugador
                Rectangle pared = {suelos[paredes5[m]].x, suelos[paredes5[m]].y, (float)tilesetlargo, (float)tilesetancho};
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRec.width, frameRec.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUp.width, frameRecUp.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDown.width, frameRecDown.height}, pared)){pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDownP.width, frameRecDownP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUpP.width, frameRecUpP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecP.width, frameRecP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                
                //Colision jugador con caja
                for (int l = 0; l < sizeof(cajaduras5) / sizeof(cajaduras5[0]); l++) {
                Rectangle caja = {suelos[cajaduras5[l]].x, suelos[cajaduras5[l]].y, 30.0f, 30.0f};
                //frameRec Animación personaje 1
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, 24, 24}, caja)) {
                    
                   if(IsKeyDown(KEY_RIGHT)){currentAnim = LadosP;}
                   if(IsKeyDown(KEY_LEFT)){currentAnim = LadosP;}
                   if(IsKeyDown(KEY_UP)){currentAnim = UpP;}
                   if(IsKeyDown(KEY_DOWN)){currentAnim = DownP;}
                    pjPosition = Vector2Subtract(pjPosition, pjVelocity);
                    // Move box
                    Vector2 cajaNewPosition = Vector2Add((Vector2){caja.x, caja.y}, pjVelocity);
                    // Check if new box position collides with any wall
                    bool collisionWithWall = false;
                    bool collisionWithBox = false;
                    for (int n = 0; n < sizeof(paredes5) / sizeof(paredes5[0]); n++) {
                        Rectangle pared = {suelos[paredes5[n]].x, suelos[paredes5[n]].y, (float)tilesetlargo, (float)tilesetancho};
                        if (CheckCollisionRecs((Rectangle){cajaNewPosition.x, cajaNewPosition.y, caja.width, caja.height}, pared)) {
                            collisionWithWall = true;
                            break;
                        }
                    }
                     // Check for collision with other boxes
                    for (int b = 0; b < sizeof(cajaduras5) / sizeof(cajaduras5[0]); b++) {
                         if (b != l) { // Don't check collision with itself
                                Rectangle otherBox = {suelos[cajaduras5[b]].x, suelos[cajaduras5[b]].y, 30.0f, 30.0f};
                                    if (CheckCollisionRecs((Rectangle){cajaNewPosition.x, cajaNewPosition.y, caja.width, caja.height}, otherBox)) {
                                        collisionWithBox = true;
                                        break;
                                    }
                                }
                            }
                    // If no collision with wall, move the box
                    if (!collisionWithWall && !collisionWithBox) {
                        suelos[cajaduras5[l]].x = cajaNewPosition.x;
                        suelos[cajaduras5[l]].y = cajaNewPosition.y;
                    }
                }else{empuja = true;}
                }
            }
      
      // Verificar si todas las cajas están en las setas
        for (int i = 0; i < sizeof(cajaduras5) / sizeof(cajaduras5[0]); i++) {
            bool cajaEnSetaLocal = false;
            for (int j = 0; j < sizeof(setas5) / sizeof(setas5[0]); j++) {
                if (fabs(suelos[cajaduras5[i]].x - suelos[setas5[j]].x)<= tolerancia && fabs(suelos[cajaduras5[i]].y - suelos[setas5[j]].y) <= tolerancia) {
                    cambio = true;
                    cajaEnSetaLocal = true;
                    break;
                }
            }
            if (!cajaEnSetaLocal) {
                cajaEnSeta = false;
                break;
            }
        }
        if (cajaEnSeta) {
            tocar = true;
        }
         if (IsKeyPressed(MOVE_CAJAS)) {
            // Mover todas las cajas a las posiciones de las setas
            for (int i = 0; i < sizeof(cajaduras5) / sizeof(cajaduras5[0]); i++) {
                if (i < sizeof(setas5) / sizeof(setas5[0])) {
                    suelos[cajaduras5[i]].x = suelos[setas5[i]].x;
                    suelos[cajaduras5[i]].y = suelos[setas5[i]].y;
                }
            }
        }
       }
    break;
    case SEIS:
     {
                cajaEnSeta = true; // Inicializar a true, asumiendo que todas las cajas están en su posición
                for (int m = 0; m < sizeof(paredes6) / sizeof(paredes6[0]); m++) {
               
                if (IsKeyPressed(MOVE_CAJAS)){
                        // Mover todas las cajas a las posiciones de las setas
                        for (int i = 0; i < sizeof(cajaduras) / sizeof(cajaduras[0]); i++) {
                            if (i < sizeof(setas6) / sizeof(setas6[0])) {
                                suelos[cajaduras6[i]].x = suelos[setas6[i]].x;
                                suelos[cajaduras6[i]].y = suelos[setas6[i]].y;
                            }
                        }
                    }
                
                //Colision pared jugador
                Rectangle pared = {suelos[paredes6[m]].x, suelos[paredes6[m]].y, (float)tilesetlargo, (float)tilesetancho};
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRec.width, frameRec.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUp.width, frameRecUp.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDown.width, frameRecDown.height}, pared)){pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDownP.width, frameRecDownP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUpP.width, frameRecUpP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecP.width, frameRecP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                
                //Colision jugador con caja
                for (int l = 0; l < sizeof(cajaduras6) / sizeof(cajaduras6[0]); l++) {
                Rectangle caja = {suelos[cajaduras6[l]].x, suelos[cajaduras6[l]].y, 30.0f, 30.0f};
                //frameRec Animación personaje 1
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, 24, 24}, caja)) {
                    
                   if(IsKeyDown(KEY_RIGHT)){currentAnim = LadosP;}
                   if(IsKeyDown(KEY_LEFT)){currentAnim = LadosP;}
                   if(IsKeyDown(KEY_UP)){currentAnim = UpP;}
                   if(IsKeyDown(KEY_DOWN)){currentAnim = DownP;}
                    pjPosition = Vector2Subtract(pjPosition, pjVelocity);
                    // Move box
                    Vector2 cajaNewPosition = Vector2Add((Vector2){caja.x, caja.y}, pjVelocity);
                    // Check if new box position collides with any wall
                    bool collisionWithWall = false;
                    bool collisionWithBox = false;
                    for (int n = 0; n < sizeof(paredes6) / sizeof(paredes6[0]); n++) {
                        Rectangle pared = {suelos[paredes6[n]].x, suelos[paredes6[n]].y, (float)tilesetlargo, (float)tilesetancho};
                        if (CheckCollisionRecs((Rectangle){cajaNewPosition.x, cajaNewPosition.y, caja.width, caja.height}, pared)) {
                            collisionWithWall = true;
                            break;
                        }
                    }
                     // Check for collision with other boxes
                    for (int b = 0; b < sizeof(cajaduras6) / sizeof(cajaduras6[0]); b++) {
                         if (b != l) { // Don't check collision with itself
                                Rectangle otherBox = {suelos[cajaduras6[b]].x, suelos[cajaduras6[b]].y, 30.0f, 30.0f};
                                    if (CheckCollisionRecs((Rectangle){cajaNewPosition.x, cajaNewPosition.y, caja.width, caja.height}, otherBox)) {
                                        collisionWithBox = true;
                                        break;
                                    }
                                }
                            }
                    // If no collision with wall, move the box
                    if (!collisionWithWall && !collisionWithBox) {
                        suelos[cajaduras6[l]].x = cajaNewPosition.x;
                        suelos[cajaduras6[l]].y = cajaNewPosition.y;
                    }
                }else{empuja = true;}
                }
            }
      
      // Verificar si todas las cajas están en las setas
        for (int i = 0; i < sizeof(cajaduras6) / sizeof(cajaduras6[0]); i++) {
            bool cajaEnSetaLocal = false;
            for (int j = 0; j < sizeof(setas6) / sizeof(setas6[0]); j++) {
                if (fabs(suelos[cajaduras6[i]].x - suelos[setas6[j]].x)<= tolerancia && fabs(suelos[cajaduras6[i]].y - suelos[setas6[j]].y) <= tolerancia) {
                    cambio = true;
                    cajaEnSetaLocal = true;
                    break;
                }
            }
            if (!cajaEnSetaLocal) {
                cajaEnSeta = false;
                break;
            }
        }
        if (cajaEnSeta) {
            tocar = true;
        }
         if (IsKeyPressed(MOVE_CAJAS)) {
            // Mover todas las cajas a las posiciones de las setas
            for (int i = 0; i < sizeof(cajaduras6) / sizeof(cajaduras6[0]); i++) {
                if (i < sizeof(setas) / sizeof(setas[0])) {
                    suelos[cajaduras6[i]].x = suelos[setas6[i]].x;
                    suelos[cajaduras6[i]].y = suelos[setas6[i]].y;
                }
            }
        }
       }
    break;
    case SIETE:
    {
                cajaEnSeta = true; // Inicializar a true, asumiendo que todas las cajas están en su posición
                for (int m = 0; m < sizeof(paredes7) / sizeof(paredes7[0]); m++) {
               
                if (IsKeyPressed(MOVE_CAJAS)){
                        // Mover todas las cajas a las posiciones de las setas
                        for (int i = 0; i < sizeof(cajaduras7) / sizeof(cajaduras7[0]); i++) {
                            if (i < sizeof(setas7) / sizeof(setas7[0])) {
                                suelos[cajaduras7[i]].x = suelos[setas7[i]].x;
                                suelos[cajaduras7[i]].y = suelos[setas7[i]].y;
                            }
                        }
                    }
                
                //Colision pared jugador
                Rectangle pared = {suelos[paredes7[m]].x, suelos[paredes7[m]].y, (float)tilesetlargo, (float)tilesetancho};
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRec.width, frameRec.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUp.width, frameRecUp.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDown.width, frameRecDown.height}, pared)){pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDownP.width, frameRecDownP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUpP.width, frameRecUpP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecP.width, frameRecP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                
                //Colision jugador con caja
                for (int l = 0; l < sizeof(cajaduras7) / sizeof(cajaduras7[0]); l++) {
                Rectangle caja = {suelos[cajaduras7[l]].x, suelos[cajaduras7[l]].y, 30.0f, 30.0f};
                //frameRec Animación personaje 1
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, 24, 24}, caja)) {
                    
                   if(IsKeyDown(KEY_RIGHT)){currentAnim = LadosP;}
                   if(IsKeyDown(KEY_LEFT)){currentAnim = LadosP;}
                   if(IsKeyDown(KEY_UP)){currentAnim = UpP;}
                   if(IsKeyDown(KEY_DOWN)){currentAnim = DownP;}
                    pjPosition = Vector2Subtract(pjPosition, pjVelocity);
                    // Move box
                    Vector2 cajaNewPosition = Vector2Add((Vector2){caja.x, caja.y}, pjVelocity);
                    // Check if new box position collides with any wall
                    bool collisionWithWall = false;
                    bool collisionWithBox = false;
                    for (int n = 0; n < sizeof(paredes7) / sizeof(paredes7[0]); n++) {
                        Rectangle pared = {suelos[paredes7[n]].x, suelos[paredes7[n]].y, (float)tilesetlargo, (float)tilesetancho};
                        if (CheckCollisionRecs((Rectangle){cajaNewPosition.x, cajaNewPosition.y, caja.width, caja.height}, pared)) {
                            collisionWithWall = true;
                            break;
                        }
                    }
                     // Check for collision with other boxes
                    for (int b = 0; b < sizeof(cajaduras7) / sizeof(cajaduras7[0]); b++) {
                         if (b != l) { // Don't check collision with itself
                                Rectangle otherBox = {suelos[cajaduras7[b]].x, suelos[cajaduras7[b]].y, 30.0f, 30.0f};
                                    if (CheckCollisionRecs((Rectangle){cajaNewPosition.x, cajaNewPosition.y, caja.width, caja.height}, otherBox)) {
                                        collisionWithBox = true;
                                        break;
                                    }
                                }
                            }
                    // If no collision with wall, move the box
                    if (!collisionWithWall && !collisionWithBox) {
                        suelos[cajaduras7[l]].x = cajaNewPosition.x;
                        suelos[cajaduras7[l]].y = cajaNewPosition.y;
                    }
                }else{empuja = true;}
                }
            }
      
      // Verificar si todas las cajas están en las setas
        for (int i = 0; i < sizeof(cajaduras7) / sizeof(cajaduras7[0]); i++) {
            bool cajaEnSetaLocal = false;
            for (int j = 0; j < sizeof(setas7) / sizeof(setas7[0]); j++) {
                if (fabs(suelos[cajaduras7[i]].x - suelos[setas7[j]].x)<= tolerancia && fabs(suelos[cajaduras7[i]].y - suelos[setas7[j]].y) <= tolerancia) {
                    cambio = true;
                    cajaEnSetaLocal = true;
                    break;
                }
            }
            if (!cajaEnSetaLocal) {
                cajaEnSeta = false;
                break;
            }
        }
        if (cajaEnSeta) {
            tocar = true;
        }
         if (IsKeyPressed(MOVE_CAJAS)) {
            // Mover todas las cajas a las posiciones de las setas
            for (int i = 0; i < sizeof(cajaduras7) / sizeof(cajaduras7[0]); i++) {
                if (i < sizeof(setas7) / sizeof(setas7[0])) {
                    suelos[cajaduras7[i]].x = suelos[setas7[i]].x;
                    suelos[cajaduras7[i]].y = suelos[setas7[i]].y;
                }
            }
        }
       }
    break;
    case OCHO:
     {
                cajaEnSeta = true; // Inicializar a true, asumiendo que todas las cajas están en su posición
                for (int m = 0; m < sizeof(paredes8) / sizeof(paredes8[0]); m++) {
               
                if (IsKeyPressed(MOVE_CAJAS)){
                        // Mover todas las cajas a las posiciones de las setas
                        for (int i = 0; i < sizeof(cajaduras8) / sizeof(cajaduras8[0]); i++) {
                            if (i < sizeof(setas8) / sizeof(setas8[0])) {
                                suelos[cajaduras8[i]].x = suelos[setas8[i]].x;
                                suelos[cajaduras8[i]].y = suelos[setas8[i]].y;
                            }
                        }
                    }
                
                //Colision pared jugador
                Rectangle pared = {suelos[paredes8[m]].x, suelos[paredes8[m]].y, (float)tilesetlargo, (float)tilesetancho};
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRec.width, frameRec.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUp.width, frameRecUp.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDown.width, frameRecDown.height}, pared)){pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecDownP.width, frameRecDownP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecUpP.width, frameRecUpP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, frameRecP.width, frameRecP.height}, pared)){ pjPosition = Vector2Subtract(pjPosition, pjVelocity);}
                
                //Colision jugador con caja
                for (int l = 0; l < sizeof(cajaduras8) / sizeof(cajaduras8[0]); l++) {
                Rectangle caja = {suelos[cajaduras8[l]].x, suelos[cajaduras8[l]].y, 30.0f, 30.0f};
                //frameRec Animación personaje 1
                if (CheckCollisionRecs((Rectangle){pjPosition.x, pjPosition.y, 24, 24}, caja)) {
                    
                   if(IsKeyDown(KEY_RIGHT)){currentAnim = LadosP;}
                   if(IsKeyDown(KEY_LEFT)){currentAnim = LadosP;}
                   if(IsKeyDown(KEY_UP)){currentAnim = UpP;}
                   if(IsKeyDown(KEY_DOWN)){currentAnim = DownP;}
                    pjPosition = Vector2Subtract(pjPosition, pjVelocity);
                    // Move box
                    Vector2 cajaNewPosition = Vector2Add((Vector2){caja.x, caja.y}, pjVelocity);
                    // Check if new box position collides with any wall
                    bool collisionWithWall = false;
                    bool collisionWithBox = false;
                    for (int n = 0; n < sizeof(paredes8) / sizeof(paredes8[0]); n++) {
                        Rectangle pared = {suelos[paredes8[n]].x, suelos[paredes8[n]].y, (float)tilesetlargo, (float)tilesetancho};
                        if (CheckCollisionRecs((Rectangle){cajaNewPosition.x, cajaNewPosition.y, caja.width, caja.height}, pared)) {
                            collisionWithWall = true;
                            break;
                        }
                    }
                     // Check for collision with other boxes
                    for (int b = 0; b < sizeof(cajaduras8) / sizeof(cajaduras8[0]); b++) {
                         if (b != l) { // Don't check collision with itself
                                Rectangle otherBox = {suelos[cajaduras8[b]].x, suelos[cajaduras8[b]].y, 30.0f, 30.0f};
                                    if (CheckCollisionRecs((Rectangle){cajaNewPosition.x, cajaNewPosition.y, caja.width, caja.height}, otherBox)) {
                                        collisionWithBox = true;
                                        break;
                                    }
                                }
                            }
                    // If no collision with wall, move the box
                    if (!collisionWithWall && !collisionWithBox) {
                        suelos[cajaduras8[l]].x = cajaNewPosition.x;
                        suelos[cajaduras8[l]].y = cajaNewPosition.y;
                    }
                }else{empuja = true;}
                }
            }
      
      // Verificar si todas las cajas están en las setas
        for (int i = 0; i < sizeof(cajaduras8) / sizeof(cajaduras8[0]); i++) {
            bool cajaEnSetaLocal = false;
            for (int j = 0; j < sizeof(setas8) / sizeof(setas8[0]); j++) {
                if (fabs(suelos[cajaduras8[i]].x - suelos[setas8[j]].x)<= tolerancia && fabs(suelos[cajaduras8[i]].y - suelos[setas8[j]].y) <= tolerancia) {
                    cambio = true;
                    cajaEnSetaLocal = true;
                    break;
                }
            }
            if (!cajaEnSetaLocal) {
                cajaEnSeta = false;
                break;
            }
        }
        if (cajaEnSeta) {
            tocar = true;
        }
         if (IsKeyPressed(MOVE_CAJAS)) {
            // Mover todas las cajas a las posiciones de las setas
            for (int i = 0; i < sizeof(cajaduras8) / sizeof(cajaduras8[0]); i++) {
                if (i < sizeof(setas8) / sizeof(setas8[0])) {
                    suelos[cajaduras8[i]].x = suelos[setas8[i]].x;
                    suelos[cajaduras8[i]].y = suelos[setas8[i]].y;
                }
            }
        }
       }
    break;
    
} 


        // Detección y corrección de colisiones con las paredes de ladrillos
        
        }else{
            //pasar a pantalla win
                PlayMusicStream(music[2]);
                if (NivelSelec == SIETE || NivelSelec == UNO || NivelSelec == TRES || NivelSelec == CINCO) {StopMusicStream(music[1]);}
                if (NivelSelec == DOS || NivelSelec == CUATRO || NivelSelec == SEIS || NivelSelec == OCHO) {StopMusicStream(music[6]);}
                currentScreen = WIN;
            };}
            else{
            //pasar a pantalla lose
                PlayMusicStream(music[3]);
                if (NivelSelec == SIETE || NivelSelec == UNO || NivelSelec == TRES || NivelSelec == CINCO) {StopMusicStream(music[1]);}
                if (NivelSelec == DOS || NivelSelec == CUATRO || NivelSelec == SEIS || NivelSelec == OCHO) {StopMusicStream(music[6]);}
              //  int cajaduras[] = {66, 83, 95,};
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
                    switch(niveldado){
                    case 1:
                    {
                        pjPosition.x =128.0f;
                        pjPosition.y =32.0f;//vector de posicion del pj, spawn del personaje Lvl2
                        limitepasos = 120;
                      //CAMBIAR POSI A NIVEL 2
                 if (IsKeyPressed(KEY_ENTER))
                    {
                        PlayMusicStream(music[6]);
                        StopMusicStream(music[2]);
                        NivelSelec = DOS;
                        niveldado++;
                        currentScreen = GAMEPLAY;
                    }
                    }break;
                    case 2:
                    {
                            pjPosition.x =160.0f;
                            pjPosition.y =96.0f;//vector de posicion del pj, spawn del personaje Lvl3
                            limitepasos = 50;
                      //CAMBIAR POSI A NIVEL 3
                 if (IsKeyPressed(KEY_ENTER))
                    {
                        PlayMusicStream(music[1]);
                        StopMusicStream(music[2]);
                        NivelSelec = TRES;
                        niveldado++;
                        currentScreen = GAMEPLAY;
                    }
                    }break;
                    case 3:
                    {
                        pjPosition.x =128.0f;
                        pjPosition.y =128.0f;//vector de posicion del pj, spawn del personaje Lvl4
                        limitepasos = 140;
                      //CAMBIAR POSI A NIVEL 4
                 if (IsKeyPressed(KEY_ENTER))
                    {
                        PlayMusicStream(music[6]);
                        StopMusicStream(music[2]);
                        NivelSelec = CUATRO;
                        niveldado++;
                        currentScreen = GAMEPLAY;
                    }
                    }break;
                    case 4:
                    {
                      pjPosition.x =160.0f;
                      pjPosition.y =64.0f;//vector de posicion del pj, spawn del personaje Lvl5
                      limitepasos = 65;
                      //CAMBIAR POSI A NIVEL 5
                 if (IsKeyPressed(KEY_ENTER))
                    {
                        PlayMusicStream(music[1]);
                        StopMusicStream(music[2]);
                        NivelSelec = CINCO;
                        niveldado++;
                        currentScreen = GAMEPLAY;
                    }
                    }break;
                    case 5:
                    {
                        pjPosition.x =352.0f;
                        pjPosition.y =128.0f;//vector de posicion del pj, spawn del personaje Lvl6
                        limitepasos = 60;
                      //CAMBIAR POSI A NIVEL 6
                 if (IsKeyPressed(KEY_ENTER))
                    {
                        PlayMusicStream(music[6]);
                        StopMusicStream(music[2]);
                        NivelSelec = SEIS;
                        niveldado++;
                        currentScreen = GAMEPLAY;
                    }
                    }break;
                    case 6:
                    {
                        pjPosition.x =160.0f;
                        pjPosition.y =160.0f;//vector de posicion del pj, spawn del personaje Lvl7
                        limitepasos = 80;
                      //CAMBIAR POSI A NIVEL 7
                 if (IsKeyPressed(KEY_ENTER))
                    {
                        PlayMusicStream(music[1]);
                        StopMusicStream(music[2]);
                        NivelSelec = SIETE;
                        niveldado++;
                        currentScreen = GAMEPLAY;
                    }
                    }break;
                    case 7:
                    {
                        pjPosition.x =320.0f;
                        pjPosition.y =256.0f;//vector de posicion del pj, spawn del personaje Lvl8
                        limitepasos = 160;
                      //CAMBIAR POSI A NIVEL 8
                 if (IsKeyPressed(KEY_ENTER))
                    {
                        PlayMusicStream(music[6]);
                        StopMusicStream(music[2]);
                        NivelSelec = OCHO;
                        niveldado++;
                        currentScreen = GAMEPLAY;
                    }
                    }break;
                    case 8:
                    {
                        if (IsKeyPressed(KEY_ENTER))
                {
                   PlayMusicStream(music[0]);
                    StopMusicStream(music[2]);
                    //CAMBIAR AQUI PARA EL SELECT MENU
                    niveldado = 1;
                    currentScreen = TITLE;
                }
                    }break;
                    }
            } break;
            case FAIL:
            {
                pasos=0;
                paso = false;
                // TODO: Update ENDING screen variables here!
                UpdateMusicStream(music[3]);
                    switch(niveldado){
                    case 1:
                    {
                      pjPosition.x =192.0f;
                      pjPosition.y =74.0f;
                        /*
                      //vector de posicion del pj, spawn del personaje Lvl1
                              for (int i = 0; i < sizeof(suelos) / sizeof(suelos[0]); i++) {
                                  for (int z = 0; z < sizeof(cajadurasquenocambian) / sizeof(cajadurasquenocambian[0]); z++) {
                        DrawTextureRec(fondo, caja, (Vector2){suelos[cajadurasquenocambian[z]].x, suelos[cajadurasquenocambian[z]].y}, WHITE);
                    }
                              }
                              */
                      //cajadurasquenocambian
                 if (IsKeyPressed(KEY_ENTER))
                    {
                        PlayMusicStream(music[1]);
                        StopMusicStream(music[3]);
                        NivelSelec = UNO;
                        currentScreen = GAMEPLAY;
                    }
                    }break;
                    case 2:
                    {
                        pjPosition.x =128.0f;
                        pjPosition.y =32.0f;
                        if (IsKeyPressed(KEY_ENTER))
                    {
                        PlayMusicStream(music[6]);
                        StopMusicStream(music[3]);
                        NivelSelec = DOS;
                        currentScreen = GAMEPLAY;
                    }
                    }break;
                    case 3:
                    {
                        pjPosition.x =160.0f;
                        pjPosition.y =96.0f;
                    if (IsKeyPressed(KEY_ENTER))
                    {
                        PlayMusicStream(music[1]);
                        StopMusicStream(music[3]);
                        NivelSelec = TRES;
                        currentScreen = GAMEPLAY;
                    }
                    }break;
                    case 4:
                    {
                          pjPosition.x =128.0f;
                          pjPosition.y =128.0f;
                        if (IsKeyPressed(KEY_ENTER))
                    {
                        PlayMusicStream(music[6]);
                        StopMusicStream(music[3]);
                        NivelSelec = CUATRO;
                        currentScreen = GAMEPLAY;
                    }
                    }break;
                    case 5:
                    {
                        pjPosition.x =160.0f;
                        pjPosition.y =64.0f;
                        if (IsKeyPressed(KEY_ENTER))
                    {
                        PlayMusicStream(music[1]);
                        StopMusicStream(music[3]);
                        NivelSelec = CINCO;
                        currentScreen = GAMEPLAY;
                    }
                    }break;
                    case 6:
                    {
                        pjPosition.x =352.0f;
                        pjPosition.y =128.0f;
                        if (IsKeyPressed(KEY_ENTER))
                    {
                        PlayMusicStream(music[6]);
                        StopMusicStream(music[3]);
                        NivelSelec = SEIS;
                        currentScreen = GAMEPLAY;
                    }
                    }break;
                    case 7:
                    {
                        pjPosition.x =160.0f;
                        pjPosition.y =160.0f;
                        if (IsKeyPressed(KEY_ENTER))
                    {
                        PlayMusicStream(music[1]);
                        StopMusicStream(music[3]);
                        NivelSelec = SIETE;
                        currentScreen = GAMEPLAY;
                    }
                    }break;
                    case 8:
                    {
                        pjPosition.x =320.0f;
                        pjPosition.y =256.0f;
                     if (IsKeyPressed(KEY_ENTER))
                    {
                        PlayMusicStream(music[6]);
                        StopMusicStream(music[3]);
                        NivelSelec = OCHO;
                        currentScreen = GAMEPLAY;
                    }
                    }break;
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
                 case ANIMATION:
                 {
                    ClearBackground(RAYWHITE);
                   DrawTexture(animacion[currentFrame], 0, 0, WHITE);               
                } break; 
                case TITLE:
                {
                    ClearBackground(RAYWHITE);//limpiar pantalla
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);//fondo negro
                    DrawTexture(textures[1], 0, 0, WHITE);

                } break;
                case SelectLevel:
                {
                    ClearBackground(RAYWHITE);//limpiar pantalla
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);//fondo negro
                    DrawTexture(textures[5], 0, 0, WHITE);

                } break;
                case GAMEPLAY:
                {
                    ClearBackground(RAYWHITE);//limpiar pantalla
                     int x, i, t;
                     
       
        for(i=0;i<screenWidth;i+= tilesetancho){ //dibujar a lo ancho
            for(x =0;x<screenHeight;x += tilesetlargo){ // dibujar a lo alto
            Vector2 bloques = {i, x};//vector de posicion bloques
             DrawTextureRec(fondo, naranja, bloques, WHITE);//dibujar textura naranja en pantalla usando un rectangulo
            }
        }//cargar fondo del mapa
        
        for(i=0;i<screenHeight;i+= tilesetlargo){ //dibujar a lo alto 
            for(x =0;x<tilesetancho;x += 1){ // dibujar a lo ancho
                t=x+420;
                DrawRectangle(x, i, 32, 32, BLACK);//dibujar rectangulo negro en pantalla 
                DrawRectangle(t, i, 32, 32, BLACK);//dibujar rectangulo negro en pantalla 
            }
        }//cargar fondo del mapa


switch (NivelSelec) {
  case UNO:
  

            ClearBackground(RAYWHITE);//limpiar pantalla
            // Dibujar las paredes
        for (int i = 0; i < sizeof(suelos) / sizeof(suelos[0]); i++) {
                    for (int j = 0; j < sizeof(paredes) / sizeof(paredes[0]); j++) {
            DrawTextureRec(fondo, ladrillo, (Vector2){suelos[paredes[j]].x, suelos[paredes[j]].y}, WHITE);
                    }
                    for (int p = 0; p < sizeof(suelogris) / sizeof(suelogris[0]); p++) {
            DrawTextureRec(fondo, suelo, (Vector2){suelos[suelogris[p]].x, suelos[suelogris[p]].y}, WHITE);
                    }
                    for (int s = 0; s < sizeof(setas) / sizeof(setas[0]); s++) {
            DrawTextureRec(fondo, rosa, (Vector2){suelos[setas[s]].x, suelos[setas[s]].y}, WHITE);
                    }
                    for (int z = 0; z < sizeof(cajaduras) / sizeof(cajaduras[0]); z++) {
                        if(cambio == true){
                            DrawTextureRec(fondo, cajausada, (Vector2){suelos[cajaduras[z]].x, suelos[cajaduras[z]].y}, WHITE);
                        }else{
                            DrawTextureRec(fondo, caja, (Vector2){suelos[cajaduras[z]].x, suelos[cajaduras[z]].y}, WHITE);
                        }
            
                    }
                    for (int z = 0; z < sizeof(cajayapuesta) / sizeof(cajayapuesta[0]); z++) {
            DrawTextureRec(fondo, cajausada, (Vector2){suelos[cajayapuesta[z]].x, suelos[cajayapuesta[z]].y}, WHITE);
                    }
                    
        }
        
        if (CollitionMode)
                {
                    // Iterar sobre las paredes y dibujar sus rectángulos de colisión
                    for (int i = 0; i < sizeof(paredes) / sizeof(paredes[0]); i++) {
                        for (int j = 0; j < sizeof(cajaduras) / sizeof(cajaduras[0]); j++) {
                        Rectangle caja = {suelos[cajaduras[j]].x, suelos[cajaduras[j]].y, (float)tilesetlargo, (float)tilesetancho};
                        DrawRectangleLines(caja.x, caja.y, caja.width, caja.height, WHITE);
                        }                                    
                        Rectangle pared = {suelos[paredes[i]].x, suelos[paredes[i]].y, (float)tilesetlargo, (float)tilesetancho};
                        DrawRectangleLines(pared.x, pared.y, pared.width, pared.height, RED);

                    }
                    
                    Vector2 hitboxPosition = {pjPosition.x, pjPosition.y};

                    // Dibujar el cuadrado de la hitbox encima del personaje
                    DrawRectangleLines(hitboxPosition.x, hitboxPosition.y, 22, 32, BLUE);

                    // Resto de rectángulos de colisión a dibujar...
                }
    break;  
  case DOS:
  
            ClearBackground(RAYWHITE);//limpiar pantalla
            // Dibujar las paredes
        for (int i = 0; i < sizeof(suelos) / sizeof(suelos[0]); i++) {
                                for (int p = 0; p < sizeof(suelogris2) / sizeof(suelogris2[0]); p++) {
            DrawTextureRec(fondo, suelo, (Vector2){suelos[suelogris2[p]].x, suelos[suelogris2[p]].y}, WHITE);
                    }
                    for (int j = 0; j < sizeof(paredes2) / sizeof(paredes2[0]); j++) {
            DrawTextureRec(fondo, ladrillo, (Vector2){suelos[paredes2[j]].x, suelos[paredes2[j]].y}, WHITE);
                    }
                    for (int s = 0; s < sizeof(setas2) / sizeof(setas2[0]); s++) {
            DrawTextureRec(fondo, rosa, (Vector2){suelos[setas2[s]].x, suelos[setas2[s]].y}, WHITE);
                    }
                    for (int z = 0; z < sizeof(cajaduras2) / sizeof(cajaduras2[0]); z++) {
                        if(cambio == true){
                            DrawTextureRec(fondo, caja, (Vector2){suelos[cajaduras2[z]].x, suelos[cajaduras2[z]].y}, WHITE);
                        }else{
                             DrawTextureRec(fondo, cajausada, (Vector2){suelos[cajaduras2[z]].x, suelos[cajaduras2[z]].y}, WHITE);
                        }
                    }
                    for (int z = 0; z < sizeof(cajayapuesta2) / sizeof(cajayapuesta2[0]); z++) {
            DrawTextureRec(fondo, cajausada, (Vector2){suelos[cajayapuesta2[z]].x, suelos[cajayapuesta2[z]].y}, WHITE);
                    }
                    
        }
        
        if (CollitionMode)
                {
                    // Iterar sobre las paredes y dibujar sus rectángulos de colisión
                    for (int i = 0; i < sizeof(2) / sizeof(paredes2[0]); i++) {
                        for (int j = 0; j < sizeof(cajaduras2) / sizeof(cajaduras2[0]); j++) {
                        Rectangle caja = {suelos[cajaduras2[j]].x, suelos[cajaduras2[j]].y, (float)tilesetlargo, (float)tilesetancho};
                        DrawRectangleLines(caja.x, caja.y, caja.width, caja.height, WHITE);
                        }
                        Rectangle pared = {suelos[paredes2[i]].x, suelos[paredes2[i]].y, (float)tilesetlargo, (float)tilesetancho};
                        DrawRectangleLines(pared.x, pared.y, pared.width, pared.height, RED);
                    }
                    Vector2 hitboxPosition = {pjPosition.x, pjPosition.y};

                    // Dibujar el cuadrado de la hitbox encima del personaje
                    DrawRectangleLines(hitboxPosition.x, hitboxPosition.y, 22, 32, BLUE);

                    // Resto de rectángulos de colisión a dibujar...
                }
    break;
   case TRES:
   ClearBackground(RAYWHITE);//limpiar pantalla
                // Dibujar las paredes
        for (int i = 0; i < sizeof(suelos) / sizeof(suelos[0]); i++) {
                    for (int p = 0; p < sizeof(suelogris3) / sizeof(suelogris3[0]); p++) {
            DrawTextureRec(fondo, suelo, (Vector2){suelos[suelogris3[p]].x, suelos[suelogris3[p]].y}, WHITE);
                    }
                    for (int j = 0; j < sizeof(paredes3) / sizeof(paredes3[0]); j++) {
            DrawTextureRec(fondo, ladrillo, (Vector2){suelos[paredes3[j]].x, suelos[paredes3[j]].y}, WHITE);
                    }
                    for (int s = 0; s < sizeof(setas3) / sizeof(setas3[0]); s++) {
            DrawTextureRec(fondo, rosa, (Vector2){suelos[setas3[s]].x, suelos[setas3[s]].y}, WHITE);
                    }
                    for (int z = 0; z < sizeof(cajaduras3) / sizeof(cajaduras3[0]); z++) {
                        if(cambio == true){
                            DrawTextureRec(fondo, caja, (Vector2){suelos[cajaduras3[z]].x, suelos[cajaduras3[z]].y}, WHITE);
                        }else{
                            DrawTextureRec(fondo, cajausada, (Vector2){suelos[cajaduras3[z]].x, suelos[cajaduras3[z]].y}, WHITE);
                        }
                    }
                    for (int z = 0; z < sizeof(cajayapuesta3) / sizeof(cajayapuesta3[0]); z++) {
            DrawTextureRec(fondo, cajausada, (Vector2){suelos[cajayapuesta3[z]].x, suelos[cajayapuesta3[z]].y}, WHITE);
                    }
        }
        
        if (CollitionMode)
                {
                    // Iterar sobre las paredes y dibujar sus rectángulos de colisión
                    for (int i = 0; i < sizeof(2) / sizeof(paredes3[0]); i++) {
                        for (int j = 0; j < sizeof(cajaduras3) / sizeof(cajaduras3[0]); j++) {
                        Rectangle caja = {suelos[cajaduras3[j]].x, suelos[cajaduras3[j]].y, (float)tilesetlargo, (float)tilesetancho};
                        DrawRectangleLines(caja.x, caja.y, caja.width, caja.height, WHITE);
                        }
                        Rectangle pared = {suelos[paredes3[i]].x, suelos[paredes3[i]].y, (float)tilesetlargo, (float)tilesetancho};
                        DrawRectangleLines(pared.x, pared.y, pared.width, pared.height, RED);
                    }
                    Vector2 hitboxPosition = {pjPosition.x, pjPosition.y};

                    // Dibujar el cuadrado de la hitbox encima del personaje
                    DrawRectangleLines(hitboxPosition.x, hitboxPosition.y, 22, 32, BLUE);

                    // Resto de rectángulos de colisión a dibujar...
                }
    break;
  case CUATRO:
            ClearBackground(RAYWHITE);//limpiar pantalla
                    // Dibujar las paredes
        for (int i = 0; i < sizeof(suelos) / sizeof(suelos[0]); i++) {
                    for (int p = 0; p < sizeof(suelogris4) / sizeof(suelogris4[0]); p++) {
            DrawTextureRec(fondo, suelo, (Vector2){suelos[suelogris4[p]].x, suelos[suelogris4[p]].y}, WHITE);
                    }
                    for (int j = 0; j < sizeof(paredes4) / sizeof(paredes4[0]); j++) {
            DrawTextureRec(fondo, ladrillo, (Vector2){suelos[paredes4[j]].x, suelos[paredes4[j]].y}, WHITE);
                    }
                    for (int s = 0; s < sizeof(setas4) / sizeof(setas4[0]); s++) {
            DrawTextureRec(fondo, rosa, (Vector2){suelos[setas4[s]].x, suelos[setas4[s]].y}, WHITE);
                    }
                    for (int z = 0; z < sizeof(cajaduras4) / sizeof(cajaduras4[0]); z++) {
                        if(cambio == true){
                            DrawTextureRec(fondo, caja, (Vector2){suelos[cajaduras4[z]].x, suelos[cajaduras4[z]].y}, WHITE);
                        }else{
                            DrawTextureRec(fondo, cajausada, (Vector2){suelos[cajaduras4[z]].x, suelos[cajaduras4[z]].y}, WHITE);
                        }
                   }
                    for (int z = 0; z < sizeof(cajayapuesta4) / sizeof(cajayapuesta4[0]); z++) {
            DrawTextureRec(fondo, cajausada, (Vector2){suelos[cajayapuesta4[z]].x, suelos[cajayapuesta4[z]].y}, WHITE);
                    }
                    
        }
        
        if (CollitionMode)
                {
                    // Iterar sobre las paredes y dibujar sus rectángulos de colisión
                    for (int i = 0; i < sizeof(2) / sizeof(paredes4[0]); i++) {
                        for (int j = 0; j < sizeof(cajaduras4) / sizeof(cajaduras4[0]); j++) {
                        Rectangle caja = {suelos[cajaduras4[j]].x, suelos[cajaduras4[j]].y, (float)tilesetlargo, (float)tilesetancho};
                        DrawRectangleLines(caja.x, caja.y, caja.width, caja.height, WHITE);
                        }
                        Rectangle pared = {suelos[paredes4[i]].x, suelos[paredes4[i]].y, (float)tilesetlargo, (float)tilesetancho};
                        DrawRectangleLines(pared.x, pared.y, pared.width, pared.height, RED);
                    }
                    Vector2 hitboxPosition = {pjPosition.x, pjPosition.y};

                    // Dibujar el cuadrado de la hitbox encima del personaje
                    DrawRectangleLines(hitboxPosition.x, hitboxPosition.y, 22, 32, BLUE);

                    // Resto de rectángulos de colisión a dibujar...
                }
    break;
   case CINCO:
        ClearBackground(RAYWHITE);//limpiar pantalla
                        // Dibujar las paredes
        for (int i = 0; i < sizeof(suelos) / sizeof(suelos[0]); i++) {
                    for (int p = 0; p < sizeof(suelogris5) / sizeof(suelogris5[0]); p++) {
            DrawTextureRec(fondo, suelo, (Vector2){suelos[suelogris5[p]].x, suelos[suelogris5[p]].y}, WHITE);
                    }
                    for (int j = 0; j < sizeof(paredes5) / sizeof(paredes5[0]); j++) {
            DrawTextureRec(fondo, ladrillo, (Vector2){suelos[paredes5[j]].x, suelos[paredes5[j]].y}, WHITE);
                    }
                    for (int s = 0; s < sizeof(setas5) / sizeof(setas5[0]); s++) {
            DrawTextureRec(fondo, rosa, (Vector2){suelos[setas5[s]].x, suelos[setas5[s]].y}, WHITE);
                    }
                    for (int z = 0; z < sizeof(cajaduras5) / sizeof(cajaduras5[0]); z++) {
                        if(cambio == true){
                            DrawTextureRec(fondo, caja, (Vector2){suelos[cajaduras5[z]].x, suelos[cajaduras5[z]].y}, WHITE);
                        }else{
                            DrawTextureRec(fondo, cajausada, (Vector2){suelos[cajaduras5[z]].x, suelos[cajaduras5[z]].y}, WHITE);
                        }
                    }
                    for (int z = 0; z < sizeof(cajayapuesta5) / sizeof(cajayapuesta5[0]); z++) {
            DrawTextureRec(fondo, cajausada, (Vector2){suelos[cajayapuesta5[z]].x, suelos[cajayapuesta5[z]].y}, WHITE);
                    }
                    
        }
        
        if (CollitionMode)
                {
                    // Iterar sobre las paredes y dibujar sus rectángulos de colisión
                    for (int i = 0; i < sizeof(2) / sizeof(paredes5[0]); i++) {
                        for (int j = 0; j < sizeof(cajaduras5) / sizeof(cajaduras5[0]); j++) {
                        Rectangle caja = {suelos[cajaduras5[j]].x, suelos[cajaduras5[j]].y, (float)tilesetlargo, (float)tilesetancho};
                        DrawRectangleLines(caja.x, caja.y, caja.width, caja.height, WHITE);
                        }
                        Rectangle pared = {suelos[paredes5[i]].x, suelos[paredes5[i]].y, (float)tilesetlargo, (float)tilesetancho};
                        DrawRectangleLines(pared.x, pared.y, pared.width, pared.height, RED);
                    }
                    Vector2 hitboxPosition = {pjPosition.x, pjPosition.y};

                    // Dibujar el cuadrado de la hitbox encima del personaje
                    DrawRectangleLines(hitboxPosition.x, hitboxPosition.y, 22, 32, BLUE);

                    // Resto de rectángulos de colisión a dibujar...
                }
    break;
  case SEIS:
        ClearBackground(RAYWHITE);//limpiar pantalla
                            // Dibujar las paredes
        for (int i = 0; i < sizeof(suelos) / sizeof(suelos[0]); i++) {
                    for (int p = 0; p < sizeof(suelogris6) / sizeof(suelogris6[0]); p++) {
            DrawTextureRec(fondo, suelo, (Vector2){suelos[suelogris6[p]].x, suelos[suelogris6[p]].y}, WHITE);
                    }
                    for (int j = 0; j < sizeof(paredes6) / sizeof(paredes6[0]); j++) {
            DrawTextureRec(fondo, ladrillo, (Vector2){suelos[paredes6[j]].x, suelos[paredes6[j]].y}, WHITE);
                    }
                     for (int s = 0; s < sizeof(setas6) / sizeof(setas6[0]); s++) {
            DrawTextureRec(fondo, rosa, (Vector2){suelos[setas6[s]].x, suelos[setas6[s]].y}, WHITE);
                    }
                    for (int z = 0; z < sizeof(cajaduras6) / sizeof(cajaduras6[0]); z++) {
                        if(cambio == true){
                            DrawTextureRec(fondo, caja, (Vector2){suelos[cajaduras6[z]].x, suelos[cajaduras6[z]].y}, WHITE);
                        }else{
                            DrawTextureRec(fondo, caja, (Vector2){suelos[cajaduras6[z]].x, suelos[cajaduras6[z]].y}, WHITE);
                        }
                    }
                    for (int z = 0; z < sizeof(cajayapuesta6) / sizeof(cajayapuesta6[0]); z++) {
            DrawTextureRec(fondo, cajausada, (Vector2){suelos[cajayapuesta6[z]].x, suelos[cajayapuesta6[z]].y}, WHITE);
                    }
                   
        }
        
        if (CollitionMode)
                {
                    // Iterar sobre las paredes y dibujar sus rectángulos de colisión
                    for (int i = 0; i < sizeof(2) / sizeof(paredes6[0]); i++) {
                        for (int j = 0; j < sizeof(cajaduras6) / sizeof(cajaduras6[0]); j++) {
                        Rectangle caja = {suelos[cajaduras6[j]].x, suelos[cajaduras6[j]].y, (float)tilesetlargo, (float)tilesetancho};
                        DrawRectangleLines(caja.x, caja.y, caja.width, caja.height, WHITE);
                        }
                        Rectangle pared = {suelos[paredes6[i]].x, suelos[paredes6[i]].y, (float)tilesetlargo, (float)tilesetancho};
                        DrawRectangleLines(pared.x, pared.y, pared.width, pared.height, RED);
                    }
                    Vector2 hitboxPosition = {pjPosition.x, pjPosition.y};

                    // Dibujar el cuadrado de la hitbox encima del personaje
                    DrawRectangleLines(hitboxPosition.x, hitboxPosition.y, 22, 32, BLUE);

                    // Resto de rectángulos de colisión a dibujar...
                }
    break;
   case SIETE:
        ClearBackground(RAYWHITE);//limpiar pantalla
   
                                // Dibujar las paredes
        for (int i = 0; i < sizeof(suelos) / sizeof(suelos[0]); i++) {
                    for (int p = 0; p < sizeof(suelogris7) / sizeof(suelogris7[0]); p++) {
            DrawTextureRec(fondo, suelo, (Vector2){suelos[suelogris7[p]].x, suelos[suelogris7[p]].y}, WHITE);
                    }
                    for (int j = 0; j < sizeof(paredes7) / sizeof(paredes7[0]); j++) {
            DrawTextureRec(fondo, ladrillo, (Vector2){suelos[paredes7[j]].x, suelos[paredes7[j]].y}, WHITE);
                    }
                     for (int s = 0; s < sizeof(setas7) / sizeof(setas7[0]); s++) {
            DrawTextureRec(fondo, rosa, (Vector2){suelos[setas7[s]].x, suelos[setas7[s]].y}, WHITE);
                    }
                    for (int z = 0; z < sizeof(cajaduras7) / sizeof(cajaduras7[0]); z++) {
                        if(cambio == true){
                            DrawTextureRec(fondo, caja, (Vector2){suelos[cajaduras7[z]].x, suelos[cajaduras7[z]].y}, WHITE);
                        }else{
                            DrawTextureRec(fondo, cajausada, (Vector2){suelos[cajaduras7[z]].x, suelos[cajaduras7[z]].y}, WHITE);
                        }
                    }
                    for (int z = 0; z < sizeof(cajayapuesta7) / sizeof(cajayapuesta7[0]); z++) {
            DrawTextureRec(fondo, cajausada, (Vector2){suelos[cajayapuesta7[z]].x, suelos[cajayapuesta7[z]].y}, WHITE);
                    }
                   
        }
        
        if (CollitionMode)
                {
                    // Iterar sobre las paredes y dibujar sus rectángulos de colisión
                    for (int i = 0; i < sizeof(2) / sizeof(paredes7[0]); i++) {
                        for (int j = 0; j < sizeof(cajaduras7) / sizeof(cajaduras7[0]); j++) {
                        Rectangle caja = {suelos[cajaduras7[j]].x, suelos[cajaduras7[j]].y, (float)tilesetlargo, (float)tilesetancho};
                        DrawRectangleLines(caja.x, caja.y, caja.width, caja.height, WHITE);
                        }
                        Rectangle pared = {suelos[paredes7[i]].x, suelos[paredes7[i]].y, (float)tilesetlargo, (float)tilesetancho};
                        DrawRectangleLines(pared.x, pared.y, pared.width, pared.height, RED);
                    }
                    Vector2 hitboxPosition = {pjPosition.x, pjPosition.y};

                    // Dibujar el cuadrado de la hitbox encima del personaje
                    DrawRectangleLines(hitboxPosition.x, hitboxPosition.y, 22, 32, BLUE);

                    // Resto de rectángulos de colisión a dibujar...
                }
    break;
  case OCHO:
        ClearBackground(RAYWHITE);//limpiar pantalla
                                    // Dibujar las paredes
        for (int i = 0; i < sizeof(suelos) / sizeof(suelos[0]); i++) {
                    for (int p = 0; p < sizeof(suelogris8) / sizeof(suelogris8[0]); p++) {
            DrawTextureRec(fondo, suelo, (Vector2){suelos[suelogris8[p]].x, suelos[suelogris8[p]].y}, WHITE);
                    }
                    for (int j = 0; j < sizeof(paredes8) / sizeof(paredes8[0]); j++) {
            DrawTextureRec(fondo, ladrillo, (Vector2){suelos[paredes8[j]].x, suelos[paredes8[j]].y}, WHITE);
                    }
                     for (int s = 0; s < sizeof(setas8) / sizeof(setas8[0]); s++) {
            DrawTextureRec(fondo, rosa, (Vector2){suelos[setas8[s]].x, suelos[setas8[s]].y}, WHITE);
                    }
                    for (int z = 0; z < sizeof(cajaduras8) / sizeof(cajaduras8[0]); z++) {
                        if(cambio == true){
                            DrawTextureRec(fondo, caja, (Vector2){suelos[cajaduras8[z]].x, suelos[cajaduras8[z]].y}, WHITE);
                        }else{
                          DrawTextureRec(fondo, caja, (Vector2){suelos[cajaduras8[z]].x, suelos[cajaduras8[z]].y}, WHITE);  
                        }
                    }
                    for (int z = 0; z < sizeof(cajayapuesta8) / sizeof(cajayapuesta8[0]); z++) {
            DrawTextureRec(fondo, cajausada, (Vector2){suelos[cajayapuesta8[z]].x, suelos[cajayapuesta8[z]].y}, WHITE);
                    }
                   
        }
        
        if (CollitionMode)
                {
                    // Iterar sobre las paredes y dibujar sus rectángulos de colisión
                    for (int i = 0; i < sizeof(2) / sizeof(paredes8[0]); i++) {
                        for (int j = 0; j < sizeof(cajaduras8) / sizeof(cajaduras8[0]); j++) {
                        Rectangle caja = {suelos[cajaduras8[j]].x, suelos[cajaduras8[j]].y, (float)tilesetlargo, (float)tilesetancho};
                        DrawRectangleLines(caja.x, caja.y, caja.width, caja.height, WHITE);
                        }
                        Rectangle pared = {suelos[paredes8[i]].x, suelos[paredes8[i]].y, (float)tilesetlargo, (float)tilesetancho};
                        DrawRectangleLines(pared.x, pared.y, pared.width, pared.height, RED);
                    }
                    Vector2 hitboxPosition = {pjPosition.x, pjPosition.y};

                    // Dibujar el cuadrado de la hitbox encima del personaje
                    DrawRectangleLines(hitboxPosition.x, hitboxPosition.y, 22, 32, BLUE);

                    // Resto de rectángulos de colisión a dibujar...
                }
    break;
  default:
}

        DrawText(TextFormat("STAGE: %d", niveldado), 288, 45, 5, YELLOW);//nivel en el que estas
        DrawText(TextFormat("STEP: %d", pasos), 288, 60, 5, YELLOW);//Pasos que ha dado el pj
        DrawText(TextFormat("LIMIT: %d", limitepasos), 288, 70, 5, YELLOW);//maximo de pasos que se pueden dar por pantalla
        DrawTexture(marco, 285, 40, WHITE);//dibujar marco puntuacion
            switch(currentAnim)
            {

                 case Lados:
                {
                     
                    //if(empuja = true){
                        DrawTextureRec(pj, frameRec, pjPosition, WHITE);
                   /* }
                    if(empuja = false){
                        DrawTextureRec(pj, frameRecP, pjPosition, WHITE);
                    }  */               

                } break;
                case Up:
                {
                    
                    //if(empuja = true){
                        DrawTextureRec(pj, frameRecUp, pjPosition, WHITE);
                   /* } 
                    if(empuja = false){
                        DrawTextureRec(pj, frameRecUpP, pjPosition, WHITE);
                    }*/
                    

                } break;
                case Down:
                {
                    
                    //if(empuja = true){
                        DrawTextureRec(pj, frameRecDown, pjPosition, WHITE);
                   /* }
                    if(empuja = false){
                        DrawTextureRec(pj, frameRecDownP, pjPosition, WHITE);
                    }*/
                    

                } break;
                case DownP:
                { 
                        empuja = false;
                        DrawTextureRec(pj, frameRecDownP, pjPosition, WHITE);                    

                } break;
                case UpP:
                { 
                        empuja = false;
                        DrawTextureRec(pj, frameRecUpP, pjPosition, WHITE);                   

                } break;
                case LadosP:
                { 
                        empuja = false;
                        DrawTextureRec(pj, frameRecP, pjPosition, WHITE);                    

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
    for (int i = 0; i < NUM_ANIM; i++) UnloadTexture(animacion[i]);
    for (int i = 0; i < NUM_MUSIC; i++) UnloadMusicStream(music[i]);
    UnloadTexture(pj);
    UnloadTexture(marco);
    UnloadTexture(fondo);
    UnloadTexture(fondo);
    CloseAudioDevice();
    CloseWindow();       
   
    return 0;
}