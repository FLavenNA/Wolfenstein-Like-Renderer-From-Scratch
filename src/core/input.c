#include "input.h"
#include "engine.h"

#include <stdio.h>

void input_init(keymap_t *key_map, key_states_t *key_states)
{
    key_map->forward = SDL_SCANCODE_W;
    key_map->backward = SDL_SCANCODE_S;
    key_map->left = SDL_SCANCODE_A;
    key_map->right = SDL_SCANCODE_D;
    key_map->strafe_left = SDL_SCANCODE_Q;
    key_map->strafe_right = SDL_SCANCODE_E;
    key_map->toggle_map = SDL_SCANCODE_M;
    key_map->quit = SDL_SCANCODE_ESCAPE;

    key_states->forward = false;
    key_states->backward = false;
    key_states->left = false;
    key_states->right = false;
    key_states->strafe_left = false;
    key_states->strafe_right = false;
    key_states->map_state = false;
    key_states->quit = false;
}

void handle_input(engine_t *engine, float delta_time)
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        // TODO: Handle events here
        switch(event.type) 
        {
            case SDL_EVENT_QUIT:
                engine->state = QUIT;
                break;
            case SDL_EVENT_KEY_DOWN:
                handle_real_time_keys(event.key.scancode, KEY_STATE_DOWN, &engine->key_map, &engine->key_states);
                break;
            case SDL_EVENT_KEY_UP:
                handle_real_time_keys(event.key.scancode, KEY_STATE_UP, &engine->key_map, &engine->key_states);
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                int new_width, new_height;
                SDL_GetWindowSize(engine->graphics.window, &new_width, &new_height);
                graphics_resize(&engine->graphics, new_width, new_height);
                break;
            default: 
                break;
        }
    }
    process_key_states(&engine->key_states, &engine->player, delta_time);
}

void process_key_states(const key_states_t *key_states, player_t *player, const float delta_time)
{
    if (key_states->forward)
    {
        player->position.x += MOV_SPEED * cos(player->dir_angle) * delta_time;
        player->position.y += MOV_SPEED * sin(player->dir_angle) * delta_time;
    }
    else if (key_states->backward)
    {
        player->position.x -= MOV_SPEED * cos(player->dir_angle) * delta_time;
        player->position.y -= MOV_SPEED * sin(player->dir_angle) * delta_time;
    }

    if (key_states->left)
        player->dir_angle -= ROT_SPEED * delta_time;
    else if (key_states->right)
        player->dir_angle += ROT_SPEED * delta_time;

    if (key_states->strafe_left)
    {
        player->position.x -= MOV_SPEED * cos(player->dir_angle + M_PI / 2) * delta_time;
        player->position.y -= MOV_SPEED * sin(player->dir_angle + M_PI / 2) * delta_time;
    }
    else if (key_states->strafe_right)
    {
        player->position.x += MOV_SPEED * cos(player->dir_angle + M_PI / 2) * delta_time;
        player->position.y += MOV_SPEED * sin(player->dir_angle + M_PI / 2) * delta_time;
    }
}

void handle_real_time_keys(const SDL_Scancode scan_code, const kdb_key_state_t state, const keymap_t *key_map,  key_states_t *key_states)
{
    if (scan_code == key_map->forward)
        key_states->forward = state;
    else if (scan_code == key_map->backward)
        key_states->backward = state;

    if (scan_code == key_map->left)
        key_states->left = state;
    else if (scan_code == key_map->right)
        key_states->right = state;

    if (scan_code == key_map->strafe_left)
        key_states->strafe_left = state;
    else if (scan_code == key_map->strafe_right) 
        key_states->strafe_right = state;
}