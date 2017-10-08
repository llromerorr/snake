#include "stdio.h"
#include "windows.h"
#include "conio.h"
#include "iostream"

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESC 27
#define ENTER 13

using namespace std;
int x, y;
bool Game_Over=false;
int dir = 2, CabezaX = 50, CabezaY = 12;
char boton;
int Ubicacion_Cuerpo [2][2000];
int tam = 4;
int n=1, e=2;   //Bucles
int velocidad=100;
int ComidaX=20, ComidaY=20;
int point = 0;
int Dificultad_Hud=2;
int Durabilidad_Contador =-1000;
int Durabilidad =0;

//PROTOTIPOS
    void Menu_Principal();
    
//FUNCIONES
    void gotoxy(int x, int y){
        HANDLE hCon;
        hCon = GetStdHandle(STD_OUTPUT_HANDLE);

        COORD dwPos;
        dwPos.X = x;
        dwPos.Y = y;
        SetConsoleCursorPosition(hCon, dwPos);
    }
        
    void OcultaCursor(){
        CONSOLE_CURSOR_INFO cci = {100, FALSE};
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
    }

    void Cambio_de_Pantalla(){
        for (int i = 1; i <= 2; i++){                                //Efecto de Intro
            for (int yIntro = 1; yIntro <= 25; yIntro++){
                for (int i = 1; i <= 60; i++){
                    y = yIntro ;
                    gotoxy(i, yIntro);
                    printf("%c", 219);
                }
                Sleep(1);
            }

            for (int yIntro2 = 1; yIntro2 <= 25; yIntro2++){
                for (int i = 1; i <= 60; i++){
                    y = yIntro2 ;
                    gotoxy(i, yIntro2);
                    printf(" ");
                }
                Sleep(1);
            }
        }
    }

    void Cambio_de_Pantalla_Corto(){
        for (int i = 1; i <= 1; i++){                                //Efecto de Intro
            for (int yIntro = 1; yIntro <= 25; yIntro++){
                for (int i = 1; i <= 60; i++){
                    y = yIntro ;
                    gotoxy(i, yIntro);
                    printf("%c", 219);
                }
                Sleep(1);
            }

            for (int yIntro2 = 1; yIntro2 <= 25; yIntro2++){
                for (int i = 1; i <= 60; i++){
                	y = yIntro2 ;
                	gotoxy(i, yIntro2);
                	printf(" ");
                }
                Sleep(1);
            }
        }
    }

    void Limpiar_Pantalla(){
        for (int yIntro2 = 1; yIntro2 <= 25; yIntro2++){
            for (int i = 1; i <= 60; i++){
                y = yIntro2 ;
                gotoxy(i, yIntro2);
                printf(" ");
            }
            Sleep(10);
        }
    }

    void Probar_Teclas(){
        char q;
        while (Game_Over==false){
            if(kbhit()){
                q=getch();
                printf("%d",q);
            }
        }
    }

    void Pintar_Cuerpo(){
        gotoxy(CabezaX,CabezaY);
        printf("o");                                           //IMPRIMRIR CABEZA        
    }

    void tocar_boton(){
        if(kbhit()){
            boton=getch();                                      //CAMBIAR DIRECCION AL TOCAR BOTON
            if (boton==ARRIBA && dir!=3) dir = 1;
            else if (boton==DERECHA && dir!=4) dir = 2;
            else if (boton==ABAJO && dir!=1) dir = 3;
            else if (boton==IZQUIERDA && dir!=2) dir = 4;
        }
    }
        
    void Almacenar_Cuerpo(){
        Ubicacion_Cuerpo[0][n]= CabezaX;
        Ubicacion_Cuerpo[1][n]= CabezaY;
        if (n>tam) n=0;n++;
    }

    void Borrar_Cuerpo(){
        gotoxy(Ubicacion_Cuerpo[0][e],Ubicacion_Cuerpo[1][e]);
        printf(" ");
        Ubicacion_Cuerpo[0][e] = 0;Ubicacion_Cuerpo[1][e]=0;
        if(e>tam) e=0; e++;
    }

    void bordes_limites(){
        //Esquinas
        x = 1; y = 6;gotoxy(x, y);printf("%c", 201); //Superio Izquierdo
        x = 60; y = 6;gotoxy(x, y);printf("%c", 187); //Superio Derecho
        x = 1; y = 25; gotoxy(x, y);printf("%c", 200); //Inferior Izquierdo
        x = 60; y = 25;gotoxy(x, y);printf("%c", 188); //Inferior Derecho

        //Bordes
        for (int B_su = 2; B_su <= 59; B_su = B_su + 1){y = 6;gotoxy(B_su, y);printf("%c", 205);} //Borde Superior
        for (int B_in = 2; B_in <= 59; B_in = B_in + 1){y = 25;gotoxy(B_in, y);printf("%c", 205);} //Borde Inferior
        for (int B_iz = 7; B_iz <= 24; B_iz = B_iz + 1){x = 1;gotoxy(x, B_iz);printf("%c", 186);} //Borde Izquierdo
        for (int B_de = 7; B_de <= 24; B_de = B_de + 1){x = 60;gotoxy(x, B_de);printf("%c", 186);} //Borde Derecho
    }

    void Verificar_Colosion()
    {
        int a=1;
        while(a<=tam){
            if(Ubicacion_Cuerpo[0][a]==CabezaX && Ubicacion_Cuerpo[1][a]==CabezaY){
                Game_Over=true;
            }
            a++;
        }
        if (CabezaX==1 || CabezaX==60 || CabezaY == 6 || CabezaY == 25) {
            Game_Over = true;
        }      
    }

    void Comida_Generador (){
        if(ComidaX == CabezaX && ComidaY == CabezaY){
            ComidaX = (rand() % 57) + 2;
            ComidaY = (rand() % 17) + 7;
            tam++;
            gotoxy(ComidaX,ComidaY);
            printf("%c", 254);
            point=point+10;
        }

        else{
            gotoxy(ComidaX,ComidaY);
            printf("%c", 254);
        }
    }

    void Movimiento_Automatico(){
        switch(dir){                    //MOVIMIENTO AUTOMATICO DEL CUERPO
            case 1: CabezaY--; break;
            case 2: CabezaX++; break;
            case 3: CabezaY++; break;
            case 4: CabezaX--; break;
        }
    }

    void HUD(){
        gotoxy(1,3);cout<<"Score: "<<point;
        switch(Dificultad_Hud){
            case 1: gotoxy(1,1);cout<<"Dificultad: Facil"; break;
            case 2: gotoxy(1,1);cout<<"Dificultad: Normal"; break;
            case 3: gotoxy(1,1);cout<<"Dificultad: Dificil"; break;
            case 4: gotoxy(1,1);cout<<"Dificultad: Modo Destruccion"; break;
        }

        Durabilidad_Contador=Durabilidad_Contador+5;
        if(Durabilidad_Contador>=0){
            gotoxy(30,1);cout<<"                ";
            Durabilidad++;
            gotoxy(40,1);
            cout<<"Resistente x"<<Durabilidad;
            Durabilidad_Contador = -1000;
        }
    }

    void Reiniciar_Valores(){
        Game_Over=false;
        dir = 2;
        CabezaX = 50;
        CabezaY = 12;
        tam = 4;
        n=1, e=2; //Bucles
        ComidaX=20;
        ComidaY=20;
        point = 0;

        int av=1;

        while(av<=tam){
            Ubicacion_Cuerpo[0][av] =0;
            Ubicacion_Cuerpo[1][av]=0;
            av++;
        }
    }

