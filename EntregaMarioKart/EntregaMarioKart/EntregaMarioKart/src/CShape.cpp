// ==================== Includes ====================
#include "Component.h"
#include "Window.h"
#include "Texture.h"
#include "TSharedPointer.h"
#include "Prerequisites.h" // Para ShapeType, ComponentType

#include <SFML/Graphics.hpp> // Librería SFML

// ==================== CShape para ChrisEngine ====================
Clase CShape : Component{
    ShapeType m_shapeType
    TSharedPointer<sf::Shape> m_shapePtr

    // --- Constructores ---
    Constructor() :
        Component(ComponentType::SHAPE),
        m_shapeType(ShapeType::EMPTY)
    {
        createShape(ShapeType::CIRCLE) // placeholder
    }

    Constructor(shapeType : ShapeType) :
        Component(ComponentType::SHAPE),
        m_shapeType(ShapeType::EMPTY)
    {
        createShape(shapeType)
    }

    // --- Crear shape según tipo ---
    Método createShape(shapeType : ShapeType) :
        m_shapeType = shapeType
        switch shapeType :
            case ShapeType::CIRCLE:
                m_shapePtr = TSharedPointer::MakeShared<sf::CircleShape>(10.f)
                m_shapePtr.setFillColor(sf::Color::Green)
            case ShapeType::RECTANGLE:
                m_shapePtr = TSharedPointer::MakeShared<sf::RectangleShape>(sf::Vector2f(100.f,50.f))
                m_shapePtr.setFillColor(sf::Color::White)
            case ShapeType::TRIANGLE:
                tri = TSharedPointer::MakeShared<sf::ConvexShape>(3)
                tri.setPoint(0, {0,0}); tri.setPoint(1, {50,100}); tri.setPoint(2, {100,0})
                tri.setFillColor(sf::Color::Blue)
                m_shapePtr = tri
            case ShapeType::POLYGON:
                poly = TSharedPointer::MakeShared<sf::ConvexShape>(5)
                poly.setPoint(0,{0,0}); poly.setPoint(1,{50,100}); poly.setPoint(2,{100,0})
                poly.setPoint(3,{75,-50}); poly.setPoint(4,{-25,-50})
                poly.setFillColor(sf::Color::Red)
                m_shapePtr = poly
            default:
                m_shapePtr.reset()
                    // LOG_ERROR("CShape", "createShape", "Unknown shape type")

        // --- Ciclo de vida ---
        Método start() {}
        Método update(dt : float) {}
        Método destroy() {}

        // --- Render ---
        Método render(window : TSharedPointer<Window>) :
            si
