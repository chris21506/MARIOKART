#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

int main() {
    // Crear ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "ChrisEngine Test");

    // Lista de archivos de personajes
    std::vector<std::string> characters = {
        "princesa.png",
        "sonic.png",
        "virdo.png",
        "wario.png"
    };

    // Vector de sprites
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Texture> textures; // Guardamos texturas para que no se destruyan

    // Cargar textura de la pista
    sf::Texture trackTexture;
    if (!trackTexture.loadFromFile("pista de carreras.png")) return -1;
    sf::Sprite trackSprite(trackTexture);
    trackSprite.setPosition(0.f, 0.f); // Coloca la pista en el origen

    // Cargar personajes
    float startX = 100.f;
    float startY = 100.f;
    for (auto& file : characters) {
        sf::Texture tex;
        if (!tex.loadFromFile(file)) return -1;
        sf::Sprite spr(tex);
        spr.setPosition(startX, startY);
        startY += 100.f; // Separar personajes verticalmente
        textures.push_back(tex);  // Guardar la textura
        sprites.push_back(spr);   // Guardar el sprite
    }

    // Bucle principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // Dibujar pista
        window.draw(trackSprite);

        // Dibujar personajes
        for (auto& spr : sprites)
            window.draw(spr);

        window.display();
    }

    return 0;
}
