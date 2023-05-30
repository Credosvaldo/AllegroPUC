#include <iostream>

#include <allegro5/allegro5.h>//biblioteca padrao do allegro
#include <allegro5/allegro_primitives.h>//biblioteca para desenhar formas na tela
#include <allegro5/allegro_font.h>//biblioteca pra escrever na tela

#define DISP_W 640//largura da tela
#define DISP_H 480//altura da tela

//Codigo do teclado
#define SEEN 1
#define RELEASED 2

struct Circle
{
    int posX;
    int posY;
    int raio;
};


int main()
{
    ALLEGRO_EVENT event;//representa o evento atual
    bool done = false;//true quando a aplicacao for encerrada
    bool logic = false;//true quando evento timer for acionado
    int mouseClickPositionX = 0;//posicao x do mouse quando clicar
    int mouseClickPositionY = 0;//posicao y do mouse quando clicar

    unsigned char key[ALLEGRO_KEY_MAX];//representa os inputs do teclado
    memset(key, 0, sizeof(key));//limpa o array key


    al_init();//inicializa o allegro

    al_init_font_addon();//inicializa o font addon do allegro (necessario pra escrever na tela)
    al_init_primitives_addon();//inicilaiza o primitives addon do allegro (necessario pra desenhar na tela)


    al_install_keyboard();//installa o teclado pro allegro
    al_install_mouse();//installa o mouse pro allegro


    ALLEGRO_DISPLAY *display = al_create_display(DISP_W, DISP_H);//cria a tela
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();//cria a fila de eventos
    ALLEGRO_FONT *font = al_create_builtin_font();//cria o font
    ALLEGRO_TIMER *timer = al_create_timer(1.0/60.0);//cria o timer


    al_register_event_source(queue, al_get_display_event_source(display));//registra os eventos do display na fila
    al_register_event_source(queue, al_get_timer_event_source(timer));//registra os eventos do timer na fila
    al_register_event_source(queue, al_get_keyboard_event_source());//registra os eventos do teclado na fila
    al_register_event_source(queue, al_get_mouse_event_source());//registra os eventos do mouse na fila

    struct Circle circle = {DISP_W/2, DISP_H/2, 20};//inicializa um circle (essa variavel representa o circulo desenhado na tela)

    al_start_timer(timer);//inicializa o timer
    //enquanto a aplicacao nao fechar faca
    while (!done)
    {
        al_wait_for_event(queue, &event);//espera o proximo evento

        //verifica o proximo evento
        switch (event.type)
        {
            //Aciona qunado a tela e fechada
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;

            //Aciona qunado bate o timer
            case ALLEGRO_EVENT_TIMER:
                logic = true;
            break;

            //Aciona quando precionada alguma tecla
            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = SEEN | RELEASED;
                break;

            //Aciona qunado solta alguma tecla
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= RELEASED;
                break;

            //Aciona quando precionado algum botao do mouse
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(event.mouse.button & 1)//Quando o botao precionado for o esquerdo
                {
                    mouseClickPositionX = event.mouse.x;
                    mouseClickPositionY = event.mouse.y;
                }
                break;
        }

        if(logic)
        {
            //KEYBOARD
            for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
            {
                key[i] &= SEEN;
            }

            //move o circulo pra direita sempre que precionada a tecla right (setinha pra direita)
            if(key[ALLEGRO_KEY_RIGHT])
            {
                circle.posX++;
            }

            //move o circulo pra esquerda sempre que precionada a tecla left (setinha pra esquerda)
            if(key[ALLEGRO_KEY_LEFT])
            {
                circle.posX--;
            }
            
            //DRAW
            al_clear_to_color(al_map_rgb(0,0,0));//limpa a tela a recolorindo toda de preto

            al_draw_filled_circle(circle.posX, circle.posY, circle.raio, al_map_rgb(255,255,255));//desenha o circulo na tela
            al_draw_textf(font, al_map_rgb(255,255,255), DISP_W/100, 30, 0, "Voce clicou na posicao x: %d y: %d", mouseClickPositionX, mouseClickPositionY);//escreve na tela a posicao do mouse quando clicar na tela

            al_flip_display();//atualiza a tela



            logic = false;
        }


    }

    //Destroy tudo que foi criado pelo allegro
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_font(font);
    al_destroy_timer(timer);


    return 0;
}




//DESAFIOS:
//
// Faca com que o circulo se mova tambem no eixo y 
// Faca com que o circulo se mova mais rapido
// Mude a cor do circulo
// 
//
//
//