/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: bulat
 *
 * Created on 29 октября 2021 г., 1:19
 */
#include <SFML/Graphics.hpp>
#include <cmath>

int speed = 100;

const int map_size_x = 32;
const int map_size_y = 24;
float tile_size = 1024 / map_size_x;
int map[map_size_x][map_size_y] = {
    {},
    {0, 0, 0, 4},
    {0, 0, 0, 4},
    {0, 0, 0, 4},
    {0, 0, 0, 4},
    {4, 4, 4, 4}
};


float player_x_pos = 0;
float player_y_pos = 0;

int mouse_x_pos = 0;
int mouse_y_pos = 0;

void map_init() {
    int water_x_pos = map_size_x, water_y_pos = 0;
    map[water_x_pos][water_y_pos] = 3;
    int step = 0;
    int n_w_y_p = water_y_pos, n_w_x_p = water_x_pos;
    for (int i = water_x_pos; i > 0; i--) {
        n_w_x_p -= 1;
        if (step % 2 == 0) {
            n_w_y_p += 1;
        }
        if (n_w_y_p < map_size_y && n_w_y_p > 0)
            map[n_w_x_p][n_w_y_p - 1] = 2;

        if (n_w_y_p < map_size_y && n_w_y_p > 1)
            map[n_w_x_p][n_w_y_p - 2] = 2;

        if (n_w_y_p < map_size_y - 4 && n_w_y_p>-5)
            map[n_w_x_p][n_w_y_p + 4] = 2;

        if (n_w_y_p < map_size_y - 5 && n_w_y_p>-6)
            map[n_w_x_p][n_w_y_p + 5] = 2;

        if (n_w_y_p < map_size_y && n_w_y_p>-1)
            map[n_w_x_p][n_w_y_p] = 3;

        if (n_w_y_p < map_size_y - 1 && n_w_y_p>-2)
            map[n_w_x_p][n_w_y_p + 1] = 3;

        if (n_w_y_p < map_size_y - 2 && n_w_y_p>-3)
            map[n_w_x_p][n_w_y_p + 2] = 3;

        if (n_w_y_p < map_size_y - 3 && n_w_y_p>-4)
            map[n_w_x_p][n_w_y_p + 3] = 3;

        step++;
    }
}

int main(int argc, char** argv) {

    sf::Texture tile_texture;
    if (!tile_texture.loadFromFile("tiles.png")) {
    }
    map_init();

    sf::RenderWindow window(sf::VideoMode(1024, 768), "Game", sf::Style::Fullscreen);
    sf::Texture player_texture;
    if (!player_texture.loadFromFile("player.png"));
    sf::Sprite player(player_texture, sf::IntRect(0, 0, 43, 64));
    player.setOrigin(16, 32);
    player.setPosition(player_x_pos, player_y_pos);
    player.setScale(0.5f, 0.5f);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time elaps = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            if (event.type == sf::Event::MouseMoved) {
                mouse_x_pos = sf::Mouse::getPosition().x;
                mouse_y_pos = sf::Mouse::getPosition().y;
            }

        }
        window.clear(sf::Color(0, 0, 0));

        for (int i = 0; i < map_size_x; i++) {
            for (int j = 0; j < map_size_y; j++) {
                sf::RectangleShape tile;
                tile.setSize(sf::Vector2f(tile_size, tile_size));
                tile.setPosition(i * tile_size, j * tile_size);
                tile.setTexture(&tile_texture);
                tile.setTextureRect(sf::IntRect(map[i][j]*512, 0, 512, 512));
                window.draw(tile);
            }
        }

        player.setPosition(player_x_pos, player_y_pos);
        player.setRotation(atan2(mouse_y_pos - player.getPosition().y, mouse_x_pos - player.getPosition().x)*(180 / M_PI));
        window.draw(player);

        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (map[(int) floor((player_x_pos) / tile_size)][((int) floor((player_y_pos) / tile_size)) - 1] != 4)
                player_y_pos -= speed * elaps.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (map[((int) floor((player_x_pos) / tile_size)) - 1][(int) floor((player_y_pos) / tile_size)] != 4)
                player_x_pos -= speed * elaps.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (map[(int) floor((player_x_pos) / tile_size)][((int) floor((player_y_pos) / tile_size)) + 1] != 4)
                player_y_pos += speed * elaps.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (map[((int) floor((player_x_pos) / tile_size)) + 1][(int) floor((player_y_pos) / tile_size)] != 4)
                player_x_pos += speed * elaps.asSeconds();
        }
        switch (map[(int) floor((player_x_pos) / tile_size)][(int) floor((player_y_pos) / tile_size)]) {
            case 0:
                speed = 100;
                break;
            case 1:
                speed = 95;
                break;
            case 2:
                speed = 60;
                break;
            case 3:
                speed = 30;
                break;
        }
    }
    return 0;
}