//NIVELES
    Juego_Nivel0(){
        OcultaCursor();
        Cambio_de_Pantalla_Corto();
        system ("color 3f");

        while (Game_Over == false){
            HUD();
            tocar_boton();
            tocar_boton();
            bordes_limites();
            Pintar_Cuerpo();
            Verificar_Colosion();
            Comida_Generador ();
            Almacenar_Cuerpo();
            Borrar_Cuerpo();
            Sleep(velocidad);
            Movimiento_Automatico();
        }
    
        if(Game_Over == true){
            system ("color 4f");
            Sleep (500);
            Limpiar_Pantalla();
            gotoxy (28,13); printf("GAME OVER");
            gotoxy (28,14); printf("Score: %d",point);
            getch();
        }
        getch();
    }

//PANTALLAS
    void Menu_Dificultad(){
        OcultaCursor();
        system ("color 3f");
        Cambio_de_Pantalla_Corto();
            
        //Esquinas y bordes-----------------------------------------------------------------------------------------------
            x = 1; y = 1;gotoxy(x, y);printf("%c", 206); //Superio Izquierdo
            x = 60; y = 1;gotoxy(x, y);printf("%c", 206); //Superio Derecho
            x = 1; y = 25; gotoxy(x, y);printf("%c", 206); //Inferior Izquierdo
            x = 60; y = 25;gotoxy(x, y);printf("%c", 206); //Inferior Derecho

            for (int B_su = 2; B_su <= 59; B_su = B_su + 1){y = 1;gotoxy(B_su, y);printf("%c", 206);} //Borde Superior
            for (int B_in = 2; B_in <= 59; B_in = B_in + 1){y = 25;gotoxy(B_in, y);printf("%c", 206);} //Borde Inferior
            for (int B_iz = 2; B_iz <= 24; B_iz = B_iz + 1){x = 1;gotoxy(x, B_iz);printf("%c", 206);} //Borde Izquierdo
            for (int B_de = 2; B_de <= 24; B_de = B_de + 1){x = 60;gotoxy(x, B_de);printf("%c", 206);} //Borde Derecho
        //----------------------------------------------------------------------------------------------------------------

        //Opciones--------------------------------------------------------------------------------------------------------
            gotoxy(30,15); cout<<"Facil";
            gotoxy(30,16); cout<<"Normal";
            gotoxy(30,17); cout<<"Dificil";
            gotoxy(30,18); cout<<"MODO DESTRUCCION";
            gotoxy(30,20); cout<<"Atras";
        //----------------------------------------------------------------------------------------------------------------
            
        //Escoger Opcion--------------------------------------------------------------------------------------------------
            bool Escoger = false;
            int Selecion_Menu_Dificultad; int Objetivo_Seleccion_Menu_Dificultad = 1;

            while(Escoger==false){
                if(kbhit()){
                    Selecion_Menu_Dificultad=getch();                                
                    if (Selecion_Menu_Dificultad==ARRIBA) Objetivo_Seleccion_Menu_Dificultad--;
                    else if (Selecion_Menu_Dificultad==ABAJO) Objetivo_Seleccion_Menu_Dificultad++;
                    else if (Selecion_Menu_Dificultad==ENTER) Escoger=true;
                }
                    
                    
                switch(Objetivo_Seleccion_Menu_Dificultad){
                    case 1:
                        gotoxy(26,15); printf("%c%c", 62,62); 
                        gotoxy(26,16); printf("  ");
                        gotoxy(26,17); printf("  "); 
                        gotoxy(26,18); printf("  "); 
                        gotoxy(26,20); printf("  "); 
                        break;

                    case 2:
                        gotoxy(26,16); printf("%c%c", 62,62); 
                        gotoxy(26,15); printf("  ");
                        gotoxy(26,17); printf("  "); 
                        gotoxy(26,18); printf("  "); 
                        gotoxy(26,20); printf("  "); 
                        break;

                    case 3: 
                        gotoxy(26,17); printf("%c%c", 62,62); 
                        gotoxy(26,15); printf("  ");
                        gotoxy(26,16); printf("  "); 
                        gotoxy(26,18); printf("  "); 
                        gotoxy(26,20); printf("  "); 
                        break;

                    case 4:
                        gotoxy(26,18); printf("%c%c", 62,62); 
                        gotoxy(26,15); printf("  ");
                        gotoxy(26,16); printf("  "); 
                        gotoxy(26,17); printf("  "); 
                        gotoxy(26,20); printf("  "); 
                        break;

                    case 0:
                        gotoxy(26,20); printf("%c%c", 62,62); 
                        gotoxy(26,15); printf("  ");
                        gotoxy(26,17); printf("  "); 
                        gotoxy(26,16); printf("  "); 
                        gotoxy(26,18); printf("  "); 
                        break;
                }

                if (Objetivo_Seleccion_Menu_Dificultad >4) Objetivo_Seleccion_Menu_Dificultad=0;
                else if (Objetivo_Seleccion_Menu_Dificultad <0) Objetivo_Seleccion_Menu_Dificultad=4;

                Selecion_Menu_Dificultad=2000;
                Sleep(5);
            }
        //----------------------------------------------------------------------------------------------------------------

        //Condicion cada Opcion-------------------------------------------------------------------------------------------
            switch(Objetivo_Seleccion_Menu_Dificultad){
            case 0: Menu_Principal(); break;
            case 1: velocidad=160; Dificultad_Hud=1; Menu_Principal(); break;
            case 2: velocidad=100; Dificultad_Hud=2; Menu_Principal(); break;
            case 3: velocidad=40; Dificultad_Hud=3; Menu_Principal(); break;
            case 4: velocidad=20; Dificultad_Hud=4; Menu_Principal(); break;}
        //----------------------------------------------------------------------------------------------------------------
    }

    void Menu_Principal(){
        OcultaCursor();
        Cambio_de_Pantalla_Corto();
        system ("color 3f");
        Reiniciar_Valores();
            
        //Esquinas y bordes---------------------------------------------------------------------------------------------
            x = 1; y = 1;gotoxy(x, y);printf("%c", 206); //Superio Izquierdo
            x = 60; y = 1;gotoxy(x, y);printf("%c", 206); //Superio Derecho
            x = 1; y = 25; gotoxy(x, y);printf("%c", 206); //Inferior Izquierdo
            x = 60; y = 25;gotoxy(x, y);printf("%c", 206); //Inferior Derecho

            for (int B_su = 2; B_su <= 59; B_su = B_su + 1){y = 1;gotoxy(B_su, y);printf("%c", 206);} //Borde Superior
            for (int B_in = 2; B_in <= 59; B_in = B_in + 1){y = 25;gotoxy(B_in, y);printf("%c", 206);} //Borde Inferior
            for (int B_iz = 2; B_iz <= 24; B_iz = B_iz + 1){x = 1;gotoxy(x, B_iz);printf("%c", 206);} //Borde Izquierdo
            for (int B_de = 2; B_de <= 24; B_de = B_de + 1){x = 60;gotoxy(x, B_de);printf("%c", 206);} //Borde Derecho

        //----------------------------------------------------------------------------------------------------------------

        //Opciones-------------------------------
            gotoxy(30,20); cout<<"JUGAR";
            gotoxy(30,22); cout<<"DIFICULTAD";
        //---------------------------------------

        bool Escoger = false;
            
        //Escoger Opcion-----------------------------------------------------------------------------------
            int Selecion_Menu_Principal, Objetivo_Seleccion_Menu_Principal = 0;
               
            while(Escoger==false){
                if(kbhit()){
                    Selecion_Menu_Principal=getch();                                
                    if (Selecion_Menu_Principal==ARRIBA) Objetivo_Seleccion_Menu_Principal++;
                    if (Selecion_Menu_Principal==ABAJO) Objetivo_Seleccion_Menu_Principal--;
                    if (Selecion_Menu_Principal==ENTER) Escoger=true;
                }

                switch(Objetivo_Seleccion_Menu_Principal){
                    case 0: gotoxy(26,20); printf("%c%c", 62,62); gotoxy(26,22); printf("  "); break;
                    case 1: gotoxy(26,22); printf("%c%c", 62,62); gotoxy(26,20); printf("  "); break;
                }

                if (Objetivo_Seleccion_Menu_Principal >1) Objetivo_Seleccion_Menu_Principal=0;
                else if (Objetivo_Seleccion_Menu_Principal <0) Objetivo_Seleccion_Menu_Principal=1;

                Selecion_Menu_Principal=2000;
                Sleep(5);
            }
        //---------------------------------------------------------------------------------------------------

            switch(Objetivo_Seleccion_Menu_Principal){
                case 0: Juego_Nivel0(); break;
                case 1: Menu_Dificultad(); break;
            }
    }
